#include <iostream>
#include <omp.h>
#include <sys/time.h>

using namespace std;

void bubble_sort_sequential(int arr[], int n) {
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void bubble_sort_parallel(int arr[], int n) {
    for(int i = 0; i < n - 1; i++) {
        #pragma omp parallel for
        for(int j = 0; j < n - i - 1; j++) {
            if(arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n, ch;
    cout << "Enter array length: ";
    cin >> n;
    int arr[n];

    cout << "Enter array elements: ";
    for(int i = 0; i < n; i++)
        cin >> arr[i];

    cout << "Unsorted Array: ";
    for(int i = 0; i < n; i++)
        cout << arr[i] << ",";
    cout << endl << endl;

    cout << "Enter 1 for Bubble Sort Sequential, 2 for Bubble Sort Parallel: ";
    cin >> ch;

    struct timeval start, end;
    gettimeofday(&start, NULL);

    if(ch == 1) {
        bubble_sort_sequential(arr, n);
        cout << "Bubble Sort Sequential" << endl;
    } else if(ch == 2) {
        bubble_sort_parallel(arr, n);
        cout << "Bubble Sort Parallel" << endl;
    } else {
        cout << "Invalid Choice." << endl;
        return 0;
    }

    gettimeofday(&end, NULL);

    cout << "Sorted Array: ";
    for(int i = 0; i < n; i++)
        cout << arr[i] << ",";
    cout << endl << endl;

    cout << "Time: " << (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_usec - start.tv_usec) * 1000 << " ns" << endl;
    cout << endl;

    return 0;
}
