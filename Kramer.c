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

//стурктура СЛАУ
struct SLAU {
	double** A;
	double** B;
	double* b;
	double* x;
	size_t rows;
	size_t columns;
};

//создание СЛАУ
void CreateSLAU(struct SLAU* one) {

	printf("Введите размерность матрицы: \n");

	one->rows = read_size();
	one->columns = read_size();

	one->A = (double**)calloc(one->rows, sizeof(double*));
	one->B = (double**)calloc(one->rows, sizeof(double*));
	for (size_t i = 0; i < one->rows; i++) {
		one->A[i] = (double*)calloc((one->columns), sizeof(double));
		one->B[i] = (double*)calloc((one->columns), sizeof(double));
	}
	one->b = (double*)calloc(one->rows, sizeof(double));
	one->x = (double*)calloc(one->columns, sizeof(double));

	printf("Введите систему линейных алгебраических уравнений в формате:\n"
		"a[1][1] a[1][2] a[1][3] ... a[1][m] b[1]\n ...\n"
		"a[n][1] a[n][2] a[n][3] ... a[n][m] b[m]\n"
		"где a[i][j] - коэффициенты уравнений, а b[i] - свободные члены\n\n");

	for (size_t i = 0; i < one->rows; i++) {
		for (size_t j = 0; j < one->columns; j++) {
			one->A[i][j] = read_double();
			one->B[i][j] = one -> A[i][j];
		}
		one->b[i] = read_double();
	}
}

//копирование СЛАУ
void CopySLAU(struct SLAU* one) {

	for (size_t i = 0; i < one->rows; i++)
		for (size_t j = 0; j < one->columns; j++)
			one->A[i][j] = one->B[i][j];
}

//вывод СЛАУ
void PrintSLAU(struct SLAU* one) {
	printf("\nРазмерность: %d / %d \n", one->rows, one->columns);

	for (size_t i = 0; i < one->rows; i++) {
		for (size_t j = 0; j < one->columns; j++) {
			if (j < one->columns - 1)
				printf("%lf*x[%zu] + ", one->A[i][j], j);
			else
				printf("%lf*x[%zu]", one->A[i][j], j);
		}
		printf(" = %lf\n", one->b[i]);
	}

	for (size_t i = 0; i < one->columns; i++) {
		printf("x[%zu] = %lf ", i, one->x[i]);
	}
	printf("\n");
}

//нахождение определителя матрицы СЛАУ
double Determine(struct SLAU* one) {

	int sign = 0;
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
				sign++;
				for (size_t j = 0; j < one->columns; j++) {
					double t = one->A[d][j];
					one->A[d][j] = one->A[k][j];
					one->A[k][j] = t;
				}
			}
		}
		for (size_t i = d + 1; i < one->rows; i++) {
			if (one->A[i][d] != 0) {
				double koef = one->A[i][d] / one->A[d][d];
				for (size_t j = d; j < one->columns; j++) {
					one->A[i][j] -= one->A[d][j] * koef;
				}
			}
		}
	}


	double Det = one->A[0][0];
	for (size_t i = 1; i < one->rows; i++) {
		Det *= one->A[i][i];
	}
	if (sign % 2 != 0) Det *= (-1);

	CopySLAU(one);
	return Det;
}

//нахождение определителя для конкретной переменной
double DetermineX(struct SLAU* one, size_t k) {
	for (size_t i = 0; i < one->rows; i++) {
		one->A[i][k] = one->b[i];
	}

	double det = Determine(one);
	return det;
}

//нахождение переменной
void FindX(struct SLAU* one, double det) {
	for (size_t i = 0; i < one->columns; i++) {
		double h = DetermineX(one, i);
		one->x[i] = h / det;
	}
}

//удаление СЛАУ
void FreeSLAU(struct SLAU* one) {
	for (size_t i = 0; i < one->rows; i++) {
		free(one->A[i]);
		free(one->B[i]);
	}

	free(one->A);
	free(one->B);
	free(one->b);
	free(one->x);
}

//объединение функций в одну
void Kramer() {
	struct SLAU one;
	CreateSLAU(&one);

	double det = Determine(&one);

	FindX(&one, det);
	PrintSLAU(&one);

	FreeSLAU(&one);
}

int main() {
	setlocale(LC_ALL, "Russian");
	Kramer();

	return 0;
}