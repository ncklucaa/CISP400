// Nick Luca
// EoM2
// Prof. Fowler CISP 400

#include <iostream>
#include <string>

using namespace std;

// Task 3
int* allocateInt()
{
	int* ptr = new int;
	*ptr = 66;
	return ptr;
}

//Task 4
void swapInts(int* val1, int* val2)
{
	int temp = *val1;
	*val1 = *val2;
	*val2 = temp;
}

// Task 5
struct Student
{
	string name;
	int age;
};

// Task 6
class Rectangle
{
private:
	int width;
	int height;

public:
	Rectangle(int w, int h)
	{
		width = w;
		height = h;
	}

	int area() const
	{
		return width * height;
	}
};

int main()
{
	int x = 55;
	int* ptr = &x;

	cout << "Direct access: " << x << '\n';
	cout << "Pointer Dereferencing: " << *ptr << '\n';

	/*
		Task 1 (no input needed)

		Output:

		Direct access: 55
		Pointer Dereferencing: 55
	*/
	
	int arr[5] = { 10, 20, 30, 40, 50 };
	int* ptrArr = arr;

	cout << '\n';

	for (int i = 0; i < 5; i++)
	{
		cout << *(ptrArr + i) << " ";
	}

	/*
		Task 2

		Output:

		Direct access: 55
		Pointer Dereferencing: 55

		10 20 30 40 50
	
	*/

	cout << '\n';

	int* dynamicInt = allocateInt();

	cout << '\n';

	cout << "Allocated value: " << *dynamicInt << '\n';

	/*
		Task 3

		Output:

		Direct access: 55
		Pointer Dereferencing: 55

		10 20 30 40 50

		Allocated Value: 66
	
	*/
	cout << '\n';
	int y = 33;
	int z = 99;

	cout << "Before Swap: " << "y = " << y << " and " << "z = " << z << '\n';
	swapInts(&y, &z);
	cout << "After Swap: " << " y = " << y << " and " << "z = " << z << '\n';

	/*
		Task 4

		Output:

		Direct access: 55
		Pointer Dereferencing: 55

		10 20 30 40 50

		Allocated value: 66

		Before Swap: y = 33 and z = 99
		After Swap:  y = 99 and z = 33
	*/

	cout << '\n';

	Student* stuPtr = new Student;
	stuPtr->name = "Nick";
	stuPtr->age = 21;
	cout << "Student Name: " << stuPtr->name << '\n';
	cout << "Student Age:  " << stuPtr->age << '\n';
	delete stuPtr;

	/*
		Task 5

		Output:

		Direct access: 55
		Pointer Dereferencing: 55

		10 20 30 40 50

		Allocated value: 66

		Before Swap: y = 33 and z = 99
		After Swap:  y = 99 and z = 33

		Student Name: Nick
		Student Age:  21
	*/
	cout << '\n';
	Rectangle* recPtr = new Rectangle(50, 100);
	cout << "Rectangle Area: " << recPtr->area() << '\n';
	delete recPtr;

	/*
		Task 6

		Output:

		Direct access: 55
		Pointer Dereferencing: 55

		10 20 30 40 50

		Allocated value: 66

		Before Swap: y = 33 and z = 99
		After Swap:  y = 99 and z = 33

		Student Name: Nick
		Student Age:  21

		Rectangle Area: 5000
	*/

	cout << '\n';
	int point1 = 69;
	int point2 = 96;
	int* ptr1 = &point1;
	int* ptr2 = &point2;

	if (ptr1 == ptr2)
	{
		cout << "Both pointing to same memory location\n";
	}
	else
	{
		cout << "Both pointing to different memory location\n";
	}

	/*
		Task 7

		Output:

		Direct access: 55
		Pointer Dereferencing: 55

		10 20 30 40 50

		Allocated value: 66

		Before Swap: y = 33 and z = 99
		After Swap:  y = 99 and z = 33

		Student Name: Nick
		Student Age:  21

		Rectangle Area: 5000

		Both pointing to different memory location
	*/

	cout << '\n';
	char stLit[] = "LeBron is the GOAT";
	char* ptrC = stLit;

	while (*ptrC)
	{
		cout << *ptrC << " ";
		ptrC++;
	}
	cout << '\n';

	/*
		Task 8

		Output:

		Direct access: 55
		Pointer Dereferencing: 55

		10 20 30 40 50

		Allocated value: 66

		Before Swap: y = 33 and z = 99
		After Swap:  y = 99 and z = 33

		Student Name: Nick
		Student Age:  21

		Rectangle Area: 5000

		Both pointing to different memory location

		L e B r o n   i s   t h e   G O A T
	*/

	// Did not have enough time to start and finish Task 9

	return 0;
}