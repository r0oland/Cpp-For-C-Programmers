// based in part on infos found in the following sources
// https://en.wikipedia.org/wiki/Dijkstra's_algorithm#
// https://www.youtube.com/watch?v=2E7MmKv0Y24

#include <stdlib.h> /* srand, rand */
#include <iostream>
#include <vector>
#include <chrono>

using namespace std::chrono;
using namespace std;

enum EdgeWeight { NO_CON = 0, MIN = 1, MAX = 9 };

// #############################################################################
// listElement as struct, because it has no methods and is fully public
// #############################################################################
// single linked list element
struct listElement {
  listElement(int n = 0, listElement* ptr = nullptr) : d(n), next(ptr) {};
  int d;
  listElement* next;
};

// #############################################################################
// List Class and it's Methods
// #############################################################################
class list {
public:
  list() : head(nullptr), cursor(nullptr) {};
  list(const list& lst);
  ~list();

  // short inline methods for better performance...
  int get_element() {
    return cursor->d; // get value of cursor
  }

  void advance() {
    cursor = cursor->next; // advance cursor to next element
  }
  void print(); // print list

  // inline prepend for better performance
  void prepend(int n) {
    if (head == nullptr) {
      cursor = head = new listElement(n);
    } else {
      head = new listElement(n, head);
    }
  }

  // overload << for printing list on cout
  friend ostream& operator<<(ostream& os, const list& l) {
    listElement* ptr = l.head;
    while (ptr != nullptr) {
      os << ptr->d << "->";
      ptr = ptr->next;
    }
    os << "NULL";
    return os;
  }

private:
  listElement* head; // head of the list, i.e. latest element
  listElement* cursor;
};

//------------------------------------------------------------------------------
// copy constructor
list::list(const list& lst) {
  if (lst.head == nullptr) {
    head   = nullptr;
    cursor = nullptr;
  } else {
    // setup new list element pointing to Null
    head   = new listElement(lst.head->d);
    cursor = head;
    // create temporary pointer to traverse list
    listElement* ptr = nullptr;
    // check if we have more to do...
    ptr = lst.head->next;
    while (ptr != nullptr) {
      cursor->next = new listElement(ptr->d);
      cursor       = cursor->next;
      ptr          = ptr->next;
    }
    cursor->next = nullptr;
  }
}

//------------------------------------------------------------------------------
// destructor
list::~list() {

  cout << "deleting list elements: ";
  cursor = head;
  while (cursor != nullptr) {
    cout << cursor->d << "->";
    cursor = head->next;
    delete head;
    head = cursor;
  }
  cout << "NULL" << endl;
};

// #############################################################################
// graph Class using Edge Matrix Representation
// #############################################################################
class GraphMatrix {
public:
  GraphMatrix(int32_t nNodes = 50, float prob = 0.5) : n(nNodes) {
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
        int rWeight = (rand() % EdgeWeight::MAX) + EdgeWeight::MIN;
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
  int n;                            // number of graph nodes / vertices
  int nEdges;                       // number of edges
  float density;                    // density of the graph
  vector<vector<bool>> conMap;      // connectivity matrix
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
        cout << " "<< weightMap[x][y] << " ";
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
vector<int> GraphMatrix::Get_Neighbors(int x){
  vector<int> neighbors;
  for (int i = 0; i < n; i++) {
    if (conMap[x][i]) {
      neighbors.push_back(i);
    }
  }
  return neighbors;
}

// -----------------------------------------------------------------------------
void GraphMatrix::Print_Neighbors(int x){
  vector<int> neighbors = Get_Neighbors(x);
  cout << "Neighbors of " << x << ": " << endl;
  for (auto i: neighbors){
    cout << x << "->" << weightMap[x][i] << "->" << i << endl;
  }
}

// float GraphMatrix::Get_Density(void) {
//   return static_cast<float>(nNodes * (nNodes - 1)) / 2.0f;
// }

// void graph::dijkstra(int start) {
//   // create a vector of vectors of ints
//   vector<vector<int>> distance(n, vector<int>(n, -1));
//   // create a vector of vectors of ints
//   vector<vector<int>> previous(n, vector<int>(n, -1));
//   // create a vector of vectors of ints
//   vector<vector<int>> visited(n, vector<int>(n, 0));
//   // create a vector of vectors of ints
//   vector<vector<int>> visited_previous(n, vector<int>(n, 0));
//   // create a vector of vectors of ints
//   vector<vector<int>> visited_distance(n, vector<int>(n, 0));
//   // create a vector of vectors of ints
//   vector<vector<int>> visited_previous_distance(n, vector<int>(n, 0));
//   // create a vector of vectors of ints
//   vector<vector<int>> visited_previous_previous(n, vector<int>(n, 0));
//   // create a vector of vectors of ints
//   vector<vector<int>> visited_previous_previous_distance(n, vector<int>(n, 0));
//   // create a vector of vectors of ints
//   vector<vector<int>> visited_previous_previous_previous(n, vector<int>(n, 0));
//   // create a vector of vectors of int
// }

int main() {

  auto startTime = high_resolution_clock::now();

  cout << "Welcome to fun with Dijkstra" << endl;

  GraphMatrix myGraph(10, 0.5);
  myGraph.Print();
  cout << "Number of edges: " << myGraph.Get_Num_Edges() << endl;
  cout << "Density: " << myGraph.Get_Density() << endl;

  myGraph.Print_Neighbors(5);
  vector<int> neighbors = myGraph.Get_Neighbors(5);

  cout << myGraph.Get_Weight(5, neighbors[0]) << endl;



  // bool** newGraph = create_graph(nNodes, graphDensity);
  // print_2d_graph(newGraph, nNodes);
  // print_graph_density(newGraph, nNodes);
  // cout << is_connected(newGraph, nNodes) << endl;

  auto stopTime            = high_resolution_clock::now();
  duration<float> duration = stopTime - startTime;
  // auto duration = duration_cast<microseconds>(stop - start);
  // auto myTime = duration_cast<fsec>(duration)*1000;
  cout << "Total Runtime: " << duration.count() * 1000 << " ms" << endl;

  return 0;
}
