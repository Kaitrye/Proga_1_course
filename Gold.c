#include <stdio.h>
#include <locale.h>
#include <math.h>

double F[1024] = {1,1,2};

//���������� ������������������ ����� ��������� �� ������� �����
double Fibo(double t) {
	int k1 = 0, k2 = 1, k3 = 2;
	while (fabs(F[k3] / F[k2] - F[k2] / F[k1]) >= t) {
		printf("%d: %.10lf\n", k2, F[k3] / F[k2]);
		F[++k3] = F[++k2] + F[++k1];
	}
	return (F[k3] / F[k2]);
}

//�������� ������� - ����� �������� �������
int main() {
	setlocale(LC_ALL, "RUS");
	double t;
	printf("������� �������� ���������:\n");
	scanf_s("%lf", &t);
	printf("������� ����� �������:\n");
	double l;
	scanf_s("%lf", &l);
	double x = Fibo(t);
	double a = l / x;
	double b = l - a;

	printf("������� ������� �������:\na = %lf, b = %lf, r = %lf\n", a, b, a/b);

	return 0;
}