// based in part on infos found in the following sources
// https://en.wikipedia.org/wiki/Dijkstra's_algorithm#
// https://www.youtube.com/watch?v=2E7MmKv0Y24

#include <stdlib.h> /* srand, rand */
#include <iostream>
#include <vector>
#include <chrono>

using namespace std::chrono;
using namespace std;

// define limits for "length" or weight of the edges
enum EdgeWeight { NO_CON = 0, MIN = 1, MAX = 9 };

void swap(int& x, int& y); // fct declaration

// #############################################################################
// Priority Queue as vector based min heap
// see https://www.geeksforgeeks.org/binary-heap/
// https://youtu.be/B7hVxCmfPtM
// using integer arithmetic (implicit flooring division, i.e. 5/2 = 2)
// heap parent is at index (i/2)
// left child is at index (2*i)
// right child is at index (2*i + 1)
// #############################################################################

class PriorityQueue {
public:
  // create simple empty priority queue
  PriorityQueue() {
    heap.push_back(0); // dummy element for indexing to work out
  };
  PriorityQueue(std::vector<int> v) {
    heap.push_back(0); // dummy element for indexing to work out
    for (int i = 0; i < v.size(); i++) {
      heap.push_back(v[i]);
    }
    // sort entire heap to get min heap
    Min_Heapify_Queue();
  };

  ~PriorityQueue() {};

  void Print();

  void Push(int value); // add new element to heap

  int Size() {
    return heap.size() - 1;
  }; // return number of elements in the heap

  // return the minimum value in the heap
  int Top() {
    return heap[1];
  }

  void Change_Prioirity(int idx, int new_priority) {
    idx = idx + 1; // indexing starts at 1
    heap[idx] = new_priority;
    // now that we have changed a priority, we need to re-heapify the heap
    // but here we have to work our way down the heap to the bottom of the tree
    for (int i = Parent(idx); i <= Size()/2; i++) {
      Min_Heapify(i);
    }
    // now we work our way up the tree to the top of the tree
    for (int i = Parent(idx); i > 0; i--) {
      Min_Heapify(i);    
    }
  }

  // return the min value from the top if the heap and remove it
  // then reorder the heap to maintain the min heap property
  int Pop() {
    int minVal = heap[1];
    heap[1]    = heap.back(); // swap old value with the end of the vector
    heap.pop_back();          // remove the end of the vector
    Min_Heapify(1);           // reorder the heap, starting with idx 0
    return minVal;
  }

  // turn the vector into a min heap at index i
  void Min_Heapify(int i);

  void Min_Heapify_Queue(){
    // walk trough the heap and reorder it from the bottom up
    // but last nodes are already in the correct order -> Size()/2
    for (int i = Size()/2; i > 0; i--) {
      Min_Heapify(i);
    }
  }

private:
  vector<int> heap;

  int Parent(int i) {
    return (i) / 2;
  }

  // to get index of left child of node at index i
  int Left(int i) {
    return (2 * i);
  }

  // to get index of right child of node at index i
  int Right(int i) {
    return (2 * i + 1);
  }
};

// A recursive method to heapify a subtree with the root at given index
// This method assumes that the subtrees are already heapified
void PriorityQueue::Min_Heapify(int i) {
  int l        = Left(i);
  int r        = Right(i);
  int smallest = i;

  // tree nodes without children are already in the correct order by definition
  if (i > Size()/2){
    return;
  }
  
  // chek if left child is smaller than parent
  if (l < Size() && heap[l] < heap[i]) {
    smallest = l;
  }

  // chek if right child is smaller than parent
  if (r < Size() && heap[r] < heap[smallest]) {
    smallest = r;
  }

  // if either child was smaller, swap with parent and recurse on the child
  if (smallest != i) {
    swap(heap[i], heap[smallest]);
    Min_Heapify(smallest);
  }
  return;
}

// Inserts a new key 'k'
void PriorityQueue::Push(int k) {
  heap.push_back(k); // insert new key at the end of the vector
  int idx = heap.size() - 1;
  // Fix the min heap property if it is violated by working our way up the tree
  while (idx != 1 && heap[Parent(idx)] > heap[idx]) {
    swap(heap[idx], heap[Parent(idx)]);
    idx = Parent(idx);
  }
}

void PriorityQueue::Print() {
  int div       = 1;
  int inLinePos = 0;
  cout << "Heap Visualization" << endl;
  cout << 1 << ": ";
  for (int i = 1; i < heap.size(); i++) {
    if ((i % (div * 2)) == 0) {
      cout << endl;
      div *= 2;
      cout << div << ": ";
      inLinePos = 0;
    }
    cout << heap[i];
    inLinePos++;
    if (inLinePos > 0 && inLinePos % 2 == 0 && i >= 4) {
      cout << " | ";
    } else {
      cout << " ";
    }
  }
  cout << endl;
}

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

  cout << "#######################################################" << endl;
  cout << "Welcome to fun with Graphs" << endl;

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
  cout << "#######################################################" << endl;
  cout << "Welcome to fun with Queues" << endl;

  constexpr uint32_t N_ELEM = (2<<2)-1;
  // init empty vector of size N_ELEM
  vector<int> unsortedVector(N_ELEM);

  for (int i = 0; i < N_ELEM; i++) {
    unsortedVector[i] = rand() % 100;
  }
  PriorityQueue MyQueue(unsortedVector);
  MyQueue.Print();

  MyQueue.Push(5);
  MyQueue.Print();

  MyQueue.Push(75);
  MyQueue.Print();


  MyQueue.Pop();
  MyQueue.Print();

  MyQueue.Pop();
  MyQueue.Print();

  MyQueue.Change_Prioirity(0,250);
  MyQueue.Change_Prioirity(0,250);
  MyQueue.Change_Prioirity(0,250);
  MyQueue.Print();

  MyQueue.Change_Prioirity(5,0);
  MyQueue.Change_Prioirity(5,0);
  MyQueue.Change_Prioirity(5,0);
  MyQueue.Print();


  cout << "#######################################################" << endl;
  cout << "Welcome to fun with Dijkstra" << endl;

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