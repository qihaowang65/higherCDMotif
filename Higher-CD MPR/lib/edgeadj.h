#ifndef EDGE_ADJ
#define EDGE_ADJ

#include "util.h"
#include "nestedmap.h"
#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

class EdgeAdj{
    public:
        EdgeAdj(const vector<int*>& matching,int order,int size);
        ~EdgeAdj();
        vector<int> GetNeighour(int* motif);
    private:
        int r;
        int k;
        int** history;
        int total;
        NestedMap<vector<int>> TupleMotif;
};


#endif