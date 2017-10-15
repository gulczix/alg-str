#include<stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(int *a, int *b){
  int temp =*a;
  *a=*b;
  *b=temp;
}

void heapify(int *A, int i, int heap_size){
  int largest = 0;
  int l = 2*i; //lewy syn
  int r = 2*i+1; //prawy syn
  if(l<=heap_size && A[l-1]>A[i-1]){
    largest = l;
  }
  else{
    largest = i;
  }
  if(r<=heap_size && A[r-1]>A[largest-1]){
    largest = r;
  }
  if(largest != i){
    swap(&A[i-1],&A[largest-1]);
    heapify(A,largest,heap_size);
  }
}

void buildHeap(int *A, int length){
  int i;
  for(i=length/2; i>0; i--) heapify(A,i,length);
}

void HeapSort(int *A, int length){
  int i;
  buildHeap(A,length);
  for(i=length; i>1; i--){
    swap(&A[i-1],&A[0]);
    length--;
    heapify(A,1,length);
  }
}


int main(int argc, char* argv[]){
  FILE *in, *out;
  char ch;
  int file_length, i,x,y,j,array_length;
  file_length = 0;
  in=fopen(argv[1], "r");
  if (argc < 2)
  {
    fprintf (stderr, "Uzycie: %s nazwa_pliku\n", argv[0]);
    exit(-1);
  }
  if(!in){
    fprintf(stderr, "Nie ma takiego pliku %s\n", argv[1]);
    exit(-1);
  }
  while(!feof(in)){
    ch = fgetc(in);
    if(ch == '\n'){
      file_length++;
    }
  }
  file_length-=2;
  rewind(in);
  fscanf(in, "%d", &x);
  fscanf(in, "%d", &y);
  array_length=y-x+1;
  int *A=(int*)malloc(array_length*sizeof(*A));
  j=0;
  for(i=0; i<file_length; i++)
  {
    if(x<=i && i<=y)
      fscanf(in, "%d", &A[j++]);
  }
  //wypis tablicy - testowy
  printf("[");
  for(i=0; i<array_length-1; i++) {
    printf("%d,",A[i]);
  }
  printf("%d",A[array_length-1]);
  printf("]");
  fclose(in);

  //test buildHeap
  /*
  buildHeap(A,length);
  //after
  printf("\n");
  printf("[");
  for(i=0; i<length-1; i++) {
    printf("%d,",A[i]);
  }
  printf("%d",A[length-1]);
  printf("]");
  */

  //HeapSort
  HeapSort(A,array_length);
  //after
  printf("\n");
  printf("[");
  for(i=0; i<array_length-1; i++) {
    printf("%d,",A[i]);
  }
  printf("%d",A[array_length-1]);
  printf("]");

  //zapis do pliku
  out=fopen(strcat(argv[1],"_2_5.txt"),"w");
  for(i=0;i<array_length; i++) fprintf(out, "%d\n", A[i]);
  fclose(out);
  return 0;

}
