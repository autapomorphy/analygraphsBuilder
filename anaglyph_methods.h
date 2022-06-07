#pragma once

#include <Eigen/Dense>
using namespace std;

struct matrixPair {

	Eigen::Matrix3f matrix_left;
	Eigen::Matrix3f matrix_right;
	bool valid_name;
};

matrixPair getAnaglyphMatrices(string name);
