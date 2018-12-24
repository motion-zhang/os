// Implement a working parser in this file that splits text into individual tokens.
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {

    char command[100];
    fgets(command, 255, stdin);
 
    char *token = strtok(command, "");

    token = strtok(command, " ");
 
    printf("%s\n", token);

    while(token != NULL){
       token = strtok(NULL, " ");
       printf(token);
       printf("\n");
    }
    
}
