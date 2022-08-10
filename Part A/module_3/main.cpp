// based in part on infos found in the following sources
// https://en.wikipedia.org/wiki/Dijkstra's_algorithm#
// https://www.youtube.com/watch?v=2E7MmKv0Y24

#include <stdlib.h> /* srand, rand */
#include <iostream>
#include <vector>

constexpr int32_t nNodes     = 5;
constexpr float graphDensity = 0.1f;

using namespace std;

class listElement {
public:
  listElement(int n = 0, listElement* ptr = nullptr) : d(n), next(ptr) {};
  int d;
  listElement* next;

private:
};

class list {
public:
  list() : head(nullptr), cursor(nullptr) {};
  list(const list& lst);
  ~list();

  void prepend(int n); // insert at front value n
  int get_element() {
    return cursor->d; // get value of cursor
  }
  void advance() {
    cursor = cursor->next; // advance cursor to next element
  }
  void print(); // print list

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

list::list(const list& lst) {
  if (lst.head == nullptr) {
    head   = nullptr;
    cursor = nullptr;
  } else {
    // setup new list element pointing to Null
    head             = new listElement(lst.head->d);
    cursor           = head;
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

list::~list() {
  for (cursor = head; cursor != nullptr;) {
    cursor = head->next;
    delete head;
    head = cursor;
  }
}; // destructor


void list::prepend(int n) {
  if (head == nullptr) {
    cursor = head = new listElement(n);
  } else {
    head = new listElement(n, head);
  }
}

void list::print(void) {
  listElement* ptr = head;
  while (ptr != nullptr) {
    cout << ptr->d << " ";
    ptr = ptr->next;
  }
  cout << "###" << endl;
}

bool** create_graph(int32_t nNodes = 50, float prob = 0.5) {
  bool** graph;
  srand(time(NULL)); // seed the random number generator
  graph = new bool*[nNodes];
  for (int i = 0; i < nNodes; i++) {
    graph[i] = new bool[nNodes];
    for (int j = 0; j < nNodes; j++) {
      if (i == j) {
        graph[i][j] = false;
      } else {
        // see https://cplusplus.com/reference/cstdlib/rand/
        graph[i][j] = ((rand() % 101) <= static_cast<int>(prob * 100));
      }
    }
  }
  return graph;
}

void print_2d_graph(bool** graph, int32_t nNodes) {
  for (int i = 0; i < nNodes; i++) {
    for (int j = 0; j < nNodes; j++) {
      if (graph[i][j]) {
        cout << " X ";
      } else {
        cout << " _ ";
      }
    }
    cout << endl;
  }
}

void print_graph_density(bool** graph, int32_t nNodes) {
  int32_t nEdges = 0;
  for (int i = 0; i < nNodes; i++) {
    for (int j = 0; j < nNodes; j++) {
      if (graph[i][j]) {
        nEdges++;
      }
    }
  }
  int32_t nPossibleEdges = nNodes * (nNodes - 1);
  float density(static_cast<float>(nEdges) / (nPossibleEdges));
  cout << "graph density: " << density << "(" << nEdges << "/" << nPossibleEdges
       << ")" << endl;
}

bool is_connected(bool** graph, int size) {
  int o_size = 0, c_size = 0;
  bool* close = new bool[size];
  bool* open  = new bool[size];
  for (int i = 0; i < size; i++)
    open[i] = close[i] = false;
  open[0] = true;
  o_size++;
  while (o_size > 0) { // while there are more nodes in the open set
    for (int i = 0; i < size; i++) {
      if (open[i] && (close[i] == false)) {
        close[i] = true;
        c_size++;
        open[i] = false;
        o_size--;
        for (int j = 0; j < size; j++) {
          if (!close[j]) {
            if (!open[j] && graph[i][j]) {
              open[j] = true;
              o_size++;
            }
          }
        }
      }
    }
  }
  if (c_size == size)
    return true;
  else
    return false;
}

int main() {

  point myFirstPoint(1.0, 2.0);
  point mySecondPoint(1.0, 2.0);

  cout << "Welcome to the super fancy stuff" << endl;
  cout << myFirstPoint << endl;
  cout << mySecondPoint << endl;
  cout << myFirstPoint.more << endl;

  bool** newGraph = create_graph(nNodes, graphDensity);
  print_2d_graph(newGraph, nNodes);
  print_graph_density(newGraph, nNodes);
  cout << is_connected(newGraph, nNodes) << endl;

  cout << "==========================================" << endl;
  list myList;
  myList.prepend(rand() % 100);
  myList.prepend(rand() % 100);
  cout << myList << endl;
  myList.prepend(rand() % 100);
  myList.prepend(rand() % 100);
  cout << myList << endl;
  myList.prepend(rand() % 100);
  cout << myList << endl;
  return 0;
}
