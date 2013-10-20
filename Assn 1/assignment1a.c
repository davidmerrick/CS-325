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
    int myarr[] = {-487,-625,-72,-311,819,70,560,5,-643,138,564,117,-762,-952,-972,629,-622,238,-888,258,-858,-584,66,558,-446,146,132,-229,-131,322,-858,197,-538,-240,-834,671,-588,-148,-472,-502,-452,98,-950,371,-473,707,-593,363,896,275,-230,-309,-22,875,899,292,-914,-787,435,-477,-505,166,65,-29,339,977,-350,-883,427,-513,-685,341,-524,752,-515,-946,-167,644,-692,-155,-1,124,-536,743,-745,192,21,161,640,604,702,-504,-936,704,361,-843,927,247,863,-526};
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
    	for(int j = i+1; j < size; j++){
	    	temp_sum = arr[i];
            for(int k = i+1; k <= j; k++){
                temp_sum += arr[k];
            }
            compare_sum = abs(temp_sum);
            if(compare_sum < abs(min_sum.sum)){
                min_sum.sum = temp_sum;
                min_sum.min = i;
                min_sum.max = j;
            }
        }
    }
}
