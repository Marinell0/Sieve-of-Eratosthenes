#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#define bits 8
#define tam 1000000000/bits
#include <pthread.h>

/*
1	10									4	 
2	100									25	 
3	1,000								168	 
4	10,000								1,229	 
5	100,000								9,592	 
6	1,000,000							78,498	 
7	10,000,000							664,579	 
8	100,000,000							5,761,455	 
9	1,000,000,000						50,847,534	 
10	10,000,000,000						455,052,511	 
11	100,000,000,000						4,118,054,813	 
12	1,000,000,000,000					37,607,912,018	 
13	10,000,000,000,000					346,065,536,839	 
14	100,000,000,000,000					3,204,941,750,802	
15	1,000,000,000,000,000				29,844,570,422,669	
16	10,000,000,000,000,000				279,238,341,033,925	
17	100,000,000,000,000,000				2,623,557,157,654,233	
18	1,000,000,000,000,000,000			24,739,954,287,740,860	
19	10,000,000,000,000,000,000			234,057,667,276,344,607	 
20	100,000,000,000,000,000,000			2,220,819,602,560,918,840	 
21	1,000,000,000,000,000,000,000		21,127,269,486,018,731,928	 
22	10,000,000,000,000,000,000,000		201,467,286,689,315,906,290	 
23	100,000,000,000,000,000,000,000		1,925,320,391,606,803,968,923	 
24	1,000,000,000,000,000,000,000,000	18,435,599,767,349,200,867,866	
25	10,000,000,000,000,000,000,000,000	176,846,309,399,143,769,411,680	 
*/
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

static char primos[tam];
char bit[8];/* = {128, 64, 32, 16, 8, 4, 2, 1};*/
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

void setTrue(){
	long i;
	
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
	
}


void* setFalse(void *a){
	long j;
	long i = *((long*) a);
	//printf("%d ", i);
	for(j=(i*i); j<tam*bits; j+=i+i)
		primos[j >> 3] &= ~bit[j & 7];
	
}


void discoverPrimes(pthread_t *tid){
	long i, j;

	for(i=9; i<tam*bits; i+=6)
		primos[i >> 3] &= ~bit[i & 7];
	

	for(i=5; i*i<(tam*bits); i+=4){
		if(primos[i >> 3] & bit[i & 7]){
			long aux1 = i;
			pthread_create(&tid[0], NULL, *setFalse, (void *) &aux1);
		}
		
		i += 2;
		
		if(primos[i >> 3] & bit[i & 7]){
			long aux2 = i;
			pthread_create(&tid[1], NULL, *setFalse, (void *) &aux2);
		}
		
		i += 4;
		
		if(primos[i >> 3] & bit[i & 7]){
			long aux3 = i;
			pthread_create(&tid[2], NULL, *setFalse, (void *) &aux3);
		}
		
		i += 2;
		
		if(primos[i >> 3] & bit[i & 7]){
			long aux4 = i;
			pthread_create(&tid[3], NULL, *setFalse, (void *) &aux4);
		}
		pthread_join(tid[0], NULL);
		pthread_join(tid[1], NULL);
		pthread_join(tid[2], NULL);
		pthread_join(tid[3], NULL);
	}
	
}

void numberOfPrimes(long *nprimos){
	long i;
	for(i=6; i<tam*bits; i+=6){
		if(primos[(i - 1) >> 3] & bit[(i - 1) & 7])
			(*nprimos)++;
		if(primos[(i + 1) >> 3] & bit[(i + 1) & 7])
			(*nprimos)++;
	}
	
}

void primeNumbers(long *primoss, long nprimos){
	long i, k=2;

	primoss[0] = 2;
	primoss[1] = 3;
	for(i=6; i<tam*bits; i+=6){
		if(primos[(i - 1) >> 3] & bit[(i - 1) & 7])
			primoss[k++]= i-1;
		if(primos[(i + 1) >> 3] & bit[(i + 1) & 7])
			primoss[k++]= i+1;
	}
	
	
}

void printPrimes(long *primoss, long nprimos){
	//FILE *arq;
	//arq = fopen("R:\\primes10m.txt", "w+");
	long i;
	char j;
	for(i=0; i<nprimos; i+=10){
		for(j=0; j<10; j++)
			printf("%d\t", primoss[i+j]);
		
		printf("\n");
	}
	
	
}

void exectime(int time_s){
	clock_t time_e = clock();
	double execution = (double) (time_e - time_s) / CLOCKS_PER_SEC;
	printf("\tTempo de execucao: %f\n", execution);
}

void main(){
	pthread_t tid[4];
	long i, j, k, nprimos=2;
	clock_t time_s = clock();
	
	
	bit[bits-1] = 1;
	for(i=bits-2; i>=0; i--)
		bit[i] = bit[i+1]<<1;
	
	setTrue();
	printf("Vetor setado para true.");
	exectime(time_s);
	
	discoverPrimes(tid);
	printf("Primos descobertos.");
	exectime(time_s);

	numberOfPrimes(&nprimos);
	printf("O numero de numeros primos e %li.", nprimos);
	exectime(time_s);
	
	long *primoss = malloc(nprimos * sizeof(*primoss));
	
	primeNumbers(primoss, nprimos);
	
	
	printf("Maior primo em %d: %li", tam*bits, primoss[nprimos-1]);
	exectime(time_s);
	
	//printPrimes(primoss, nprimos);
	
	
}
