#include <stdio.h>
#include <stdlib.h>

void changegreedy(int* O, int *V, int c, int size);

int main(){

  //int C = 40;
  int size = 4;
  int V[] = {1,5,10,25,50};
  int O[] = {0,0,0,0};

  for (int C = 2000; C<=2300; C++){
    changegreedy(O,V,C, size);
    }

}

void changegreedy(int* O, int *V, int C, int size){
  int total_coins=0;
  int initial_change = C;

  for (int i = size; i>=0; i--){
    while (V[i] <= C){
      C = C - V[i];
      //O[i]++;
      total_coins++;
    }
  }

  /*for (int i = 0; i <= size; i++){
    printf("%d\n", O[i]);
   
    }*/

  printf("%d, %d\n", initial_change, total_coins);

}
