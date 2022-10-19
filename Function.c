#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <locale.h>

//���������� �������� ��������
double avg(double* x, int n) {
	double sum = 0;
	for (int i = 0; i < n; i++) {
		sum += x[i];
	}

	return sum / (double)n;
}

//���������� ���������
double D(double* x, int n, double avg) {
	double sum = 0;
	for (int i = 0; i < n; i++) {
		sum += (x[i] - avg) * (x[i] - avg);
	}

	return sum / (double)n;
}

//���������� ������������ ����������
double R(double* x, double* y, int n, double D_x, double D_y, double avg_x, double avg_y) {
	double sum = 0;
	for (int i = 0; i < n; i++) {
		sum += (x[i] - avg_x) * (y[i] - avg_y);
	}

	return sum / ((double)n * sqrt(D_x) * sqrt(D_y));
};

//���������� �������� �������� ���������
double avg2(double* x, int n) {
	double sum = 0;
	for (int i = 0; i < n; i++) {
		sum += x[i]*x[i];
	}

	return sum / (double)n;
}

//���������� �������� �������� ������������ ���� ����������
double avgxy(double* x, double* y, int n) {
	double sum = 0;
	for (int i = 0; i < n; i++) {
		sum += x[i]*y[i];
	}

	return sum / (double)n;
}

//�������� ������� - ����� �������� ����������� ����� �������
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
		fprintf(fin, "\n\n������� �������� x: %lf\n", avg_x);
		printf("\n\n������� �������� x: %lf\n", avg_x);

		double avg_y = avg(y, n);
		fprintf(fin, "������� �������� y: %lf\n\n", avg_y);
		printf("������� �������� y: %lf\n\n", avg_y);


		double D_x = D(x, n, avg_x);
		fprintf(fin, "��������� �� x: %lf\n", D_x);
		printf("��������� �� x: %lf\n", D_x);

		double D_y = D(y, n, avg_y);
		fprintf(fin, "��������� �� y: %lf\n\n", D_y);
		printf("��������� �� y: %lf\n\n", D_y);


		double r = R(x, y, n, D_x, D_y, avg_x, avg_y);
		fprintf(fin, "����������� ����������: %lf\n\n", r);
		printf("����������� ����������: %lf\n\n", r);


		if (r >= 0.5) {

			fprintf(fin, "�������� �����������: \n");
			printf("�������� �����������: \n");


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

			fprintf(fin, "�������: y = %.3lf + %.3lfx\n", a[0], a[1]);
			printf("�������: y = %.3lf + %.3lfx\n", a[0], a[1]);

		}
		else {
			fprintf(fin, "����������� ����� ����������� �� �������\n");
			printf("����������� ����� ����������� �� �������\n");

		}

		fclose(fin);
		free(x);
		free(y);
		printf("\n��������� ���������. ��������� �������� � �������� ����\n");
	}
	else
		printf("���� �� ������");

	return 0;
}