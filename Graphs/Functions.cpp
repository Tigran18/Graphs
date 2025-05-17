#include "Functions.h"

void sort(int* t, int k) {
	bool swapped;
	for (int i = 0; i < k - 1; i++) {
		swapped = false;
		for (int j = 0; j < k - i - 1; j++) {
			if (t[j] > t[j + 1]) {
				int temp = t[j];
				t[j] = t[j + 1];
				t[j + 1] = temp;
				swapped = true;
			}
		}
		if (!swapped) {
			break;
		}
	}
}

bool Duplicate(int a[], int size, int num) {
	for (int i = 0; i < size; ++i) {
		if (num == a[i]) {
			return true;
		}
	}
	return false;
}

bool AllZeroes(int** arr, int size) {
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			if (arr[i][j] != 0) {
				return false;
			}
		}
	}
	return true;
}

void MultiplyMatrices(int** a, int** b, int** result, int size) {
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			result[i][j] = 0;
			for (int k = 0; k < size; ++k) {
				result[i][j] += a[i][k] * b[k][j];
			}
		}
	}
}

void NewMatrix(int count, int** new_array, int** result, int size) {
	int i, j;
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			new_array[i][j + count * size] = result[i][j];
		}
	}
}
