#include <iostream>
#include <vector>



// Three types of paramaters
// Passing Parameter by Value
// Passing pointer to somthing
// Passing by refernce
void GetUserInputCStyle(char*& arr, int* length_ptr) {  // by pointer, the content of the pointer is modifiable

	*length_ptr = 0;
	std::cin >> *length_ptr;

	//int* ptr_to_length = &length;

	arr = new char[*length_ptr];

	for (int i = 0; i < *length_ptr; i++) {

		char ch;
		std::cin >> ch;

		arr[i] = ch;
	}

}
void GetUserInputCPPStyle(char*& arr_ref, int& length_ref) { // by ref - the content is modifiable

	length_ref = 0;
	std::cin >> length_ref;

	arr_ref = new char[length_ref];

	for (int i = 0; i < length_ref; i++) {

		char ch;
		std::cin >> ch;

		arr_ref[i] = ch;
	}

}
void ReverseArray(char* arr, int length) {

	for (int i = 0; i < length / 2; i++) {
		char temp = arr[i];
		arr[i] = arr[length - 1 - i];
		arr[length - 1 - i] = temp;
	}
}


void PrintResult(char* arr, int length) {

	for (int i = 0; i < length; i++) {
		std::cout << arr[i];
	}
}

int main()
{
	int length = 0;
	char* arr = nullptr;

	// GetUserInputCStyle(arr, &length);
	GetUserInputCPPStyle(arr, length);
	ReverseArray(arr, length);
	PrintResult(arr, length);
}