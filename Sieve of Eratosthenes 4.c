#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define bits 8
#define tam (1000000000/bits)/2

static char primos[tam];
char bit[8];	/* = {128, 64, 32, 16, 8, 4, 2, 1};*/

/*
Para bit = 1 com OU  | Para bit = 0 com E
0 - 1                | 0 - 254
1 - 2                | 1 - 253
2 - 4                | 2 - 251
3 - 8                | 3 - 247
4 - 16               | 4 - 239
5 - 32               | 5 - 223
6 - 64               | 6 - 191
7 - 128              | 7 - 127

----------------------------------------------

Dividido por 8 = >> 3 (shift 3 pra direita)
Mod 8 = & 7 (pega os 3 ultimos bits);
*/

void exectime(int time_s){
	clock_t time_e = clock();
	double execution = (double) (time_e - time_s) / CLOCKS_PER_SEC;
	printf("\tTempo de execucao: %f\n", execution);
}

void setTrue(){
	long long i;	
	
	primos[0]&=~bit[0]; 
	primos[0]|=bit[1];
	primos[0]|=bit[2];
	primos[0]|=bit[3];
	primos[0]&=~bit[4];
	primos[0]|=bit[5];
	primos[0]|=bit[6];
	primos[0]&=~bit[7];
	
	for(i=1; i<tam; i++)
		primos[i] = ~(primos[i] & 0);
}

void discoverPrimes(){
	long long int i, j, dozes=24, somadozes = 36, vezespassou =2;

	for(i=4; i<tam*bits; i+=3)
		primos[i >> 3] &= ~bit[i & 7];
	
	for(i=12; i<tam*bits; i+=5)
		primos[i >> 3] &= ~bit[i & 7];
	
	for(i=24; i<tam*bits; i+=7)
		primos[i >> 3] &= ~bit[i & 7];
	
	for(i=5; i*i<tam*bits; i+=2){
		//printf("Para i = %d, ", (i*2)+1);
		if(primos[i >> 3] & bit[i & 7]){
			//printf("entrou!", (i*2)+1);
			for(j=dozes+somadozes; j<tam*bits; j+=(i+i+1)){
				primos[j >> 3] &= ~bit[j & 7];
				//printf("Primos[%d], bit[%d], significando o numero %d\n", j >> 3, j&7, (j*2)+1);
			}
		}
		//printf("\n");
		i += 1;
		dozes += 12*vezespassou;
		
		//printf("Para i = %d, ", (i*2)+1);
		if(primos[i >> 3] & bit[i & 7]){
			//printf("entrou!", (i*2)+1);
			for(j=dozes+somadozes; j<tam*8; j+=(i+i+1)){
				primos[j >> 3] &= ~bit[j & 7];
				//printf("Primos[%d], bit[%d], significando o numero %d\n", j >> 3, j&7, (j*2)+1);
			}
		}
		dozes += somadozes;
		somadozes+=24;
		vezespassou++;
		//printf("\n");
	}
	
}

void numberofPrimes(long long int *nprimos){
	long long int i;

	for(i=2; i<tam*bits; i+=3){
		if(primos[i >> 3] & bit[i & 7])
			(*nprimos)++;
		if(primos[(i + 1) >> 3] & bit[(i + 1) & 7])
			(*nprimos)++;
	}
}

void primeVector(long long int *primoss, long long int nprimos){
	long long int i, k=2;
	
	primoss[0] = 2;
	primoss[1] = 3;
	for(i=2; i<tam*bits; i+=3){
		if(primos[i >> 3] & bit[i & 7])
			primoss[k++]= (i*2)+1;
		if(primos[(i + 1) >> 3] & bit[(i + 1) & 7])
			primoss[k++]= ((i+1)*2)+1;
	}
	
}

void printPrimos(long long int *primoss, long long int nprimos){
	long long int i;

	for(i=0; i<nprimos; i++)
		printf("%lld ", primoss[i]);
	
}


void main(){

	long long int i, j, k, nprimos=2;
	
	clock_t time_s = clock();
	
	bit[bits-1] = 1;
	for(i=bits-2; i>=0; i--)
		bit[i] = bit[i+1]<<1;
		
	/*######################################################################################*/
	
	setTrue();
	printf("Vetor setado para true.");
	exectime(time_s);
	
	/*######################################################################################*/
	
	discoverPrimes();
	printf("Primos descobertos.");
	exectime(time_s);
	
	/*######################################################################################*/
	
	numberofPrimes(&nprimos);
	printf("O numero de numeros primos e %lld.", nprimos);
	exectime(time_s);
	
	/*######################################################################################*/
	
	long long *primoss = malloc(nprimos * sizeof(*primoss));
	primeVector(primoss, nprimos);
	printf("Maior primo em %ld: %lld", tam*bits*2, primoss[nprimos-1]);
	
	exectime(time_s);

	//printPrimos(primoss, nprimos);
	
}
