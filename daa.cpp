#include <iostream>
using namespace std;

// Helper function to add two matrices
void add(int A[2][2], int B[2][2], int result[2][2]) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
}

// Helper function to subtract two matrices
void subtract(int A[2][2], int B[2][2], int result[2][2]) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            result[i][j] = A[i][j] - B[i][j];
        }
    }
}

// Strassen's matrix multiplication algorithm
void strassen(int A[2][2], int B[2][2], int C[2][2]) {
    int P1, P2, P3, P4, P5, P6, P7;
    
    // Calculate intermediate products
    P1 = (A[0][0] + A[1][1]) * (B[0][0] + B[1][1]);
    P2 = (A[1][0] + A[1][1]) * B[0][0];
    P3 = A[0][0] * (B[0][1] - B[1][1]);
    P4 = A[1][1] * (B[1][0] - B[0][0]);
    P5 = (A[0][0] + A[0][1]) * B[1][1];
    P6 = (A[1][0] - A[0][0]) * (B[0][0] + B[0][1]);
    P7 = (A[0][1] - A[1][1]) * (B[1][0] + B[1][1]);

    // Calculate the final quadrants of the result matrix C
    C[0][0] = P1 + P4 - P5 + P7;
    C[0][1] = P3 + P5;
    C[1][0] = P2 + P4;
    C[1][1] = P1 - P2 + P3 + P6;
}

// Utility function to print a matrix
void printMatrix(int matrix[2][2]) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int A[2][2], B[2][2], C[2][2];

    // Input for matrix A
    cout << "Enter 4 elements for matrix A (2x2):" << endl;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            cin >> A[i][j];
        }
    }

    // Input for matrix B
    cout << "Enter 4 elements for matrix B (2x2):" << endl;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            cin >> B[i][j];
        }
    }

    // Perform Strassen's matrix multiplication
    strassen(A, B, C);

    // Output the result
    cout << "Resultant matrix C (2x2) after multiplication:" << endl;
    printMatrix(C);

    return 0;
}
