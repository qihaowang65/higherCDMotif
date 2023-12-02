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
        int BFS(const vector<int*>& matching, int start,int target);
    private:
        int r;
        int k;
        vector<vector<int>> adj;
};


#endif