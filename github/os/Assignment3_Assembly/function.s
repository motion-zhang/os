# your code here

.global _start

# strings and longs
.select.str:
   .ascii "Select an operation\n1 - add\n2 - subtract\n"

.bss 
   f: .skip 1
   long1: .skip 1
   long2: .skip 1

.data 
   s: .int 0
   n1: .long 0 
   n2: .long 0
   result: .long 0

# text segment of the program
.text
_writeStart:

    # write start selections
    movq $1, %rax
    movq $1, %rdi
    leaq .select.str, %rsi
    movq $41, %rdx
    syscall
    ret

# get the input selection
_getSelection:
     movq $0, %rax        #read
     movq $0, %rdi        #stdin
     movq $f, %rsi        #buffer
     movq $1, %rdx        #size
     syscall
     ret
     
# get the input values
_getFirValue:
     # get the first value
     movq $0, %rax        #read
     movq $0, %rdi        #stdin
     movq $0, %rsi       #clear
     movq $n1, %rsi      #buffer
     movq $8, %rdx        #size
     syscall    
    # ret
 
_getSecValue:
     # get the second value
     movq $0, %rax        #read
     movq $0, %rdi       #stdin
     movq $0, %rsi       #clear
     movq $n2, %rsi       #buffer
     movq $8, %rdx        #size
     syscall
     ret
      
     
_add:
     movq $0, %rax
     movq n1, %rax
     movq $0, %rdx
     movq n2, %rdx
     addq %rax, %rdx
     movq result, %rdx
     ret

_sub:
     movq $0, %rax
     movq n1, %rax
     movq $0, %rdx
     movq n2, %rdx
     subq %rax, %rdx
     movq result, %rdx
     ret 
             

_writeOut:
     movq $1, %rax
     movq $1, %rdi
     movq $0, %rsi
     movq $n1, %rsi
     movq $8, %rdx
     syscall
     ret 

_exitProgram:
    # exit
    movq $60, %rax
    movq $0, %rdi
    syscall
    ret



_start:

    pushq %rbp
    movq %rsp, %rbp

    call _writeStart
    call _getSelection
    call _getFirValue
   
    call  _getSecValue

    call _writeOut

    call _exitProgram

    pop %rbp

