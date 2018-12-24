// You will compile this source using the following:
// 
// clang -std=c11 -mavx2 avx5.c -o avx5prog
//
// Run as normal with: 
// 
// ./avx5prog
//
#include <stdio.h>
#include <immintrin.h>

// Last example we looked at masking data.
// Now lets look at a new way to work with the data in our registers.
// We are going to do something called 'permuting' our data.
// Permuting is the rearrangment of data within a register that we have loaded.
// 
// We will use 'permute' instructions to do this.

// print
void print__m256(__m256 data){
	float*f = (float*)&data;
	printf("%f %f %f %f %f %f %f %f\n", f[0],f[1],f[2],f[3],f[4],f[5],f[6],f[7]);
}

int main(){

	// Let's start with some data here
	// Note I am using the 'setr' version to intialize data.
	__m256 a = _mm256_setr_ps(1.0,2.0,3.0,4.0,1.0,2.0,3.0,4.0);	
	print__m256(a);

	// One strategy to permute data would be again to use a mask.
	// This mask would tell me where to arrange items
	// in our registers, this can be incredibly useful.
	// To keep things simple, let us just input binary
	// so we can see exactly what is going.
	//
	// The mask that I am going to input is in binary.
	// The mask I insert is done by passing in 0b10110100 as an argument.
	// I read the binary numbers in sets of two.
	// |10|11|01|00
	//  2  3  1  0
	//
	//  ^ The above is telling me how to 'shuffle' data around, like if I was
	// shuffling a deck of cards in my hand while playing poker.
	// Pretend you are holding two hands of '4' playing cards in each of your hand.
	// That is the result--convince yourself after running this.
	//
	// (Again, be careful of the order for how data is laid out) Try!
	__m256 result = _mm256_permute_ps(a,0b10110100); 

	print__m256(result);
	
	// Discuss whether this can be a useful function?
	// Here is one particular domain in which it is used.
	// Color formats!
	//
	// Images are often stored in the format RGBA
	// Where R is red, G green, B is blue, and A is the alpha(transparnecy)
	//
	// Some image formats however are stored in BGRA, and we have to convert them in real-time.
	// This is something your professor had to work on doing while at Intel.
	//
	// (Discuss): Can you think of other domains in which you may need to 'permute'?
	// Do you think this instruction would be interesting for companies like Instagram to
	// create new filters, or remove color?


	return 0;
}
