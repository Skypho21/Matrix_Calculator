#ifndef MATRIX_OPERATIONS_HPP
#define MATRIX_OPERATIONS_HPP

#include <vector>

using std::vector;


void displayMatrix(const vector<vector<double>>& matrix);
vector<vector<double>> createMatrix();
vector<vector<double>> scalarMultiply(const vector<vector<double>>& matrix, double scalar);
vector<vector<double>> matrixMultiply(const vector<vector<double>>& a, const vector<vector<double>>& b);
vector<vector<double>> matrixAdd(const vector<vector<double>>& a, const vector<vector<double>>& b);
vector<vector<double>> matrixSubtract(const vector<vector<double>>& a, const vector<vector<double>>& b);
vector<vector<double>> gaussJordanElimination(const vector<vector<double>>& a);
vector<vector<double>> addIdentityMatrix(vector<vector<double>>& a);
vector<vector<double>> inverse(vector<vector<double>>& a);

#endif MATRIX_OPERATIONS_HPP
