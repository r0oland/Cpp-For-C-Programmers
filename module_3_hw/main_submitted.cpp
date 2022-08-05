// based in part on infos found in the following sources
// https://en.wikipedia.org/wiki/Dijkstra's_algorithm#
// https://www.youtube.com/watch?v=2E7MmKv0Y24

#include <stdlib.h> /* srand, rand */
#include <iostream>
#include <vector>
#include <chrono>
#include <limits>

using namespace std::chrono;
using namespace std;

// define limits for "length" or weight of the edges
enum EdgeWeight { NO_CON = 0};

void swap(int& x, int& y); // fct declaration

// #############################################################################
// graph Class using Edge Matrix Representation
// #############################################################################
class GraphMatrix {
public:
  GraphMatrix(int32_t nNodes = 50, float prob = 0.5, vector<int> range = {0,100}) : n(nNodes) {
    srand(time(NULL)); // seed the random number generator

    // create empty 2d matricies for connections and weights
    conMap.resize(n);
    weightMap.resize(n);
    for (int i = 0; i < n; i++) {
      conMap[i].resize(n, false);
      weightMap[i].resize(n, EdgeWeight::NO_CON);
    }
    for (int x = 0; x < n; x++) {
      for (int y = x + 1; y < n; y++) {
        int rCon = rand() % 101; // rand number between 0 and 100
        // rand number between EdgeWeight::MIN and EdgeWeight::MAX
        int rWeight = (rand() % range[1]) + range[0];
        if (rCon < (prob * 100)) {
          conMap[x][y]    = true;
          weightMap[x][y] = rWeight;
          // unidirected graph, so we need to fill the other way too
          conMap[y][x]    = true;
          weightMap[y][x] = rWeight;
        }
      }
    }
  }

  ~GraphMatrix() {};

  int Get_Num_Nodes() {
    return n;
  }

  // methods defined below -----------------------------------------------------
  void Print(void); // print out connectivity matrix

  // return nodes y such that there is an edge from x to y.
  vector<int> Get_Neighbors(int x);
  // print neighbors for x
  void Print_Neighbors(int x);

  // short inline methods  ---------------------------------------------------
  // tests whether there is an edge from node x to node y.
  bool Is_Adjacent(int x, int y) {
    if ((x < n) && (y < n) && (x != y)) {
      return conMap[x][y];
    } else {
      return false;
    }
  };

  // adds to G the edge from x to y
  // returns true if the edge was added, false if not added or already exists
  bool Add_Node(int x, int y) {
    if ((x < n) && (y < n) && (x != y)) {
      conMap[x][y] = true;
      return true;
    } else {
      return false;
    }
  }
  // removes the edge from x to y, if it is there.
  void Del_Node(int x, int y) {
    if ((x < n) && (y < n)) {
      conMap[x][y] = false;
    }
    return;
  }

  // get weight of a connection between x and y
  int Get_Weight(int x, int y) {
    if ((x < n) && (y < n)) {
      return weightMap[x][y];
    } else {
      return EdgeWeight::NO_CON;
    }
  }

  // no need to set the weight...we do that during ctor of GraphMatrix class

  // void dijkstra(int start); // TODO

  // set / get method declarations ---------------------------------------------
  int Get_Num_Edges();
  float Get_Density();

private:
  int n;                         // number of graph nodes / vertices
  int nEdges;                    // number of edges
  float density;                 // density of the graph
  vector<vector<bool>> conMap;   // connectivity matrix
  vector<vector<int>> weightMap; // weight matrix, range 0-255
};

// -----------------------------------------------------------------------------
void GraphMatrix::Print() {
  cout << "  ";
  // print column indices
  for (int i = 0; i < n; i++) {
    cout << " " << i << " ";
  }
  cout << endl;
  for (int x = 0; x < n; x++) {
    cout << x << ":"; // print row indices
    for (int y = 0; y < n; y++) {
      if (x == y) {
        cout << " \\ ";
      } else if (conMap[x][y]) {
        cout << " " << weightMap[x][y] << " ";
      } else {
        cout << "   ";
      }
    }
    cout << endl;
  }
}

// -----------------------------------------------------------------------------
// Setter / Getter Methods come here...
// -----------------------------------------------------------------------------
int GraphMatrix::Get_Num_Edges() {
  nEdges = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (conMap[i][j]) {
        nEdges++;
      }
    }
  }
  return nEdges;
}

// -----------------------------------------------------------------------------
float GraphMatrix::Get_Density() {
  int32_t nPossibleEdges = n * (n - 1); // we don't allow self-loop
  nEdges                 = Get_Num_Edges();
  density                = (static_cast<float>(nEdges) / nPossibleEdges);
  return density;
}

// -----------------------------------------------------------------------------
vector<int> GraphMatrix::Get_Neighbors(int x) {
  vector<int> neighbors;
  for (int i = 0; i < n; i++) {
    if (conMap[x][i]) {
      neighbors.push_back(i);
    }
  }
  return neighbors;
}

// -----------------------------------------------------------------------------
void GraphMatrix::Print_Neighbors(int x) {
  vector<int> neighbors = Get_Neighbors(x);
  cout << "Neighbors of " << x << ": " << endl;
  for (auto i : neighbors) {
    cout << x << "->" << weightMap[x][i] << "->" << i << endl;
  }
}

// Dikstra's Algorithm

// A utility function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree
int minDistance(vector<int> dist, vector<bool> sptSet) {

  // Initialize min value
  int min = numeric_limits<int>::max();
  int min_index;

  for (int v = 0; v < dist.size(); v++) {
    if ((sptSet[v] == false) && (dist[v] <= min)) {
      min       = dist[v];
      min_index = v;
    }
  }
  return min_index;
}

// A utility function to print the constructed distance array
void printSolution(vector<int> dist) {
  int cumSum = 0;
  // cout << "Vertex \tDistance from Source" << endl;
  for (int i = 0; i < dist.size(); i++) {
    if (dist[i] == numeric_limits<int>::max()) {
      // cout << i << "\t\t" << "INF" << endl;
    } else {
      // cout << i << "\t\t" << dist[i] << endl;
      cumSum += dist[i];
    }
  }
  cout << "#######################################################" << endl;
  cout << "Average Distance: " << static_cast<float>(cumSum)/dist.size() << endl;
  cout << "#######################################################" << endl;

}

// Function that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
void dijkstra(GraphMatrix G, int src) {

  // Create a priority queue to store vertices that
  int nNodes = G.Get_Num_Nodes();
  // dist[i] will hold the shortest distance from src to i
  vector<int> dist(nNodes, numeric_limits<int>::max());

  // sptSet[i] will be true if vertex i is included in shortest
  // path tree or shortest distance from src to i is finalized
  vector<bool> sptSet(nNodes, false);

  // Distance of source vertex from itself is always 0
  dist[src] = 0;

  // Find shortest path for all vertices
  for (int count = 0; count < nNodes - 1; count++) {
    // Pick the minimum distance vertex from the set of vertices not
    // yet processed. u is always equal to src in the first iteration.
    int u = minDistance(dist, sptSet);

    // Mark the picked vertex as processed
    sptSet[u] = true;

    vector<int> neighbors = G.Get_Neighbors(u); // idx of neighbors of u

    // loop through all neighbors of u
    for (const auto& v : neighbors) {
      // Update dist[v] only if is not in sptSet, there is an edge from
      // u to v, and total weight of path from src to  v through u is
      // smaller than current value of dist[v]
      if (!sptSet[v] && (dist[u] != numeric_limits<int>::max()) &&
          (dist[u] + G.Get_Weight(u, v)) < dist[v]) {
        dist[v] = dist[u] + G.Get_Weight(u, v);
      }
    }
  }

  // print the constructed distance array
  printSolution(dist);

}

int main() {

  auto startTime = high_resolution_clock::now();

  GraphMatrix MyGraph(100, 0.20, {1,100});

  cout << "### Graph Infos ### " << endl;
  cout << "Number of edges: " << MyGraph.Get_Num_Edges() << endl;
  cout << "Density: " << MyGraph.Get_Density() << endl;
  cout << endl;

  // Compute for a set of randomly generated graphs an average shortest path.
  dijkstra(MyGraph, 0);

  auto stopTime            = high_resolution_clock::now();
  duration<float> duration = stopTime - startTime;
  // auto duration = duration_cast<microseconds>(stop - start);
  // auto myTime = duration_cast<fsec>(duration)*1000;
  cout << "Total Runtime: " << duration.count() * 1000 << " ms" << endl;

  return 0;
}

// util to swap two ints
inline void swap(int& x, int& y) {
  int temp = x;
  x        = y;
  y        = temp;
  return;
}