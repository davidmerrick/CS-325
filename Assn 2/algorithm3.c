/* Assignment 2 - Algorithm 3: Divide and Conquer using Enumeration for Sum of Suffices.
 * Using divide and conquer to test the last case of a suffix from the first half and a prefix from the second half
 * Group members: David Merrick, Nick A, Taylor Friesen
 */

#include <stdio.h>
#include <stdlib.h>

int *compute_sum_array(int *array, int size);
void print_array(int *array, int size);

int main()
{
	int array1_size = 4;
	int array2_size = 4;
	
	int array1[] = {1,-3,5,-7};
	int array2[] = {-2,4,-6,8};
	int array2rev[array2_size];


	for(int t=1; t<=array2_size; t++){
	  array2rev[t-1] = array2[array2_size-t];
	  printf("%d\n",array2rev[t-1]);
	}

	//Compute sum arrays
	int *sumarray1 = compute_sum_array(array1, array1_size);
	int *sumarray2 = compute_sum_array(array2, array2_size);
	
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
