#include <iostream>
#include <string>
#include <fstream>
#include "convar.h"
#include "optimize.h"
using namespace std;
double* getVarianz_array(double* gewicht_array, double** covmatrix, int x, int y);
int main() {
	while (true)
	{
		//Start Program
		cout << "Program Menu:\n";
		cout << "( 1 ) to create new serie of test files\n";
		cout << "( 2 ) to open a existing test file\n";
		cout << "( 3 ) Exit\n";
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
		// Write Serie of Files
		if (param == 1)
		{
			// Getting Parameter
			try
			{
				cout << "\nHow many Files ?  ";
				cin >> y;
				cout << "\nHow many Input per Array ?   ";
				cin >> x;
			}
			catch (const std::exception&)
			{
				cout << "Wrong Input Parameter. Using Default Parameter\n";
				cout << " 1 File of 5 Inputs\n";
				x = 5;
				y = 1;
			}
			// Creating file
			for (int i = 0; i < y; i++)
			{

				cout << "Name of " << i + 1 << ". File ?   ";
				string filename;
				cin >> filename;
				ofstream data;

				/* Length of array*/
				
				data.open(filename);
				data << x << "\n";
				for (int j = 0; j < x; j++)
				{
					double input;
					cout << "Input for " << j << " row : ";
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
				cout << "File " << filename << " successfully created\n";
			}
		}
		// Read
		else if (param == 2)
		{
			try
			{
				cout << "\nHow many Files ?  ";
				cin >> y;
			}
			catch (const std::exception&)
			{
				cout << "Wrong Input Parameter. Using Default Parameter\n";
				y = 5;
			}
			arr = new double*[y];
			// Reading Loop
			for (int i = 0; i < y; i++)
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
				data >> x;
				arr[i] = new double[x];
				for (int j = 0; j < x; j++)
				{
					data >> arr[i][j];
				}
				cout << "Go Next File...\n";
			}
			
			cout << "Rendite Table\n";
			showDoubleArray(arr, x, y);
			cout << "COV Matrix\n";
			double** covmatrix = getCovMatrix(arr, x, y);
			showDoubleArray(covmatrix, y, y);
			cout << endl;
			
			
			while (true)
			{
				int option;
				cout << "(1) Maximal Rendit \noder\n(2) Minimale Risiko\noder\n(3) Gewicht eingeben \n(4) Exit? :";
				try
				{
					cin >> option;
					cout << endl;
				}
				catch (const std::exception&)
				{
					cout << "\nWrong Input Parameter. Using Default Parameter (3)\n";
					option = 1;
				}
				if (option == 1)
				{
					try
					{
						cout << "MAX RENDIT\n";
						cout << "max Varianz ? ";
						int maxVar;
						cin >> maxVar;
						cout << "Continue with new OPTION ? (y/n)\n";
						char c;
						cin >> c;
						if (c != 'y')break;
					}
					catch (const std::exception&)
					{
						cout << "Invalid Input!\n";
						continue;
					}
					
				}
				else if (option == 2)
				{
					try
					{
						cout << "MIN RISIKO\n";
						cout << "min Gewinn ? ";
						int minGewinn;
						cin >> minGewinn;
						cout << "Continue with new OPTION ? (y/n)\n";
						char c;
						cin >> c;
						if (c != 'y')break;
					}
					catch (const std::exception&)
					{
						cout << "Invalid Input!\n";
						continue;
					}
					
				}
				else if (option == 3)
				{
					try
					{
						cout << "WEIGHT INPUT\n";
						double* gewicht_array = new double[y];
						for (int i = 0; i < y; i++)
						{
							cout << "Weight of Asset " << i << " : ";
							double input;
							cin >> input;
							gewicht_array[i] = input * 0.01;
						}
						//cout << "RENDIT\n";
						//showArray(getRenditArray(arr, x, y), y);
						cout << "Gesamt Rendit : " << getGesamtRendit(gewicht_array, getRenditArray(arr, x, y), y)<<" %\n";
						//cout << "VARIANZ\n";
						//showArray(getVarianz_array(gewicht_array, covmatrix, x, y), y);
						cout << "Gesamt Varianz : " << sum(getVarianz_array(gewicht_array, covmatrix, x, y), y)<<" %\n";

						cout << "Continue with new OPTION ? (y/n)\n";
						char c;
						cin >> c;
						if (c != 'y')break;
					}
					catch (const std::exception&)
					{
						cout << "Invalid Input\n";
						continue;
					}
				}
				else if (option == 4)
				{
					break;
				}
				else
				{
					cout << "Invalid Input.Try again!\n";
				}
			}
		}
		else if (param == 3) break;
		//End Program
		cout << "Do you want to continue? (y/n)\n";
		char end;
		cin >> end;
		if (end != 'y')break;
	}
	return 0;
}
double* getVarianz_array(double* gewicht_array, double** covmatrix, int x, int y)
{
	double* varianz_array = new double[y];
	for (int i = 0; i < y; i++)
	{
		varianz_array[i] = gewicht_array[i] * summproduct(gewicht_array, covmatrix[i], y);
	}
	return varianz_array;
}