#include <iostream>
#include <string>
#include <fstream>
#include "convar.h"
#include "optimize.h"
using namespace std;
void showVarianzAndRendit(double * gewicht_array, double** covmatrix, double** arr, int x, int y);
int main() {
	while (true)
	{
		//Start Program
		cout << "Programm Auswahl:\n";
		cout << "( 1 ) to create new test file\n";
		cout << "( 2 ) to open a existing test file\n";
		int param, x, y;
		double** arr;
		try
		{
			cin >> param;
		}
		catch (const std::exception&)
		{
			cout << "invalid parameter\n";
		}
		// Write
		if (param == 1)
		{
			// Getting Parameter
			string filename;
			try
			{
				cout << "Name of File ?   ";
				cin >> filename;
				cout << "\nHow many Arrays ?  ";
				cin >> y;
				cout << "\nHow many Input per Array ?   ";
				cin >> x;
			}
			catch (const std::exception&)
			{
				cout << "Wrong Input Parameter. Using Default Parameter\n";
				filename = "test";
				x = 5;
				y = 5;
			}

			// Creating file
			ofstream data;
			data.open(filename);
			data << y << "\t" << x <<endl;
			for (int i = 0; i < y; i++)
			{
				for (int j = 0; j < x; j++)
				{
					double input;
					cout << "Input for " << i << " " << j << " : ";
					try
					{
						cin >> input;
					}
					catch (const std::exception&)
					{
						cout << "\nWrong Input Parameter. Using Default Parameter\n";
						input = 5.0;
					}
					data << input << "\t";
				}
				data << "\n";
			}

		}
		// Read
		else if (param == 2)
		{
			cout << "Name of File ?   ";
			string filename;
			cin >> filename;
			
			ifstream data(filename);
			if (!data.good())
			{
				cout << "Error in data\n";
				break;
			}
			data >> y >> x;
			arr = new double*[y];
			for (int i = 0; i < y; i++)
			{
				arr[i] = new double[x];
				for (int j = 0; j < x; j++)
				{
					data >> arr[i][j];
				}
			}
			cout << "Origin\n";
			showDoubleArray(arr, x, y);
			cout << "COV Matrix\n";
			double** covmatrix = getCovMatrix(arr, x, y);
			showDoubleArray(covmatrix, y, y);
			cout << endl;
			
			//Gewicht Abfrage
			
			double * gewicht_array = new double[y];
			for (int i = 0; i < y; i++)
			{
				cout << "Gewicht von Asset " << i + 1 << " in Prozent : ";
				cin >> gewicht_array[i];
				gewicht_array[i] *= 0.01;
				cout << endl;
			}
			
			
			showVarianzAndRendit(gewicht_array, covmatrix, arr, x, y);
			cout << "(1) Maximal Rendit \noder\n(2) Minimale Risiko ? :";
			int option;
			try
			{
				cin >> option;
				cout << endl;
			}
			catch (const std::exception&)
			{
				cout << "\nWrong Input Parameter. Using Default Parameter Maximale Rendit\n";
				option = 1;
			}
			if (option == 1)
			{
				cout << "max Varianz ? ";
				int maxVar;
				cin >> maxVar;
			}
			else if (option == 2)
			{
				cout << "min Gewinn ? ";
				int minGewinn;
				cin >> minGewinn;
			}
			

		}
		//End Program
		cout << "Do you want to continue? (y/n)\n";
		char end;
		cin >> end;
		if (end != 'y')break;
	}
	return 0;
}
void showVarianzAndRendit(double * gewicht_array, double** covmatrix, double** arr, int x, int y)
{
	/*
	Varianz Anteil
	*/
	double * varianz_anteil = new double[y];
	for (int i = 0; i < y; i++)
	{
		varianz_anteil[i] = gewicht_array[i] * summproduct(gewicht_array, covmatrix[i], y);
		printf("Varianz Anteil Asset %i : %.2f\n", i + 1, varianz_anteil[i]);

	}

	printf("Gesamte Varianz : %.2f\n", sum(varianz_anteil, y));
	/*
	Rendite Anteil
	*/
	double * exp_rendit = new double[y];
	for (int i = 0; i < y; i++)
	{
		exp_rendit[i] = avgOfArray(arr[i], x);
	}
	double * rendit_anteil = new double[y];
	for (int i = 0; i < y; i++)
	{
		rendit_anteil[i] = gewicht_array[i] * 0.01 * exp_rendit[i];
		printf("Rendite Anteil Asset %i : %.2f\n", i + 1, rendit_anteil[i]);
	}

	printf("Gesamte Rendite : %.2f\n", sum(rendit_anteil, y));
}