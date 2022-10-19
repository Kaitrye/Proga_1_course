#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <math.h>

int main() {

	setlocale(LC_ALL, "RUS");
	FILE* input;

	int n;

	if ((input = fopen("data2.txt", "r")) != NULL) {
		fscanf_s(input, "%d", &n);
		int len = n / 2;

		//раздел€ем данные на обучающую и тестовую выборки
		double* train_x = calloc(len, sizeof(double));
		double* train_y = calloc(len, sizeof(double));
		double* test_x = calloc(len, sizeof(double));
		double* test_y = calloc(len, sizeof(double));
		
		for (int i = 0; i < len; i++) {
			if (train_x && train_y)
				fscanf_s(input, "%lf %lf", &train_x[i], &train_y[i]);
		}

		for (int i = 0; i < len; i++) {
			if (test_x && test_y)
				fscanf_s(input, "%lf %lf", &test_x[i], &test_y[i]);
		}

		//заполн€ем массив весов начальным значением 0
		double w[2] = { 0, 0 }, w_new[2], Q = 0, Q_new;

		//находим среднюю квадратическую ошибку при данных весах
		for (int i = 0; i < len; i++) {
			if (train_x && train_y)
				Q += (w[0] + w[1] * train_x[i] - train_y[i])*(w[0] + w[1] * train_x[i] - train_y[i]);
		}

		Q /= len;
		double a = 0.000001, G0 = 0, G1 = 0, t = 0.001;

		//находим градиент и измен€ем весы
		while (1) {
			for (int i = 0; i < len; i++) {
				if (train_x && train_y) {
					G0 += 2 * (w[0] + w[1] * train_x[i] - train_y[i]);
					G1 += 2 * (w[0] + w[1] * train_x[i] - train_y[i]) * train_x[i];
				}
			}
			G0 /= (double)len;
			G1 /= (double)len;

			w_new[0] = w[0] - a * G0;
			w_new[1] = w[1] - a * G1;
			//находим новую среднюю квадратичную ошибку при новых весах
			Q_new = 0;
			for (int i = 0; i < len; i++) {
				if (train_x && train_y)
					Q_new += (w_new[0] + w_new[1]*train_x[i] - train_y[i]) * (w_new[0] + w_new[1]*train_x[i] - train_y[i]);
			}

			//смотрим изменение ошибки и весов. ѕри достижении нужной погрешности заканчиваем градиентный спуск
			if (fabs(Q - Q_new) < t || (fabs(w[0] - w_new[0]) < t && fabs(w[1] - w_new[1]) < t)) {
				Q = Q_new;
				w[0] = w_new[0];
				w[1] = w_new[1];
				break;
			}
			else {
				Q = Q_new;
				w[0] = w_new[0];
				w[1] = w_new[1];
			}
		}
		
		//выводим найденную функцию
		printf("y = %lf + %lf*x\n", w[0], w[1]);

		//находим и выводим среднюю, максимальную и минимальную ошибки на обучающей и тестовой выборках
		double P = 0;
		for (int i = 0; i < len; i++) {
			if (train_x && train_y)
				P += fabs(w[0] + w[1] * train_x[i] - train_y[i]);
		}
		double maxi = 0;
		for (int i = 0; i < len; i++) {
				if (fabs(w[0] + w[1] * train_x[i] - train_y[i]) > maxi)
					maxi = fabs(w[0] + w[1] * train_x[i] - train_y[i]);
		}
		double mini = maxi;
		for (int i = 0; i < len; i++) {
			if (train_x && train_y)
				if (fabs(w[0] + w[1] * train_x[i] - train_y[i]) < mini)
					mini = fabs(w[0] + w[1] * train_x[i] - train_y[i]);
		}

		P /= len;
		printf("%lf %lf %lf\n", P, maxi, mini);


		P = 0;
		for (int i = 0; i < len; i++) {
			if (test_x && test_y)
				P += fabs(w[0] + w[1] * test_x[i] - test_y[i]);
		}
		maxi = 0;
		for (int i = 0; i < len; i++) {
			if (fabs(w[0] + w[1] * test_x[i] - test_y[i]) > maxi)
				maxi = fabs(w[0] + w[1] * test_x[i] - test_y[i]);
		}
		mini = maxi;
		for (int i = 0; i < len; i++) {
			if (test_x && test_y)
				if (fabs(w[0] + w[1] * test_x[i] - test_y[i]) < mini)
					mini = fabs(w[0] + w[1] * test_x[i] - test_y[i]);
		}

		P /= len;
		printf("%lf %lf %lf", P, maxi, mini);
		fclose(input);
	}

	return 0;
}