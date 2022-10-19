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

	return sum / (n);
}

//���������� ������������ ����������
double R(double* x, double* y, int n, double D_x, double D_y, double avg_x, double avg_y) {
	double sum = 0;
	for (int i = 0; i < n; i++) {
		sum += (x[i] - avg_x) * (y[i] - avg_y);
	}

	return sum / ((n) * sqrt(D_x) * sqrt(D_y));
};

//���������� �������� �������� ���������
double avg2(double* x, int n) {
	double sum = 0;
	for (int i = 0; i < n; i++) {
		sum += x[i] * x[i];
	}

	return sum / n;
}

//���������� �������� �������� ������������ ���� ����������
double avgxy(double* x, double* y, int n) {
	double sum = 0;
	for (int i = 0; i < n; i++) {
		sum += x[i] * y[i];
	}

	return sum / n;
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

			double x1 = sqrt(D_y) / sqrt(D_x) * r;
			double x2 = avg_y - x1 * avg_x;

			fprintf(fin, "�������: y = %.3lf + %.3lfx\n", x2, x1);
			printf("�������: y = %.3lf + %.3lfx\n", x2, x1);
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