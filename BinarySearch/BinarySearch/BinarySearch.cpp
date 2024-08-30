#include <iostream>
using namespace std;

int binarySearch(int array[], int size, int searchValue) {
    int low = 0;
    int high = size - 1;

    while (low <= high) {
        int mid = (low + high) / 2;

        if (searchValue == array[mid]) {
            return mid;
        }
        else if (searchValue > array[mid]) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    return -1;
}

void sortArray(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int smallestIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[smallestIndex]) {
                smallestIndex = j;
            }
        }

        if (smallestIndex != i) {
            int temp = arr[smallestIndex];
            arr[smallestIndex] = arr[i];
            arr[i] = temp;
        }
    }
}

int main() {
    int size;
    cout << "Enter the number of elements in the array: ";
    cin >> size;

    int* array = new int[size];

    cout << "Enter the elements of the array: " << endl;
    for (int i = 0; i < size; i++) {
        cin >> array[i];
    }

    sortArray(array, size);

    cout << "Sorted array: ";
    for (int i = 0; i < size; i++) {
        cout << array[i] << " ";
    }
    cout << endl;

    int userValue;
    cout << "Enter an integer to search for: ";
    cin >> userValue;

    int result = binarySearch(array, size, userValue);

    if (result >= 0) {
        cout << "The number " << array[result] << " was found at index " << result << endl;
    }
    else {
        cout << "The number " << userValue << " was not found." << endl;
    }

    delete[] array;

    return 0;
}
