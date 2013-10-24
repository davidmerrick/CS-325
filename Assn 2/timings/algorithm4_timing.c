//
//  main.c
//  test2
//
//  Created by David Merrick on 10/23/13.
//  Copyright (c) 2013 David Merrick. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct arraymeta{
    int value;
    int parent_array;
} arraymeta;

typedef struct arraydiff{
    int value;
    int lower_bound;
    int upper_bound;
} arraydiff;

int *compute_sum_array(int *array, int size);
int compare_sort(int *array, int size);
void print_array(int *array, int size);
int recurse(int *array, int size);
int lesser_of(int a, int b);
void merge(arraymeta numbers[], arraymeta temp[], int left, int mid, int right);
void m_sort(arraymeta numbers[], arraymeta temp[], int left, int right);
void mergeSort(arraymeta numbers[], arraymeta temp[], int array_size);

int main(int argc, const char * argv[]){
    int size = 8;
    int array[] = {1,2,-4,4,5,6,7,8};
    int smallestsum = recurse(array, size);
    printf("Smallest sum is %d\n", smallestsum);
}

int recurse(int *array, int size){
    //Returns the smallest sum recursively
    if(size == 3 || size == 4){
        return compare_sort(array, size);
    } else if(size == 1){
        return array[0];
    } else if(size == 2){
        return lesser_of(array[0], array[1]);
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
    if(abs(a) < abs(b)){
        return a;
    } else {
        return b;
    }
}

int compare_sort(int *array, int size){
    //Split and reverse the array
    
    int array1_size = size/2;
    int array1[array1_size];
    for(int i = 0; i < size/2; i++){
        array1[i] = array[i];
    }
    int j = 0;
    int array2_size = size - size/2;
    int array2[array2_size];
    for(int i = size/2; i < size; i++){
        array2[j] = -array[i];
        j++;
    }
    
    int array2rev[array2_size];
    
    for(int t=1; t<=array2_size; t++){
        array2rev[t-1] = array2[array2_size-t];
    }
    
    int totalsize = array1_size + array2_size;
    
    //Compute sum arrays
    //Dump positive array 1 sums into first half of sumarray
    arraymeta *sumarray = malloc(totalsize * sizeof(arraymeta));
    j = 0; //index for sumarray
    int tempsum = 0;
    for (int i=array1_size-1; i >= 0; i--){
        tempsum += array1[i];
        sumarray[j].value = tempsum;
        sumarray[j].parent_array = 1;
        j++;
    }
    tempsum = 0;
    //Dump negative array 2 sums into second half of sumarray
    for (int i=array2_size-1; i >= 0; i--){
        tempsum += array2[i];
        sumarray[j].value = tempsum;
        sumarray[j].parent_array = 2;
        j++;
    }
    
    arraymeta temp[totalsize];
    
    mergeSort(sumarray, temp, totalsize);
    
    arraydiff smallestdiff, tempdiff;
    
    //These will invert the number if it's in the negative array
    int inversion1 = 1;
    int inversion2 = 1;
    
    //Initial case
    int i = 0;
    while(sumarray[i].parent_array == sumarray[i+1].parent_array){
        i++;
    }
    if(sumarray[i].parent_array != sumarray[i+1].parent_array){
        if(sumarray[i].parent_array == 2){
            inversion1 = -1;
        } else if(sumarray[i+1].parent_array == 2){
            inversion2 = -1;
        }
        smallestdiff.value = inversion1 * sumarray[i].value + inversion2 * sumarray[i+1].value;
        smallestdiff.lower_bound = inversion1 * sumarray[i].value;
        smallestdiff.upper_bound = inversion2 * sumarray[i+1].value;
    }
    for(i; i < totalsize; i++){
        if(sumarray[i].parent_array != sumarray[i+1].parent_array){
            inversion1 = inversion2 = 1; //Reset
            if(sumarray[i].parent_array == 2){
                inversion1 = -1;
            } else if(sumarray[i+1].parent_array == 2){
                inversion2 = -1;
            }
            tempdiff.value = inversion1 * sumarray[i].value + inversion2 * sumarray[i+1].value;
            if(abs(tempdiff.value) < abs(smallestdiff.value)){
                smallestdiff.value = tempdiff.value;
                smallestdiff.lower_bound = inversion1 * sumarray[i].value;
                smallestdiff.upper_bound = inversion2 * sumarray[i+1].value;
            }
        }
    }
    //Compare this with the sums within the arrays
    int tempsum1, tempsum2;
    tempsum1 = tempsum2 = 0;
    for(i = 0; i < array1_size; i++){
        tempsum1 += array1[i];
    }
    
    for(i = 0; i < array2_size; i++){
        tempsum2 += array2[i];
    }
    return lesser_of(lesser_of(smallestdiff.value, tempsum1), tempsum2);
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
            tmp_pos = tmp_pos + 1;
            left = left +1;
        }
        else
        {
            temp[tmp_pos].value = numbers[mid].value;
            //Todo: is this necessary?
            temp[tmp_pos].parent_array = numbers[mid].parent_array;
            tmp_pos = tmp_pos + 1;
            mid = mid + 1;
        }
    }
    
    while (left <= left_end){
        temp[tmp_pos].value = numbers[left].value;
        //Todo: is this necessary?
        temp[tmp_pos].parent_array = numbers[left].parent_array;
        left = left + 1;
        tmp_pos = tmp_pos + 1;
    }
    
    while (mid <= right){
        temp[tmp_pos].value = numbers[mid].value;
        //Todo: is this necessary?
        temp[tmp_pos].parent_array = numbers[mid].parent_array;
        mid = mid + 1;
        tmp_pos = tmp_pos + 1;
    }
    
    for (i=0; i <= num_elements; i++){
        numbers[right].value = temp[right].value;
        numbers[right].parent_array = temp[right].parent_array;
        right = right - 1;
    }
}