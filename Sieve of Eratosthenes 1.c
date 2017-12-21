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
	int i, j, k, nprimos=0;
	static bool primos[tam];
	clock_t time_s = clock();

	
	for(i=0; i<tam; i++){
		primos[i]=true;
	}
	
	printf("Vetor setado para true.");
	exectime(time_s);
	
	for(i=2; i*i<tam; i++){
		if(primos[i]==true){
			for(j=(i*i); j<tam; j+=i){
				primos[j]=false;
			}
		}
	}
	
	printf("Primos descobertos.");
	exectime(time_s);
	
	for(i=2; i<tam; i++){
		if(primos[i]==true){
			nprimos++;
		}
	}
	
	printf("O numero de numeros primos e %d.", nprimos);
	exectime(time_s);
	
	int *primoss = (int *) malloc(nprimos * sizeof(int));
	
	j=0;
	for(i=2; i<tam; i++){
		if(primos[i]==true){
			primoss[j]=i;
			j++;
		}
	}
	printf("Maior primo em %d: %d", tam, primoss[nprimos-1]);
	
	exectime(time_s);
}
