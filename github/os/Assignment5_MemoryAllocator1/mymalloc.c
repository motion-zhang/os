#include <string.h>
#include <unistd.h>
#include <stdio.h> 
// We bring in the old malloc function
// NOTE: You should remove malloc.h, and not include <stdlib.h> in your final implementation.
// This is a first-fit memory allocator

typedef struct block {
  size_t size;
  struct block *next;
  int free;
}block;

#define BLOCK_SIZE sizeof(block)
void *header = NULL;    //  the current head 
block *tail = NULL;   //  the lined-list blocks stacks
void *space;          // memory space incremented by the sbrk command

// find the blocks that is free
void *find_free_block(size_t s) {
   block *temp;
   for (temp = header; temp->next != NULL; temp = temp->next) {
     if (temp->size >= s) {
        return temp;
     }
   }
   return NULL; 
}


void *mymalloc(size_t s){

     if (s <= 0)
        return NULL;
     // if head is null
     if(!header) {
        space = sbrk(s + BLOCK_SIZE);
        if (space == (void*) - 1)  // check if the sbrk command failed
           return NULL;
        block *temp = space;
        temp->free = 1;
        temp->size = s;
        temp->next = NULL;
        tail = temp; // push the temp block to the block-list stack
        header = temp;  // store the current block-list
        printf("malloc %zu bytes\n",s);
        return (void*) (++temp);
     }
     else {
        block *temp = find_free_block(s);
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
           return (void*) (++temp);
        }
        else {
           temp->free = 1;
           temp->size = s;
           printf("malloc %zu bytes\n",s);
           return (void*) (++temp);
        }
     }
}

void *mycalloc(size_t nmemb, size_t s){
     
     size_t size = nmemb * s;
     void *temp = mymalloc(size);
        
     if(temp){
        memset(temp, 0, size); // check if temp is between give two sizes
        printf("calloc %zu bytes\n",s);
     }

     return temp;
}
	
void myfree(void *ptr){
     // if given ptr is null
     if (!ptr)
         return ;
     block *temp = ptr;  
     --temp;         // free the memory
     temp->free = 0; // change free to 0 meaning freed.
     printf("Freed some memory\n");

}

