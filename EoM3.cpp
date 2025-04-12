// Nick Luca
// CISP 400
// EoM 3

#include <iostream>
#include <memory>
#include <cmath>

using namespace std;

// Task 2
struct Book { string title; int year; };

// Task 4
class Circle
{
public:
	double radius;

	double area() const
	{
		const double PI = 3.14;
		return PI * pow(radius, 2);
	}
};

// Task 5
/*
	I wanted to finish Task 5 but ran out of time because got sort of confused with the overload +
*/

int main()
{
	// Task 1
	int num1 = 55;
	int num2 = 66;

	int* const cPtrToInt = &num1;
	*cPtrToInt = 77;

	const int* ptrToC = &num2;
	ptrToC = &num1;

	cout << "Constant pointer to an integer = " << *cPtrToInt << '\n';
	cout << "Pointer to a constant integer = " << *ptrToC << '\n';

	/*
		Task 1 (no input needed)

		Output:

		Constant pointer to an integer = 77
		Pointer to a constant integer = 77
	*/

	// Task 2
	Book* book = new Book;
	book->title = "Lebron is the GOAT";
	book->year = 2025;

	cout << "\n";
	cout << "Book title: " << book->title << '\n';
	cout << "Pulished year: " << book->year << '\n';

	//delete book;

	/*
		Task 2 (no input needed)

		Output:

		Constant pointer to an integer = 77
		Pointer to a constant integer = 77

		Book title: Lebron is the GOAT
		Pulished year: 2025
	*/

	// Task 3
	/*
		Off-topic hopefully you read this prof, but wouldn't it be better if we use auto for a task like this?
		Not specifically this one but for future references for example.
	*/

	unique_ptr<int> sInt = make_unique<int>(88);

	cout << '\n';
	cout << "Smart pointer integer = " << *sInt << '\n';

	/*
		Task 3 (no input needed)

		Output:

		Constant pointer to an integer = 77
		Pointer to a constant integer = 77

		Book title: Lebron is the GOAT
		Pulished year: 2025

		Smart pointer integer = 88
	*/

	// Task 4
	Circle circle[3];

	circle[0].radius = 1.0;
	circle[1].radius = 2.0;
	circle[2].radius = 3.0;

	cout << '\n';
	cout << "circle 1 areas = " << circle[0].area() << '\n';
	cout << "circle 2 areas = " << circle[1].area() << '\n';
	cout << "circle 3 areas = " << circle[2].area() << '\n';

	/*
		Task 4 (no input needed)

		Output:

		Constant pointer to an integer = 77
		Pointer to a constant integer = 77

		Book title: Lebron is the GOAT
		Pulished year: 2025

		Smart pointer integer = 88

		circle 1 areas = 3.14
		circle 2 areas = 12.56
		circle 3 areas = 28.26
	*/

	return 0;
}