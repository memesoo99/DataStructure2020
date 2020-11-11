#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define X 10	
#define Y 10
#define Z 10

double*** mem_alloc_3D_double() {
	double*** Arr = (double***)malloc(sizeof(double**) * X);
	for (int i = 0; i < X; i++) {
		Arr[i] = (double**)malloc(Y * sizeof(double*));
		for (int j = 0; j < Y; j++) {
			Arr[i][j] = (double*)malloc(Z * sizeof(double));
		}
	}
	if (Arr == NULL) return 0;
	return Arr;
}
double*** addition_3D(double*** a, double*** b) {
	double*** Sum = mem_alloc_3D_double();
	for (int i = 0; i < X; i++) {
		for (int j = 0; j < Y; j++) {
			for (int k = 0; k < Z; k++) {
				Sum[i][j][k] = a[i][j][k] + b[i][j][k];
			}
		}
	}
	return Sum;
}
void print_arr(double*** a) {
	for (int i = 0; i < X; i++) {
		for (int j = 0; j < Y; j++) {
			for (int k = 0; k < Z; k++) {
				printf("%.2lf ", *(*(*(a + i) + j) + k));
			}
			printf("\n");
		}
		printf("\n\n");
	}
}
void free_arr(double*** a) {
	for (int i = 0; i < X; i++)
	{
		for (int j = 0; j < Y; j++)
		{
			free(a[i][j]);
		}
		free(a[i]);
	}
	free(a);
}
int main(void) {
	double*** A = mem_alloc_3D_double();
	int cnt = 0;
	for (int i = 0; i < X; i++) {
		for (int j = 0; j < Y; j++) {
			for (int k = 0; k < Z; k++) {
				A[i][j][k] = ++cnt;
			}
		}
	}
	
	double*** B = mem_alloc_3D_double();
	for (int i = 0; i < X; i++) {
		for (int j = 0; j < Y; j++) {
			for (int k = 0; k < Z; k++) {
				B[i][j][k] = 1;
			}
		}
	}

	double*** Sum = addition_3D(A, B);
	
	print_arr(Sum);

	free_arr(A);
	free_arr(B);
	free_arr(Sum);
	
	
}