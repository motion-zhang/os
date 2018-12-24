# Linked List
> "A first non-trivial data structure"

Data structures are a way for us to store information. Most programming languages come with support for an 'array' data structure for instance. As a reminder, an array is a data structure which stores homogenous datatypes in a contiguous piece of memory. That is a fancy way of saying:

```cpp
int array1[100]; // This array holds strictly integers.
unsigned int array2[100]; // This array holds strictly unsigned ints.
float array3[100]; // This array holds strictly floats.
```

Arrays can also be *statically allocated*. That is, at compile-time (before a program is run), we know exactly how much memory is required of the array.

Here are some examples of statically allocated arrays:
```cpp
int numbers[10];	// 'numbers' is large enough to store exactly 10 integers.
char firstName[15];	// 'firstName' stores up to 15 char's
float piDigits[5000];	// 'piDigits' holds 3.1415....well, up to 5000 digits.
```

Again, the *statically allocated* portion means that there is a fixed number of elements in the arrays. This value is decided when we write our source code and compile it at compile-time. From the example above, we may thus only store the first 5000 digits of pi, or first names that are 15 characters or less.

Often however, we do not know how many elements need to be stored, or the number of elements may need to be reduced over time. For this problem, a data structure that can expand and contract can be very efficient in terms of time and space, as we only have a finite amount of memory on our computers.

For today's lab, we will be implementing a data structure known as the **singly linked list**. This exercise will give you practice with:

1. struct's
2. pointers
3. file I/O
4. Connecting our previous work with bash scripts to C programs

# Part 0 - SSH and git pull

First open a terminal and ssh into the CCIS servers
``` ssh ccis_user_name_here@login.ccs.neu.edu ```

Navigate to your Monorepo directory and do a ```git pull```. This will add all of the files I have previously pushed into your repositories.

# Part 1 - Understanding a struct - Creating Custom Data Types

A struct is a user defined data type (i.e. it does not exist natively in C) that stores multiple pieces of data. We call this a composite data type. Here is an example of a struct in C:

```cpp
  // The keyword 'struct' is followed by our new data type name.
  struct Student{
    int age;      // A field called 'age' that holds integer values is stored.
    int userID;   // An additional field 'userID' also holds integer values.
  };
  
  // Using the struct
  int main(){
    // We create a new struct named 'mike'
    // Note the 'struct' keyword is followed by the data type we defined above.
    struct Student mike;
    // We set the fields for our variable 'mike', which were previously not initialized.
    mike.age = 100;
    mike.userID = 123456789;
  
    return 0;
  }
```

# Part 2 - Understanding Pointers

<img src="./media/pointer.png" style="float:right;" alt="Pointer">

A pointer is a variable that points to an address in memory. That is, it stores an 'address' in memory as its value.

Here are some examples in a program you can type out and run.

```cpp
#include <stdio.h>
  
// Using the struct
int main(){
	// A regular variable	
	int x = 10;
	// A pointer that points to 
	// where 'x' is stored in memory.
	// Think of the data type as 'int*' 
	// (i.e. the asterisk or star is stuck to the data type)
	int* pointer_x = &x;
	// So if we print out the value we should get some
	// address in memory.	
	// (Note: You can google what %p is doing)
	// (	  Why do you think we had to cast the value?)
	printf("pointer_x value: %p\n",(void*)pointer_x);

	// Here we 'dereference' pointer_x to extract the value
	// of the 'thing' it points to. That is, what is the value
	// that exists at its address.
	printf("dereferencing pointer_x gives us %d\n",*pointer_x); 

	return 0;
}
```

So if a pointer can point to one value, and then point to another, do you think those values can be chained together?

# Part 3 - The Linked List

As previously discussed, the linked list is a data structure that can grow or expand. The way in which it does this is by 'pointing' to other addresses.

Conceptually a linked list is a composite data type called a 'node' that stores some data, and the location of the next node.

(Image from zentut)
<img src="http://www.zentut.com/wp-content/uploads/2013/04/linked-list-node.png" alt="Linked List visual">

From a coding perspective, it may look something like this.

```cpp
typedef struct node{ // Note typedef saves us some typing so we do not have to type 'struct' everytime.
    int myData;
    struct node* next;
} node_t;	// Here is where the 'typedef' name is specified as 'node_t'
```

Everytime we create a node, we point the 'next' pointer to that node. This stores the location of the next node.

(Image from zentut)
(Note the first node is typically called the 'head' and the end is the 'tail')
<img src="http://www.zentut.com/wp-content/uploads/2013/04/c-linked-list.png" alt="Linked List visual">

Here is one example of a singly linked list that exists in stack allocated memory.

```cpp
#include <stdio.h>

typedef struct node{
	int myData;
	struct node* next;
}node_t;
  
// Using the struct
int main(){

	// Create a first node
	node_t node1;
	node1.myData = 100;
	// Create a second node
	node_t node2;
	node2.myData = 200;

	// Link together the nodes
	// node1 points to the address of node2
	node1.next = &node2;
	// node2 does not have a next node, so set it to 
	// NULL.
	node2.next = NULL;	

	return 0;
}

```
## Iterator Pattern

Now what if we want to traverse the linked list?

We can do so by using an 'iterator' pattern. That is, we use a temporary node that points to each node. The 'iterator' then hops from the current node_t to node_t.next each iteration until *next* it is NULL.

Here is an example you can try to program. This one is also fun to draw out on paper to understand how it works.

```cpp
#include <stdio.h>

typedef struct node{
	int myData;
	struct node* next;
}node_t;
  
// Using the struct
int main(){

	// Create a first node
	node_t node1;
	node1.myData = 100;
	// Create a second node
	node_t node2;
	node2.myData = 200;

	// Link together the nodes
	// node1 points to the address of node2
	node1.next = &node2;
	// node2 does not have a next node, so set it to 
	// NULL.
	node2.next = NULL;	

	// iterating through the nodes
	node_t* iterator;
	// point to the first node (i.e. the head of the list)
	iterator = &node1;
	// While the iterator is not NULL, continue
	while(iterator != NULL){
		// Print myData, which is the head in the first iteration.
		printf("%d\n",iterator->myData);
		// Then move our iterator to whatever our 'next' node is in the linked list.
		iterator = iterator->next;
		// If our iterator is NULL, this loop terminates.
	}

	return 0;
}
```


# Part 4 - The task--linked list function with real world data

Now we are ready to put our linked list to work.

## First task - obtain some data

The first thing we will do, is write a shell script (by modifying **data.sh**) to obtain some data. Provided below are some examples for obtaining some data that we can read in using shell scripts. You can choose whichever data you and your partner like.

```shell
# Column selector for Red Sox data (prints out index and column name):
curl -s http://www.ccs.neu.edu/home/awjacks/cs3650f18/Labs/2/red_sox_history.csv | awk -F ',' '{ if (NR ==1)  for (i=1; i<=NF; i++){ print i, $i } }

# Win column from Red Sox historical data:
curl -s http://www.ccs.neu.edu/home/awjacks/cs3650f18/Labs/2/red_sox_history.csv | awk -F ',' '{ if (NR > 2)  { print $5 } }' > /tmp/sox_wins.txt

# An alternative win column selector (Now you know about curl and wget)
wget -O - http://www.mshah.io/comp/Fall18/Systems/Lab/2/baseballdata.csv | cut -d ',' -f 5 | tail -n +2 > data.txt

# There are more public domain texts at the Guttenberg project https://www.gutenberg.org/ 
# Below are some other examples.

# US Declaration of Independence broken up at each comma:
curl -s http://www.ccs.neu.edu/home/awjacks/cs3650f18/Labs/2/usdeclar.txt | awk -F ',' '{ if (NR > 6)  for (i=1; i<=NF; i++) { print $i } }' > /tmp/doi-segment.txt

# US Declaration of Independence word by word:
curl -s http://www.ccs.neu.edu/home/awjacks/cs3650f18/Labs/2/usdeclar.txt | awk '{ if (NR > 6)  for (i=1; i<=NF; i++) { print $i } }' > /tmp/doi-word.txt

```

## Task 2 - Read and store data

Your second task is to read in the data you have generated and store it in a linked list.

Your guidelines for this task are:
1. Write a function (create_list) that creates a Linked list and reads data line by line from a text file. 
	1. *Hint* This means within your function you must allocate on the heap.
2. Create a second function (print_list) that iterates through the linked list and prints out the data.
	1. The data should be output it in some meaningful way.
3. Write a third function(free_list) that free's your linked list.
	1. This means you are calling 'free' on each node you have malloc'd. Think carefully about how to do this. How will you know this works?

### Example output with redsox data

Here is an example output of a program (criteria two from task 2) of the output:

In our print_list function, as it is traversed, based on the value found, the data is printed and output.

```
101 wins -- This was a good year.
93 wins -- This was a good year.
93 wins -- This was a good year.
78 wins -- We did okay.
71 wins -- This was a bad year.
// etc.
```

**Hints**
- What does this code do? ``` node_t* new_node = (node_t*)malloc(sizeof(node_t));```
- Would it be useful to make a ```node_t* create_node(int data, node_t* next)``` function?
  - You may use the http://www.zentut.com/c-tutorial/c-linked-list/ resource as a reference. Cite sources in your source file if you use them.
- Depending on the data you read in, it may be text or integer based--adapt your function signatures as needed.

# Deliverable

- Modify the file called **linkedlist.c** and **data.sh** demonstrating an example of a linked list following the guidelines in Part 4.


# More resources to help

- Structs: https://www.tutorialspoint.com/cprogramming/c_structures.htm
- Pointers: https://www.tutorialspoint.com/cprogramming/c_pointers.htm
- Linked List: http://www.zentut.com/c-tutorial/c-linked-list/ or https://www.cprogramming.com/tutorial/c/lesson15.html
- Typedef: https://en.wikipedia.org/wiki/Typedef
