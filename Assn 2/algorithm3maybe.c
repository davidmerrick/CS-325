/* Assignment 2 - Algorithm 3: Divide and Conquer using Enumeration for Sum of Suffices.
 * Using divide and conquer to test the last case of a suffix from the first half and a prefix from the second half
 * Group members: David Merrick, Nick Jordan, Taylor Friesen
 */

#include <stdio.h>
#include <stdlib.h>

int *compute_sum_array(int *array, int size);
void print_array(int *array, int size);
int enumerate(int *array, int *array2,  int, int);
int recurse(int *array, int size);
int lesser_of(int a, int b);

int close_to_zero(int *arr, int size);

//This struct contains the indices min and max to indicate the bounds of the subarray
//Also contains minimum sum
/*struct sum_struct{
	int min;
	int max;
	int sum;
	} min_sum;*/

int main(){

	int size = 8;
	int array[] = {1,-2,-4,3,6,-5,1,4};

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


	int sum1 = close_to_zero(array1, array1_size);
	int sum2 = close_to_zero(array2, array2_size);
	int sum_mid = enumerate(array1, array2rev, array1_size, array2_size);

	printf("smallest sum from first half: %d\n", sum1);
	printf("smallest sum from second half: %d\n", sum2);
	printf("smallest sum from middle: %d\n", sum_mid);
 
	//compare the 3

	//printf("Smallest sum is:\n%d\n", smallestsum);
}


int enumerate(int *array1, int *array2, int array1_size, int array2_size){

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


//this method computes pretty much every subarray individually
int close_to_zero(int *arr, int size)
{
    int sum, min, max;
    int temp_sum;
    int compare_sum; //variable to hold absolute value
    sum = abs(arr[0]); //set initial value
    min = 0;
    max = 0;
	for(int i = 0; i < size; i++){
    	temp_sum = 0;
    	compare_sum = abs(arr[i]);
        if(compare_sum < abs(sum)){
      		sum = arr[i];
      		min = i;
      		max = i;
    	}
    	temp_sum = arr[i];
    	for(int j = i+1; j < size; j++){
      		temp_sum += arr[j];
            compare_sum = abs(temp_sum);
      		if(compare_sum < abs(sum)){
				sum = temp_sum;
				min = i;
				max = j;
      		}
    	}
    }
	return sum;
}
