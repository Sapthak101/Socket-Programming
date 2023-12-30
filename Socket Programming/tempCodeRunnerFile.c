#include <stdio.h>

void merge(int a[], int beg, int mid, int end)
{
	int i, j, k;
	int n1 = mid - beg + 1;
	int n2 = end - mid;

	int Larr[n1], Rarr[n2];

	for (i = 0; i < n1; i++)
		Larr[i] = a[beg + i];
	for (j = 0; j < n2; j++)
		Rarr[j] = a[mid + 1 + j];

	i = 0;
	j = 0;
	k = beg;
	while (i < n1 && j < n2) {
		if (Larr[i] <= Rarr[j]) {
			a[k] = Larr[i];
			i++;
		}
		else {
			a[k] = Rarr[j];
			j++;
		}
		k++;
	}

	while (i < n1) {
		a[k] = Larr[i];
		i++;
		k++;
	}

	while (j < n2) {
		a[k] = Rarr[j];
		j++;
		k++;
	}
}

void mergeSort(int a[], int beg, int end)
{
	if (beg < end) {
		int mid = (beg+end) / 2;

		mergeSort(a, beg, mid);
		mergeSort(a, mid + 1, end);

		merge(a, beg, mid, end);
	}
}

void printArray(int A[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		printf("%d ", A[i]);
	printf("\n");
}

int main()
{
	int arr[] = { 12, 11, 13, 5, 6, 7 };
	int arr_size = sizeof(arr) / sizeof(arr[0]);

	printf("Given array is \n");
	printArray(arr, arr_size);

	mergeSort(arr, 0, arr_size - 1);

	printf("\nSorted array is \n");
	printArray(arr, arr_size);
	return 0;
}
