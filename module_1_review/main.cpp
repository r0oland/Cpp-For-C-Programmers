//   Convert this program to C++
//  change to C++ io
//  change to one line comments
//  change defines of constants to const
//  change array to vector<>
//  inline any short function
#include <iostream> // used c++ io
#include <vector>
using namespace std;
const int N = 40; // removed macro
inline void sum(int& p, int n, vector<int> d)  // converted to inline function
{
    p = 0;
    for (auto i = d.begin(); i !=d.end(); ++i)
        p = p + *i;
}

int main()
{
    int accum = 0;
    vector<int> data; // vector used
    for (int i = 0; i < N; ++i)
        data.push_back(i);
    sum(accum, N, data);
    cout << "summ is " << accum << endl;
    return 0;
}



