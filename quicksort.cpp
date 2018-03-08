#include <bits/stdc++.h>
using namespace std;

void swap (int* arr, int idx1, int idx2) {
	if (idx1 != idx2) {
		int temp = arr[idx1];
		arr[idx1] = arr[idx2];
		arr[idx2] = temp;
	}
}

int partition (int* arr, int start, int end) {
	int pivot = arr[end];
	int i = -1;
	for (int j=0; j<end; j++) {
		if (arr[j] <= pivot) {
			i++;
			swap(arr, i, j);
		}
	}
	swap (arr, i+1, end);
	return (i+1);
}

void quicksort (int* arr, int start, int end) {
	if (start < end) {
		int pivot_idx = partition (arr, start, end);
		quicksort (arr, start, pivot_idx-1);
		quicksort (arr, pivot_idx+1, end);
	}
}

int main() {
	int arr[] = {89, 34, 78, 23, 66, -90, 12, 36};
	// int arr[] = {45, 45, 45, 45, 45, 45};
	int arr_size = sizeof (arr) / sizeof (arr[0]);
	quicksort (arr, 0, arr_size - 1);
	for (auto x : arr) {
		cout << x << " ";
	}
	cout << endl;
}