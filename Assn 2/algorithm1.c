/* Assignment 2 - Algorithm 1: Enumeration for Sum of Suffices.
 * Loop over every pair s and t and compute the sum, keeping the sum closest to zero
 * Group members: David Merrick, Nick A, Taylor Friesen
 */

#include <stdio.h>
#include <stdlib.h>

int *compute_sum_array(int *array, int size);
void print_array(int *array, int size);

int main()
{
	int array1_size = 4;
	int array2_size = 5;
	
	int array1[] = {-3,-1,0,0};
	int array2[] = {0,0,1,3,0};

	//Compute sum arrays
	int *sumarray1 = compute_sum_array(array1, array1_size);
	int *sumarray2 = compute_sum_array(array2, array2_size);
	
	//Find the smallest sum
	int smallestsum = sumarray1[0] + sumarray2[0];
	int tempsum;
	int j = 0; //index for sumarray 2
	for(int i = 1; i < array1_size; i++){
		tempsum = sumarray1[i] + sumarray2[j];
		if(abs(tempsum) < abs(smallestsum)){
			smallestsum = tempsum;
		}
		j++;
	}
	
	printf("Smallest sum is %d\n", smallestsum);
}

int *compute_sum_array(int *array, int size){
	int *sumarray = malloc(size * sizeof(int));
	int j = 0; //index for sumarray
	int tempsum = 0;
	for (int i=size-1; i >= 0; i--){
		tempsum += array[i];
		sumarray[j] = tempsum;
		j++;
	}
	return sumarray;
}

void print_array(int *array, int size){
	for(int i = 0; i < size; i++){
		printf("%d\n", array[i]);
	}
}