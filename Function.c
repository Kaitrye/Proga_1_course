#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <locale.h>

//нахождение среднего значения
double avg(double* x, int n) {
	double sum = 0;
	for (int i = 0; i < n; i++) {
		sum += x[i];
	}

	return sum / (double)n;
}

//нахождение дисперсии
double D(double* x, int n, double avg) {
	double sum = 0;
	for (int i = 0; i < n; i++) {
		sum += (x[i] - avg) * (x[i] - avg);
	}

	return sum / (double)n;
}

//нахождение коэффициента корреляции
double R(double* x, double* y, int n, double D_x, double D_y, double avg_x, double avg_y) {
	double sum = 0;
	for (int i = 0; i < n; i++) {
		sum += (x[i] - avg_x) * (y[i] - avg_y);
	}

	return sum / ((double)n * sqrt(D_x) * sqrt(D_y));
};

//нахождение среднего значения квадратов
double avg2(double* x, int n) {
	double sum = 0;
	for (int i = 0; i < n; i++) {
		sum += x[i]*x[i];
	}

	return sum / (double)n;
}

//нахождение среднего значения произведения двух переменных
double avgxy(double* x, double* y, int n) {
	double sum = 0;
	for (int i = 0; i < n; i++) {
		sum += x[i]*y[i];
	}

	return sum / (double)n;
}

//основная функция - поиск линейной зависимости через матрицы
int main() {

	setlocale(LC_ALL, "RUS");
	
	FILE* fin;
	if (fopen_s(&fin, "data.txt", "r+") == 0) {

		int n;
		fscanf_s(fin, "%zu", &n);
		double* x = (double*)calloc(n, sizeof(double));
		double* y = (double*)calloc(n, sizeof(double));

		for (int i = 0; i < n; i++) {
			if (x)
				fscanf_s(fin, "%lf", &x[i]);
			if (y)
				fscanf_s(fin, "%lf", &y[i]);
		}

		double avg_x = avg(x, n);
		fprintf(fin, "\n\nСреднее значение x: %lf\n", avg_x);
		printf("\n\nСреднее значение x: %lf\n", avg_x);

		double avg_y = avg(y, n);
		fprintf(fin, "Среднее значение y: %lf\n\n", avg_y);
		printf("Среднее значение y: %lf\n\n", avg_y);


		double D_x = D(x, n, avg_x);
		fprintf(fin, "Дисперсия по x: %lf\n", D_x);
		printf("Дисперсия по x: %lf\n", D_x);

		double D_y = D(y, n, avg_y);
		fprintf(fin, "Дисперсия по y: %lf\n\n", D_y);
		printf("Дисперсия по y: %lf\n\n", D_y);


		double r = R(x, y, n, D_x, D_y, avg_x, avg_y);
		fprintf(fin, "Коэффициент корреляции: %lf\n\n", r);
		printf("Коэффициент корреляции: %lf\n\n", r);


		if (r >= 0.5) {

			fprintf(fin, "Выявлена зависимость: \n");
			printf("Выявлена зависимость: \n");


			double avg_x2 = avg2(x, n);
			double avg_xy = avgxy(x, y, n);

			double A[2][2] = { 1, avg_x, avg_x, avg_x2 };
			double a[2] = { avg_y, avg_xy };
			double b[2] = { avg_y, avg_xy };

			if (A[1][0] != 0) {
				double koef = A[1][0];
				A[1][0] = 0;
				A[1][1] -= A[0][1] * koef;
				a[1] -= a[0] * koef;
			}

			if (A[1][1] != 1) {
				double koef = A[1][1];
				A[1][1] = 1;
				if (a[1] != 0)
					a[1] /= koef;
			}

			if (A[0][1] != 0) {
				double koef = A[0][1];
				A[0][1] = 0;
				a[0] -= a[1] * koef;
			}

			fprintf(fin, "Функция: y = %.3lf + %.3lfx\n", a[0], a[1]);
			printf("Функция: y = %.3lf + %.3lfx\n", a[0], a[1]);

		}
		else {
			fprintf(fin, "Зависимость между переменными не найдена\n");
			printf("Зависимость между переменными не найдена\n");

		}

		fclose(fin);
		free(x);
		free(y);
		printf("\nПрограмма выполнена. Результат сохранен в исходный файл\n");
	}
	else
		printf("Файл не найден");

	return 0;
}