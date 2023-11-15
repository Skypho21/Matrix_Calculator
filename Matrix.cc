/**
  Filename   : matrixCalculator.cc
  Authors    : Ganga Acharya, Adam Glick-Lynch, Sovannary Sok, Skyfa inthavong
  Description: A calculator which can do matrix algebra including:
               addition
               subtraction
               scalar multiplication
               matrix multiplication
               inverting a matrix
*/

#include <iostream>
#include <iostream>
#include <vector>
#include <string.h>
#include <iomanip>
#include <limits>
//////////////////////////////////////////////////////////////////
using std::vector;
using std::cout;
using std::cin;
using std::string;
using std::setprecision;
using std::setw;
using std::numeric_limits;
using std::streamsize;
using std::max;
//////////////////////////////////////////////////////////////////
vector<vector<double>> createMatrix() 
{
    vector<vector<double>> matrix;
    int rows, cols;

    // Validation loop for the number of rows
    while (true) 
    {
        cout << "Enter the number of rows: ";
        if (!(cin >> rows) || rows <= 0) 
        {
            cout << "Invalid input for the number of rows. Please enter a valid positive integer.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } 
        else 
        {
            break;
        }
    }

    // Validation loop for the number of columns
    while (true) 
    {
        cout << "Enter the number of columns: ";
        if (!(cin >> cols) || cols <= 0)
        {
            cout << "Invalid input for the number of columns. Please enter a valid positive integer.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } 
        else 
        {
            break;
        }
    }
    cout << "\n";

    matrix.resize(rows, vector<double>(cols));

    cout << "Entering Matrix elements...\n";

    for (int i = 0; i < rows; ++i) 
    {
        for (int j = 0; j < cols; ++j) 
        {
            while (true) 
            {
                cout << "row " << i + 1 << " column " << j + 1 << ": ";
                if (!(cin >> matrix[i][j])) 
                {
                    cout << "Invalid input for matrix element. Please enter a valid number.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                } 
                else 
                {
                    break;
                }
            }
        }
    }
    return matrix;
}

void 
displayMatrix(const vector<vector<double>>& matrix) 
{
   for (auto row = 0; row < matrix.size(); row++)
    {
        for (auto col = 0; col < matrix[0].size(); col++)
        {
            cout << setw(5) << setprecision(5) << matrix[row][col] << " ";
        }
        cout << "\n";
    }
}

vector<vector<double>> scalarMultiply(vector<vector<double>>& input, double scalar)
{
    vector<vector<double>> result;

    for (int i = 0; i < input.size(); i++)
    {
        vector<double> row;

        for (int j = 0; j < input[i].size(); j++)
        {
            // multiply each element by the scalar value
            int element = input[i][j] * scalar;
            row.push_back(element);
        }
        result.push_back(row);
    }
    return result;
}

/* Implementation of the dot product rule to fill the result matrix 
 by the given row multiplied by the given column*/
vector<vector<double>> 
matrixMultiply(vector<vector<double>> &a, vector<vector<double>> &b)
{
    // Create vector of appropriate rows/cols
    double rows = a.size();
    double cols = b[0].size();
    vector<vector<double>> res(rows, vector<double>(cols));

    // Iterate through each location in result matrix
    for (double row = 0; row < rows; ++row)
    {
        for (double col = 0; col < cols; ++col)
        {
            double sum = 0.0;
            // Multiply given row with given col, element by element
            for (double i = 0; i < a[row].size(); ++i)
            {
                sum += a[row][i] * b[i][col];
            }
            res[row][col] = sum;
        }
    }
    return res;
}

// fucntion to add two matrices
vector<vector<double>> 
matrixAdd(const vector<vector<double>>& a, const vector<vector<double>> & b)
{
    // get the number of rows from matrix 'a'
    double rows = a.size();
    // get the number of columns from matrix 'a'    
    double cols = a[0].size(); 
    // create a result matrix with the same number of rows and columns as 'a'
    vector<vector<double>> result (rows, vector<double>(cols));

    // iterate though each element of the matrices and add corresponding elements
    for(double row = 0; row < rows; ++row)
    {
        for(double col = 0; col < cols; ++col)
        {
            result[row][col] = a[row][col] + b[row][col];
        }
    }
    return result;
}

// function to subtract matrix b from matrix a
vector<vector<double>> 
matrixSubtract(const vector<vector<double>>& a, const vector<vector<double>> & b)
{
    // get the number of rows from matrix 'a'
    double rows = a.size();
    // get the number of columns from matrix 'a'    
    double cols = a[0].size(); 
    // create a result matrix with the same number of rows and columns as 'a'
    vector<vector<double>> result (rows, vector<double>(cols));

    // iterate though each element of the matrices and substract corresponding of b from a
    for(double row = 0; row < rows; ++row)
    {
        for(double col = 0; col < cols; ++col)
        {
            result[row][col] = a[row][col] - b[row][col];
        }
    }
    return result;
}

// Calculates the determinant of a matrix.
double determinant(vector<vector<double>>& matrix) 
{
    size_t n = matrix.size();
    if (n == 1) 
    {
        return matrix[0][0];
    } else if (n == 2) 
    {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];

    } 
    else if (n == 3) 
    {
        return matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) -
               matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]) +
               matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);
    }
    return 0;
}

// Calculates the adjoint of an nxn matrix.
// Loops through each element of the matrix, computes the corresponding minor, and calculates its determinant.
// Calculates the sign of the elements of the adjoint matrix based on the minor determinants.
// Builds the adjoint matrix by transposing the matrix of minors and applying the sign determined.
void adjoint(const vector<vector<double>>& matrix, vector<vector<double>>& adj) 
{
    size_t n = matrix.size();
    for (size_t i = 0; i < n; ++i) 
    {
        for (size_t j = 0; j < n; ++j) 
        {
            int sign = ((i + j) % 2 == 0) ? 1 : -1;
            vector<vector<double>> minor(n - 1, vector<double>(n - 1));
            size_t x = 0, y = 0;
            for (size_t row = 0; row < n; ++row) 
            {
                if (row == i) continue;
                for (size_t col = 0; col < n; ++col) 
                {
                    if (col == j) continue;
                    minor[x][y] = matrix[row][col];
                    y++;
                }
                x++;
                y = 0;
            }
            adj[j][i] = sign * determinant(minor);
        }
    }
}

// Checks if the matrix is of size 3x3 or smaller. For matrices of size up to 3x3, it calculates the inverse using the adjoint and determinant.
// Returns false and a message if the matrix is singular or larger than 3x3.
// Computes the inverse by dividing the adjoint by the determinant for matrices within the supported size.

bool inverse(const vector<vector<double>>& matrix, vector<vector<double>>& inv) 
{
    size_t n = matrix.size();
    double det = determinant(const_cast<vector<vector<double>>&>(matrix));

    if (n <= 3) 
    {
        if (std::abs(det) < 1e-6) 
        {
            cout << "Matrix is singular, inverse does not exist.\n";
            return false;
        }

        vector<vector<double>> adj(n, vector<double>(n));
        adjoint(matrix, adj);

        for (size_t i = 0; i < n; ++i) 
        {
            for (size_t j = 0; j < n; ++j) 
            {
                inv[i][j] = adj[i][j] / det;
            }
        }
        return true;
    } 
    else 
    {
        cout << "Matrix size exceeds 3x3. Inversion is not supported for matrices larger than 3x3.\n";
        return false;
    }
}
//////////////////////////////////////////////////////////////////
int
main() 
{
   std::vector<std::vector<std::vector<double>>> allMatrices;
    char userInput;

    cout << "Welcome to our Matrix Calculator!\n";
    cout << "Start by creating the matrices.\n\n";

    while (true) 
    {
        cout << "Press 'c' to enter matrices, 'd' to perform operations, or 'e' to exit: ";
        cin >> userInput;
        cout << "\n";

        switch (userInput) 
        {
            case 'c':
            case 'C':
                allMatrices.push_back(createMatrix());
                break;
            case 'd':
            case 'D':

                if (allMatrices.empty())
                {
                    cout << "Must create matrices first!\n";
                    break;
                }
                //If done, user enters D 
                //and we can call functions here to operate
                //on vectors within allMatrices
                cout << "Entered Matrices:" << "\n";
                for (double i = 0; i < allMatrices.size(); ++i) 
                {
                    cout << "Matrix " << i + 1 << ":\n";
                    displayMatrix(allMatrices[i]);
                }
                cout << "\n";


                cout << "What operation would you like to perform?\n"
                    << "x - scalar multiply\n"
                    << "i - matrix inverse\n"
                    << "a - matrix addition\n"
                    << "s - matrix subtraction\n"
                    << "m - matrix multiplication\n\n";
                    char operation;
                    cin >> operation;

                    int matrixIndex;
                    int matrix1Index, matrix2Index;
                    switch (operation) 
                    {
                        case 'x':
                            cout << "Select the matrix to perform an operation on (e.g., '1'): ";
                           
                            cin >> matrixIndex;
                            cout << "\n";

                            if (matrixIndex <= allMatrices.size()) 
                            {
                                cout << "Enter a number to multiply by: ";
                                int scalar;
                                cin >> scalar;
                                cout << "\n";
                                vector<vector<double>> scalarMatrix = scalarMultiply(allMatrices[matrixIndex-1], scalar);
                                displayMatrix(scalarMatrix);
                            }
                        break;
                        case 'i':

                            cout << "Select the matrix to perform an operation on (e.g., '1'): ";
                            cin >> matrixIndex;
                            cout << "\n";

                            if (matrixIndex <= allMatrices.size()) 
                            {
                                if (allMatrices[matrixIndex - 1].size() <= 3 &&
                                    allMatrices[matrixIndex - 1][0].size() <= 3) 
                                {
                                    vector<vector<double>> inverseMatrix(allMatrices[matrixIndex - 1].size(),
                                                                        vector<double>(allMatrices[matrixIndex - 1][0].size()));

                                    if (inverse(allMatrices[matrixIndex - 1], inverseMatrix)) 
                                    {
                                        cout << "Inverse of the matrix:\n";
                                        displayMatrix(inverseMatrix);
                                    }
                                } 
                                else 
                                {
                                    cout << "Matrix dimensions exceed 3x3. Operations not supported for matrices larger than 3x3.\n";
                                }
                            }

                        break;
                        case 'a':

                            cout << "Select the matrices to perform an operation on (e.g., '1 2'): ";
                            cin >> matrix1Index >> matrix2Index;
                            cout << "\n";
                             // Ensures user enters valid indices
                            if (!(matrix1Index <= allMatrices.size() && matrix2Index <= allMatrices.size())) 
                            {
                                cout << "invalid indices!";
                                break;
                            }

                            // Ensures matrices are compatible dimensions
                            if (allMatrices[matrix1Index - 1].size() == allMatrices[matrix2Index - 1].size() &&
                                allMatrices[matrix1Index - 1][0].size() == allMatrices[matrix2Index - 1][0].size()) 
                            {
                                 vector<vector<double>> result = matrixAdd(allMatrices[matrix1Index - 1],
                                                                       allMatrices[matrix2Index - 1]);
                                cout << "Result of addition:\n";
                                displayMatrix(result);
                            } 
                            else 
                            {
                                cout << "Matrices are not of the same size for addition!\n";
                            }
                            break;
                        case 's':
                            
                            cout << "Select the matrices to perform an operation on (e.g., '1 2'): ";
                            cin >> matrix1Index >> matrix2Index;
                            cout << "\n";
                             // Ensures user enters valid indices
                            if (!(matrix1Index <= allMatrices.size() && matrix2Index <= allMatrices.size())) 
                            {
                                cout << "invalid indices!";
                                break;
                            }

                            if (allMatrices[matrix1Index - 1].size() == allMatrices[matrix2Index - 1].size() &&
                                allMatrices[matrix1Index - 1][0].size() == allMatrices[matrix2Index - 1][0].size()) 
                            {
                                vector<vector<double>> result = matrixSubtract(allMatrices[matrix1Index - 1],
                                                                           allMatrices[matrix2Index - 1]);
                                cout << "Result of subtraction:\n";
                                displayMatrix(result);
                            } 
                            else 
                            {
                                cout << "Matrices are not of the same size for subtraction!\n";
                            }
                            break;
                        
                        case 'm':

                            cout << "Select the matrices to perform an operation on (e.g., '1 2'): ";
                            cin >> matrix1Index >> matrix2Index;
                            cout << "\n";

                            if (!(matrix1Index <= allMatrices.size() && matrix2Index <= allMatrices.size())) 
                            {
                                cout << "invalid indices!";
                                break;
                            }

                            if (allMatrices[matrix1Index - 1][0].size() == allMatrices[matrix2Index - 1].size()) 
                            {
                                vector<vector<double>> result = matrixMultiply(allMatrices[matrix1Index - 1],
                                                                           allMatrices[matrix2Index - 1]);
                                cout << "Result of multiplication:\n";
                                displayMatrix(result);
                            } 
                            else 
                            {
                                cout << "Matrix dimensions are incompatible for multiplication!\n";
                            }
                            break;
                        default:
                            cout << "Invalid operation!\n";
                    }
                break;
            case 'e':
            case 'E':
                return 0;
            default:
                cout << "Invalid input. Please try again." << "\n";
        }
    }
}
