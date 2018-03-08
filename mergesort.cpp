#include <bits/stdc++.h>
using namespace std;

void merge (int* arr, int start, int mid, int end) {
	int left_size = mid - start + 1;
	int right_size = end - mid;
	int* left = new int [left_size];
	int* right = new int [right_size];
	for (int x = 0; x < left_size; x++) {
		left[x] = arr[start + x];
	}
	for (int x = 0; x < right_size; x++) {
		right[x] = arr[mid+1+x];
	}
	int i = 0, j = 0, k = start;
	while (k < end + 1) {
		while (i < left_size && j < right_size) {
			if (left[i] < right[j]) {
				arr[k++] = left[i++];
			} else {
				arr[k++] = right[j++];
			}
		}
		while (i < left_size) {
			arr[k++] = left[i++];
		}
		while (j < right_size) {
			arr[k++] = right[j++];
		}
	}
}

void mergesort (int* arr, int start, int end) {
	if (start < end) {
		int mid = (start + end) / 2;
		mergesort (arr, start, mid);
		mergesort (arr, mid+1, end);
		merge (arr, start, mid, end);
	}
}

int main() {
	int arr[] = {89, 34, 78, 23, 66, -90, 12, 36};
	// int arr[] = {45, 34, 45, 34, 45, 34, 45, 34, 45};
	int arr_size = sizeof (arr) / sizeof (arr[0]);
	mergesort (arr, 0, arr_size-1);
	for (auto x : arr) {
		cout << x << " ";
	}
	cout << endl;
}