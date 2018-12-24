// You will compile this source using the following:
// 
// clang -std=c11 -mavx2 avx2.c -o avx2prog
//
// Run as normal with: 
// 
// ./avx2prog
//
#include <stdio.h>
#include <immintrin.h>

// Now I want to talk about a few handy functions in the AVX library that
// are things we frequently do as programmers. 
// The first is initializing our data to a starting value.
//
// Additionally, here are two requirements in this sample.
// (1) 	We are going to work with floats
// (2) 	It would be nice to be able to have a function to print out
// 	floats given an __m256 data type.


// TODO: Implement this function
void print__m256(__m256 data){
	//
	// Your implementation can be done in 2 lines
	//
}


int main(){

	__m256 evensAVX = _mm256_set_ps(2.0,4.0,6.0,8.0,10.0,12.0,14.0,16.0);

	// Implement your print function above.
	printf("=========Printing evens=========\n\n");
	print__m256(evensAVX);


	// Okay, now lets to experiment with a few commands to setup our data.
	//
	// TODO: Experiment with following commands below, and print out the values.
	//	 If you do not know what the command does, look it up in the intrinsics guide.
	//	 Intrinsics guide: https://software.intel.com/sites/landingpage/IntrinsicsGuide/
	// 
	// _mm256_setzero_ps
	// _mm256_set1_ps
	//
	// Your output should include a vector of all zeroes and a vector all with 42.00000.
	
	__m256 test1 = ...
	__m256 test2 = ...

	printf("=========Printing 0's and 42's=========\n\n");
	print__m256(test1);
	print__m256(test2);

	// The previous 'setzero' and 'set1' commands are nice ways to very quickly fill up a __m256 register.
	// In C we have a command 'memset' which zeros out a number of bytes in an array.
	// Sometimes however, we want to explicitly set individual values.
	// In AVX2 we have the following intrinsic functions:
	//
	// _mm256_set_ps(0,...,7); 
	// _mm256_setr_ps(7,...,0);
	//
	// Here is the actual signature for conveinience. Again, look in the intrinsics guide for exact syntax:
	// __m256 _mm256_set_ps (float e7, float e6, float e5, float e4, float e3, float e2, float e1, float e0)
	//
	// Try to use each of these commands and print out the result.

	test3 = ...
	
	printf("=========Printing _mm256_set_ps=========\n\n");
	print__m256(test3);

	// Now why might we have a version of set and setr? (The 'r' at the end means reverse, referring to ordering of arguments)
	// Intel machines are typically little-endian based architectures, this means order of our bits matters
	// (Remember with our intrinsics, we are just playing around with a 'bucket of 256 bits' if that is helpful to think about.).
	//
	// Little-Endian means the least signficant value in the sequence is stored first.

	// Okay, so we have spent some time setting data up. But often we
	// work with data in which we load from memory. We have the ability to do so
	// using the intrinsic functions.
	//
	// One concept that becomes important, is the idea of alignment in memory.
	// That is, we need to make sure the memory address from which we load data
	// is aligned on a 32-byte boundary.
	//
	// We have previously learned about malloc which does indeed load memory that
	// is aligned, but always in multiples of 8 or 16. Let us make sure it is always in 
	// 32 byte using aligned_malloc.
	
	float* aligned_32 = (float*)aligned_alloc(32, 64 * sizeof(float));

	// Let's break that functiond down.
	// First, we cast to a float*, just as we would have done with a regular malloc.
	// The first parameter describes our alignment, in this case 32 bytes.
	// Remember, our 256-bit vector is divided into nice 32 byte chunks.
	//
	// |32|32|32|32|32|32|32|32| = 256 bits
	//  7  6  5  4  3  2  1  0
	//
	//
	// And why do we multiply 64 * sizeof(float)?	
	// Well, lets verify on our architecture the data size of a float in bytes.

	printf("=========Loading aligned data=========\n");
	printf("sizeof(float)=%lu\n",sizeof(float));
	
	// And hopefully whatever our result is for sizeof(float) times 64 is equal to 256!
	// You can read more here: 
	// https://www.gnu.org/software/libc/manual/html_node/Aligned-Memory-Blocks.html
	//
	// Okay, now let us populate our data data in a normal C array.
	
	aligned_32[0] = 0.0f;
	aligned_32[1] = 1.0f;
	aligned_32[2] = 2.0f;
	aligned_32[3] = 3.0f;
	aligned_32[4] = 4.0f;
	aligned_32[5] = 5.0f;
	aligned_32[6] = 6.0f;
	aligned_32[7] = 7.0f;

	// Now we finally load our array of floats into an AVX2 register.
	// '_mm256_load_ps' is the command to do so.
	__m256 aligned_avx = _mm256_load_ps(aligned_32);
	// And of course, we can always debug this working by printing out the individual
	// values stored in our register.
	print__m256(aligned_avx);

	// What happens if you need to load data that is unaligned?
	// Investigate _mm256_loadu_ps(...) in the intrinsics guide.
	// The short answer is this command can help us load code aligned on any boundary.


	return 0;
}
