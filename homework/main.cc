#include <iostream>
#include <vector>
using namespace std;

#include "graph.h"

int main(void) {
    Graph g("mst_data.txt");
    double cost = g.find_mst_prim(); 
    cout << "-------------------------------" << endl;
    cout << "The total cost of the MST is " << cost << endl;
    int n = g.V();
    cout << "-------------------------------" << endl;
    cout << "The edge list of the MST is:\n" << endl;
    for(int i = 1; i < n; ++i) {
        cout << *(g.get_vertex(i)->edge_mst) << endl;
    }
    cout << "-------------------------------" << endl;
    return 0;
}
