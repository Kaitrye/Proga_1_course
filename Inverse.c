#include <stdio.h> 
#include <stdlib.h>
#include <stdint.h>
#include <locale.h>
#include <math.h>
#include <malloc.h>
#include <inttypes.h>

//чтение размера
size_t read_size() {
	size_t size;
	scanf_s("%zu", &size);
	return size;
}

//чтение числа
double read_double() {
	double a;
	scanf_s("%lf", &a);
	return a;
}

//структура матрицы
struct Matrix {
	double** A;
	double** B;
	size_t rows;
	size_t columns;
};

//создание матрицы
void CreateMatrix(struct Matrix* one) {

	printf("Введите размерность матрицы: \n");

	one->rows = read_size();
	one->columns = read_size();

	one->A = (double**)calloc(one->rows, sizeof(double*));
	one->B = (double**)calloc(one->rows, sizeof(double*));
	for (size_t i = 0; i < one->rows; i++) {
		one->A[i] = (double*)calloc((one->columns), sizeof(double));
		one->B[i] = (double*)calloc((one->columns), sizeof(double));
		one->B[i][i] = 1;
	}

	printf("Введите матрицу в формате:\n"
		"a[1][1] a[1][2] a[1][3] ... a[1][m]\n ...\n"
		"a[n][1] a[n][2] a[n][3] ... a[n][m]\n");

	for (size_t i = 0; i < one->rows; i++) {
		for (size_t j = 0; j < one->columns; j++) {
			one->A[i][j] = read_double();
		}
	}
}

//вывод основной матрицы
void PrintMatrixA(struct Matrix* one) {
	printf("\nРазмерность: %d / %d \n", one->rows, one->columns);

	for (size_t i = 0; i < one->rows; i++) {
		for (size_t j = 0; j < one->columns; j++) {
			printf("%lf ", one->A[i][j]);
		}
		printf("\n");
	}
}

//вывод вспомогательной матрциы
void PrintMatrixB(struct Matrix* one) {
	printf("\nРазмерность: %d / %d \n", one->rows, one->columns);

	for (size_t i = 0; i < one->rows; i++) {
		for (size_t j = 0; j < one->columns; j++) {
			printf("%lf ", one->B[i][j]);
		}
		printf("\n");
	}
}

//нахождение обратной матрицы
void FindInverse(struct Matrix* one) {

	for (size_t d = 0; d < one->rows; d++) {
		if (one->A[d][d] == 0) {
			size_t k = one->rows;
			for (size_t i = d + 1; i < one->rows; i++) {
				if (one->A[i][d] != 0) {
					k = i;
					break;
				}
			}
			if (k != one->rows) {
				for (size_t j = 0; j < one->columns; j++) {
					double t = one->A[d][j];
					one->A[d][j] = one->A[k][j];
					one->A[k][j] = t;
					t = one->B[d][j];
					one->B[d][j] = one->B[k][j];
					one->B[k][j] = t;
				}
			}
		}
		for (size_t i = d + 1; i < one->rows; i++) {
			if (one->A[i][d] != 0) {
				double koef = one->A[i][d] / one->A[d][d];
				for (size_t j = 0; j < one->columns; j++) {
					one->A[i][j] -= one->A[d][j] * koef;
					one->B[i][j] -= one->B[d][j] * koef;
				}
			}
		}
	}
	
	for (size_t i = 0; i < one->rows; i++) {
		if (one->A[i][i] != 1) {
			double koef = one->A[i][i];
			for (size_t j = 0; j < one->columns; j++) {
				if (one->A[i][j] != 0)
					one->A[i][j] /= koef;
				if (one->B[i][j] != 0)
					one->B[i][j] /= koef;
			}
		}
	}

	for (int i = one->rows - 2; i >= 0; i--) {
		for (int j = one->columns - 1; j > i; j--) {
			if (one->A[i][j] != 0) {
				double koef = one->A[i][j];
				one->A[i][j] = 0;
				for (size_t h = 0; h < one->columns; h++) {
					one->B[i][h] -= one->B[j][h] * koef;
				}
			}
		}
	}

}

//объединение функций в одну
void Inverse() {
	struct Matrix one;
	CreateMatrix(&one);
	FindInverse(&one);
	PrintMatrixB(&one);
}

int main() {
	setlocale(LC_ALL, "Russian");
	Inverse();

	return 0;
}