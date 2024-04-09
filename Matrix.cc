/**
 * @file Matrix.cc
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
#include "MatrixOperations.hpp"
#include <iomanip>
#include <iostream>
#include <limits>
#include <string.h>
#include <vector>
#include <algorithm>
//////////////////////////////////////////////////////////////////
using std::cin;
using std::cout;
using std::numeric_limits;
using std::string;
using std::vector;
using std::endl;
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

