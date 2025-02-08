// Nick Luca
// EoM1
// Prof. Fowler CISP 400

#include <iostream>

using namespace std;

void randomFunc(int* a, int* b)
{
	int tempIntPtr = *a;
	*a = *b;
	*b = tempIntPtr;
}

int main()
{
	int x = 5;
	int* ptr = &x;

	cout << x << " and " << *ptr << '\n';

	/*
		Task 1 (no input needed)

		Output:
		5 and 5
	*/

	int arr[5] = {};
	int* ptrArr = arr;

	cout << "\narr elements: ";
	for (int i = 0; i < 5; i++)
	{
		cout << *(ptrArr + i) << " ";
	}

	/*
	
		Task 2 (no input needed)

		Output:
		5 and 5

		array elements: 0 0 0 0 0 

	*/

	int y = 6;
	int z = 7;

	int* ptr2 = &y;
	int* ptr3 = &z;

	cout << "\n\nptr2 points at: " << *ptr2 << " and ptr3 points at: " << *ptr3 << '\n';

	if (ptr2 == ptr3)
	{
		cout << "\nboth pointers are pointing to the same memory location\n";
	}
	else
	{
		cout << "\nboth pointers are not pointing to the same memory location\n";
	}

	/*

		Task 3 (no input needed)

		Output:
		5 and 5

		array elements: 11 22 33 44 55

		ptr2 points at: 6 and ptr3 points at: 7

		both pointers are not pointing to the same memory location

	*/

	randomFunc(ptr2, ptr3);
	cout << "\nswapping ptrs...\n";
	cout << "ptr2 points at: " << *ptr2 << " and ptr3 points at: " << *ptr3 << '\n';

	/*
	
		Task 4: (no input needed)

		Output:
		5 and 5

		array elements: 11 22 33 44 55

		ptr2 points at: 6 and ptr3 points at: 7

		both pointers are not pointing to the same memory location

		swapping ptrs...
		ptr2 points at: 7 and ptr3 points at: 6
	
	*/

	int arr2[3] = { 112, 113, 114 };

	cout << "\nshowing arr2 elements with a for-loop: ";
	for (int i = 0; i < 3; i++)
	{
		cout << arr2[i] << " ";
	}


	cout << "\n\nnow showing arr2 elements with a while-loop: ";
	int k = 0;
	while (k < 3)
	{
		cout << arr2[k] << " ";
		k++;
	}
	cout << '\n';

	/*
		Task 5 (no input needed)

		Output:
		5 and 5

		arr elements: 0 0 0 0 0

		ptr2 points at: 6 and ptr3 points at: 7

		both pointers are not pointing to the same memory location

		swapping ptrs...
		ptr2 points at: 7 and ptr3 points at: 6

		showing arr2 elements with a for-loop: 112 113 114

		now showing arr2 elements with a while-loop: 112 113 114
	
	*/

	int arr3D[3][3] = {};

	int nums = 1;
	for (int i = 0; i < 3; i++)
	{
		for (int k = 0; k < 3; k++)
		{
			arr3D[i][k] = nums++;
		}
	}

	cout << "\nmatrix format display: \n";
	for (int i = 0; i < 3; i++)
	{
		for (int k = 0; k < 3; k++)
		{
			cout << arr3D[i][k] << " ";
		}
	}

	/*
	
		Task 6 (no input needed)

		Output:
		5 and 5

		arr elements: 0 0 0 0 0

		ptr2 points at: 6 and ptr3 points at: 7

		both pointers are not pointing to the same memory location

		swapping ptrs...
		ptr2 points at: 7 and ptr3 points at: 6

		showing arr2 elements with a for-loop: 112 113 114

		now showing arr2 elements with a while-loop: 112 113 114

		matrix format display:
		1 2 3 4 5 6 7 8 9
	
	
	*/

	// unfortunately i ran out of time because i am very nitpicky when it comes to the output and making sure it looks readable


	return 0;
}