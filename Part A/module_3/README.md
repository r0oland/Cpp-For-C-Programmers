## Reference Abstractions:  

Implementing Dijkstra’s algorithm requires thinking about at least three basic abstractions: 
- Graph G = (V, E)
- PriorityQueue
- ShortestPath algorithm

### Class Graph:

A potential partial interface definition for a Graph could be:

**methods**
- V(G): returns the number of vertices in the graph
- E(G): returns the number of edges in the graph
- adjacent (G, x, y): tests whether there is an edge from node x to node y.
- neighbors (G, x): lists all nodes y such that there is an edge from x to y.
- add (G, x, y): adds to G the edge from x to y, if it is not there.
- delete (G, x, y): removes the edge from x to y, if it is there.
- get_node_value (G, x): returns the value associated with the node x.
- set_node_value( G, x, a): sets the value associated with the node x to a.
- get_edge_value( G, x, y): returns the value associated to the edge (x,y).
- set_edge_value (G, x, y, v): sets the value associated to the edge (x,y) to v.

### Class PriorityQueue

The value of the PriorityQueue is to always have access to the vertex with the next shortest link in the shortest path calculation at the top of the queue. A typically implementation is a minHeap:

- chgPrioirity(PQ, priority): changes the priority (node value) of queue element.
- minPrioirty(PQ): removes the top element of the queue.
- contains(PQ, queue_element): does the queue contain queue_element.
- Insert(PQ, queue_element): insert queue_element into queue
- top(PQ):returns the top element of the queue.
- size(PQ): return the number of queue_elements.

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