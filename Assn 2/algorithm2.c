/* Assignment 2 - Algorithm 1: Enumeration for Sum of Suffices.
 * Loop over every pair s and t and compute the sum, keeping the sum closest to zero
 * Group members: David Merrick, Nick A, Taylor Friesen
 */

#include <stdio.h>
#include <stdlib.h>

int *compute_sum_array(int *array, int size);
void print_array(int *array, int size);
void merge(int numbers[], int temp[], int left, int mid, int right);
void m_sort(int numbers[], int temp[], int left, int right);
void mergeSort(int numbers[], int temp[], int array_size);


int array1_size = 4;
int array2_size = 4;

int main(){	
	int array1[] = {3,5,7,9};
	int array2[] = {2,4,6,8};

	//Compute sum arrays
	//Dump positive array 1 sums into first half of sumarray
	int sumarray[array1_size + array2_size];
	int j = 0; //index for sumarray
	int tempsum = 0;
	for (int i=array1_size-1; i >= 0; i--){
		tempsum += array1[i];
		sumarray[j] = tempsum;
		j++;
	}
	tempsum = 0;
	//Dump negative array 2 sums into second half of sumarray
	for (int i=array2_size-1; i >= 0; i--){
		tempsum += array2[i];
		sumarray[j] = -tempsum;
		j++;
	}
	
	int totalsize = array1_size + array2_size;
	int temp[totalsize];
	
	mergeSort(sumarray, temp, totalsize);
	int smallestdiff = sumarray[0] - sumarray[1];
	int tempdiff;
	for(int i=1; i < (totalsize-1); i++){
		tempdiff = sumarray[i] - sumarray[i+1];
		if(abs(tempdiff) < abs(smallestdiff)){
			smallestdiff = tempdiff;
		}
	}

	printf("Smallest sum is %d\n", smallestdiff);
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

int *compute_negative_sum_array(int *array, int size){
	int *sumarray = malloc(size * sizeof(int));
	int j = 0; //index for sumarray
	int tempsum = 0;
	for (int i=size-1; i >= 0; i--){
		tempsum += array[i];
		sumarray[j] = -tempsum;
		j++;
	}
	return sumarray;
}

void mergeSort(int numbers[], int temp[], int array_size){
	m_sort(numbers, temp, 0, array_size - 1);
}

void m_sort(int numbers[], int temp[], int left, int right){
	  int mid;

	  if (right > left){
		mid = (right + left) / 2;
	    m_sort(numbers, temp, left, mid);
	    m_sort(numbers, temp, mid+1, right);

	    merge(numbers, temp, left, mid+1, right);
	  }
}

void merge(int numbers[], int temp[], int left, int mid, int right){
	  int i, left_end, num_elements, tmp_pos;

	  left_end = mid - 1;
	  tmp_pos = left;
	  num_elements = right - left + 1;

	  while ((left <= left_end) && (mid <= right))
	  {
	    if (numbers[left] <= numbers[mid])
	    {
	      temp[tmp_pos] = numbers[left];
	      tmp_pos = tmp_pos + 1;
	      left = left +1;
	    }
	    else
	    {
	      temp[tmp_pos] = numbers[mid];
	      tmp_pos = tmp_pos + 1;
	      mid = mid + 1;
	    }
	  }

	  while (left <= left_end){
	    temp[tmp_pos] = numbers[left];
	    left = left + 1;
	    tmp_pos = tmp_pos + 1;
	  }
	
	  while (mid <= right){
	    temp[tmp_pos] = numbers[mid];
	    mid = mid + 1;
	    tmp_pos = tmp_pos + 1;
	  }

	  for (i=0; i <= num_elements; i++){
	  	numbers[right] = temp[right];
	    right = right - 1;
	  }
}
	
void print_array(int *array, int size){
	for(int i = 0; i < size; i++){
		printf("%d\n", array[i]);
	}
}