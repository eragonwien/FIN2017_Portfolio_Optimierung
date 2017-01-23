#include <iostream>
#include <string>
#include <fstream>
#include "convar.h"
using namespace std;
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
					cout << endl;
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
			cout<<"Origin\n";
			showDoubleArray(arr,x,y);
			cout<<"COV Matrix\n";
			showDoubleArray(getCovMatrix(arr, x, y), y, y);
		}
		



		//End Program
		cout << "Do you want to continue? (y/n)\n";
		char end;
		cin >> end;
		if (end != 'y')break;
	}
	return 0;
}