// Simple Caeser Shift decrypt
// 
// Load the data from data2.txt. Increment all of the values by 1 then output
// the result
// 
// You will compile this source using the following:
// 
// clang -std=c11 -mavx2 ex2.c -o ex2prog
//
// Run as normal with: 
// 
// ./ex2prog
//
#include <stdio.h>
#include <immintrin.h>



// print
void print__m256(__m256 data){
	float*f = (float*)&data;
	printf("%f %f %f %f %f %f %f %f\n", f[0],f[1],f[2],f[3],f[4],f[5],f[6],f[7]);
}

int main(){



	return 0;
}
