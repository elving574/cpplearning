#include <iostream>
using namespace std;

void sortArray(int arr[], int n, int value, int &index) {
    for (int i = 0; i < n - 1; i++) {
        int largestIndex = 0;
        for (int j = 1; j < n - i; j++) {
            if (arr[j] > arr[largestIndex]) {
                largestIndex = j;
            }
        }

        if (largestIndex != n - i - 1) {
            int temp = arr[largestIndex];
            arr[largestIndex] = arr[n - i - 1];
            arr[n - i - 1] = temp;
        }

        if (arr[n - i - 1] == value) {
            index = n - i - 1;
        }
    }
}

int findValue(int* arr, int size, int value) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == value) {
            return i;
        }
    }
    return -1;
}

int main() {
    int size;
    int value;
    
    cout << "Enter the size of the array: ";
    cin >> size;

    int* arr = new int[size];
    cout << "Enter the elements of the array: ";
    for (int i = 0; i < size; i++) {
        cin >> arr[i];
    }

    cout << "Enter the value to find: ";
    cin >> value;

    int index = -1;
    sortArray(arr, size, value, index);

    if (index != -1) {
        cout << "Value found at index: " << index << endl;
    }
    else {
        cout << "Value not found." << endl;
    }

    cout << "Sorted array: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    delete[] arr;
}