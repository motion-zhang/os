
# Your code here
 # Example for x86-64 processor using AT&T Style syntax
  .global _start

  .text

  _start:
  	# Write a message to the screen
  	mov $1, %rax
  	mov $1, %rdi
  	mov $message, %rsi
  	mov $13, %rdx
  	syscall

  	# Exit the program
  	mov $60, %rax
  	xor %rdi, %rdi
  	syscall

  message:
  	.ascii "Hello, World\n"
