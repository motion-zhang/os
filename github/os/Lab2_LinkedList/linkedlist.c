//  Modify this file
//  compile with: gcc linkedlist.c -o linkedlist

#include <stdio.h>
#include <stdlib.h>

// Create your node_t type here

struct record {
    int year;
    int win;
    struct record *next;
};


// Write your functions here
// There should be 1.) create_list 2.) print_list 3.) free_list
// You may create as many helper functions as you like.

int insertRecord(struct record *head, struct record *which) {

    if (head == NULL || which == NULL) {
        return -1;
    }


    struct record *next = head;
    struct record *prev = NULL;
    //Get the first instance where next is less than which or
    //the last node.
    while( (next->win > which->win) && next->next != NULL) {
        prev = next;
        next = next->next;
    }

    if (prev == NULL) {
        head->next = which;
    } else {
        if (next->win > which->win) {
            next->next = which;
        } else {
            prev->next = which;
            which->next = next;
        }
    }

    return 0;
}


int createLinkedList(struct record *head){
    //Open file  
    FILE *filePointer;
    filePointer = fopen("sox_wins.txt", "r");
    int yearBuffer;
    int winBuffer;

    int index = 0;
    while(!feof(filePointer)){
        fscanf(filePointer, "%d", &yearBuffer);
        fscanf(filePointer, "%d", &winBuffer);
        struct record *pRecord_node;

        if (index == 0) {
            pRecord_node = head;
        } else {
            pRecord_node = malloc(sizeof(struct record));
        }

        pRecord_node->win = winBuffer;
        pRecord_node->year = yearBuffer;
        pRecord_node->next = NULL;

        if (index != 0) {
            if ( insertRecord(head, pRecord_node) == -1) {
                return -1;
            }
        }

        index = index + 1;
    }


    return 0;
}

int getMeaning(struct record *rec) {
    if (rec->win > 90) {
        printf("Wow! %d was a fantastic year! The Red Sox's got %d wins.\n", rec->year, rec->win);
    } else if (rec->win > 80) {
        printf("%d was a really good year! The Red Sox's got %d wins.\n", rec->year, rec->win);
    } else if (rec->win > 70) {
        printf("%d was a great year. The Red Sox's got %d wins.\n", rec->year, rec->win);
    } else if (rec->win > 60) {
        printf("%d was an okay year. The Red Sox's got %d wins.\n", rec->year, rec->win);
    } else {
        printf("This was a bad year %d :(! The Red Sox's only got %d wins.\n", rec->year, rec->win);
    }

    free(rec);

    return 0;

}

int main(){
    struct record *head = malloc(sizeof(struct record));
    if (createLinkedList(head) == -1) {
        printf("issue creating linked list");

    } else {
        struct record *next = head;

        while(next != NULL){
            getMeaning(next);
            next = next->next;
        }

    }
}


















