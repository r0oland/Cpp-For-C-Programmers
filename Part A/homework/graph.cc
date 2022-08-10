#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <random>
#include <fstream>
#include <string>
#include <queue>
#include <unordered_set>

using namespace std;

#include "graph.h"

// define a node including a vertex and its cost connecting to the MST
struct node {
    int vertex;
    double cost;
    
    node(int vt, double c): vertex(vt), cost(c) {}

    bool operator< (const node& other) const {
        return cost > other.cost;
    }
};

typedef priority_queue<node> mypq_type;

Vertex::Vertex(int id): id(id), val(0) {}

Edge::Edge(Vertex *v1, Vertex *v2): first(v1), second(v2), val(0) {}

ostream& operator<<(ostream& out, const Vertex& v) {
    out << "v" << v.id << ": " << v.val;
    return out;
}

ostream& operator<<(ostream& out, const Edge& e) {
    out << "e: " << e.first->id << "--" << e.second->id << ", " << e.val;
    return out;
}

Graph::Graph(size_t size, double density): v(size), e(0) {
    for(int i = 0; i < size; i++) {
        Vertex vt(i);
        graph.push_back(vt);
    }
    default_random_engine el(r());
    uniform_real_distribution<double> ud(0, 1);
    uniform_real_distribution<double> uv(1.0, 10.0);
    for(int i = 0; i < size; i++) {
        for(int j = i + 1; j < size; j++) {
            if(ud(el) < density) {
                Edge ed(&graph[i], &graph[j]);
                ed.val = uv(el);
                graph[i].edges.push_back(ed);
                graph[j].edges.push_back(ed);
                e++;
            }
        }
    }
}

Graph::Graph(string filename) {
    ifstream data(filename);
    istream_iterator<int> start(data), end;
    v = *start;
    e = 0;
    ++start;
    for(int i = 0; i < v; i++) {
        Vertex vt(i);
        graph.push_back(vt);
    }
    while(start != end) {
        int i = *start;
        ++start;
        int j = *start;
        ++start;
        Edge ed(&graph[i], &graph[j]);
        ed.val = static_cast<double>(*start);
        graph[i].edges.push_back(ed);
        ++start;
        ++e;
    }
    e = e / 2;
}    

int Graph::V() {
    return v;
}

int Graph::E() {
    return e;
}

bool Graph::adjacent(int x, int y) {
    if(x < 0 || x >= v || y < 0 || y >= v || x == y) {
        return false;
    }
    vector<Edge> x_edges = graph[x].edges;
    for(vector<Edge>::iterator it = x_edges.begin(); it != x_edges.end(); ++it) {
        if(it->first->id == y || it->second->id == y) {
            return true;
        }
    }
    return false;
}

vector<int> Graph::neighbors(int x) {
    vector<int> nei;
    if(x < 0 || x >= v) {
        return nei;
    }
    vector<Edge> x_edges = graph[x].edges;
    for(vector<Edge>::iterator it = x_edges.begin(); it != x_edges.end(); ++it) {
        if(it->first->id == x) {
            nei.push_back(it->second->id);
        } else {
            nei.push_back(it->first->id);
        }
    }
    return nei;
}

bool Graph::add_edge(int x, int y) {
    if(x < 0 || x >= v || y < 0 || y >= v || x == y
            || adjacent(x, y)) {
        return false;
    }
    default_random_engine el(r());
    uniform_real_distribution<double> uv(1.0, 10.0);
    Edge ed(&graph[x], &graph[y]);
    ed.val = uv(el);
    graph[x].edges.push_back(ed);
    graph[y].edges.push_back(ed);
    e++;
    return true;
}
        
bool Graph::delete_edge(int x, int y) {
    if(x < 0 || x >= v || y < 0 || y >= v || x == y 
            || !adjacent(x, y)) {
        return false;
    }
    vector<Edge>* x_edges = &(graph[x].edges);
    for(vector<Edge>::iterator it = x_edges->begin(); it != x_edges->end(); ++it) {
        if(it->first->id == y || it->second->id == y) {
            x_edges->erase(it);
            break;
        }
    }
    vector<Edge>* y_edges = &(graph[y].edges);
    for(vector<Edge>::iterator it = y_edges->begin(); it != y_edges->end(); ++it) {
        if(it->first->id == x || it->second->id == x) {
            y_edges->erase(it);
            break;
        }
    }
    e--;
    return true;
}

Vertex* Graph::get_vertex(int x) {
    if(x < 0 || x >= v) {
        return nullptr;
    }
    return &(graph[x]);
}

double Graph::get_node_value(int x) {
    if(x < 0 || x >= v) {
        return -1;
    }
    return graph[x].val;
}

bool Graph::set_node_value(int x, double a) {
    if(x < 0 || x >= v) {
        return false;
    }
    graph[x].val = a;
    return true;
}

double Graph::get_edge_value(int x, int y) {
    if(x < 0 || x >= v || y < 0 || y >= v || x == y
            || !adjacent(x, y)) {
        return -1;
    }
    vector<Edge>* x_edges = &(graph[x].edges);
    for(vector<Edge>::iterator it = x_edges->begin(); it != x_edges->end(); ++it) {
        if(it->first->id == y || it->second->id == y) {
            return it->val;
        }
    }
    return -1;
}

bool Graph::set_edge_value(int x, int y, double a) {
    if(x < 0 || x >= v || y < 0 || y >= v || x == y
            || !adjacent(x, y)) {
        return false;
    }
    vector<Edge>* y_edges = &(graph[y].edges);
    for(vector<Edge>::iterator it = y_edges->begin(); it != y_edges->end(); ++it) {
        if(it->first->id == x || it->second->id == x) {
            it->val = a;
        }
    }
    vector<Edge>* x_edges = &(graph[x].edges);
    for(vector<Edge>::iterator it = x_edges->begin(); it != x_edges->end(); ++it) {
        if(it->first->id == y || it->second->id == y) {
            it->val = a;
            return true;
        }
    }
    return false;
}

vector<Vertex> Graph::get_vertices() {
    return graph;
}

// This funciton implement Prim algorithm to find the MST
double Graph::find_mst_prim() {

    // Total cost of the MST
    double cost = 0;

    // Open set stores the unvisited node
    unordered_set<int> open;
    // Close set stors the visited node in the MST
    unordered_set<int> close;
    for(int i = 0; i < v; ++i) {
        open.insert(i);
    }
    // The search starts from node 0. Node 0 works as a root and no MST edgeis bounded to node 0.
    node start(0, 0);
    // The priority queue stores the visiting node connecting to the MST 
    mypq_type pq;
    pq.push(start);
    // Running the Prim algorithm
    while(!pq.empty()) {
        // Find the next node bounded to the MST with minimum cost
        node curr = pq.top();
        pq.pop();
        // Skip the processed nodes
        if(close.find(curr.vertex) != close.end()) {
            continue;
        }
        close.insert(curr.vertex);
        cost += curr.cost;
        // Loop the neightbors of the curr Vertex
        for(Edge &edge : graph[curr.vertex].edges) {
            int vt = 0;
            if(edge.first->id == curr.vertex) {
                vt = edge.second->id;
            } else {
                vt = edge.first->id;
            }
            // case 1: the neighbor is unvisited
            if(open.find(vt) != open.end()) {
                graph[vt].edge_mst = &edge;
                open.erase(vt);
                node next(vt, edge.val);
                pq.push(next);
            } 
            // case 2: the neighbor is in the queue and a shorter bounding edge is found 
            else if(close.find(vt) == close.end() && edge.val < graph[vt].edge_mst->val) {
                graph[vt].edge_mst = &edge;
                node next(vt, edge.val);
                pq.push(next);
            }
        }
    }
    return cost;
}

ostream& operator<<(ostream& out, Graph &g) {
    out << "Number of vertices: " << g.V() << endl;
    out << "Number of edges: " << g.E() << endl;
    vector<Vertex> vertices = g.get_vertices();
    int n = vertices.size();
    for(int i = 0; i < n; i++) {
        cout << vertices[i] << " : ";
        for(vector<Edge>::iterator it = vertices[i].edges.begin(); it != vertices[i].edges.end(); ++it) {
            cout << *it << "; ";
        }
        cout << endl;
    }
    return out;
}

