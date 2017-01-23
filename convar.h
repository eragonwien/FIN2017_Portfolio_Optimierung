#ifndef CONVAR_H
#define CONVAR_H
#include <iostream>
#include <random>
using namespace std;

double sum(double*, int);
double avgOfArray(double*, int);
double covar(double*, double*, int);
/*
y ist die Breite bzw. die Anzahl der Arrays
x ist die Tiefe bzw. die Größe der einzelnen Array
*/
void showDoubleArray(double** arr, int x, int y)
{
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			printf("%.4f ", arr[i][j]);
		}
		cout << endl;
	}
}
inline double sum(double * arr, int len)
{
	double sum = 0.0;
	for (int i = 0; i < len; i++)
	{
		sum += arr[i];
	}
	return sum;
}
double avgOfArray(double* arr, int len)
{
	return sum(arr,len) / len;
}
double covar(double* arr1, double* arr2, int len)
{
	// Bottom Part
	double avg1 = avgOfArray(arr1, len);
	double avg2 = avgOfArray(arr2, len);
	
	// Upper Part
	double * upper = new double[len];
	for (int i = 0; i < len; i++)
	{
		upper[i] = (arr1[i] - avg1) * (arr2[i] - avg2);
	}
	return sum(upper, len) / len;
}
double** getCovMatrix(double** arr, int x, int y)
{
	double a = 0.0;
	double ** matrix = new double*[y];
	for (int i = 0; i < y; i++)
	{
		matrix[i] = new double[y];
		for (int j = 0; j < y; j++)
		{
			matrix[i][j] = covar(arr[i], arr[j], x);
		}
	}
	return matrix;
}
#endif

