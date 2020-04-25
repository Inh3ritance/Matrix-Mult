#pragma once
class Matrix {

private:
	int** matrix = NULL;
	int size1, size2;
	void BuildMatrix();
	void BuildEmptyMatrix();
	void copyMatrix(int**);
	int half2k(int);
	Matrix Join(Matrix const&, Matrix const&, Matrix const&, Matrix const&);
	Matrix Q1(Matrix const&);
	Matrix Q2(Matrix const&);
	Matrix Q3(Matrix const&);
	Matrix Q4(Matrix const&);

public:
	Matrix();
	~Matrix();
	Matrix(Matrix const&);
	Matrix(int, int, int = 1);
	void Display();
	Matrix Add(Matrix const&, Matrix const&);
	Matrix Subtract(Matrix const&, Matrix const&);
	Matrix Classic(Matrix const&, Matrix const&);
	Matrix DivideConquer(Matrix const&, Matrix const&, int = 1); // Defualt leaf set to 1
	Matrix Strassen(Matrix const&, Matrix const&, int = 1); // Default leaf set to 1

};