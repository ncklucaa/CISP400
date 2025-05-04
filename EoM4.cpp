// Nick Luca
// CISP 400
// EoM 4

#include <iostream>

using namespace std;

// Task 3
double* dPiPtr()
{
	static double pi = 3.14;
	return &pi;
}

// Task 4
class Employee
{
private:
	double salary;

public:
	Employee(double s)
	{
		salary = s;
	}

	friend void showS(const Employee& e);
};

// Task 4
void showS(const Employee& e)
{
	cout << "salary: " << e.salary << '\n';
}

// Task 5
class Point
{
private:
	int x;
	int y;
};

int main()
{
	// Task 1
	int x = 42;

	cout << "x = " << x << '\n';
	cout << "address of x: " << &x << '\n';

	/*
		Task 1 (no input needed)

		Output:
		x = 42
		address of x: 0000003513AFF5A4
	*/

	// Task 2
	cout << '\n';
	int* array = new int[3];
	int temp[] = { 7, 8, 9 };

	for (int i = 0; i < 3; i++)
	{
		array[i] = temp[i];
	}

	cout << "array printing: ";

	for (int i = 0; i < 3; i++)
	{
		cout << array[i] << " ";
	}
	cout << '\n';

	delete[] array;

	/*
		Task 2 (no input needed)

		Output:
		x = 42
		address of x: 000000AF58BEFA94

		array printing: 7 8 9
	*/


	// Task 3
	cout << '\n';
	double* piPtr = dPiPtr();
	cout << "PI = " << *piPtr << '\n';
	cout << "address of PI = " << piPtr << '\n';

	/*
		Task 3 (no input needed)

		Output:
		x = 42
		address of x: 000000C5E36FFA04

		array printing: 7 8 9

		PI = 3.14
		address of PI = 00007FF7E041F048
	*/

	// Task 4
	cout << '\n';
	Employee employee(75000.0);
	showS(employee);

	/*
		Task 4 (no input needed)

		Output:
		x = 42
		address of x: 0000004308AFF984

		array printing: 7 8 9

		PI = 3.14
		address of PI = 00007FF60AA4F000

		salary: 75000
	*/

	// Task 5
	cout << '\n';


	return 0;
}