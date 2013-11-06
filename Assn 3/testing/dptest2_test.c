#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


void changedp(int* O, int *V, int C, int size);

void main(){

  int C = 40;
  int size = 4;
  int V[] = {1,5,10,25,50};
  int O[] = {0,0,0,0};

  for (int C = 2000; C<=2300; C++){
   	changedp(O,V,C, size);
	}
}

void changedp(int* O, int* V, int C, int size){
	int *T = malloc(C * sizeof(int)); //Array to hold number of coins for optimal solution
	int *S = malloc(C * sizeof(int)); 

	T[0] = 0;
	
	int coin;

	for(int p = 1; p <= C; p++){ 
	  int min = INT_MAX; //pretend this is infinity
		for(int i = 0; i <= size; i++){
			if(V[i] <= p){
				if(1 + T[p-V[i]] < min){
					min = 1 + T[p - V[i]];
					coin = i;
				}
			}
		}
		T[p] = min; // minimum number of coins to make change for p
		S[p] = coin;
	}

	
	printf("Total needed for %d: %d\n\n", C, T[C]);
      
	while (C > 0){
	        O[S[C]]++;
		C = C - V[S[C]];
	}

	for(int i = 0; i <= size; i++){
	        printf("%d\n", O[i]);
        }
}

int count_array(int *array){
	int sum = 0;
	for(int i = 0; i < sizeof(array); i++){
		
	}
}
