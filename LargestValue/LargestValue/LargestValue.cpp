#include <iostream>
using namespace std;

void moveLargestValue(int arr[], int n) {
    int largeIndex = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] > arr[largeIndex]) {
            largeIndex = i;
        }
    }

    if (largeIndex != n - 1) {
        int temp = arr[largeIndex];
        arr[largeIndex] = arr[n - 1];
        arr[n - 1] = temp;
    }
}

int main() {
    int n;

    cout << "Input the size of your array: ";
    cin >> n;

    int arr[n];

    cout << "Input the elements of your array: ";

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    moveLargestValue(arr, n);

    cout << "Resulted array: ";

    for (int i = 0; i < n; i++) {
        cout >> arr[i] << " ";
    }
    cout << endl;
}