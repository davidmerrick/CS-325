#include <stdio.h>
#include <stdlib.h>

#define REALLY_BIG 10e8

void print_array(int *array);
int* change(int *denom_array, int k, int n, int *s);

int main(){
	int denom_array[] = {0, 1, 5}; //Array of possible denominations
	int k = 2; //Number of possible denominations (not including 0)
	int n = 5; //Number for which change is to be made
	int s[5];
	int *change_array = change(denom_array, k, n, s);
	
	printf("Change array:\n");	
	print_array(change_array);
	
	printf("\nS array:\n");	
	print_array(s);
	
	return 0;
}

int* change(int *denom_array, int k, int n, int *s){
	int *c = malloc(n * sizeof(int)); //Array to hold number of coins for optimal solution
	c[0] = 0;
	
	//At worst, it will take n number of coins/bills, so make that the base solution
	int min = n;
	int coin;
	for(int p = 2; p < n; p++){
		for(int i = 1; i < k; i++){
			if(denom_array[i] <= p){
				if(1 + c[p-denom_array[i]] < min){
					min = 1 + c[p - denom_array[i]];
					coin = i;
				}
			}
		}
		c[p] = min;
		s[p] = coin;
	}
	return c;
}

void print_array(int *array){
        for(int i = 0; i < sizeof(array); i++){
                printf("%d\n", array[i]);
        }
}