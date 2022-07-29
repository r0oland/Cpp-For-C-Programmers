//   Convert this program to C++
//   change to C++ io
//   change to one line comments
//   change defines of constants to const
//   change array to vector<>
//   inline any short function

#include <iostream>

using namespace std;
const int N = 40;

inline void sum(int* p, int n, int d[]) {
  *p = 0; // set sum to zero

  // start collecting the acumulated sum
  for (int i = 0; i < n; ++i) {
    *p = *p + d[i];
  }
}

int main() {

  // init array with increasing values
  int data[N];
  for (int i = 0; i < N; ++i) {
    data[i] = i;
  }

  int accum = 0;
  sum(&accum, N, data); // call inline sum function

  cout << "sum is " << accum << endl;

  return 0;
}