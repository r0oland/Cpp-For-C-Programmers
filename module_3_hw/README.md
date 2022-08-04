## Reference Abstractions:  

Implementing Dijkstra’s algorithm requires thinking about at least three basic abstractions: 
- Graph G = (V, E)
- PriorityQueue
- ShortestPath algorithm

Additionally, deciding on a scheme for naming vertices (V) is an important first step in implementation design.
By convention, vertices are generally mapped onto the set of Integers in the range from 0 : |V| -1.  
This provides an effective Key into sequential containers (like ARRAY) to access vertex records in constant time - Θ(1). 

### Class PriorityQueue

The value of the PriorityQueue is to always have access to the vertex with the next shortest link in the shortest path calculation at the top of the queue. A typically implementation is a minHeap:

- chgPrioirity(PQ, priority): changes the priority (node value) of queue element.
- minPrioirty(PQ): removes the top element of the queue.
- contains(PQ, queue_element): does the queue contain queue_element.
- Insert(PQ, queue_element): insert queue_element into queue


### Class ShortestPath

Finally, the class: ShortestPathAlgo - implements the mechanics of Dijkstra’s algorithm. Besides having member fields (has a relationship) of Graph and Priority Queue, an additional ADT maybe required to maintain the parent relationship of the shortest path.

- vertices(List): list of vertices in G(V,E).
- path(u, w): find shortest path between u-w and returns the sequence of vertices representing shorest path u-v1-v2-…-vn-w.
- path_size(u, w): return the path cost associated with the shortest path.

The class implementing your Monte Carlo simulation is the workflow manager for this assignment, but other helper classes may be necessary depending on your particular implementation

## Notes and Reminders

Write an appropriate set of constructors for each of your classes ensuring proper initialization – especially think about the process for declaring and initializing a graph.

In this implementation, assume that an edge will have a positive cost function like distance (no negative edge cost).

Assume the graph edges (E)  are undirected.

Ensure that your ADTs support a graph of at least size 50.

The random graph procedure should have edge density as a parameter and distance range as a parameter.

Random graph generator should generate a sufficient set of edges to satisfy the edge density parameter, and each edge should be assigned a randomly generated cost based on the distance range parameter.

So a graph whose density is 0.1 would have 10% of its edges picked at random and its edge distance would be selected at random from the distance range.

Compute for a set of randomly generated graphs an average shortest path.