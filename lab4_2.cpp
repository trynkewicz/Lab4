#include <iostream>
#include <math.h>
#include <fstream>
using namespace std;
double norma(double l[]) {

	double sum1 = 0;
	for (int i = 0; i < 100; i++) {
		sum1 += fabs(l[i]) * fabs(l[i]);
	}
	return sqrt(sum1);
}
int main()
{


	double tempx[100] = { 0 };
	double x[100] = { 0 };
	double a[100][100] = { 0 };
	double b[100] = { 0 };

	for (int i = 0; i < 100; i++)
	{
		double ai = 1, bi = 10, ci = 1, pi = 1;
		b[i] = i + 1;
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


	int m = 0; 
	double norm = 0;
	double eps = 0.0001;
	double h;
	do
	{
		h = norm;
		for (int i = 0; i < 100; i++)
		{
			x[i] = b[i];
			for (int j = 0; j < 100; j++)
			{
				if (i != j)
					x[i] -= a[i][j] * x[j];
			}
			x[i] /= a[i][i];

		}
		for (int k = 0; k < 100; k++)
		{
			norm += (x[k] - tempx[k]) * (x[k] - tempx[k]);
			tempx[k] = x[k];
		}
		norm = sqrt(norm);
		m++;

	

	} while (abs(h - norm) > eps);

	cout<<"itera="<<m<<endl;


	 
	double l[100] = { 0 };
	double sum;
	for (int i = 0; i < 100; i++)
	{
		sum = 0;
		for (int j = 0; j < 100; j++)
		{
			sum += a[i][j] * x[j];
		}
		l[i] = abs(b[i] - sum);

	}

	int i;
	ofstream out;
	out.open("ans2.dat");
	for (i = 0; i < 100; i++) {
		out << x[i] << endl;
	}
	out.close();
	cout << "norma=";
	cout << norma(l);
	return 0;
}