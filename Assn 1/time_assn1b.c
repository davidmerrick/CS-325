/* Assignment 1 - Finding the Largest Subarray
 * Group members: David Merrick, Nick Jordan, Taylor Friesen
 */


#include <stdlib.h>
#include <stdio.h>
#include <time.h>


//Prototypes
int create_rand();
void close_to_zero(int *arr, int size);

//This struct contains the indices min and max to indicate the bounds of the subarray
//Also contains minimum sum
struct sum_struct{
	int min;
	int max;
	int sum;
} min_sum;


int main(int argc, char *argv[])
{
	srand(time(NULL));
	clock_t start, end;
    double elapsed; 
    int input_size;
	int x;
	int *myarr;
	
	printf("Elapsed time, input size\n");
	
	for(input_size = 100; input_size <= 1000; input_size += 100){
    	//Initialize array
		myarr = (int *) malloc(input_size * sizeof(int));
    	for (x = 0; x < input_size; x++){
			myarr[x] = create_rand();
		}
    
		start = clock();
    	close_to_zero(myarr, input_size);
    	end = clock();
    	elapsed = ((double)(end-start))/CLOCKS_PER_SEC;
	
    	printf("%f, ", elapsed);
		printf("%d\n", input_size);
	}
	
	for(input_size = 2000; input_size <= 9000; input_size += 1000){
    	//Initialize array
		myarr = (int *) malloc(input_size * sizeof(int));
    	for (x = 0; x < input_size; x++){
			myarr[x] = create_rand();
		}
    
		start = clock();
    	close_to_zero(myarr, input_size);
    	end = clock();
    	elapsed = ((double)(end-start))/CLOCKS_PER_SEC;
	
    	printf("%f, ", elapsed);
		printf("%d\n", input_size);
	}
	
    return 0;
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

//this method computes pretty much every subarray individually
void close_to_zero(int *arr, int size)
{
    int temp_sum;
    int compare_sum; //variable to hold absolute value
    min_sum.sum = abs(arr[0]); //set initial value
    min_sum.min = 0;
    min_sum.max = 0;
	for(int i = 0; i < size; i++){
    	temp_sum = 0;
    	compare_sum = abs(arr[i]);
        if(compare_sum < abs(min_sum.sum)){
      		min_sum.sum = arr[i];
      		min_sum.min = i;
      		min_sum.max = i;
    	}
    	temp_sum = arr[i];
    	for(int j = i+1; j < size; j++){
      		temp_sum += arr[j];
            compare_sum = abs(temp_sum);
      		if(compare_sum < abs(min_sum.sum)){
				min_sum.sum = temp_sum;
				min_sum.min = i;
				min_sum.max = j;
      		}
    	}
    }
}