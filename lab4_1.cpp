#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
double* gauss(double** a, double* y, int n)
{
	double* x, max;
	int k, index;
	const double eps = 0.00001;
	x = new double[n];
	k = 0;
	while (k < n)
	{
		max = abs(a[k][k]);
		index = k;
		for (int i = k + 1; i < n; i++)
		{
			if (abs(a[i][k]) > max)
			{
				max = abs(a[i][k]);
				index = i;
			}
		}

		if (max < eps)
		{
			return 0;
		}
		for (int j = 0; j < n; j++)
		{
			double temp = a[k][j];
			a[k][j] = a[index][j];
			a[index][j] = temp;
		}
		double temp = y[k];
		y[k] = y[index];
		y[index] = temp;

		for (int i = k; i < n; i++)
		{
			double temp = a[i][k];
			if (abs(temp) < eps) continue;
			for (int j = 0; j < n; j++)
				a[i][j] = a[i][j] / temp;
			y[i] = y[i] / temp;
			if (i == k)  continue;
			for (int j = 0; j < n; j++)
				a[i][j] = a[i][j] - a[k][j];
			y[i] = y[i] - y[k];
		}
		k++;
	}

	for (k = n - 1; k >= 0; k--)
	{
		x[k] = y[k];
		for (int i = 0; i < k; i++)
			y[i] = y[i] - a[i][k] * x[k];
	}
	return x;
}


double norma(double l[]) {
	double sum1 = 0;
	for (int i = 0; i < 100; i++) {
		sum1 += fabs(l[i]) * fabs(l[i]);
	}
	return sqrt(sum1);
}


int main()
{
	double a[100][100] = { 0 };
	double f[100] = { 0 };

	for (int i = 0; i < 100; i++)
	{
		double ai = 1, bi = 10, ci = 1, pi = 1;
		f[i] = i + 1;
		if (i > 0 && i < 99)
		{
			a[i][i - 1] = ai;
			a[i][i] = bi;
			a[i][i + 1] = ci;
		}
		else if (i == 0)
		{
			a[i][i] = bi;
			a[i][i + 1] = ci;
		}
		else if (i == 99)
		{
			for (int j = 0; j < 100; j++)
			{
				a[i][j] = pi;
			}
		}
	}



	double** p, * y, * x;
	int n = 100;

	p = new double* [n];
	y = new double[n];
	for (int i = 0; i < n; i++)
	{
		p[i] = new double[n];
		for (int j = 0; j < n; j++)
		{
			p[i][j] = a[i][j];
		}
	}
	for (int i = 0; i < n; i++)
	{

		y[i] = f[i];
	}

	x = gauss(p, y, n);

	double l[100] = { 0 };
	double sum;
	for (int i = 0; i < 100; i++)
	{
		sum = 0;
		for (int j = 0; j < 100; j++)
		{
			sum += a[i][j] * x[j];
		}
		l[i] = abs(f[i] - sum);

	}

	int i;
	ofstream out;
	out.open("ans1.dat");
	for (i = 0; i < 100; i++) {
		out << x[i] << endl;
	}
	out.close();

	cout << "norma=";
	cout << norma(l);
	return 0;
}
