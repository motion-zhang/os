#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/mman.h>
#include <sched.h>


typedef struct block {
  size_t size;
  struct block *next;
  int free;
}block;

#define BLOCK_SIZE sizeof(block)
#define MAX_SBRK_SIZE 64
#define NUM_CPU 3
#define _GNU_SOURCE 

void *header = NULL;    //  the current head 
block *tail = NULL;   //  the lined-list blocks stacks
void *space;          // memory space incremented by the sbrk command
size_t size_temp;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

struct block *free_list[3]; // 3 cpu units, 3 free lists

void init() {

    // initialize the free list elements
    free_list[0] = NULL;
    free_list[1] = NULL;
    free_list[2] = NULL;

}    

// find the blocks that is free
void *find_free_block(size_t s, int i) {
   block *temp;

   
   for (temp = free_list[i]->next; temp->next != NULL; temp = temp->next) {
     if (temp->size >= s) {
        return temp;
     }
   }
   return NULL;
}

// find the blocks that is free for mmap
void *find_free_mmap_blocks(size_t s, int i) {
   
   block *temp;
   for (temp = free_list[i]; temp->next != NULL; temp = temp->next) {
      if (temp->size > 4096) {
         return temp;
      }
   }
   return NULL;
}


// split the blocks for the mmap call
void *split_block(block *b, size_t s) {
   pthread_mutex_lock(&mutex); // lock
   //pthread_mutex_lock(&mu);
   block *temp_next = b->next; //store the next
   size_t b_size = b->size;   //store the size 
   block *split;
   char *gap;

   b->free = 1;
   b->size = s;
   ++b;

   gap = (char* ) b;
   gap = gap + s + 1;

   // adding a split block
   split = (block*) gap;
   split->free = 0;
   split->size = (b_size - s);
   split->next = temp_next;
   
   --b;
   b->next = split;
   pthread_mutex_unlock(&mutex);  // unlock
   return (void*) (++b);
}


void *mymalloc_help(size_t s, int i) {
          int len = s + BLOCK_SIZE;
          pthread_mutex_lock(&mutex);
          block *temp = find_free_mmap_blocks(s, i);
          if (!temp) {
             space = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
             temp = space;
             block *temp2 = tail; // store the current block-list 
             temp->free = 1;
             temp->size = s;
             temp->next = temp2;   // append the temp2 to the temp
             tail = temp;         // let start = temp
             printf("malloc %zu bytes\n",s);
             pthread_mutex_unlock(&mutex);
             return (void*) (++temp);
          }
          else {
             if (temp->size > s + BLOCK_SIZE + 1) {
                pthread_mutex_unlock(&mutex);
                return split_block(temp, s); 
             }
             else {
               temp->free = 1;
               temp->size = s; // s+len?
               pthread_mutex_unlock(&mutex);
               return (void*) (++temp);
             }
          }      
}

void *mymalloc(size_t s){
     init();
     int i = sched_getcpu();
     int len = s + sizeof(s);
     if (s <= 0)
        return NULL;
     pthread_mutex_lock(&mutex); 
     if(!header) {    // if head is null
        if (s <= MAX_SBRK_SIZE) {
           space = sbrk(s + BLOCK_SIZE);
           if (space == (void*) - 1)  // check if the sbrk command failed
              return NULL;}
        else {
           space = mmap(NULL, len, PROT_READ | PROT_WRITE, 
                                       MAP_PRIVATE | MAP_ANONYMOUS, 0, 0 );}
           block *temp = space;
           temp->free = 1;
           temp->size = s;
           temp->next = NULL;
           tail = temp; // push the temp block to the block-list stack
           header = temp;  // store the current block-list
           free_list[i] = header; // allocates the header to the right running cpu
           printf("malloc %zu bytes\n",s);
           pthread_mutex_unlock(&mutex);
           return (void*) (++temp);}
     else {
        if (s <= MAX_SBRK_SIZE) {
           block *temp = find_free_block(s,i);
           if (!temp) {
              space = sbrk(s + BLOCK_SIZE);
              if (space == (void*) - 1)
                 return NULL;
              temp = space;
              block *temp2 = tail; // store the current block-list 
              temp->free = 1;
              temp->size = s;
              temp->next = temp2;   // append the temp2 to the temp
              tail = temp;         // let start = temp
              printf("malloc %zu bytes\n",s);
              pthread_mutex_unlock(&mutex);
              return (void*) (++temp);}
           else {
              temp->free = 1;
              temp->size = s;
              printf("malloc %zu bytes\n",s);
              pthread_mutex_unlock(&mutex);
              return (void*) (++temp);}}
        else {
           return  mymalloc_help(s, i);}}
  
  pthread_mutex_unlock(&mutex);
}

void *mycalloc(size_t nmemb, size_t s) {

     size_t size = nmemb * s;
     void *temp = mymalloc(size);

     pthread_mutex_lock(&mutex);

     if(temp){
        memset(temp, 0, size); // check if temp is between give two sizes
        printf("calloc %zu bytes\n",s);
     }
     
     pthread_mutex_unlock(&mutex);
     return temp;
}

void myfree(void *ptr){
     // if given ptr is null
     if (!ptr)
         return ;
     pthread_mutex_lock(&mutex);
     block *temp = ptr;
     --temp;         // free the memory
     temp->free = 0; // change free to 0 meaning freed.
     pthread_mutex_unlock(&mutex);
     printf("Freed some memory\n");

}
