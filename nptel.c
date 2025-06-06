#include<stdio.h>

int main(){

  int *p ,n=5;
  p=&n;
  *p += 1;

  printf("%d,%d",*p,n);
  






    return 0;
}