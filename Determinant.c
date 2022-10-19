#include <stdio.h>
#include <locale.h>
#include <malloc.h>

//функции чтения данных для удобства
int read_size() {
	int size;
	scanf_s("%d", &size);
	return size;
}

double read_double() {
	double a;
	scanf_s("%lf", &a);
	return a;
}

//структура матрицы
struct Matrix {
	double** A;
	double** B;
	double** C;
	double** D;
	int rows;
	int columns;
};

//создание матрицы
void CreateMatrix(struct Matrix* one) {

	printf("Введите количество строк матрицы: \n");
	one->rows = read_size();

	printf("Введите количество столбцов матрицы: \n");
	one->columns = read_size();

	one->A = (double**)calloc(one->rows, sizeof(double*));
	one->B = (double**)calloc(one->rows, sizeof(double*));
	one->C = (double**)calloc(one->rows, sizeof(double*));
	one->D = (double**)calloc(one->columns, sizeof(double*));

	for (int i = 0; i < one->rows; i++) {
		one->A[i] = (double*)calloc((one->columns), sizeof(double));
		one->B[i] = (double*)calloc((one->columns), sizeof(double));
		one->C[i] = (double*)calloc((one->columns), sizeof(double));
	}

	for (int i = 0; i < one->columns; i++) {
		one->D[i] = (double*)calloc((one->rows), sizeof(double));
	}

	printf("Введите матрицу в формате:\n"
		"a[1][1] a[1][2] a[1][3] ... a[1][m]\n ...\n"
		"a[n][1] a[n][2] a[n][3] ... a[n][m]\n\n");

	for (int i = 0; i < one->rows; i++) {
		for (int j = 0; j < one->columns; j++) {
			one->A[i][j] = read_double();
			one->B[i][j] = one->A[i][j];
			one->D[j][i] = one->A[i][j];

		}
		if (one->columns == one->rows && one->C[i])
			one->C[i][i] = 1;
	}
}

//копирование матрицы. Используется для того чтобы основная матрица в структуре не менялась
void CopyMatrix(struct Matrix* one) {
	for (int i = 0; i < one->rows; i++)
		for (int j = 0; j < one->columns; j++)
			one->A[i][j] = one->B[i][j];
}

//удаление матрицы
void FreeMatrix(struct Matrix* one) {
	for (int i = 0; i < one->rows; i++) {
		free(one->A[i]);
		free(one->B[i]);
		free(one->C[i]);
	}

	for (int i = 0; i < one->columns; i++) {
		free(one->D[i]);
	}

	free(one->A);
	free(one->B);
	free(one->C);
	free(one->D);
}

//функция нахождения определителя
double DetermineMatrix(struct Matrix* one) {

	int sign = 0;
	for (int d = 0; d < one->rows; d++) {
		if (one->A[d][d] == 0) {
			int k = one->rows;
			for (int i = d + 1; i < one->rows; i++) {
				if (one->A[i][d] != 0) {
					k = i;
					break;
				}
			}
			if (k != one->rows) {
				sign++;
				for (int j = 0; j < one->columns; j++) {
					double t = one->A[d][j];
					one->A[d][j] = one->A[k][j];
					one->A[k][j] = t;
				}
			}
		}
		for (int i = d + 1; i < one->rows; i++) {
			if (one->A[i][d] != 0) {
				double koef = one->A[i][d] / one->A[d][d];
				for (int j = d; j < one->columns; j++) {
					one->A[i][j] -= one->A[d][j] * koef;
				}
			}
		}
	}


	double Det = one->A[0][0];
	for (int i = 1; i < one->rows; i++) {
		if (one->A[i][i] != 0)
			Det *= one->A[i][i];
		else
			Det = 0;
	}
	if (sign % 2 != 0 && Det != 0) Det *= (-1);

	CopyMatrix(one);
	return Det;
}

//объединение всех функций в одну и вывод результата
void Determinant() {
	struct Matrix one;
	CreateMatrix(&one);

	if (one.columns != one.rows) {
		printf("Размерность матрицы не позволяет произвести данное действие. Попробуйте изменить данные\n");
		return;
	}

	double det = DetermineMatrix(&one);
	printf("\nРезультат:\n%.1lf\n", det);

	FreeMatrix(&one);
}

int main() {
	setlocale(LC_ALL, "Russian");
	Determinant();
}