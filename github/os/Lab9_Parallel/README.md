# Lab 9 Parallel Programming

We have discovered that if we want to write parallel software, our compilers are not yet capable of figuring out our intentions and automatically parallelizing our code. We have however explored how a tool like OpenMP can be used to provide hints and attempt to make code run in parallel by using threads. In today's lab, we are going to work with some parallelism pragmas in OpenMP. The best way to learn a tool like OpenMP is by using it.  So let's read a little bit of documentation and write some examples.

# Motivation

Writing code that can run in parallel is important for reasons of performance and reducing power consumption. In languages like C (C++, Rust, etc.) parallel programming is a real thing that people are using, so we should continue practicing. We have previously explored this in our artists homework and lab.


## Part 1 -- Finding the specs for your machine

* Type `lscpu` on the terminal to find out how many cpus you have.

Note, if you are curious about your GPUs on Linux: You can try on the terminal: `lspci` (or look under Systems/Preferences/Hardware Information.)

## Part 2 - OpenMP

Today we are going to primarily work on fork-join parallelism tasks using OpenMP, which is a mature libray that will help transform our serial code into parallel code.

### Task 1 - OpenMP

#### Example 1 - Hello World

Let's first do a little hello world to make sure OpenMP is setup and running properly. The thing to note is that we will have to include  a compiler flag for OpenMP to make sure the library is properly linked in.

```c
// A basic hello world with OMP
// Compile with: gcc -std=c99 -fopenmp omp1.c -o omp1
#include <stdio.h>
#include <omp.h>

int main(){
  
  // Create our pragma, and then within curly braces
  // run OpenMP on this structuerd block.
  #pragma omp parallel
  {
      int ID = omp_get_thread_num();
      printf("hello (%d)\n",ID);
      printf(" world(%d)\n",ID);
  }

  return 0;
}

```

Go ahead and run the program with `./omp1`.

**Discuss with your partner and answer:** *answer in a sentence here, what your output is, and whether you expected it to be as such.*

The output is a couple of hellowords with ids. We dont expected to be that much.

#### Example 2 - For-loops

Loops are a common structure that can be looked at for potential parallelism. We must know the exact number of iterations for this to run however, in order for it to be successful.

```c
// gcc -std=c99 -fopenmp omp2.c -o omp2
#include <stdio.h>
#include <omp.h>

int main(){

  // Attempt to parallelize this block of code
  #pragma omp parallel
  {
    // Parallel-for loop
    #pragma omp for
    for(int n=0; n <100; ++n){
      printf(" %d",n);
    }
  }
  return 0;
}
```

**Discuss with your partner and answer:** *Why is our output not ordered?*

It is running in parallel, not sequential. 

#### Example 3 - Synchronization

The previous examples do a nice job of spawning many threads that print (one even displaying the thread ID). However, we do not have any information about how many threads were launched within our parallel-for loop. Let's go ahead and record this information, by storing the number of threads launched. In addition, we will also add some synchronization (i.e. using the barrier pattern) to print the number of threads. The barrier pattern waits for all active threads to arrive, and then proceeds.

```c
// gcc -std=c99 -fopenmp omp3.c -o omp3
#include <stdio.h>
#include <omp.h>

int main(){
   int nthreads;

  // Attempt to parallelize this block of code
  #pragma omp parallel
  {
    // Parallel-for loop
    #pragma omp for
    for(int n=0; n <100; ++n){
      printf(" %d",n);
    }
    // Master thread waits
    #pragma omp barrier
    if(omp_get_thread_num()==0){
        nthreads = omp_get_num_threads();
    }
  }

  printf("\nSolved problem with %d threads\n",nthreads);
 
  return 0;
}

```

#### Example 4 - Fibonacci Sequence

For our first example, take a look at the following code.

```c
// This program computes the fibonacci sequence.
// Compile with: gcc omp4.c -o omp4

#include <stdio.h>

int fib_recursive(int n){
  // base case
  if(n < 2){
   return 1;
  }
  // Accumulate our result 
  return fib_recursive(n-1)+fib_recursive(n-2);
}


int main(){
  
  // Computes the 45th number(n+1) in the fibonacci sequence
  printf("%d ",fib_recursive(40));
  printf("\n");
  
  return 0;
}
```
**Run the program above**: With `time ./omp4`

So the question now is, with this algorithm is there any potential parallelism? Well, in our current implementation, not so much. We need to transform our algorithm slightly, so we can remove data dependency.

Take a look below and see how OpenMP can be used to separate work into different tasks.

```c
// A new snippet
// Compile with: gcc -std=c11 -fopenmp omp4.c -o omp4

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
```

**Run the program above**: With `time ./omp4`

Note that you may not see any performance gain--why?



**Discuss with your partner and answer:** It seems like the parallelism isnt't helping.


#### Example 5 - Computing PI 3.1415....

You may remember that we watched a [video](https://www.youtube.com/watch?v=FQ1k_YpyG_A&list=PLLX-Q6B8xqZ8n8bwjGdzBJ25X2utwnoEG&index=6) on computing PI. Let's go ahead and type in this code, first in serial, and then you can parallelize it. Again, this is a nice example, because you can check that your solution does indeed add up to PI.

```c
// gcc -std=c11 -fopenmp omp5.c -o omp5
#include <stdio.h>

static long num_steps = 100000;
double step;

int main(){
  int i;
  double x, pi, sum = 0.0;
  
  step = 1.0/(double)num_steps;
  for(i =0; i < num_steps; i++){
    x = (i+0.5)*step;
    sum = sum+ 4.0/(1.0+x*x);
  }
  pi = step * sum;
  
  printf("PI = %f\n", pi);
 
  return 0;
}

```

Now we are going to try to solve this problem in parallel.

In general, this is a type of [Reduction](http://www.drdobbs.com/architecture-and-design/parallel-pattern-7-reduce/222000718) algorithm, in that we are chunking our problem and solving pieces of it, and then rebuilding the result.

**Discuss with your partner and answer:** *What is a strategy for solving this problem?*

**Now implement in omp5.c your strategy:** Note: You can revisit [Tim Mattson's video](https://www.youtube.com/watch?v=OuzYICZUthM&list=PLLX-Q6B8xqZ8n8bwjGdzBJ25X2utwnoEG&index=7) if you get stuck.

#### Example 6 - Quick Sort

Do a little bit of research with your partner to understand quick sort. Implement a parallel version of quick sort in omp6.c. A nice sample pdf of [Quick Sort](https://www.openmp.org/wp-content/uploads/sc16-openmp-booth-tasking-ruud.pdf) is provided if you get stuck.

## Lab Deliverable

1. Complete Part 2, task 1 and commit your 6 OpenMP examples to the repository.
  * Modify and implement the parallel solutions to: omp1.c omp2.c omp3.c omp4.c omp5.c omp6.c

## More Resources to Help

* The following guide provides some insight into using OpenMP. 
  * https://bisqwit.iki.fi/story/howto/openmp/#ParallelConstruct 
  * Lawrence Livermore National Labroratory https://computing.llnl.gov/tutorials/openMP/exercise.html 
  * Tim's video series https://www.youtube.com/watch?v=nE-xN4Bf8XI&list=PLLX-Q6B8xqZ8n8bwjGdzBJ25X2utwnoEG&index=1

* The following resources may be useful to observe for those interested in GPGPU programming
   * OpenCL for MacOS https://developer.apple.com/opencl/
   * The following guide will get you started for CUDA: https://devblogs.nvidia.com/even-easier-introduction-cuda/
   * The following guide will get you started for OpenCL: https://www.eriksmistad.no/getting-started-with-opencl-and-gpu-computing/
   
* For fun
  * Parallel Programming Patterns: http://www.drdobbs.com/architecture-and-design/parallel-pattern-7-reduce/222000718
  * See other Parallel Programming libraries in C/C++ here: https://www.youtube.com/watch?v=y0GSc5fKtl8

## Going Further

- Investigate OpenMP's `#pragma omp simd`
