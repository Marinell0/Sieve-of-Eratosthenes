#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#define tam 1000000000

void exectime(int time_s){
	clock_t time_e = clock();
	double execution = (double) (time_e - time_s) / CLOCKS_PER_SEC;
	printf("\tTempo de execucao: %f\n", execution);
}

void main(){
	int i, j, k, nprimos=2;
	static bool primos[tam];
	clock_t time_s = clock();
	
	primos[2]=true;
	primos[3]=true;
	
	for(i=4; i<tam; i+=2)
		primos[i]=false;
	
	for(i=5; i<tam; i+=2)
		primos[i]=true;
	
	
	printf("Vetor setado para true.");
	exectime(time_s);
	
	/*
	for(j=4; j<tam; j+=2)
		primos[j] = false;
	*/
	
	for(j=9; j<tam; j+=6)
		primos[j] = false;
	
	for(i=6; i*i<=tam; i+=6){
		if(primos[i-1]){
			for(j=((i-1)*(i-1)); j<tam; j+=(i+i-2))
				primos[j]=false;
		}
		if(primos[i+1]){
			for(j=((i+1)*(i+1)); j<tam; j+=(i+i+2))
				primos[j]=false;
		}
	}
	
	printf("Primos descobertos.");
	exectime(time_s);
	
	for(i=6; i<tam; i+=6){
		if(primos[i-1])
			nprimos++;
		if(primos[i+1])
			nprimos++;
	}
	
	printf("O numero de numeros primos e %d.", nprimos);
	exectime(time_s);
	
	int *primoss = (int *) malloc(nprimos * sizeof(int));
	
	j=2;
	primoss[0] = 2;
	primoss[1] = 3;
	for(i=6; i<tam; i+=6){
		if(primos[i-1])
			primoss[j++]=i-1;
		if(primos[i+1])
			primoss[j++]=i+1;
	}
	printf("Maior primo em %d: %d", tam, primoss[nprimos-1]);
	
	exectime(time_s);

	/*

	for(i=0; i<nprimos; i++)
		printf("%d ", primoss[i]);
	*/
	
}
