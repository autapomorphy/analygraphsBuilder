# analygraphsBuilder

An analygraph image builder, generate analygraph images from image stereo pairs.
Developed with Visual Studio 2022

## Requirements

- Eigen
- OpenCV
- OpenMP

## Usage

analygraphsBuilder.exe [path to the left image] [path to the right image] [name of method] [path to the output image]

analygraphsBuilder.exe [path to the pair image] [name of method] [path to the output image]

## Supported methods

true_analygraph

gray_analygraph

color_analygraph

half_color_analygraph

dubois_analygraph

roscolux_analygraph

## Examples

Method: dubois_analyraph

input:
![input file:](https://github.com/autapomorphy/analygraphsBuilder/blob/master/sample_image/Kasuga_Lantern_pair.jpeg)

output:
![output file:](https://github.com/autapomorphy/analygraphsBuilder/blob/master/sample_image/output_full.jpg)
