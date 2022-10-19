#include <stdio.h>
#include <locale.h>
#include <malloc.h>

//чтение размера
int read_size() {
	int size;
	scanf_s("%d", &size);
	return size;
}

//чтение числа
double read_double() {
	double a;
	scanf_s("%lf", &a);
	return a;
}

//структура СЛАУ
struct SLAU {
	double** A;
	double** B;
	double* b;
	double* x;
	int rows;
	int columns;
};

//создание СЛАУ
void CreateSLAU(struct SLAU* one) {

	printf("Введите количество уравнений: \n");
	one->rows = read_size();

	printf("Введите количество переменных: \n");
	one->columns = read_size();

	one->A = (double**)calloc(one->rows, sizeof(double*));
	one->B = (double**)calloc(one->rows, sizeof(double*));
	for (int i = 0; i < one->rows; i++) {
		one->A[i] = (double*)calloc((one->columns), sizeof(double));
		one->B[i] = (double*)calloc((one->columns), sizeof(double));
	}
	one->b = (double*)calloc(one->rows, sizeof(double));
	one->x = (double*)calloc(one->columns, sizeof(double));

	printf("Введите систему линейных алгебраических уравнений в формате:\n"
		"a[1][1] a[1][2] a[1][3] ... a[1][m] b[1]\n ...\n"
		"a[n][1] a[n][2] a[n][3] ... a[n][m] b[m]\n"
		"где a[i][j] - коэффициенты уравнений, а b[i] - свободные члены\n\n");

	for (int i = 0; i < one->rows; i++) {
		for (int j = 0; j < one->columns; j++) {
			one->A[i][j] = read_double();
			one->B[i][j] = one->A[i][j];
		}
		one->b[i] = read_double();
		one->x[i] = one->b[i];
	}
}

//копирование СЛАУ
void CopySLAU(struct SLAU* one) {

	for (int i = 0; i < one->rows; i++)
		for (int j = 0; j < one->columns; j++)
			one->A[i][j] = one->B[i][j];
}

//вывод СЛАУ
void PrintSLAU(struct SLAU* one) {
	printf("\nРазмерность: %d / %d \n", one->rows, one->columns);

	for (int i = 0; i < one->rows; i++) {
		for (int j = 0; j < one->columns; j++) {
			if (j < one->columns - 1)
				printf("%.3lf*x[%d] + ", one->A[i][j], j);
			else
				printf("%.3lf*x[%d]", one->A[i][j], j);
		}
		printf(" = %.3lf\n", one->b[i]);
	}

	for (int i = 0; i < one->columns; i++) {
		printf("x[%d] = %.3lf ", i, one->x[i]);
	}
	printf("\n");
}

//удаление СЛАУ
void FreeSLAU(struct SLAU* one) {
	for (int i = 0; i < one->rows; i++) {
		free(one->A[i]);
		free(one->B[i]);
	}

	free(one->A);
	free(one->B);
	free(one->b);
	free(one->x);
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

//вывод основной матрицы
void PrintMatrixA(struct Matrix* one) {
	printf("\nРезультат:\n\nРазмерность матрицы: %d / %d \n", one->rows, one->columns);

	for (int i = 0; i < one->rows; i++) {
		for (int j = 0; j < one->columns; j++) {
			printf("%.1lf ", one->A[i][j]);
		}
		printf("\n");
	}
}

//вывод вспомогательной матрицы
void PrintMatrixB(struct Matrix* one) {
	printf("\nРезультат:\n\nРазмерность матрицы: %d / %d \n", one->rows, one->columns);

	for (int i = 0; i < one->rows; i++) {
		for (int j = 0; j < one->columns; j++) {
			printf("%.1lf ", one->B[i][j]);
		}
		printf("\n");
	}
}

//вывод единичной матрицы
void PrintMatrixC(struct Matrix* one) {
	printf("\nРезультат:\n\nРазмерность матрицы: %d / %d \n", one->rows, one->columns);

	for (int i = 0; i < one->rows; i++) {
		for (int j = 0; j < one->columns; j++) {
			printf("%.1lf ", one->C[i][j]);
		}
		printf("\n");
	}
}

//вывод транспонированной матрицы
void PrintMatrixD(struct Matrix* one) {
	printf("\nРезультат:\n\nРазмерность матрицы: %d / %d \n", one->columns, one->rows);

	for (int i = 0; i < one->columns; i++) {
		for (int j = 0; j < one->rows; j++) {
			printf("%.1lf ", one->D[i][j]);
		}
		printf("\n");
	}
}

//копирование матрицы
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

//нахождение определителя матрицы
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

//нахождение определителя матрицы СЛАУ
double DetermineSLAU(struct SLAU* one) {

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

	CopySLAU(one);
	return Det;
}

//нахождение частного определителя для конкретной переменной
double DetermineX(struct SLAU* one, int k) {
	for (int i = 0; i < one->rows; i++) {
		one->A[i][k] = one->b[i];
	}

	double det = DetermineSLAU(one);
	return det;
}

//нахождение переменной с помощью алгоритма Крамера решения СЛАУ
void FindX(struct SLAU* one, double det) {
	for (int i = 0; i < one->columns; i++) {
		double h = DetermineX(one, i);
		if (h != 0)
			one->x[i] = h / det;
		else
			one->x[i] = 0;
	}
}

//проверка результата с помощью умножения матриц
double* Mul(struct SLAU* one) {

	double* c = (double*)calloc(one->rows, sizeof(double));

	for (int i = 0; i < one->rows; i++) {
		c[i] = 0;
		for (int k = 0; k < one->columns; k++) {
			c[i] += one->A[i][k] * one->x[k];
		}
	}

	return c;
}

void Check(struct SLAU* one) {
	double* c = Mul(one);
	int l = 1;
	for (int i = 0; i < one->rows; i++) {
		if ((float)c[i] != (float)one->b[i]) l = 0;
	}
	if (l) {
		printf("\nРезультат найден верно\n");
	}
	else {
		printf("\nК сожалению, результат неверный, так как получаются иные ответы:\n");
		for (int i = 0; i < one->rows; i++) {
			printf("b[%d] = %.3lf\n", i, c[i]);
		}
	}
}

//объединения функций в одну
void Kramer() {
	struct SLAU one;
	CreateSLAU(&one);

	double det = DetermineSLAU(&one);

	FindX(&one, det);
	PrintSLAU(&one);
	Check(&one);

	FreeSLAU(&one);
}

//нахождение обратной матрицы
void FindInverse(struct Matrix* one) {

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
				for (int j = 0; j < one->columns; j++) {
					double t = one->A[d][j];
					one->A[d][j] = one->A[k][j];
					one->A[k][j] = t;
					t = one->C[d][j];
					one->C[d][j] = one->C[k][j];
					one->C[k][j] = t;
				}
			}
		}
		for (int i = d + 1; i < one->rows; i++) {
			if (one->A[i][d] != 0) {
				double koef = one->A[i][d] / one->A[d][d];
				for (int j = 0; j < one->columns; j++) {
					one->A[i][j] -= one->A[d][j] * koef;
					one->C[i][j] -= one->C[d][j] * koef;
				}
			}
		}
	}

	for (int i = 0; i < one->rows; i++) {
		if (one->A[i][i] != 1) {
			double koef = one->A[i][i];
			for (int j = 0; j < one->columns; j++) {
				if (one->A[i][j] != 0)
					one->A[i][j] /= koef;
				if (one->C[i][j] != 0)
					one->C[i][j] /= koef;
			}
		}
	}

	for (int i = one->rows - 2; i >= 0; i--) {
		for (int j = one->columns - 1; j > i; j--) {
			if (one->A[i][j] != 0) {
				double koef = one->A[i][j];
				one->A[i][j] = 0;
				for (int h = 0; h < one->columns; h++) {
					one->C[i][h] -= one->C[j][h] * koef;
				}
			}
		}
	}
}

//объединения функций в одну
void Inverse() {

	struct Matrix one;
	CreateMatrix(&one);

	FindInverse(&one);
	PrintMatrixC(&one);
}

//решение СЛАУ с помощью алгоритма Гаусса
void Steps(struct SLAU* one) {

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
				double t;
				for (int j = 0; j < one->columns; j++) {
					t = one->A[d][j];
					one->A[d][j] = one->A[k][j];
					one->A[k][j] = t;
				}
				t = one->x[d];
				one->x[d] = one->x[k];
				one->x[k] = t;
			}
		}
		for (int i = d + 1; i < one->rows; i++) {
			if (one->A[i][d] != 0) {
				double koef = one->A[i][d] / one->A[d][d];
				for (int j = 0; j < one->columns; j++) {
					one->A[i][j] -= one->A[d][j] * koef;
				}
				one->x[i] -= one->x[d] * koef;
			}
		}
	}


	for (int i = 0; i < one->rows; i++) {
		if (one->A[i][i] != 1) {
			double koef = one->A[i][i];
			for (int j = 0; j < one->columns; j++) {
				if (one->A[i][j] != 0)
					one->A[i][j] /= koef;
			}
			if (one->x[i] != 0)
				one->x[i] /= koef;
		}
	}

	for (int i = one->rows - 2; i >= 0; i--) {
		for (int j = one->columns - 1; j > i; j--) {
			if (one->A[i][j] != 0) {
				double koef = one->A[i][j];
				one->A[i][j] = 0;
				one->x[i] -= one->x[j] * koef;
			}
		}
	}
	CopySLAU(one);
}

//объединение функций в одну
void Gauss() {
	struct SLAU one;
	CreateSLAU(&one);

	Steps(&one);
	PrintSLAU(&one);
	Check(&one);

	FreeSLAU(&one);
}

//нахождение определителя матрицы
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

//сложение матриц
void Add() {

	printf("Первая матрица: \n\n");
	struct Matrix one;
	CreateMatrix(&one);

	printf("\nВторая матрица: \n\n");
	struct Matrix two;
	CreateMatrix(&two);

	if (one.columns != two.columns || one.rows != two.rows) {
		printf("Размерности матриц не позволяют произвести данное действие. Попробуйте изменить данные\n");
		return;
	}

	for (int i = 0; i < one.rows; i++) {
		for (int j = 0; j < one.columns; j++) {
			one.C[i][j] = one.A[i][j] + two.A[i][j];
		}
	}

	PrintMatrixC(&one);
	FreeMatrix(&one);
	FreeMatrix(&two);
}

//вычитание матриц
void Sub() {

	printf("Первая матрица: \n\n");
	struct Matrix one;
	CreateMatrix(&one);

	printf("\nВторая матрица: \n\n");
	struct Matrix two;
	CreateMatrix(&two);

	if (one.columns != two.columns || one.rows != two.rows) {
		printf("Размерности матриц не позволяют произвести данное действие. Попробуйте изменить данные\n");
		return;
	}

	for (int i = 0; i < one.rows; i++) {
		for (int j = 0; j < one.columns; j++) {
			one.C[i][j] = one.A[i][j] - two.A[i][j];
		}
	}

	PrintMatrixC(&one);
	FreeMatrix(&one);
	FreeMatrix(&two);
}

//умножение матриц
void MulMM() {

	printf("Первая матрица: \n\n");
	struct Matrix one;
	CreateMatrix(&one);

	printf("\nВторая матрица: \n\n");
	struct Matrix two;
	CreateMatrix(&two);

	if (one.columns != two.rows) {
		printf("Размерности матриц не позволяют произвести данное действие. Попробуйте изменить данные\n");
		return;
	}

	double** R = (double**)calloc(one.rows, sizeof(double*));

	for (int i = 0; i < one.rows; i++) {
		R[i] = (double*)calloc(two.columns, sizeof(double));
	}

	for (int i = 0; i < one.rows; i++) {
		for (int j = 0; j < two.columns; j++) {
			R[i][j] = 0;
			for (int k = 0; k < one.columns; k++) {
				R[i][j] += one.A[i][k] * two.A[k][j];
			}
		}
	}

	printf("\nРезультат:\n\nРазмерность матрицы: %d / %d \n", one.rows, two.columns);

	for (int i = 0; i < one.rows; i++) {
		for (int j = 0; j < two.columns; j++) {
			printf("%.1lf ", R[i][j]);
		}
		printf("\n");
	}

	FreeMatrix(&one);
	FreeMatrix(&two);
	for (int i = 0; i < one.rows; i++) {
		free(R[i]);
	}
	free(R);
}

//умножение матрицы на число
void MulMC() {

	struct Matrix one;
	CreateMatrix(&one);

	printf("Введите число: \n");
	double l;
	scanf_s("%lf", &l);

	for (int i = 0; i < one.rows; i++) {
		for (int j = 0; j < one.columns; j++) {
			one.C[i][j] = one.A[i][j] * l;
		}
	}

	PrintMatrixC(&one);
	FreeMatrix(&one);
}

//транспонирование
void Transposition() {

	struct Matrix one;
	CreateMatrix(&one);

	PrintMatrixD(&one);
	FreeMatrix(&one);
}

//основная функция и вывод меню
int main() {
	setlocale(LC_ALL, "Russian");
	int command;
	printf("Выберите нужное действие:\n\n"
		"0 - вывести список команд\n"
		"1 - решить СЛАУ методом Гаусса\n"
		"2 - решить СЛАУ методом Крамера\n"
		"3 - найти определитель матрицы\n"
		"4 - найти сумму матриц\n"
		"5 - найти разность матриц\n"
		"6 - найти произведение матриц\n"
		"7 - найти произведение матрицы на число\n"
		"8 - найти обратную матрицу\n"
		"9 - транспонировать матрицу\n"
		"10 - выйти из программы\n");
	int k = 1;

	while (k) {
		printf("\nВведите номер действия:\n");
		scanf_s("%d", &command);
		printf("\n");
		switch (command) {
		case 0:
			printf("0 - вывести список команд\n"
				"1 - решить СЛАУ методом Гаусса\n"
				"2 - решить СЛАУ методом Крамера\n"
				"3 - найти определитель матрицы\n"
				"4 - найти сумму матриц\n"
				"5 - найти разность матриц\n"
				"6 - найти произведение матриц\n"
				"7 - найти произведение матрицы на число\n"
				"8 - найти обратную матрицу\n"
				"9 - транспонировать матрицу\n"
				"10 - выйти из программы\n");
			break;
		case 1:
			Gauss();
			break;
		case 2:
			Kramer();
			break;
		case 3:
			Determinant();
			break;
		case 4:
			Add();
			break;
		case 5:
			Sub();
			break;
		case 6:
			MulMM();
			break;
		case 7:
			MulMC();
			break;
		case 8:
			Inverse();
			break;
		case 9:
			Transposition();
			break;
		case 10:
			k = 0;
			break;
		default:
			printf("Неизвестная команда. Попробуйте ещё раз\n");
			break;
		}
	}
}
