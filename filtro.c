#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define N 2048

void FFT(double *ReX, double *ImX)
{	double  tr, ti, ur, ui, sr, si;
	int i, j, k, m, l, le, le2, ip;

	m=(int)(log(N)/log(2));
	j=N/2;
	
	for(i=1;i<N-2;i++)
	{	if(i<j)
		{	tr=ReX[j];
			ti=ImX[j];
			ReX[j]=ReX[i];
			ImX[j]=ImX[i];
			ReX[i]=tr;
			ImX[i]=ti;		
		}
		k=N/2; 
		while(k<=j)
		{	j=j-k;
			k=k/2;
		}
		j=j+k;
	}

	for(l=1;l<=m;l++)
	{	le=(int)pow(2,l);
		le2=le/2;
		ur=1.;
		ui=0.;
		sr=cos(M_PI/(float)le2);
		si=(-1)*sin(M_PI/(float)le2);
		for(j=1;j<=le2;j++)
		{	for(i=j-1;i<=N-1;i=i+le)
			{	ip=i+le2;	
				tr=ReX[ip]*ur-ImX[ip]*ui;
				ti=ReX[ip]*ui+ImX[ip]*ur;
				ReX[ip]=ReX[i]-tr;
				ImX[ip]=ImX[i]-ti;
				ReX[i]=ReX[i]+tr;
				ImX[i]=ImX[i]+ti;		
			}	
			tr=ur;
			ur=tr*sr-ui*si;
			ui=tr*si+ui*sr;
		}
	}
}
void Janelamento(double *ReX, double *ImX, int kernel)
{	int i, j, k, ip, ind;
	double *t;
	
	t=(double*)malloc((N)*sizeof(double));

	for(i=0;i<N;i++)
	{	ind=i+ kernel/2;
		if(ind>N-1)
			ind=ind-N;
		t[ind]=ReX[i];
		ReX[i]=0.;	
		ImX[i]=0.;
		
	}	
	for(i=0;i<N;i++)
	{	ReX[i]=t[i];
	}
	
	for(i=0;i<N;i++)
	{	if(i<=kernel)
			ReX[i]=ReX[i]*(0.54 - 0.46*cos((2.*M_PI*i)/kernel));
		else{	
		ReX[i]=0.;
		ImX[i]=0.;	
		}
		
	}
}

void main()
{	double *ReX, *ImX, *t, *magX;
	int i, j, kernel;
	FILE *in, *out, *fp, *fr, *ft, *fd;
		
	in=fopen("dados.dat", "r"); //entrada de dados
	out=fopen("fft.dat", "w"); //saída de dados fft
	fp=fopen("kernel200.dat","w"); //Janelamento 
	fd=fopen("mag200.dat", "w"); //Magnitude

	//alocação dinâmica de memória
	ReX=(double*)malloc((N)*sizeof(double));
	ImX=(double*)malloc((N)*sizeof(double));
	magX=(double*)malloc((N)*sizeof(double));
	t=(double*)malloc((N)*sizeof(double));

	for(i=0;i<N;i++)
        {       ReX[i]=0.;
        }


	//preenchendo os vetores ReX e ImY com os valores do gráfico
	for(i=0;i<(N/2);i++)
		fscanf(in, "%lf %lf", &ImX[i], &ReX[i]);	
	

	//Invertendo o ImX
	for(i=0;i<N;i++)
	{	ImX[i]=0.;
	}	

	//Chamando a FFT
	FFT(ReX, ImX);

	//Dividindo o domínio por N, e invertendo ImX
	for(i=0;i<N;i++)
	{	ReX[i]=ReX[i]/N;
		ImX[i]=-ImX[i]/N;
	}

	//Passando os dados da resposta ao Impulso no domínio do tempo
	for(i=0;i<N;i++)
		fprintf(out, "%d \t %lf\n", i, sqrt(ReX[i]*ReX[i]+ ImX[i]*ImX[i]));

	//Chamando o Janelamento para kernel=30
	Janelamento(ReX, ImX, 200);
	for(i=0;i<(N/2);i++)
               fprintf(fp, "%d \t %lf\n", i, sqrt(ReX[i]*ReX[i]+ ImX[i]*ImX[i]));
        
	//Chamando novamente a FFT
	FFT(ReX, ImX);
	
	//Para retornar ao valor original, é necessário multiplicar a magnitude por um fator de 2
	for(i=0;i<(N/2);i++)
	{	magX[i]=2*sqrt(ReX[i]*ReX[i]+ ImX[i]*ImX[i]);
		t[i]=(float)i/(float)N;
	}

	for(i=0;i<(N/2);i++)
		fprintf(fd, "%lf \t %lf\n", t[i], magX[i]);
	

}
