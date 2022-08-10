### Class ShortestPath

Finally, the class: ShortestPathAlgo - implements the mechanics of Dijkstra’s algorithm. Besides having member fields (has a relationship) of Graph and Priority Queue, an additional ADT maybe required to maintain the parent relationship of the shortest path.

- vertices(List): list of vertices in G(V,E).
- path(u, w): find shortest path between u-w and returns the sequence of vertices representing shorest path u-v1-v2-…-vn-w.
- path_size(u, w): return the path cost associated with the shortest path.

The random graph procedure should have edge density as a parameter and distance range as a parameter.

Compute for a set of randomly generated graphs an average shortest path.