/* Assignment 2 - Algorithm 1: Enumeration for Sum of Suffices.
 * Loop over every pair s and t and compute the sum, keeping the sum closest to zero
 * Group members: David Merrick, Nick A, Taylor Friesen
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct arraymeta{
	int value;
	int parent_array;
	int position; //Position in parent array
} arraymeta;

typedef struct arraydiff{
	int value;
	int lower_bound;
	int upper_bound;
} arraydiff;

int *compute_sum_array(int *array, int size);
void print_array(int *array, int size);
void merge(arraymeta numbers[], arraymeta temp[], int left, int mid, int right);
void m_sort(arraymeta numbers[], arraymeta temp[], int left, int right);
void mergeSort(arraymeta numbers[], arraymeta temp[], int array_size);

int array1_size = 4;
int array2_size = 4;

int main(){	
	int array1[] = {-3,2,-1,-3};
	int array2[] = {1,2,3,3};

	int totalsize = array1_size + array2_size;

	//Compute sum arrays
	//Dump positive array 1 sums into first half of sumarray
	arraymeta *sumarray = malloc(totalsize * sizeof(arraymeta));
	int j = 0; //index for sumarray
	int tempsum = 0;
	for (int i=array1_size-1; i >= 0; i--){
		tempsum += array1[i];
		sumarray[j].value = tempsum;
		sumarray[j].parent_array = 1;
		sumarray[j].position = i;
		j++;
	}
	tempsum = 0;
	//Dump negative array 2 sums into second half of sumarray
	for (int i=array2_size-1; i >= 0; i--){
		tempsum += array2[i];
		sumarray[j].value = -tempsum;
		sumarray[j].parent_array = 2;
		sumarray[j].position = i;
		j++;
	}
	
	arraymeta temp[totalsize];
	
	mergeSort(sumarray, temp, totalsize);
	
	arraydiff smallestdiff, tempdiff;
	
	//Initial case
	int i = 0;
	while(sumarray[i].parent_array == sumarray[i+1].parent_array){
		i++;
	}
	if(sumarray[i].parent_array != sumarray[i+1].parent_array){
		smallestdiff.value = abs(sumarray[i].value) - abs(sumarray[i+1].value);
		smallestdiff.lower_bound = sumarray[i].value;
		smallestdiff.upper_bound = sumarray[i+1].value;
	}
	for(i; i < totalsize; i++){
		tempdiff.value = abs(sumarray[i].value) - abs(sumarray[i+1].value);
		if(abs(tempdiff.value) < abs(smallestdiff.value)){
			smallestdiff.value = tempdiff.value;
			smallestdiff.lower_bound = sumarray[i].value;
			smallestdiff.upper_bound = sumarray[i+1].value;
		}
	}

	printf("Smallest diff is %d, found between %d and %d\n", smallestdiff.value, smallestdiff.lower_bound, smallestdiff.upper_bound);
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

void mergeSort(arraymeta numbers[], arraymeta temp[], int array_size){
	m_sort(numbers, temp, 0, array_size - 1);
}

void m_sort(arraymeta numbers[], arraymeta temp[], int left, int right){
	  int mid;

	  if (right > left){
		mid = (right + left) / 2;
	    m_sort(numbers, temp, left, mid);
	    m_sort(numbers, temp, mid+1, right);
	    merge(numbers, temp, left, mid+1, right);
	  }
}

void merge(arraymeta numbers[], arraymeta temp[], int left, int mid, int right){
	  int i, left_end, num_elements, tmp_pos;

	  left_end = mid - 1;
	  tmp_pos = left;
	  num_elements = right - left + 1;

	  while ((left <= left_end) && (mid <= right))
	  {
	    if (numbers[left].value <= numbers[mid].value)
	    {
	      temp[tmp_pos].value = numbers[left].value;
		  //Todo: is this necessary?
		  temp[tmp_pos].parent_array = numbers[left].parent_array;
		  temp[tmp_pos].position = numbers[left].position;
	      tmp_pos = tmp_pos + 1;
	      left = left +1;
	    }
	    else
	    {
	      temp[tmp_pos].value = numbers[mid].value;
	      //Todo: is this necessary?
		  temp[tmp_pos].parent_array = numbers[mid].parent_array;
		  temp[tmp_pos].position = numbers[mid].position;
	      tmp_pos = tmp_pos + 1;
	      mid = mid + 1;
	    }
	  }

	  while (left <= left_end){
	    temp[tmp_pos].value = numbers[left].value;
	    //Todo: is this necessary?
		temp[tmp_pos].parent_array = numbers[left].parent_array;
		temp[tmp_pos].position = numbers[left].position;
	    left = left + 1;
	    tmp_pos = tmp_pos + 1;
	  }
	
	  while (mid <= right){
	    temp[tmp_pos].value = numbers[mid].value;
	    //Todo: is this necessary?
		temp[tmp_pos].parent_array = numbers[mid].parent_array;
		temp[tmp_pos].position = numbers[mid].position;
	    mid = mid + 1;
	    tmp_pos = tmp_pos + 1;
	  }

	  for (i=0; i <= num_elements; i++){
	  	numbers[right].value = temp[right].value;
	    //Todo: is this necessary?
		temp[tmp_pos].parent_array = numbers[right].parent_array;
		temp[tmp_pos].position = numbers[right].position;
	    right = right - 1;
	  }
}
	
void print_array(int *array, int size){
	for(int i = 0; i < size; i++){
		printf("%d\n", array[i]);
	}
}