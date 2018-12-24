// Write a C program that swaps two integers in a function


long swap (int* a, int* b) {
    long  t0 = *a;
    long  t1 = *b;
    *a = t1;
    *b = t0;
}


long  main() {

    long a = 1001;
    long b = 1110;

    swap(&a,&b);
 
    return 0;
}


