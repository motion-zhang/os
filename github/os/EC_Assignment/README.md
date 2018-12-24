# Extra Credit Assignment: K-source shortest paths

# Due December 1, 2018 @ 11:59pm

TODO Please edit the following information in your assignment

- Name:
- How many hours did it take you to complete this assignment?
- Did you collaborate with any other students/TAs/Professors?
- Did you use any external resources? (Cite them below)
  - tbd
  - tbd
- (Optional) What was your favorite part of the assignment?
- (Optional) How would you improve the assignment?

# Logistics

__This is an *OPTIONAL* extra credit assignment.  The points you earn will be added to your lowest assignment grade.  You can NOT go over 100% on any assignment.  Any points left over after raising your lowest grade to 100% will be discarded.  Task 1 is manditory if you do the assignment.  You choose how much you want to do and turn in.__

For this assignment, you can use either your Linux VM or the CCS machines.  You will likely have much better performance on the CCS machines. 

# Introduction
One of the ways to traverse a graph is using Breadth First Search (BFS).  BFS has several nice qualities:  
- Computes if the graph is connected
- Visits all the vertices of the graph
- Can find a path with the minimum number of edges between any two vertices
- Can find a simple cycle


# The Breadth First Search Algorithm
BFS is an algorithm where you start traversing from a selected node (the source or start node) and traverse the graph layerwise, exploring the neighbor nodes (nodes which are directly connected to source node). One done, you move towards the next-level neighbor nodes.

A graph can contain cycles, which may bring you to the same node again (and again, and again, ...) while traversing the graph. To avoid processing the same node over and over again, you need to mark the node after it is processed. 

The algorithm puts each node of the graph into one of two categories:
1. Visited
1. Not Visited

The goal of the algorithm is to mark each node as visited while avoiding cycles.

The algorithm works as follows:

Start by putting the source or start node at the back of a queue .
Take the front item of the queue and add it to the visited list.
Create a list of that node’s adjacent nodes. Add the ones which aren't in the visited list to the back of the queue.
Keep repeating steps 2 and 3 until the queue is empty.

The queue follows a First In First Out (FIFO) queuing method, and therefore, the neighbors of the node will be visited in the order in which they were inserted in the node i.e. the node that was inserted first will be visited first, and so on. 

If the graph is thought to not be connected, run BFS starting at every node to cover all the nodes. 

# Example:
Let’s look at an example with five nodes (from https://www.programiz.com/dsa/graph-bfs).

<img align="center" src="https://cdn.programiz.com/sites/tutorial2program/files/graph-bfs-step-0.jpg" width="600px" alt="picture">

Let’s start with node 0, the BFS algorithm starts by putting it in the Visited list and putting all its adjacent nodes in the queue.

<img align="center" src="https://cdn.programiz.com/sites/tutorial2program/files/graph-bfs-step-1.jpg" width="600px" alt="picture">

Next, we visit the element at the front of queue i.e. 1 and go to its adjacent nodes. Since 0 has already been visited, we visit 2 instead (which is at the front of the queue).

<img align="center" src="https://cdn.programiz.com/sites/tutorial2program/files/graph-bfs-step-2.jpg" width="600px" alt="picture">

Node 2 has an unvisited adjacent node in 4, so we add that to the back of the queue and visit 3, which is at the front of the queue.

<img align="center" src="https://cdn.programiz.com/sites/tutorial2program/files/graph-bfs-step-3.jpg" width="600px" alt="picture">

<img align="center" src="https://cdn.programiz.com/sites/tutorial2program/files/graph-bfs-step-4.jpg" width="600px" alt="picture">

Node 3 doesn’t have any neighbors that have not already been marked as Visited.  So we mark it as Visited and visit node 4, which is at the front of the queue. 

<img align="center" src="https://cdn.programiz.com/sites/tutorial2program/files/graph-bfs-step-5.jpg" width="600px" alt="picture">

Since the queue is empty, we have completed the Depth First Traversal of the graph.

# Task 1: Single Source Shortest Path (If you do the assignment, you must do Task 1)
You are given a source node, 5, find the shortest path from the source node to rest of the nodes using BFS. Print out the path length from the source node to all the nodes (assume the edge cost is 1 for all edges).  Print out the path as a distance ordered list of “(node, distance from source)” pairs separated by commas.  For the example above, the list for source 0 would be: (0, 0), (1, 1), (2, 1), (3, 1), (4, 2).

BFS gives you the shortest path from one node to all the other connected nodes.  You will need to augment the algorithm above to record the path length ( # of levels) to each node you touch.  

## Reading in a graph representation
One of the ways to represent the graph structure is using edge sets. A graph consists of nodes connected by the set of edges. In this assignment, you are given text files containing edge info. Each line contains edge represented by A, B meaning there’s an edge from node A to node B.

For simplicity, we assume the length of all edges are the same (one unit).

Sample edge file
-    A, B
-    B, C
-    C, D
-    D, A



# Task 2: K-source Shortest Path
Now you are given K source nodes. Find the shortest path from K nodes to all other nodes. For each source node, print out the path in an distance ordered list of “(node, distance from source)” pairs separated by commas.  

## Part 1:
- Write a single thread/process version to iteratively calculate the shortest path from K given nodes.
- Write a multi-process / multi-threaded version (K threads?) to calculate shortest path to all the nodes.  You can use any of the techniques we’re covered, from forking sub-processes, to generating multiple threads explicitly, to using OpenMP.

Graph| K nodes
-----|--------
8-nodes.txt | All nodes
10-nodes.txt | All nodes
93-nodes.txt | 3, 47, 18, 26, 57, 27, 63, 6, 57, 52, 74, 52, 30, 24, 56, 87, 37, 78, 34, 64, 52, 80, 8, 44, 59, 27, 16, 55, 60, 43, 27, 16
100-nodes.txt | 3, 47, 18, 26, 57, 27, 63, 6, 57, 52, 74, 52, 30, 24, 56, 87, 37, 78, 34, 64, 52, 80, 8, 44, 59, 27, 16, 55, 60, 43, 27, 16
1000-nodes.txt | Do not do for Part 1

1. Which multi thread/proccess implementation did you choose and why?
	- *Your answer here*
1. Compare the running times for finding K-source shortest paths on your single process implementation versus your multi-thread/process implementation and explain your findings.

	- *Your answer here*

## Part 2:
Compare the running time (mean and median running time) of both implementations over 101 runs for different size of graphs in the repo.  Select the K source nodes randomly (uniform) from all the nodes in the network for each run.  The node IDs range from 0 to N-1, where N is the number of nodes in the network. Add a table to the README for the mean and median running times for each size network that is in the repo. See an example below.  

### Questions

1. Why did I ask you to randomly select the K nodes for each run? 
	- *Your answer here*
2. What do you think the performance would have been over the multiple runs if you used the same set of K nodes?  
	- *Your answer here*
3. What would you have been measuring if you used the same set of K nodes for in the experiment?
	- *Your answer here*
4. What other data might you want to collect about the system environment when you ran your experiment to help you compare your results to others running on the same or different types computers?
	- *Your answer here*
 
Graph  | Mean run time (101 runs) | Median run time (101 runs)
-----------|--------------------------|---------------------------
8-nodes.txt| nnnn usec | nnnn usec
10-nodes.txt | ... | ...
93-nodes.txt | ... | ...
100-nodes.txt |... | ...
1000-nodes.txt | ... | ...

# Deliverable

- Upload bfs.c, k-bfs.c, and k-multi-bfs.c.
- Specify what Tasks and parts you wish to be graded. 
	- *Your answer here*
- Answer the questions in the Task you wish to be graded. 

# Rubric

- 30 points - Task 1

- 30 points - Task 2
	- 20 points for Part 1
	- 10 points for Part 2

Remember the points you earn are added to your lowest Assignment grade.  You cannot go over 100% on any assignment. 

     
### Tips
1. Many on-line sites refer to BFS over directed graphs.  The graphs in this assignment are undirected and do not have links that loop back to the same node. 
1. Commit your code changes to the repository often, this is best practice.
1. Do not commit your .o file or your executable file to the repository, this is considered bad practice!
1. On Functionality/Style
	1. You should have comments in your code to explain what is going on, and use good style (80 characters per line maximum for example, functions that are less than 50 lines, well named variables, well named functions etc.).

### Resources

- [Breadth First Search or BFS for a Graph](https://www.geeksforgeeks.org/breadth-first-search-or-bfs-for-a-graph/)
- [Breadth First Search](https://www.hackerearth.com/practice/algorithms/graphs/breadth-first-search/tutorial/)
- [Breadth first search](https://www.programiz.com/dsa/graph-bfs) A nice queue implementation in C.


