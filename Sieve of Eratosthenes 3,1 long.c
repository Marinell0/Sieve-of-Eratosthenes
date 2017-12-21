#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#define bits 32
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
8 - 256
9 - 512
10 - 1024
11 - 2048
12 - 4096
13 - 8192
14 - 16384
15 - 32768
16 - 65536
17 - 131072
18 - 262144
19 - 524288
20 - 1048576
21 - 2097152
22 - 4194304
23 - 8388608
24 - 

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
	unsigned int bit[32];
	int i, j, k, nprimos=0;
	static unsigned int primos[tam];
	clock_t time_s = clock();
	
	bit[bits-1] = 1;
	for(i=bits-2; i>=0; i--)
		bit[i] = bit[i+1]<<1;
	
	primos[0] = 890523909; // primos ate 31;
	
	for(i=1; i<tam; i++)
		primos[i] = ~(primos[i] & 0);
	
	printf("Vetor setado para true.");
	exectime(time_s);
	
	for(i=4; i<tam*bits; i+=2){
		int indiceI = i >> 5;
		char indiceBit = i & 31;
		primos[indiceI] &= ~bit[indiceBit];
	}
	
	for(i=9; i<tam*bits; i+=6){
		int indiceI = i >> 5;
		char indiceBit = i & 31;
		primos[indiceI] &= ~bit[indiceBit];
	}
	
/*
	for(i=0; i*i*64<tam*8; i++){
		for(j=0; j<bits; j++){
			if(primos[i] & bit[j]){
				//printf("Entrou para %d*8 + %d\n", i, j);
				 int aux = i*8 + j;
				 int aux2;
				for(aux2 = (aux*aux); aux2 < tam*8; aux2+=aux+aux){
					int indiceI = aux2 >> 3;
					int indiceBit = aux2 % 8;
					primos[indiceI] &= ~bit[indiceBit];
					//printf("aux = %d e aux2 = %d, IndiceI = %d e IndiceBit = %d\n", aux, aux2, indiceI, indiceBit);
				}
			}
		}
	}
*/

	for(i=6; i*i<tam*bits; i+=6){
		int stindiceI = (i - 1) >> 5;
		char stindiceBit = (i - 1) & 31;
		int ndindiceI = (i + 1) >> 5;
		char ndindiceBit = (i + 1) & 31;
		if(primos[stindiceI] & bit[stindiceBit]){
			for(j=((i-1)*(i-1)); j<tam*bits; j+=(i+i-2)){
				int indiceI = j >> 5;
				char indiceBit = j & 31;
				primos[indiceI] &= ~bit[indiceBit];
			}
		}

		if(primos[ndindiceI] & bit[ndindiceBit]){
			for(j=((i+1)*(i+1)); j<tam*bits; j+=(i+i+2)){
				int indiceI = j >> 5;
				char indiceBit = j & 31;
				primos[indiceI] &= ~bit[indiceBit];
			}
		}
	}
	
	printf("Primos descobertos.");
	exectime(time_s);
	
	nprimos=2;
	
	/*
	for(i=0; i<tam; i++){
		for(j=0; j<bits; j++){
			if(primos[i] & bit[j]){
				//printf("Entrou para %d*8 + %d\n", i, j);
				nprimos++;
			}
		}
	}
	*/
	
	for(i=6; i<tam*bits; i+=6){
		int stindiceI = (i - 1) >> 5;
		char stindiceBit = (i - 1) & 31;
		int ndindiceI = (i + 1) >> 5;
		char ndindiceBit = (i + 1) & 31;
		if(primos[stindiceI] & bit[stindiceBit])
			nprimos++;
		if(primos[ndindiceI] & bit[ndindiceBit])
			nprimos++;
	}

	
	printf("O numero de numeros primos e %d.", nprimos);
	exectime(time_s);
	
	int *primoss = malloc(nprimos * sizeof(*primoss));
	/*
	k=0;
	for(i=0; i<tam; i++){
		for(j=0; j<bits; j++){
			if(primos[i] & bit[j])
				primoss[k++] = i*8+j;
		}
	}
	*/
	
	k=2;
	primoss[0] = 2;
	primoss[1] = 3;
	for(i=6; i<tam*bits; i+=6){
		int stindiceI = (i - 1) >> 5;
		char stindiceBit = (i - 1) & 31;
		int ndindiceI = (i + 1) >> 5;
		char ndindiceBit = (i + 1) & 31;
		if(primos[stindiceI] & bit[stindiceBit])
			primoss[k++]= i-1;
		if(primos[ndindiceI] & bit[ndindiceBit])
			primoss[k++]= i+1;
	}
	printf("Maior primo em %d: %d", tam*bits, primoss[nprimos-1]);
	
	exectime(time_s);

	
/*
	for(i=0; i<nprimos; i++)
		printf("%d ", primoss[i]);
	
	*/
}