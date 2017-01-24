
#include <iostream>
#ifndef OPT_H
#define OPT_H
using namespace std;
double summproduct(double* arr1, double* arr2, int len);
double* getGewichtArray_MaxRendit(int minVar, double** arr, int x, int y)
{
	// erwartete Rendit
	double * exp_rendit = new double[y];
	for (int i = 0; i < y; i++)
	{
		exp_rendit[i] = avgOfArray(arr[i], x);
	}
	// Covarriance Matrix
	double** covmatrix = getCovMatrix(arr, x, y);
	//Gewichtarray
	double* gewichtarray = new double[y];
	return NULL;
}
double summproduct(double* arr1, double* arr2, int len)
{
	double result = 0;
	for (int i = 0; i < len; i++)
	{
		result += arr1[i] * arr2[i];
	}
	return result;
}
double* getRenditArray(double** arr, int x, int y)
{
	double * exp_rendit = new double[y];
	for (int i = 0; i < y; i++)
	{
		exp_rendit[i] = avgOfArray(arr[i], x) * 0.01;
	}
	return exp_rendit;
}
double getGesamtRendit(double* gewicht_array, double* rendit_array, int y)
{
	double sum = 0;
	for (int i = 0; i < y; i++)
	{
		sum += gewicht_array[i] * rendit_array[i];
	}
	return sum;
}
#endif