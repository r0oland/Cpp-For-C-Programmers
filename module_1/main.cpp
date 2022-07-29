//   Convert this program to C++
//   change to C++ io
//   change to one line comments
//   change defines of constants to const
//   change array to vector<>
//   inline any short function

#include <iostream>
#include <vector>

using namespace std;
const int N = 40;

// write generic template function to sum elements of vector
template <class T>
inline void sum(T& sum, std::vector<T> data) {
  for (int i = 0; i < data.size(); i++) {
    sum += data[i];
  }
}

int main() {

  // init empty vector object
  std::vector<int> data; 

  // fill vector with data as needed
  for (int i = 0; i < N; ++i) {
    data.push_back(i);
  }

  int accum = 0;
  sum(accum, data); // call inline sum function

  cout << "sum is " << accum << endl;

  return 0;
}