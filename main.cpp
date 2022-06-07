#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <Eigen/Dense>
#include "omp.h"
#include "time.h"

#include "anaglyph_methods.h"


using namespace cv;

int main(int argc, char* argv[])
{
    // arguments: [path to the left image] [path to the right image] [name of method] [path to the output image]
    // or [path to the pair image] [name of method] [path to the output image]
    

    if (argc != 4 && argc != 5) {
        std::cout << "bad arguments" << std::endl;
        std::cout << "Usage: [path to the left image] [path to the right image] [name of method] [path to the output image]" << std::endl;
        std::cout << "or [path to the pair image] [name of method] [path to the output image]" << std::endl;
        return 1;
    }


    //set timer
    clock_t start, end;
    start = clock();

    
    //input images
    Mat img_left;
    Mat img_right;

    //size of output image
    int target_rows, target_cols;

    //name of 
    std::string method_name;
    std::string output_name;



    std::cout << "Reading images ..." << std::endl;

    if (argc == 5) {
        //two input files
        Mat img_left_raw = imread(argv[1], IMREAD_COLOR);
        if (img_left_raw.empty()) {
            std::cout << "could not read the image: " << argv[1] << std::endl;
            return 1;
        }
        Mat img_right_raw = imread(argv[2], IMREAD_COLOR);
        if (img_right_raw.empty()) {
            std::cout << "could not read the image: " << argv[2] << std::endl;
            return 1;
        }

        target_rows = img_right_raw.rows > img_left_raw.rows ? img_left_raw.rows : img_right_raw.rows;
        target_cols = img_right_raw.cols > img_left_raw.cols ? img_left_raw.cols : img_right_raw.cols;

        Rect crop_rect = Rect(0, 0, target_cols, target_rows);
        img_left = img_left_raw(crop_rect);
        img_right = img_right_raw(crop_rect);

        method_name.assign(argv[3]);
        output_name.assign(argv[4]);

    }
    else {
        //one input file
        Mat img_pair_raw = imread(argv[1], IMREAD_COLOR);
        if (img_pair_raw.empty()) {
            std::cout << "could not read the image: " << argv[1] << std::endl;
            return 1;
        }
        if (img_pair_raw.cols % 2 != 0) {
            std::cout << "Could not cut the pair image into two equal parts: " << argv[1] << std::endl;
        }
        //split it into pair
        target_rows = img_pair_raw.rows;
        target_cols = img_pair_raw.cols/2;
        img_left = img_pair_raw(Rect(0, 0, target_cols, target_rows));
        img_right = img_pair_raw(Rect(target_cols, 0, target_cols, target_rows));

        method_name.assign(argv[2]);
        output_name.assign(argv[3]);

    }
    
    //get the matrices for anaglyph compuation
    matrixPair anaglyph_matrices = getAnaglyphMatrices(method_name);

    if (anaglyph_matrices.valid_name == false) {

        std::cout << "Unknown Anaglyph Method Name: " << method_name <<std::endl;
        std::cout << "Supported methods: true_analygraph, gray_analygraph, color_analygraph, half_color_analygraph, 3dtv_optimized_analygraph, dubois_analygraph, roscolux_analygraph" << std::endl;
        return 1;
    }


    Mat output_image(target_rows, target_cols, img_left.type());

    //cv:Mat format: a y*x matrix of vector <B,G,R>
    //in memory: [B,G,R,B,G,R,B,G,R.....]

        
    //multi-thread setting: omp loop over each pixels

    int num_pixel = target_rows * target_cols;
#pragma omp parallel for num_threads(8)
    for (int i = 0; i < num_pixel; i++) {

        //position of the pixel
        int y = i / target_cols;
        int x = i % target_cols;
        
        //opencv matrix(BGR) to eigen vector(RGB)
        Vec3b pixel_vector_left = img_left.at<Vec3b>(y, x);
        Vec3b pixel_vector_right = img_right.at<Vec3b>(y, x);
        Eigen::Vector3i eigen_pixel_vector_left;
        Eigen::Vector3i eigen_pixel_vector_right;
        Eigen::Vector3f analygraph_pixel_RGB;

        
        eigen_pixel_vector_left = { pixel_vector_left[2],pixel_vector_left[1],pixel_vector_left[0] };
        eigen_pixel_vector_right = { pixel_vector_right[2],pixel_vector_right[1],pixel_vector_right[0] };

        //compute analygraph pixel
        analygraph_pixel_RGB = (anaglyph_matrices.matrix_left * eigen_pixel_vector_left.cast <float>() + anaglyph_matrices.matrix_right * eigen_pixel_vector_right.cast <float>());
        
        output_image.at<Vec3b>(y, x) << analygraph_pixel_RGB[2], analygraph_pixel_RGB[1], analygraph_pixel_RGB[0];
    }

    imwrite(output_name, output_image);

    std::cout << "Anaglyph images generated: " << output_name <<std::endl;

    end = clock();
    std::cout << "time consuming: " << (end - start) << " ms" << std::endl;

    return 0;
}