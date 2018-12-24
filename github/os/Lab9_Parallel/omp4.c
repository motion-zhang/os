// This program computes the fibonacci sequence.
// Compile with: gcc omp4.c -o omp4
#include <stdio.h>
int fib_recursive(int n){
  // base case
  if(n < 2){
   return 1;
  }
  // Some shared variables
  int x,y;

  // Accumulate our result
  #pragma omp task shared(x) 
  x = fib_recursive(n-1);
  #pragma omp task shared(y)
  y = fib_recursive(n-2);
  #pragma omp taskwait
  return x + y;
}

int main(){
  
  // Computes the 45th number(n+1) in the fibonacci sequence
  printf("%d ",fib_recursive(40));
  printf("\n");
  
  return 0;
}
