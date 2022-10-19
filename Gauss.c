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

//копирование СЛАУ
void CopySLAU(struct SLAU* one) {

	for (int i = 0; i < one->rows; i++)
		for (int j = 0; j < one->columns; j++)
			one->A[i][j] = one->B[i][j];
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

//функция, реализующая алгоритм Гаусса решения СЛАУ
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
		printf("\nРезультат неверный. Получаются иные ответы:\n");
		for (int i = 0; i < one->rows; i++) {
			printf("b[%d] = %.3lf\n", i, c[i]);
		}
	}
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

int main() {

	setlocale(LC_ALL, "RUS");
	Gauss();

	return 0;
}