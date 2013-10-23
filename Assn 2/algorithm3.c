/* Assignment 2 - Algorithm 3: Divide and Conquer using Enumeration for Sum of Suffices.
 * Using divide and conquer to test the last case of a suffix from the first half and a prefix from the second half
 * Group members: David Merrick, Nick A, Taylor Friesen
 */

#include <stdio.h>
#include <stdlib.h>

int *compute_sum_array(int *array, int size);
void print_array(int *array, int size);
int enumerate(int *array, int size);

int main(){
	int size = 8;
	int array[] = {1,2,3,4,5,6,7,8};
	int smallestsum = enumerate(array, size);	
	printf("Smallest sum is %d\n", smallestsum);
}

int enumerate(int *array, int size){
	int array1_size = size/2;
	int array1[array1_size];
	for(int i = 0; i < size/2; i++){
		array1[i] = array[i];
	}
	int j = 0;
	int array2_size = size - size/2;
	int array2[array2_size];
	for(int i = size/2; i < size; i++){
		array2[j] = array[i];
		j++;
	}
	
	int array2rev[array2_size];

	for(int t=1; t<=array2_size; t++){
	  array2rev[t-1] = array2[array2_size-t];
	}

	//Compute sum arrays
	int *sumarray1 = compute_sum_array(array1, array1_size);
	int *sumarray2 = compute_sum_array(array2rev, array2_size);
	
	//Find the smallest sum
	int smallestsum = sumarray1[0] + sumarray2[0];
	int tempsum;
	for(int i = 1; i < array1_size; i++){
		for(int j = 0; j < array2_size; j++){
			tempsum = sumarray1[i] + sumarray2[j];
			if(abs(tempsum) < abs(smallestsum)){
				smallestsum = tempsum;
			}
		}
	}
	return smallestsum;
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
