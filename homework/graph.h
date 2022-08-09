/**
    @file       graph.h
    @author     Kexi Liu
    @date       12/10/17
    @version    1.0

    @brief      This header file defines the graph class

    @section DESCRIPTION
    This graph class is an undirected graph containing n vertices (nodes) labeled from 0 to n - 1. Each node contains a double value. There could be an edge connecting any two vertices (nodes). Each edge contains a double value, e.g. the length.
*/

#ifndef __GRAPH_H_INCLUDED__
#define __GRAPH_H_INCLUDED__

#include <vector>
#include <iostream>
#include <random>
#include <string>

// Vertex is the node in the graph
struct Vertex;

// Edge is the edge connecting two nodes in the graph
struct Edge {
    
    // the first and second vertices the edge connects
    Vertex *first, *second;

    // the value in the edge, e.g. length (non-negative value)
    double val;
    
/**
    @brief  edge constructor

    @param  v1 is the first vertex the edge connects
    @param  v2 is the second vertex the edge connects 
*/
    Edge(Vertex* v1, Vertex* v2);
};

struct Vertex {

    // the id of the vertex
    int id;

    // the value in the vertex
    double val;

    // the edge list connecting to the vertex
    vector<Edge> edges;

    // The ptr to the edge in the minimum spanning tree connecting this Vertex. The first node (node 0) is the root with null_ptr
    Edge *edge_mst;

/**
    @brief  vertex constructor

    @param  id is the id of the vertex
*/
    Vertex(int id);
};

// output stream operator << override for vertex 
ostream& operator<<(ostream& out, const Vertex& v);

// output stream operator << override for edge
ostream& operator<<(ostream& out, const Edge& e);

class Graph {

private:

    // v is the total number of vertices, e is the total number of edges
    int v, e;

    // the list of all the vertices in the graph
    vector<Vertex> graph;

    // random generator
    random_device r;

public:

/**
    @brief  graph constructor

    @param  size is the total number of the nodes in the graph
    @param  density is the percentage of edges generated randomly from all the possible edges 
*/
    Graph(size_t size, double density);

/**
    @brief  graph constructor from an input file

    @param  the input file name
    The file format will be an initial integer that is the node size of the graph and the further values will be integer triples: (i, j, cost).
*/
    Graph(std::string filename);

/**
    @brief  get the number of vertices in the graph

    @return the number of vertices in the graph
*/
    int V();

/**
    @brief  get the number of edges in the graph

    @return the number of edges in the graph
*/
    int E();
    
/**
    @brief  tests whether there is an edge from node x to node y

    @param  x is the id of node x
    @param  y is the id of node y 
    @return whether the edge between x and y exists
*/
    bool adjacent(int x, int y);

/**
    @brief  get all the neighbors of a vertex

    @param  x is the id of node x
    @return a list of all nodes y such that there is an edge from x to y
*/
    vector<int> neighbors(int x);

/**
    @brief  add an edge from x to y, if it is not there

    @param  x is the id of node x
    @param  y is the id of node y
    @return whether the addition is successful
*/
    bool add_edge(int x, int y);

/**
    @brief  delete the edge from x to y, if it is there

    @param  x is the id of node x
    @param  y is the id of node y
    @return whether the deletion is successful
*/
    bool delete_edge(int x, int y);

/**
    @brief  get the pointer to the node x

    @param  x is the id of node x
    @return the pointer to the node x
*/
    Vertex* get_vertex(int x);
/**
    @brief  get the value of node x

    @param  x is the id of node x
    @return the value assocaited with node x
*/
    double get_node_value(int x);

/**
    @brief  set the value of node x

    @param  x is the id of node x
    @param  a is the value to be set
    @return whether setting the value of node x successfully
*/
    bool set_node_value(int x, double a);

/**
    @brief  get the value of the edge between the nodes x and y

    @param  x is the id of node x
    @param  y is the id of node y
    @return the value assocaited with the edge between the nodes x and y
*/
    double get_edge_value(int x, int y);

/**
    @brief  set the value of the edge bewteen the nodes x and y

    @param  x is the id of node x
    @param  y is the id of node y
    @param  a is the value to be set
    @return whether setting the value of the edge successfully
*/
    bool set_edge_value(int x, int y, double a);

/**
    @brief  get all the vertices in the graph

    @return a list of all the vertices in the graph 
*/
    vector<Vertex> get_vertices();
    
/**
    @brief  find the minimum spanning tree in the graph using prim algorithm

    @return the cost of the minimum spanning tree
*/
    double find_mst_prim();

};

// output stream operator << override for graph 
ostream& operator<<(ostream& out, Graph &g);

#endif
