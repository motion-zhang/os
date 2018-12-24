#include <stdio.h>
#include <malloc.h>
#include <pthread.h>


// Here is some data structure that will be shared.
// It is an array of strings, but nothing has been allocated yet.

// Assume we have 64 CPUs
int num_threads = 64;
char** shared_data;

void thread1(int index) {

     char *text = malloc(20);
     shared_data[index] = "hellow world";
     free(text);
     pthread_exit(0);

}

void thread2(int index) {

     char *text = malloc(10);
     shared_data[index] = "nice job";
     free(text);
     pthread_exit(0);

}



int main(){
	// (1) Malloc for some size of your shared data (i.e. how many strings will you have)
        shared_data = malloc(sizeof(char*) *num_threads);
        pthread_t tid[num_threads];
     
	// (2) Launch some number of threads (perhaps with two or more different functions)
        size_t i,j;
        for (i = 0; i < num_threads / 2; i++) {
            pthread_create(&tid[i], NULL, (void*)thread1, (void*)i);
        }
        for (j = num_threads / 2 + 1; j < num_threads + 1; j++) {
            pthread_create(&tid[j], NULL, (void*)thread2, (void*)j);
        }

	// (3) Join some number of threads
        int m;
        for (m = 0; m < num_threads; m++) {
            pthread_join(tid[m], NULL);
        }	

	// (4) Print the results of shared data (i.e. this is done sequentially)
        int n;
        for (n = 0; n < num_threads; n++) {
            printf("%s\n", shared_data[n]);	
	}

        // (5) Cleanup your program
	free(shared_data);
}
