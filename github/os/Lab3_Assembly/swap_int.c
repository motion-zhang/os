// Write a C program that swaps two integers(in the main body of code).

int swap (int* a, int* b) {
    int t0 = *a;
    int t1 = *b;
    *a = t1;
    *b = t0;
}

int main(){
    int x, y;
    x = 3;
    y = 5055;

    swap (&x, &y);
    return 0;
}
