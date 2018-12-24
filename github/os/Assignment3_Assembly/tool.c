// Implement your cycle count tool here

#include "stdio.h"
#include "string.h"

int main() {
    
    int add = 0;
    int sub = 0;
    int mul = 0;
    int div = 0;
    int lea = 0;
    int push = 0;
    int pop = 0;
    int ret = 0;
    int mov = 0;
    int instructions = 0;
    int cycle = 0;

    const char *subt = "sub";
    const char *movt = "mov";
    const char *addt = "add";
    const char *mult = "mul";
    const char *divt = "div";
    const char *leat = "lea";
    const char *pusht = "push";
    const char *popt = "pop";
    const char *rett = "ret";

    printf("Please enter the file name you want to parse\n");

    char fname[50];
   
    scanf("%s", fname);
    
    FILE *pToFile = fopen(fname, "r");
    
    char input[512];
    
    while ( fgets (input, 512, pToFile) ) {
        char *token = strtok(input, "%#.$");
       
        const char *temp = token;
       
        

        if (strstr(temp, subt) != NULL) {
           sub++;
        }

        if (strstr(temp, addt) != NULL) {
           add++;
        }
       
        if (strstr(temp, mult) != NULL) {
           mul++;
        }
       
        if (strstr(temp, divt) != NULL) {
           div++;
        }
       
        if (strstr(temp, leat) != NULL) {
           lea++;
        }
       
        if (strstr(temp, pusht) != NULL) {
           push++;
        }
       
        if (strstr(temp, popt) != NULL) {
           pop++;
        }
       
        if (strstr(temp, rett) != NULL) {
           ret++;
        }
       
        if (strstr(temp, movt) != NULL) {
           mov++;
        }
    }

    fclose(pToFile);
    
    if (mov != 0) {    
        printf("MOV: %d\n", mov);    
        instructions = instructions + mov;
    }
    
    if (add != 0) {
        printf("ADD: %d\n", add);
        instructions = instructions + add;    
    }

    if (sub != 0) {
        printf("SUB: %d\n", sub);
        instructions = instructions + sub;
    }

    if (mul != 0) {
        printf("MUL: %d\n", mul);
        instructions = instructions + mul;
    } 

    if (div != 0) {
        printf("DIV: %d\n", div);
        instructions = instructions + div;
    }   

    if (lea != 0) {
        instructions = instructions + lea;       
        printf("LEA: %d\n", lea);
    }
    
    if (push != 0) {
       instructions = instructions + push;
       printf("PUSH: %d\n", push);
    }    
    
    if (pop != 0) {
        instructions = instructions + pop;
        printf("POP: %d\n", pop);
    }

    if (ret != 0) {
        instructions = instructions + ret;
        printf("RET: %d\n", ret);
    }
 
    printf ("Total Instructions: %d\n", instructions);
    // Using the intel core i7 for calculating the cycles  
    cycle = mov * 1 + push * 1 + sub * 1 +  pop * 2 + lea * 1 + add * 1 + mul * 3 + div * 4 + ret * 1;
    printf ("Total Cycle: %d\n", cycle); 
    return 0;
}
