#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double fft(double reX[], double imX[], int N);
double window(double reX[], double imX[], int N, int kernel);

void main() {
	int i, j, k;
	int N=1024, int kernel=500;
	double reX[N], imX[N];
}
