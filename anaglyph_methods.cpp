#include "anaglyph_methods.h"

using namespace std;

matrixPair getAnaglyphMatrices(string name) {

	struct matrixPair requested_matrix_pair;

	requested_matrix_pair.valid_name = false;

	if (name == "true_analygraph") {
		requested_matrix_pair.valid_name = true;
		requested_matrix_pair.matrix_left 
			<<  0.299, 0.587, 0.114,
				0, 0, 0,
				0, 0, 0;
		requested_matrix_pair.matrix_right
			<<  0, 0, 0,
				0, 0, 0,
				0.299, 0.587, 0.114;


	}
	if (name == "gray_analygraph") {
		requested_matrix_pair.valid_name = true;
		requested_matrix_pair.matrix_left
			<< 0.299, 0.587, 0.114,
			0, 0, 0,
			0, 0, 0;
		requested_matrix_pair.matrix_right
			<< 0, 0, 0,
			0.299, 0.587, 0.114,
			0.299, 0.587, 0.114;


	}

	if (name == "color_analygraph") {
		requested_matrix_pair.valid_name = true;
		requested_matrix_pair.matrix_left
			<<  1,0,0,
				0, 0, 0,
				0, 0, 0;
		requested_matrix_pair.matrix_right
			<<  0, 0, 0,
				0, 1, 0,
				0, 0, 1;


	}
	if (name == "half_color_analygraph") {
		requested_matrix_pair.valid_name = true;
		requested_matrix_pair.matrix_left
			<< 0.299, 0.587, 0.114,
			0, 0, 0,
			0, 0, 0;
		requested_matrix_pair.matrix_right
			<< 0, 0, 0,
			0, 1, 0,
			0, 0, 1;


	}

	if (name == "3dtv_optimized_analygraph") {
		requested_matrix_pair.valid_name = true;
		requested_matrix_pair.matrix_left
			<< 0, 0.7, 0.3,
			0, 0, 0,
			0, 0, 0;
		requested_matrix_pair.matrix_right
			<< 0, 0, 0,
			0, 1, 0,
			0, 0, 1;


	}

	if (name == "dubois_analygraph") {
		requested_matrix_pair.valid_name = true;
		requested_matrix_pair.matrix_left
			<< 0.437,0.449,0.164,
			-0.062,-0.062,-0.024,
			-0.048,-0.050,-0.017;
		requested_matrix_pair.matrix_right
			<< -0.011, -0.032, -0.007,
			0.377, 0.761, 0.009,
			-0.026, -0.093, 1.234;
	}

	if (name == "roscolux_analygraph") {
		requested_matrix_pair.valid_name = true;
		requested_matrix_pair.matrix_left
			<< 0.3185, 0.0769, 0.0109,
			0.1501, 0.0767, 0.0056,
			0.0007, 0.002, 0.0156;
		requested_matrix_pair.matrix_right
			<< 0.0174, 0.0484, 0.1402,
			0.0184, 0.1807, 0.0458,
			0.0286, 0.0991, 0.7662;
	}

	return requested_matrix_pair;
	
	

}