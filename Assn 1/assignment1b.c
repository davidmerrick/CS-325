/* Assignment 1 - Finding the Largest Subarray
 * Group members: David Merrick, Nick A, Taylor Friesen
 */

#include <stdlib.h>
#include <stdio.h>


//Prototypes
void close_to_zero(int *arr, int size);

//This struct contains the indices min and max to indicate the bounds of the subarray
//Also contains minimum sum
struct sum_struct{
	int min;
	int max;
	int sum;
} min_sum;

int main()
{
    int myarr[] = {536,565,-319,653,667,67,-331,297,-688,963,730,-725,298,21,797,557,286,-641,-290,-151,271,-534,730,865,986,-4,-984,762,-792,-450,428,-753,49,245,-141,-710,325,-862,294,-859,517,-911,-671,223,-577,778,916,-871,-835,541,986,593,-913,-357,-358,478,616,958,-440,-75,155,645,508,-29,-715,-275,633,-790,-441,6,98,-232,-78,-941,-67,-29,539,-791,702,-81,-477,-481,978,901,-784,563,-589,-712,-860,373,872,-315,-13,-691,-953,-602,380,834,-734,-778};
	close_to_zero(myarr, 100);
    printf("Minimum sum is %d\n", min_sum.sum);
	printf("Found between indices %d and %d\n", min_sum.min, min_sum.max);
	printf("Corresponding to %d and %d\n", myarr[min_sum.min], myarr[min_sum.max]);
	return 0;
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