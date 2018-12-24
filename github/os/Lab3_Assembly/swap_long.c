// Now modify your program to swap two long's. 

int swap (int* a, int* b) {
    long t0 = *a;
    long t1 = *b;
    *a = t1;
    *b = t0;
}

int main(){
    long x, y;
    x = 3;
    y = 5055;

    swap (&x, &y);
    return 0;
}

