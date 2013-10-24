/* Assignment 2 - Algorithm 3: Divide and Conquer using Enumeration for Sum of Suffices.
 * Using divide and conquer to test the last case of a suffix from the first half and a prefix from the second half
 * Group members: David Merrick, Nick A, Taylor Friesen
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *compute_sum_array(int *array, int size);
void print_array(int *array, int size);
int enumerate(int *array, int size);
int recurse(int *array, int size);
int lesser_of(int a, int b);
int create_rand();

int main(){
	srand(time(NULL));
	//	clock_t start, end;
	struct timespec start, finish;
	double elapsed; 
	int input_size;
	int x;
	int *myarr;
	int total = 0;
	printf("Elapsed time, input size\n");

	for(input_size = 10000; input_size <= 200000; input_size += 10000){
	            //Initialize array
	                myarr = (int *) malloc(input_size * sizeof(int));
	            for (x = 0; x < input_size; x++){
	                        myarr[x] = create_rand();
	                }

		    // start = clock();
		    clock_gettime(CLOCK_MONOTONIC, &start);
		    int smallestsum = recurse(myarr, input_size);	
		    // end = clock();
		    clock_gettime(CLOCK_MONOTONIC, &finish);
		    total += smallestsum;
		    //elapsed = ((double)(end-start))/CLOCKS_PER_SEC;
		    elapsed = (finish.tv_sec - start.tv_sec);
		    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

	            printf("%f, ", elapsed);
	                printf("%d\n", input_size);
	        }
	
	//	printf("printing this to get the compiler to not optimize it out %d\n", total);
}

//returns random positive or negative integer
int create_rand()
{
    int sign = rand() % 2;
        int num = rand() % 999;
        //Make sure array never has 0 in it
        while(num == 0){ 
            num = rand() % 999;
        }
        if (sign == 0) num = 0 - num;
    return num;
}

int recurse(int *array, int size){
	//Returns the smallest sum recursively
	if(size == 1){
		return array[0];
	} else if(size == 2){
		return lesser_of(array[0], array[1]);
	} else if(size == 3 || size == 4){
		return enumerate(array, size);
	} else {
		//Split the array
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
		return lesser_of(recurse(array1, array1_size), recurse(array2, array2_size));
	}
}

int lesser_of(int a, int b){
	if(a < b){
		return a;
	} else {
		return b;
	}
	
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
