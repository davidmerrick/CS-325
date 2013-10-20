/*
 * Parses text file into appropriate array.
 */

#define BLOCKSIZE 1
#define INPUT_FILE "close_to_zero_problems.txt"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int get_offset(FILE *fd){
	//Returns the offset of the file
	return lseek(fd, 0, SEEK_CUR);
}

int store_array(int *arr, FILE *fd){
	//Returns the size of the array
	int element_count = count_elements(fd);
	arr = malloc(sizeof(int) * (element_count)); //Array to hold the numbers
	
	//Reads from file and stores in array
	char *buffer;
	buffer = (char*) malloc (sizeof(char));
	char curr_elt[5]; //Current element temp buffer
	int curr_elt_idx = 0; //Index of current element temp buffer
	int arr_idx = 0; //Index of bigger array
	
	while(buffer[0] != ']'){
		fread (buffer,1,1,fd);
		printf("buffer == %c\n", buffer[0]);
		if(buffer[0] == ','){
			//convert current element to int, store in big array
			curr_elt[curr_elt_idx] = '\0'; //Append escape character
			arr[arr_idx] = atoi(curr_elt);
			arr_idx++;
			curr_elt_idx = 0; //Start over
		}else {
			if(buffer[0] != ' '){ //ignore spaces
				//store the current element in the temp buffer
				curr_elt[curr_elt_idx] = buffer[0];
				curr_elt_idx++;
			}
		}
	}
	
	//Last case
	//convert current element to int, store in big array
	curr_elt[curr_elt_idx] = '\0'; //Append escape character
	arr[arr_idx] = atoi(curr_elt);
	return element_count;
}

void seek_next_array(FILE *fd){
	char *buffer;
	buffer = (char *) malloc(sizeof(char));
	while(!feof(fd)){
		fread (buffer,1,1,fd);
		printf("Buffer: %c\n", buffer[0]);
		printf("Offset inside seek = %d\n", lseek(fd, 0, SEEK_CUR));
		if(buffer[0] == '['){
			break;
		}
	}
	free(buffer);
}

int count_elements(FILE *fd){
	int offset = lseek(fd, 0, SEEK_CUR);
				printf("File offset inside count_elements = %d\n", offset);
	//Returns a count of the elements in the array in the current file
	//First pass, to count the commas and determine the size of the array we need
	int comma_count = 0;
	char *buffer;
	buffer = malloc(sizeof(char));
	while(buffer[0] != ']'){
		fread (buffer,1,1,fd);
		if(buffer[0] == ','){
			comma_count++;
		}
	}
	free(buffer);
	//Return to previous offset
	lseek(fd, offset, SEEK_SET);
	return comma_count + 1;
}

void print_array(int *arr, int size){
	//for debugging
	//Testing: print the array
	printf("Testing: print the array\n");
	for(int i = 0; i< size; i++){
		printf("%d\n", arr[i]);
	}
}

int main(){
	FILE *fd;
	fd = fopen(INPUT_FILE, "r");
	
	if(fd != NULL){
		char *buffer;
		buffer = malloc(sizeof(char));
		int *arr;
		int arr_size = 0;
		
		//while(!feof(fd)){
			seek_next_array(fd);
			printf("File offset = %d\n", lseek(fd, 0, SEEK_CUR));
			arr_size = store_array(arr, fd);
			print_array(arr, arr_size);
		//}
		
		fclose(fd);
	} else {
		printf("Error opening file.\n");
	}
}