#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double fft(double reX[], double imX[], int N);
double window(double reX[], double imX[], int N, int M);


void main(int argc, char **argv) {
	FILE *fp;
	int i, j, k;
	int N, M=30;
	N=atof(argv[1]);
	double reX[N], imX[N];
	
	//Abrindo arquivo com os dados da curva
	fp = fopen("curva.dat", "r");
	
	if(fp == NULL) {
		puts("\nErro ao abrir o arquivo!\n");
		return;
	}
	
	//Lendo os dados do arquivo
	i=0;
	while(i!=N){
		fscanf(fp, "%lf  %lf\n", &imX[i], &reX[i]);
		i++;
	}
	fclose(fp);
	
	//Invertendo imagem
	for(i=0; i<N/2; i++)
 		imX[i]=-imX[i];
 		
 			
	//Chamar FFT aqui!!
	
	
	for(i=0; i<N/2; i++) {
		reX[i]=reX[i]/N;
		imX[i]=-imX[i]/N;
	}
	
	//Passando os dados da resposta ao Impulso no domínio do tempo
	for(i=0; i<N; i++)
		imp[i]=sqrt(reX[i]*reX[i]+imX[i]*imX[i]);
	
}
