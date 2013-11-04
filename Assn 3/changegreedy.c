#include <stdio.h>
#include <stdlib.h>

void changegreedy(int* O, int *V, int c, int size);

int main(){

  int C = 40;
  int size = 3;
  int V[] = {1,10,25,50};
  int O[] = {0,0,0,0};

  changegreedy(O,V,C, size);

}


void changegreedy(int* O, int *V, int C, int size){
  for (int i = size; i>=0; i--){
    while (V[i] <= C){
      C = C - V[i];
      O[i]++;
    }
  }

  for (int i = 0; i <= size; i++){
    printf("%d\n", O[i]);
  }

}
