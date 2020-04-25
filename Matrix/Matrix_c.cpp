#include <iostream>
#include <cmath>
#include "Matrix.h";

using namespace std;

/* Default Constructor */
Matrix::Matrix() {
	size1 = rand() % 128 + 1;
	size2 = rand() % 128 + 1;
	BuildMatrix();
}

/* Copy Consrucor */
Matrix::Matrix(Matrix const& x) { 
	size1 = x.size1;
	size2 = x.size2;
	copyMatrix(x.matrix);
}

/* Default Desructor */
Matrix::~Matrix() {
	//Free each sub-array
	for (int i = 0; i < size1; ++i) {
		delete[] matrix[i];
	}
	//Free the array of pointers
	delete[] matrix;
}


/* Constructor with size Parameter*/
Matrix::Matrix(int x, int y, int v) {
	if (x < 0) {
		size1 = 1024;
	} else {
		size1 = x;
	}

	if (y < 0) {
		size2 = 1024;
	} else {
		size2 = y;
	}
	
	if (v == 0) {
		BuildEmptyMatrix();
	} else {
		BuildMatrix();
	}
}

/* Mulitiplication operator overloading */
Matrix operator*(Matrix const& matr1, Matrix const& matr2) {
	Matrix res;
	return res.Classic(matr1,matr2);
}

/* Addition operator overloading*/
Matrix operator+(Matrix const& matr1, Matrix const& matr2) {
	Matrix res;
	return res.Add(matr1,matr2);
}

/* Subtraction operator overloading */
Matrix operator-(Matrix const& matr1, Matrix const& matr2) {
	Matrix res;
	return res.Subtract(matr1, matr2);
}

/* This method finds the half value to determine padding size for zeros */
int Matrix::half2k(int x) {
	double l = log2(x);
	int k = int(l);
	if (l - k > 0) {
		return (pow(2.0, k));
	} else {
		return x / 2;
	}
}

/* Joins Matrix after splitting */
Matrix Matrix::Join(Matrix const& A, Matrix const& B, Matrix const& C, Matrix const& D) {
	Matrix res(A.size1 + B.size1, A.size2 + C.size2, 0);
	
	for (int i = 0; i < A.size1; i++) {
		for (int j = 0; j < A.size2; j++) {
			res.matrix[i][j] = A.matrix[i][j];
		}
	}

	for (int i = 0; i < B.size1; i++) {
		for (int j = 0; j < B.size2; j++) {
			res.matrix[i][j + B.size2] = B.matrix[i][j];
		}
	}

	for (int i = 0; i < C.size1; i++) {
		for (int j = 0; j < C.size1; j++) {
			res.matrix[i + C.size1][j] = C.matrix[i][j];
		}
	}

	for (int i = 0; i < D.size1; i++) {
		for (int j = 0; j < D.size2; j++) {
			res.matrix[i + D.size1][j + D.size2] = D.matrix[i][j];
		}
	}

	return res;
}

/* Returns 1st Quadrant of a matrix*/
Matrix Matrix::Q1(Matrix const& x) {
	Matrix res(half2k(x.size1), half2k(x.size2), 0);
	for (int i = 0; i < res.size1; i++) {
		for (int j = 0; j < res.size2; j++) {
			res.matrix[i][j] = x.matrix[i][j];
		}
	}
	return res;
}

/* Returns 2nd Quadrant of a matrix*/
Matrix Matrix::Q2(Matrix const& x) {
	Matrix res(half2k(x.size1), half2k(x.size2), 0);
	for (int i = 0; i < res.size1; i++) {
		for (int j = res.size2, k = 0; j < x.size2; j++, k++) {
			res.matrix[i][k] = x.matrix[i][j];
		}
	}
	return res;
}

/* Returns 3rd Quadrant of a matrix*/
Matrix Matrix::Q3(Matrix const& x) {
	Matrix res(half2k(x.size1), half2k(x.size2), 0);
	for (int i = res.size1, k = 0; i < x.size1; i++, k++) {
		for (int j = 0; j < res.size2; j++) {
			res.matrix[k][j] = x.matrix[i][j];
		}
	}
	return res;
}

/* Returns 4th Quadrant of a matrix*/
Matrix Matrix::Q4(Matrix const& x) {
	Matrix res(half2k(x.size1), half2k(x.size2), 0);
	for (int i = res.size1, k = 0; i < x.size1; i++, k++) {
		for (int j = res.size2, s = 0; j < x.size2; j++, s++) {
			res.matrix[k][s] = x.matrix[i][j];
		}
	}
	return res;
}

/* Builds Matrix given set size inputs */
void Matrix::BuildMatrix() {
	matrix = new int* [size1];
	for (int i = 0; i < size1; ++i) {
		matrix[i] = new int[size2];
		for (int j = 0; j < size2; j++) {
			matrix[i][j] = rand() % 10;
		}
	}
}

/* Builds Matrix given set size inputs, Fils with zero */
void Matrix::BuildEmptyMatrix() {
	matrix = new int* [size1];
	for (int i = 0; i < size1; ++i) {
		matrix[i] = new int[size2];
		for (int j = 0; j < size2; j++) {
			matrix[i][j] = 0;
		}
	}
}

/* Copies array to new instance */
void Matrix::copyMatrix(int** arr) {
	matrix = new int* [size1];
	for (int i = 0; i < size1; i++) {
		matrix[i] = new int[size2];
		for (int j = 0; j < size2; j++) {
			matrix[i][j] = arr[i][j];
		}
	}
}

/* Displays Matrix in appropriate format */
void Matrix::Display() {
	for (int i = 0; i < size1; i++) {
		for (int j = 0; j < size2; j++) {
			if (j == 0) {
				cout << "|";
				if (matrix[i][j] < 10) std::cout << "0" << matrix[i][j] << " ";
				else cout << matrix[i][j] << " ";
				if (j + 1 == size2) cout << "|" << endl;
			} else {
				if (matrix[i][j] < 10) std::cout << "0" << matrix[i][j] << " ";
				else cout << matrix[i][j] << " ";
				if (j + 1 == size2) cout << "|" << endl;
			}
		}
	}
	cout << endl;
}

/* Adds 2 Matrices */
Matrix Matrix::Add(Matrix const& x, Matrix const& y) {
	Matrix matr(x.size1, y.size2, 0);
	if (x.size1 == y.size1 && x.size2 == y.size2) {
		for (int i = 0; i < x.size1; i++) {
			for (int j = 0; j < x.size2; j++) {
				matr.matrix[i][j] = x.matrix[i][j] + y.matrix[i][j];
			}
		}
		return matr;
	} else {
		cout << "Cannot Add these 2 Matrices" << endl;
		return Matrix(0,0);
	}
}

/* Subtract 2 Matrices */
Matrix Matrix::Subtract(Matrix const& x, Matrix const& y) {
	Matrix matr(x.size1, y.size2, 0);
	if (x.size1 == y.size1 && x.size2 == y.size2) {
		for (int i = 0; i < x.size1; i++) {
			for (int j = 0; j < x.size2; j++) {
				matr.matrix[i][j] = x.matrix[i][j] - y.matrix[i][j];
			}
		}
		return matr;
	} else {
		cout << "Cannot Subtract these 2 Matrices" << endl;
		return Matrix(0,0);
	}
}

/* Multiplies 2 Matrices using the Traditional Method*/
Matrix Matrix::Classic(Matrix const &x, Matrix const &y) {
	Matrix matr(x.size1,y.size2,0);
	if (x.size2 == y.size1) {
		for (int i = 0; i < x.size1; i++) {
			for (int j = 0; j < y.size2; j++) {
				for (int k = 0; k < x.size2; k++) {
					matr.matrix[i][j] += x.matrix[i][k] * y.matrix[k][j];
				}
			}
		}
		return matr;
	} else {
		cout << "Cannot Multiply these 2 Matrices" << endl;
		return Matrix(0,0);
	}
}

/* Multiplies 2 Matrices using the Divide and Conquer Method */
Matrix Matrix::DivideConquer(Matrix const&x, Matrix const&y, int leaf_size) {
	// Adjust leaf size and check for matrix size errors
	if ((x.size1 != y.size1 || x.size2 != y.size2) || x.size1 <= leaf_size) return x * y;
	Matrix x1 = Q1(x);
	Matrix x2 = Q2(x);
	Matrix x3 = Q3(x);
	Matrix x4 = Q4(x);
	Matrix y1 = Q1(y);
	Matrix y2 = Q2(y);
	Matrix y3 = Q3(y);
	Matrix y4 = Q4(y);
	Matrix C = Join(DivideConquer(x1, y1, leaf_size) + DivideConquer(x2, y3, leaf_size),
			        DivideConquer(x1, y2, leaf_size) + DivideConquer(x2, y4, leaf_size),
			        DivideConquer(x3, y1, leaf_size) + DivideConquer(x4, y3, leaf_size),
				    DivideConquer(x3, y2, leaf_size) + DivideConquer(x4, y4, leaf_size));
	C.size1 = x.size1;
	C.size2 = y.size2;
	return C;
}

/* Multiplies 2 Matrices using the Strassen method */
Matrix Matrix::Strassen(Matrix const& x, Matrix const& y, int leaf_size) {
	// Adjust leaf size and check for matrix size errors
	if ((x.size1 != y.size1 || x.size2 != y.size2) || x.size1 <= leaf_size) return x * y;
	Matrix x1 = Q1(x);
	Matrix x2 = Q2(x);
	Matrix x3 = Q3(x);
	Matrix x4 = Q4(x);
	Matrix y1 = Q1(y);
	Matrix y2 = Q2(y);
	Matrix y3 = Q3(y);
	Matrix y4 = Q4(y);
	Matrix p1 = Strassen(x1, y2 - y4, leaf_size);
	Matrix p2 = Strassen(x1 + x2, y4, leaf_size);
	Matrix p3 = Strassen(x3 + x4, y1, leaf_size);
	Matrix p4 = Strassen(x4, y3 - y1, leaf_size);
	Matrix p5 = Strassen(x1 + x4, y1 + y4, leaf_size);
	Matrix p6 = Strassen(x2 - x4, y3 + y4, leaf_size);
	Matrix p7 = Strassen(x1 - x3, y1 + y2, leaf_size);
	Matrix C = Join(p5+p4-p2+p6,p1+p2,p3+p4,p1+p5-p3-p7);
	C.size1 = x.size1;
	C.size2 = y.size2;
	return C;
}