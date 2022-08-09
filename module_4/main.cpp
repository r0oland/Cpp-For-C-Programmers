#include <stdlib.h> /* srand, rand */
#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
#include <chrono>
#include <array>

using namespace std;
using namespace std::chrono;

// first integer is the node size of the graph
// aother values will be integer triples: (nodeI, nodeJ, cost).
// read graph info from file and create graph
void readGraph(string fileName) {
  ifstream file;
  file.open(fileName);
  if (!file.is_open()) {
    cout << "Error opening file" << endl;
    exit(1);
  }
  // read and print out all lines
  string line;
  int nodeSize;
  file >> nodeSize;
  cout << "Node size: " << nodeSize << endl;
  // while (getline(file, line)) {
  //     cout << line << endl;
  // }

  // file >> nodeSize >> edgeSize;
  // for (int i = 0; i < edgeSize; i++) {
  //     int nodeI, nodeJ, cost;
  //     file >> nodeI >> nodeJ >> cost;
  //     cout << nodeI << " " << nodeJ << " " << cost << endl;
  //     // graph[nodeI].push_back(nodeJ);
  //     // graph[nodeJ].push_back(nodeI);
  //     // graph[nodeI].push_back(cost);
  //     // graph[nodeJ].push_back(cost);
  // }
  file.close();
}

// create point class to define point in xy
class Point {
public:
  Point(int x, int y) : x(x), y(y) {};
  Point(double x, double y) : x(x), y(y) {};

  // overload double cast
  explicit operator double() const {
    return x + y;
  }

  // overload << operator to print out point
  friend ostream& operator<<(ostream& os, const Point& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
  }

  void Print(void) {
    cout << "(" << x << ", " << y << ")" << endl;
  };

private:
  double x, y;
};

class Pixel {
public:
  int r, g, b;

  Pixel() {};
  Pixel(int r, int g, int b) : r(r), g(g), b(b) {};
};

int main() {

  cout << "Welcome to the super fancy stuff" << endl;
  cout << "Please enter the name of the file containing the graph" << endl;
  string fileName = "../testdata_mst_data.txt";
  readGraph(fileName);
  cout << "Graph read successfully" << endl;
  Point myPoint(1, 2);

  myPoint.Print();
  cout << static_cast<double>(myPoint) << endl;
  cout << myPoint << endl;
  cout << (double)myPoint << endl;

#define DIM 1000

  auto stopTime            = high_resolution_clock::now();
  auto startTime           = high_resolution_clock::now();
  duration<float> duration = stopTime - startTime;

  // ---------------------------------------------------------------------------
  startTime = high_resolution_clock::now();
  Pixel * pixelsOld = (Pixel *)malloc(sizeof(Pixel) * DIM * DIM);
  for (int i = 0; i < DIM*DIM; ++i) {
    // Modify each element
    pixelsOld[i].r = 255;
    pixelsOld[i].g = 0;
    pixelsOld[i].b = 0;
  }
  stopTime = high_resolution_clock::now();
  duration = stopTime - startTime;
  cout << "Runtime: " << duration.count() * 1000 << " ms" << endl;

  // ---------------------------------------------------------------------------
  startTime = high_resolution_clock::now();
  std::vector<Pixel> pixels;
  pixels.resize(DIM*DIM); // Create elements that need to be modified
  for (int i = 0; i < DIM*DIM; ++i) {
    // Modify each element
    pixels[i].r = 255;
    pixels[i].g = 0;
    pixels[i].b = 0;
  }

  stopTime = high_resolution_clock::now();
  duration = stopTime - startTime;
  cout << "Runtime: " << duration.count() * 1000 << " ms" << endl;

  // ---------------------------------------------------------------------------
  startTime = high_resolution_clock::now();
  std::vector<Pixel> newPixels(DIM*DIM, Pixel(255, 0, 0)); // Create desired
                                                             // elements directly
  stopTime = high_resolution_clock::now();
  duration = stopTime - startTime;
  cout << "Runtime: " << duration.count() * 1000 << " ms" << endl;

  // ---------------------------------------------------------------------------
  startTime = high_resolution_clock::now();
  for (auto p = newPixels.begin(); p != newPixels.end(); ++p) {
    p->r = 255;
    p->g = 0;
    p->b = 0;
  }

  stopTime = high_resolution_clock::now();
  duration = stopTime - startTime;
  cout << "Runtime: " << duration.count() * 1000 << " ms" << endl;


  ifstream data_file("../testdata_mst_data.txt");
  istream_iterator<int> start(data_file);
  istream_iterator<int> end;
  vector<int> data(start, end);

  cout << "Data: " << endl;
  for (auto d : data) {
    cout << d << endl;
  }

  return 0;
}

// Implement either the Prim or Kruskal Minimum Spanning Tree Algorithm.
// These algorithms are similar in flavor to Dijkstra’s shortest path algorithm.
// Links to these algorithms are provided besides being explained in the videos.
