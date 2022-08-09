// based in part on infos found in the following sources
// https://en.wikipedia.org/wiki/Dijkstra's_algorithm#
// https://www.youtube.com/watch?v=2E7MmKv0Y24

#include <stdlib.h> /* srand, rand */
#include <iostream>
#include <vector>
#include <chrono>
#include <limits>
#include <fstream>
#include <iterator>
#include <iomanip>
#include <queue>
#include <algorithm> // std::find

using namespace std::chrono;
using namespace std;

// define limits for "length" or weight of the edges
enum EdgeWeight { NO_CON = 0 };

enum class Color { NO_COLOR, RED, GREEN, BLUE };

// store weight / node
typedef std::pair<int, int> Node_t;
// typedef std::vector<Node_t> VNode_t;

// overload << for printing out the color
ostream& operator<<(ostream& os, Color c) {
  switch (c) {
  case Color::RED:
    os << "R";
    break;
  case Color::GREEN:
    os << "G";
    break;
  case Color::BLUE:
    os << "B";
    break;
  case Color::NO_COLOR:
    os << " ";
    break;
  }
  return os;
}

// #############################################################################
// graph Class using Edge Matrix Representation
// #############################################################################
class GraphMatrix {
public:
  GraphMatrix(int32_t nNodes, float prob, vector<int> range);

  GraphMatrix(string fileName) {
    Read_Graph_File(fileName);
  };

  ~GraphMatrix() {};

  // methods defined below -----------------------------------------------------
  void Print(void);       // print out connectivity matrix
  void Print_Color(void); // print out color of nodes matrix

  // return nodes y such that there is an edge from x to y.
  vector<int> Get_Neighbors(int x);
  // print neighbors for x
  void Print_Neighbors(int x);

  void Read_Graph_File(string fileName);

  void Prims_MST(int sourceNode);

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

  // get number of graph nodes
  int Get_Num_Nodes() {
    return n;
  }
  // same as Get_Num_Nodes() but close in style to stl vector size() etc
  int Size() {
    return n;
  }

  // find number of edges in graph
  int Get_Num_Edges();

  // calculate the graph density
  float Get_Density();

private:
  int n;                          // number of graph nodes / vertices
  int nEdges;                     // number of edges
  float density;                  // density of the graph
  vector<vector<bool>> conMap;    // connectivity matrix
  vector<vector<int>> weightMap;  // weight matrix, range 0-255
  vector<vector<Color>> colorMap; // colors per node, range 0-3
  vector<vector<Node_t>> nodes;   // matrix of nodes wight / node
};

// fct declarations
int minDistance(vector<int> dist, vector<bool> sptSet);
void printSolution(vector<int> dist);
void dijkstra(GraphMatrix G, int src);
void swap(int& x, int& y);

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
int main() {

  auto startTime = high_resolution_clock::now();

  // GraphMatrix MyGraph(10, 0.20, {1, 9});
  GraphMatrix MyGraph("../testdata_mst_data.txt");

  cout << endl;
  cout << "########## Graph Infos ##########" << endl;
  cout << "Number of nodes: " << (int)MyGraph.Size() << endl;
  cout << "Number of edges: " << (int)MyGraph.Get_Num_Edges() << endl;
  cout << "Density: " << MyGraph.Get_Density() << endl;
  cout << endl;

  MyGraph.Print();

  cout << endl;

  MyGraph.Prims_MST(0);

  auto stopTime            = high_resolution_clock::now();
  duration<float> duration = stopTime - startTime;
  // auto duration = duration_cast<microseconds>(stop - start);
  // auto myTime = duration_cast<fsec>(duration)*1000;
  cout << "Total Runtime: " << duration.count() * 1000 << " ms" << endl;

  return 0;
}

// -----------------------------------------------------------------------------
GraphMatrix::GraphMatrix(int32_t nNodes, float prob, vector<int> range) : n(nNodes) {
  srand(time(NULL)); // seed the random number generator

  // create empty 2d matricies for connections and weights
  conMap.resize(n);
  weightMap.resize(n);
  colorMap.resize(n);

  for (int i = 0; i < n; i++) {
    conMap[i].resize(n, false);
    weightMap[i].resize(n, EdgeWeight::NO_CON);
    colorMap[i].resize(n, Color::NO_COLOR);
  }

  for (int x = 0; x < n; x++) {
    for (int y = x + 1; y < n; y++) {
      int rCon = rand() % 101; // rand number between 0 and 100
      // rand number between EdgeWeight::MIN and EdgeWeight::MAX
      int rWeight = (rand() % range[1]) + range[0];
      if (rCon < (prob * 100)) {
        // create new color in range 1-3 (red, green, blue)
        Color newColor  = static_cast<Color>((rand() % 3) + 1);
        conMap[x][y]    = true;
        weightMap[x][y] = rWeight;
        colorMap[x][y]  = newColor;
        // unidirected graph, so we need to fill the other way too
        conMap[y][x]    = true;
        weightMap[y][x] = rWeight;
        colorMap[y][x]  = newColor;
      }
    }
  }
}

// -----------------------------------------------------------------------------
// read in a graph from a file.
// initial integer == node size of the graph
// remainder are integer triples: (i, j, cost)
void GraphMatrix::Read_Graph_File(string fileName) {
  ifstream file;
  file.open(fileName);
  if (!file.is_open()) {
    cout << "Error opening file" << endl;
    return;
  }

  ifstream dataFile(fileName);
  istream_iterator<int> start(dataFile), end;
  vector<int> data(start, end);

  auto it = data.begin();
  n       = *it; // get first data

  conMap.resize(n);
  weightMap.resize(n);
  colorMap.resize(n);
  nodes.resize(n);
  for (int i = 0; i < n; i++) {
    conMap[i].resize(n, false);
    weightMap[i].resize(n, EdgeWeight::NO_CON);
    colorMap[i].resize(n, Color::NO_COLOR);
    nodes[i].resize(n, {EdgeWeight::NO_CON, -1});
  }

  for (it = (data.begin() + 1); it != data.end(); it++) {
    // if the current index is needed:
    auto idx = std::distance(data.begin(), it);
    if (idx % 3 == 0) {
      int thisNode     = *(it - 2);
      int neighborNode = *(it - 1);
      int weight       = *it;
      // cout << node << " " << neighbor << " " << weight << endl;
      conMap[thisNode][neighborNode]    = true;
      weightMap[thisNode][neighborNode] = weight;
      nodes[thisNode][neighborNode]     = {weight, neighborNode};
      conMap[neighborNode][thisNode]    = true;
      weightMap[neighborNode][thisNode] = weight;
      nodes[neighborNode][thisNode]     = {weight, thisNode};

      // create new color in range 1-3 (red, green, blue) as file does not specify
      Color newColor                   = static_cast<Color>((rand() % 3) + 1);
      colorMap[thisNode][neighborNode] = newColor;
      colorMap[neighborNode][thisNode] = newColor;
    }
  }
  file.close();
}

// -----------------------------------------------------------------------------
void GraphMatrix::Print() {
  cout << "Colored Connectivity Map: " << endl;
  cout << "      ";
  // print column indices
  for (int i = 0; i < n; i++) {
    cout << " " << std::setfill('0') << std::setw(2);
    cout << i << "";
  }
  cout << endl;
  int x {0};
  int y {0};
  for (auto i : nodes) {
    cout << "N " << std::setfill('0') << std::setw(2) << x << ": "; // print row
                                                                    // indices
    y = 0;
    for (auto j : i) {
      if (x == y) {
        cout << " \\ ";
      } else if (j.first != EdgeWeight::NO_CON) {
        // see
        // https://stackoverflow.com/questions/4842424/list-of-ansi-color-escape-sequences
        // for anso color coding
        switch (colorMap[x][y]) {
        case Color::RED:
          cout << "\033[31m";
          break;
        case Color::GREEN:
          cout << "\033[32m";
          break;
        case Color::BLUE:
          cout << "\033[34m";
          break;
        }
        cout << " " << std::setfill('0') << std::setw(2) << j.first;
        cout << "\033[0m";
      } else {
        cout << "   ";
      }
      ++y;
    }
    cout << endl;
    ++x;
  }
}

// -----------------------------------------------------------------------------
void GraphMatrix::Print_Color() {
  cout << "Color Map: " << endl;
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
        cout << " " << colorMap[x][y] << " ";
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

// -----------------------------------------------------------------------------
void GraphMatrix::Prims_MST(int sourceNode) {

  cout << "Running Prims MST algorithm:" << endl;

  // The priority_queue stores the pair<weight, node>
  priority_queue<Node_t, std ::vector<Node_t>, std ::greater<Node_t>> q;

  // The cost of the source node to itself is 0
  q.push(std::make_pair(0, sourceNode));

  vector<bool> addedNodes(nodes.size(), false);

  int mst_cost = 0;
  int lastNode = 0;

  while (!q.empty()) {

    // Select the item <cost, node> with minimum cost
    Node_t item = q.top();

    q.pop(); // remove item from queue

    int cost     = item.first;
    int thisNode = item.second;

    // If the node is node not yet addedNodes to the minimum spanning tree add it,
    // and increment the cost.
    if (!addedNodes[thisNode]) {
      mst_cost += cost;
      addedNodes[thisNode] = true;
      cout << "edge: " << setfill('0') << setw(2) << lastNode;
      cout << " to " << setfill('0') << setw(2) << thisNode;
      cout << " with cost " << cost << endl;
      lastNode = item.second;

      // Iterate through all the nodes adjacent to the node taken out of priority
      // queue. Push only those nodes (weight,node) that are not yet present in the
      // minumum spanning tree.
      for (auto& pair_cost_node : this->nodes[thisNode]) {
        int adjacentNode = pair_cost_node.second;
        if ((adjacentNode != -1) && (addedNodes[adjacentNode] == false)) {
          q.push(pair_cost_node);
        }
      }
    }
  }
  cout << "#######################################################" << endl;
  cout << "Total MST Distance: " << mst_cost << endl;
  cout << "#######################################################" << endl;
}
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// Dikstra's Algorithm

// -----------------------------------------------------------------------------
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

// -----------------------------------------------------------------------------
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
  cout << "Average Distance: " << static_cast<float>(cumSum) / dist.size() << endl;
  cout << "#######################################################" << endl;
}

// -----------------------------------------------------------------------------
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

// util to swap two ints
inline void swap(int& x, int& y) {
  int temp = x;
  x        = y;
  y        = temp;
  return;
}
