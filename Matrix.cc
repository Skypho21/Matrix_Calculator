/**
 * @file matrixCalculator.cc
 * @brief Matrix Calculator for basic matrix operations
 * 
 * This calculator performs various matrix operations such as:
 * - Addition
 * - Subtraction
 * - Scalar Multiplication
 * - Matrix Multiplication
 * - Matrix Inversion
 * - Gaussian Elimination
 * 
 * @authors Ganga Acharya, Adam Glick-Lynch, Sovannary Sok, Skyfa Inthavong
 */

#include <iomanip>
#include <iostream>
#include <limits>
#include <string.h>
#include <vector>
#include <algorithm>
//////////////////////////////////////////////////////////////////
using std::cin;
using std::cout;
using std::max;
using std::numeric_limits;
using std::setprecision;
using std::setw;
using std::streamsize;
using std::string;
using std::vector;
using std::endl;
//////////////////////////////////////////////////////////////////
vector<vector<double>>
createMatrix ();

void
displayMatrix (const vector<vector<double>>& matrix);

vector<vector<double>>
scalarMultiply (vector<vector<double>>& input, double scalar);

vector<vector<double>>
matrixMultiply (vector<vector<double>>& a, vector<vector<double>>& b);

vector<vector<double>>
matrixAdd (const vector<vector<double>>& a, const vector<vector<double>>& b);

vector<vector<double>>
matrixSubtract (const vector<vector<double>>& a,
                const vector<vector<double>>& b);

vector<vector<double>>
gaussJordanElimination (const vector<vector<double>>& a);

vector<vector<double>> 
addIdentityMatrix(vector<vector<double>>& a);

vector<vector<double>> 
inverse(vector<vector<double>>& a);

//////////////////////////////////////////////////////////////////
/**
 * Entry point of the application.
 */
int
main ()
{
    std::vector<std::vector<std::vector<double>>> allMatrices;
    char userInput;

    cout << "Welcome to our Matrix Calculator!\n";
    cout << "Start by creating the matrices.\n\n";
    
    // Main loop
    while (true)
    {
        cout << "Press 'c' to enter matrices, 'd' to perform operations, or 'e' to "
                "exit: ";
        cin >> userInput;
        // add a check to validate user input
        cout << "\n";

        switch (userInput)
        {
            case 'c':
            case 'C': {
                allMatrices.push_back (createMatrix ());
                break;
            }
            case 'd':
            case 'D': {
                if (allMatrices.empty ())
                {
                    cout << "Must create matrices first!\n";
                    break;
                }
                //If done, user enters D
                //and we can call functions here to operate
                //on vectors within allMatrices
                cout << "Entered Matrices:" << "\n";
                for (double i = 0; i < allMatrices.size (); ++i)
                {
                    cout << "Matrix " << i + 1 << ":\n";
                    displayMatrix (allMatrices[i]);
                }
                cout << "\n";

                cout << "What operation would you like to perform?\n"
                    << "x - scalar multiply\n"
                    << "i - matrix inverse\n"
                    << "a - matrix addition\n"
                    << "s - matrix subtraction\n"
                    << "m - matrix multiplication\n"
                    << "g - Gauss_Jordan elimination\n\n" ;
                char operation;
                cin >> operation;

                int matrixIndex, matrix1Index, matrix2Index;
                double scalar;
                vector<vector<double>> result;

                try {
                    switch (operation) {
                        case 'x':
                            cout << "Select the matrix to perform a scalar multiply on (e.g., '1'): ";
                            cin >> matrixIndex;
                            cout << "\nEnter a number to multiply by: ";
                            cin >> scalar;
                            // add check for incorrect input
                            result = scalarMultiply(allMatrices[matrixIndex - 1], scalar);
                            displayMatrix(result);
                            break;
                        case 'a':
                            cout << "Select the matrices to perform addition on (e.g., '1 2'): ";
                            cin >> matrix1Index >> matrix2Index;
                            // add check for incorrect input
                            result = matrixAdd(allMatrices[matrix1Index - 1], allMatrices[matrix2Index - 1]);
                            cout << "Result of addition:\n\n";
                            displayMatrix(result);
                            break;
                        case 's':
                            cout << "Select the matrices to perform a subtraction on (e.g., '1 2'): ";
                            cin >> matrix1Index >> matrix2Index;
                            // add check for incorrect input
                            result = matrixSubtract(allMatrices[matrix1Index - 1], allMatrices[matrix2Index - 1]);
                            cout << "Result of subtraction:\n\n";
                            displayMatrix(result);
                            break;
                        case 'm':
                            cout << "Select the matrices to perform a matrix multiply on (e.g., '1 2'): ";
                            cin >> matrix1Index >> matrix2Index;
                            // add check for incorrect input
                            result = matrixMultiply(allMatrices[matrix1Index - 1], allMatrices[matrix2Index - 1]);
                            cout << "Result of multiplication:\n\n";
                            displayMatrix(result);
                            break;
                        case 'g':
                            cout << "Select the matrix for Gauss-Jordan elimination (e.g., '1'): ";
                            cin >> matrixIndex;
                            // add check for incorrect input
                            result = gaussJordanElimination(allMatrices[matrixIndex - 1]);
                            cout << "Result of Gauss-Jordan Elimination:\n\n";
                            displayMatrix(result);
                            break;
                        case 'i':
                            cout << "Select the matrix for inverse (e.g., '1'): ";
                            cin >> matrixIndex;
                            // add check for incorrect input
                            result = inverse(allMatrices[matrixIndex - 1]);
                            cout << "Result of Inverse:\n\n";
                            displayMatrix(result);
                            break;
                        default:
                            cout << "Invalid operation!\n";
                    }
                    break;
                } catch (const std::invalid_argument& e){
                    //catch and handle the exception
                    cout << "An error occured: " << e.what() << endl;
                }
            }
            case 'e':
            case 'E':
                return 0;
            default:
                cout << "Invalid input. Please try again." << "\n";
        }
    }
}

// Create a mxn matrix, then prompts for input in positions.
vector<vector<double>>
createMatrix ()
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
            cin.clear ();
            cin.ignore (numeric_limits<streamsize>::max (), '\n');
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
        cout << "Invalid input for the number of columns. Please enter a valid "
                "positive integer.\n";
        cin.clear ();
        cin.ignore (numeric_limits<streamsize>::max (), '\n');
        }
        else
        {
        break;
        }
    }
    cout << "\n";

    matrix.resize (rows, vector<double> (cols));

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
            cout << "Invalid input for matrix element. Please enter a valid "
                    "number.\n";
            cin.clear ();
            cin.ignore (numeric_limits<streamsize>::max (), '\n');
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

// Displays a matrix.
void
displayMatrix (const vector<vector<double>>& matrix)
{
    for (auto row = 0; row < matrix.size (); row++)
    {
        for (auto col = 0; col < matrix[0].size (); col++)
        {
        cout << setw (5) << setprecision (5) << matrix[row][col] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

// Function to multiply a matrix by a scalar
vector<vector<double>>
scalarMultiply (vector<vector<double>>& matrix, double scalar)
{
    vector<vector<double>> result;

    for (int i = 0; i < matrix.size (); i++)
    {
        vector<double> row;

        for (int j = 0; j < matrix[i].size (); j++)
        {
        // multiply each element by the scalar value
        int element = matrix[i][j] * scalar;
        row.push_back (element);
        }
        result.push_back (row);
    }
    return result;
}

// Implementation of the dot product rule to fill the result matrix
// by the given row multiplied by the given column.
vector<vector<double>>
matrixMultiply (vector<vector<double>>& a, vector<vector<double>>& b)
{

     // Check if dimensions of both matrices have same mxn by mxn
     // if a[0].size() != b.size()
    if (a[0].size() != b.size()) {
        //throw an excpetion for dimension mismatch
        throw std::invalid_argument("Matrices do not have compatible dimensions, cannot multiply.\n");
    }
    // Create vector of appropriate rows/cols
    double rows = a.size ();
    double cols = b[0].size ();
    vector<vector<double>> res (rows, vector<double> (cols));

    // Iterate through each location in result matrix
    for (double row = 0; row < rows; ++row)
    {
        for (double col = 0; col < cols; ++col)
        {
        double sum = 0.0;
        // Multiply given row with given col, element by element
        for (double i = 0; i < a[row].size (); ++i)
        {
            sum += a[row][i] * b[i][col];
        }
        res[row][col] = sum;
        }
    }
    return res;
}

// Function to add two matrices.
vector<vector<double>>
matrixAdd (const vector<vector<double>>& a, const vector<vector<double>>& b)
{
    // Check if dimensions of both matrices are the same
    if (a.size() != b.size() || (a.size() > 0 && a[0].size() != b[0].size())) {
        //throw an excpetion for dimension mismatch
        throw std::invalid_argument("Matrices have different dimensions and cannot be added");
    }

    // get the number of rows from matrix 'a'
    double rows = a.size ();
    // get the number of columns from matrix 'a'
    double cols = a[0].size ();
    // create a result matrix with the same number of rows and columns as 'a'
    vector<vector<double>> result (rows, vector<double> (cols));

    // iterate though each element of the matrices and add corresponding elements
    for (double row = 0; row < rows; ++row)
    {
        for (double col = 0; col < cols; ++col)
        {
            result[row][col] = a[row][col] + b[row][col];
        }
    }
    return result;
}

// Function to subtract matrix b from matrix a.
vector<vector<double>>
matrixSubtract (const vector<vector<double>>& a, const vector<vector<double>>& b)
{
    // Check if dimensions of both matrices are the same
    if (a.size() != b.size() || (a.size() > 0 && a[0].size() != b[0].size())) {
        //throw an excpetion for dimension mismatch
        throw std::invalid_argument("Matrices have different dimensions and cannot be added");
    }

    // get the number of rows from matrix 'a'
    double rows = a.size ();
    // get the number of columns from matrix 'a'
    double cols = a[0].size ();
    // create a result matrix with the same number of rows and columns as 'a'
    vector<vector<double>> result (rows, vector<double> (cols));

    // iterate though each element of the matrices and substract corresponding of b from a
    for (double row = 0; row < rows; ++row)
    {
        for (double col = 0; col < cols; ++col)
        {
            result[row][col] = a[row][col] - b[row][col];
        }
    }
    return result;
}

vector<vector<double>> 
gaussJordanElimination(const vector<vector<double>>& input) {
    vector<vector<double>> a = input;  // Creating a mutable copy of the input matrix
    int rows = a.size();
    int cols = a[0].size();

    for (int col = 0, row = 0; col < cols && row < rows; ++col) {
        // Search for the maximum element in the current column
        int maxRow = row;
        for (int i = row + 1; i < rows; i++) {
            if (abs(a[i][col]) > abs(a[maxRow][col])) {
                maxRow = i;
            }
        }

        if (a[maxRow][col] == 0) {
            // Skip this column if no non-zero element is found
            continue;
        }

        // Swap the row with the maximum element with the current row
        swap(a[maxRow], a[row]);

        // Make the element in the current column and row equal to 1
        // and the rest of the column elements equal to 0
        for (int i = 0; i < rows; i++) {
            if (i != row) {
                double divider = a[i][col] / a[row][col];
                for (int j = col; j < cols; j++) {
                    a[i][j] -= a[row][j] * divider;
                }
            }
        }

        // Normalize the current row
        float divider = a[row][col];
        for (int j = col; j < cols; j++) {
            a[row][j] /= divider;
        }
        row++;
    }
    return a;
}


// Function that is a helper to calculate matrix Inverse by 
// setting the identity matrix.
vector<vector<double>> 
addIdentityMatrix(vector<vector<double>>& a) {
    int n = a.size();
    vector<vector<double>> res(n, vector<double>(n * 2, 0));

    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            res[row][col] = a[row][col];
        }
        res[row][n + row] = 1;  // Directly setting the identity matrix part
    }
    return res;
}

// Function that calculates a Matrix inverse.
vector<vector<double>> 
inverse(vector<vector<double>>& a) {
    if (a.size() != a[0].size()) {
        throw std::invalid_argument("Matrix must be square to find its inverse.");
    }

    vector<vector<double>> temp = addIdentityMatrix(a);
    temp = gaussJordanElimination(temp);

    // Check for a row of zeros in the left half (the original matrix part)
    for (const auto& row : temp) {
        if (std::all_of(row.begin(), row.begin() + a.size(), [](double val) { return val == 0; })) {
            throw std::invalid_argument("Matrix is singular and not invertible.");
        }
    }

    // Extract the right half of the matrix (the inverse part)
    vector<vector<double>> res(a.size(), vector<double>(a.size()));
    for (int row = 0; row < a.size(); row++) {
        std::copy(temp[row].begin() + a.size(), temp[row].end(), res[row].begin());
    }
    return res;
}
