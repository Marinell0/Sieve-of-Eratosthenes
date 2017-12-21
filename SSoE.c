#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define tam 10000
#define segment 262144

void exectime(int time_s){
	clock_t time_e = clock();
	double execution = (double) (time_e - time_s) / CLOCKS_PER_SEC;
	printf("\tTempo de execucao: %f\n", execution);
}

int nprimos=0, totalprimos=0;


int *SimpleSieve(int firstpart){
	int i, j, k;
	clock_t time_s = clock();
	char primos[firstpart];
	
	
	for(i=0; i<firstpart; i++){
		primos[i]=255;
	}
	
	
	for(i=2; i*i<firstpart; i++){
		if(primos[i]){
			for(j=(i*i); j<firstpart; j+=i){
				primos[j]=0;
			}
		}
	}
	
	for(i=2; i<tam; i++){
		if(primos[i]){
			nprimos++;
		}
	}
	
	int *primoss = (int *) malloc(nprimos * sizeof(int));
	
	j=0;
	for(i=2; i<tam; i++)
		if(primos[i])
			primoss[j++]=i;

	return(primoss);
}

void main(){
	int i, j;
	int firstpart = floor(sqrt(tam)+1);
	int low = firstpart;
	int high = firstpart*2;
	
	int *primoss = SimpleSieve(firstpart);
	
	clock_t time_s = clock();
	totalprimos = nprimos;
	
	printf("%d ", primoss[0]);
	while(low < tam){
		char SegmentedPrimes[firstpart+1];
		
		for(i=0; i<firstpart+1; i++)
			SegmentedPrimes[i] = 255;
		
		for(i=0; i<nprimos; i++){
			int lowLimit = floor(low/primoss[i])*primoss[i];
			
			if(lowLimit < low) lowLimit += primoss[i];
			
			for(j=lowLimit; j<high; j+=primoss[i])
				SegmentedPrimes[j-low] = 0;
			
		}
		for(i=low; i<high; i++)
			if(SegmentedPrimes[i-low])
				totalprimos++;
			
		low += segment;
		high += segment*2;
		if(high >= tam) high = tam;
		
	}
	
	printf("O numero de numeros primos e %d.", nprimos);
	exectime(time_s);
	
	printf("Maior primo em %d: %d", tam, primoss[nprimos-1]);
	exectime(time_s);
	
}