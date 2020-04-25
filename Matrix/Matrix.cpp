#include "Matrix_c.cpp"
#include <cstdio>
#include <ctime>

int main() {
	std::clock_t start;
	double duration;

	/* Initialize test variables */
	Matrix A(2,9);
	Matrix B(9,7);
	Matrix C = A * B;

	/* Prove that they produce same results */ 
	C.Display();
	C.DivideConquer(A, B).Display();
	C.Strassen(A, B).Display();

	/*Choose any valid number > 0 to begin matrix multiplication with a valid leaf size > 1 */
	cout << "Choose N Starting Point (N X N): ";
	int i;
	cin >> i;
	cout << endl << "Choose leaf size: ";
	int l;
	cin >> l;
	cout << endl;

	/* Test Runtime Speeds(multiplies initial value by 2 every loop), Until Memory runs out and crashes */
	for (i; i <= 1000000000; i*=2) {
		Matrix X(i, i);
		Matrix Y(i, i);

		start = clock();
		C = X * Y;
		duration = (clock() - start) / (double)CLOCKS_PER_SEC;
		std::cout << "Classic: " << duration  << " Size: "<< i << std::endl;
		
		start = clock();
		C.DivideConquer(X, Y, l);
		duration = (clock() - start) / (double)CLOCKS_PER_SEC;
		std::cout << "Divide&Conquer: " << duration << " Size: " << i << std::endl;

		start = clock();
		C.Strassen(X, Y, l);
		duration = (clock() - start) / (double)CLOCKS_PER_SEC;
		std::cout << "Strassen: " << duration << " Size: " << i << std::endl << std::endl;
	}
	return 0;
}