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
            #pragma omp critical
            {
                if(arr[j] > arr[j + 1]) {
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    }
}

void merge(int arr[], int l, int mid, int r) {
    int n1 = mid - l + 1, n2 = r - mid;
    int left[n1], right[n2];

    for (int i = 0; i < n1; i++)
        left[i] = arr[l + i];
    for (int i = 0; i < n2; i++)
        right[i] = arr[mid + i + 1];

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2) {
        if (left[i] <= right[j])
            arr[k++] = left[i++];
        else
            arr[k++] = right[j++];
    }

    while (i < n1)
        arr[k++] = left[i++];
    while (j < n2)
        arr[k++] = right[j++];
}

void merge_sort_sequential(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort_sequential(arr, left, mid);
        merge_sort_sequential(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void merge_sort_parallel(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        #pragma omp parallel
        {
            merge_sort_parallel(arr, left, mid);
        }
        #pragma omp parallel
        {
            merge_sort_parallel(arr, mid + 1, right);
        }
        #pragma omp critical
        {
            merge(arr, left, mid, right);
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

    cout << "Enter 1 for Bubble Sort Sequential, 2 for Bubble Sort Parallel, 3 for Merge Sort Sequential, or 4 for Merge Sort Parallel: ";
    cin >> ch;

    struct timeval start, end;
    gettimeofday(&start, NULL);

    if(ch == 1) {
        bubble_sort_sequential(arr, n);
        cout << "Bubble Sort Sequential" << endl;
    } else if(ch == 2) {
        bubble_sort_parallel(arr, n);
        cout << "Bubble Sort Parallel" << endl;
    } else if(ch == 3) {
        merge_sort_sequential(arr, 0, n - 1);
        cout << "Merge Sort Sequential" << endl;
    } else if(ch == 4) {
        merge_sort_parallel(arr, 0, n - 1);
        cout << "Merge Sort Parallel" << endl;
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