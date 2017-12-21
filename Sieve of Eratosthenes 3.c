#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define bits 8
#define tam 1000000000/bits

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



void main(){
	char bit[8];/* = {128, 64, 32, 16, 8, 4, 2, 1};*/
	long long i, j, k, nprimos=0;
	static char primos[tam];
	clock_t time_s = clock();
	
	bit[bits-1] = 1;
	for(i=bits-2; i>=0; i--)
		bit[i] = bit[i+1]<<1;
	
	primos[0]&=~bit[0]; 
	primos[0]&=~bit[1];
	primos[0]|=bit[2];
	primos[0]|=bit[3];
	primos[0]&=~bit[4];
	primos[0]|=bit[5];
	primos[0]&=~bit[6];
	primos[0]|=bit[7];
	
	for(i=1; i<tam; i++)
		primos[i] = ~(primos[i] & 0);
	
	printf("Vetor setado para true.");
	exectime(time_s);
	

	for(i=9; i<tam*8; i+=6)
		primos[i >> 3] &= ~bit[i & 7];

	for(i=5; i*i<tam*8; i+=4){
		
		if(primos[i >> 3] & bit[i & 7])
			for(j=(i*i); j<tam*8; j+=(i+i))
				primos[j >> 3] &= ~bit[j & 7];
			
		i += 2;
			
		if(primos[i >> 3] & bit[i & 7])
			for(j=(i*i); j<tam*8; j+=(i+i))
				primos[j >> 3] &= ~bit[j & 7];
		
	}
	
	printf("Primos descobertos.");
	exectime(time_s);
	
	nprimos=2;
	
	for(i=6; i<tam*8; i+=6){
		if(primos[(i - 1) >> 3] & bit[(i - 1) & 7])
			nprimos++;
		if(primos[(i + 1) >> 3] & bit[(i + 1) & 7])
			nprimos++;
	}

	
	printf("O numero de numeros primos e %d.", nprimos);
	exectime(time_s);
	
	int *primoss = malloc(nprimos * sizeof(*primoss));
	
	k=2;
	primoss[0] = 2;
	primoss[1] = 3;
	for(i=6; i<tam*8; i+=6){
		if(primos[(i - 1) >> 3] & bit[(i - 1) & 7])
			primoss[k++]= i-1;
		if(primos[(i + 1) >> 3] & bit[(i + 1) & 7])
			primoss[k++]= i+1;
	}
	
	printf("Maior primo em %d: %d", tam*8, primoss[nprimos-1]);
	
	exectime(time_s);

	
/*
	for(i=0; i<nprimos; i++)
		printf("%d ", primoss[i]);
	
	*/
}