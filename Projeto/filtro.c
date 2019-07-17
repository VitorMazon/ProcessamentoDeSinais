#include <stdio.h>
#include <stdlib.h>
#include <math.h>



//===============================================
//================== FFT ========================
//===============================================

void fft(double *reX, double *imX, int N) {
	double tr, ti, sr, si, ur,ui;
	int i, j, k , m, ip, l, le, le2;
	
	m=(int)log((double)N)/log((double)2);

	j=(N/2);
	for(i=1; i<N-2; i++) {
		if(i<j) {
			tr=reX[j];
			ti=imX[j];
			reX[j]=reX[i];
			imX[j]=imX[i];
			reX[i]=tr;
			imX[i]=ti;    
		}

		k=(N/2);

		while(k<=j){ 
			j = j-k;
			k = k/2;
		}
		j=j+k;
	}
	
	for(l=1; l<=m; l++) { 
		le=(int)pow(l,2);
		le2=(int) (int)le/(int)2;
		ur=1.0;
		ui=0.0;
		sr=cos(M_PI/(float) le2);
		si=(-1)*sin(M_PI/(float) le2);

		for(j=1; j<=le2; j++) {
			for(i=(j-1); i<=N-1; i=i+le) {
				ip = i+le2;
				tr = (reX[ip]*ur) - (imX[ip]*ui);
				ti = (reX[ip]*ui) + (imX[ip]*ur);
				reX[ip] = reX[i] - tr;
				imX[ip] = imX[i] - ti;
				reX[i] = reX[i] + tr;
				imX[i] = imX[i] + ti;
			}  
			tr = ur;
			ur = (tr*sr) - (ui*si);
			ui = (tr*si) + (ui*sr);
		}
    	}
	
	return;
}


//==================================================
//================ JANELAMENTO =====================
//==================================================

void window(double *reX, double *imX, int N, int M) {
	int i, j, k, ip, ind;
	double *t;
	
	t=(double*) malloc((N)*sizeof(double));

	for(i=0;i<N;i++) {
		ind=i+ M/2;
		
		if(ind>N-1)
			ind=ind-N;
		
		t[ind]=reX[i];
		reX[i]=0.;	
		imX[i]=0.;
	}
	
	for(i=0;i<N;i++)
		reX[i]=t[i];
	
	for(i=0;i<N;i++){
		if(i<=M)
			reX[i]=reX[i]*(0.54 - 0.46*cos((2.*M_PI*i)/M));
		else{
			reX[i]=0.;
			imX[i]=0.;	
		}		
	}
}

//================================================
//================== MAIN ========================
//================================================

void main(int argc, char **argv) {
	FILE *curva, *imp, *jan;
	int i, j, k;
	int N=2048, M;
	M=30;
	double *reX, *imX, *t, *magX;
	
	//Abrindo arquivo com os dados da curva
	curva = fopen("curva.dat", "r");
	imp = fopen("impulso.dat", "w");
	jan = fopen("janelamento.dat", "w");
	
	if(curva == NULL) {
		puts("\nErro ao abrir o arquivo!\n");
		return;
	}
	
	reX=(double*) malloc((N)*sizeof(double));
	imX=(double*) malloc((N)*sizeof(double));
	magX=(double*) malloc((N)*sizeof(double));
	t=(double*) malloc((N)*sizeof(double));

	//Lendo os dados do arquivo
	i=0;
	while( i!=N/2 ){
		fscanf(curva, "%lf  %lf\n", &imX[i], &reX[i]);
		i++;
	}
	fclose(curva);
	
	//Invertendo imagem
	for(i=0; i<N; i++)
 		imX[i]=-imX[i];
 		
 	
	//Chamando a FFT
	fft(reX, imX, N);
	
	//Dividindo o domínio por N, e invertendo o imX
	for(i=0; i<(N/2); i++) {
		reX[i]=reX[i]/N;
		imX[i]=-imX[i]/N;
	}
	
	//Passando os dados da resposta ao Impulso no domínio do tempo
	for(i=0; i<N; i++)
		fprintf(imp, "%d  %12.6lf\n", i, sqrt(reX[i]*reX[i]+imX[i]*imX[i]));
	
	//Janelamento
	window(reX, imX, N, M);
	for(i=0;i<(N/2);i++)
               fprintf(jan, "%d \t %lf\n", i, sqrt(reX[i]*reX[i]+ imX[i]*imX[i]));
        
	//Chamando novamente a FFT
	fft(reX, imX, N);
	
	//Multiplicar por 2 para voltar ao valor de entrada
	for(i=0;i<(N/2);i++) {
		magX[i]=2*sqrt(reX[i]*reX[i]+ imX[i]*imX[i]);
		t[i]=(float)i/(float)N;
	}

	for(i=0;i<(N/2);i++)
		printf("%lf \t %lf\n", t[i], magX[i]);
	
	return;	
}

