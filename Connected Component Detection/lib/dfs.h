#ifndef DFS_H
#define DFS_H

#include "util.h"
#include "nestedmap.h"
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class DFS{
    public:
        DFS(int order):r(order),next_point(order),visited(order) {};
        ~DFS();
        int Solve(const vector<int*>& matching, int** history,int q);
    private:
        int r;
        NestedMap<vector<vector<int>>> next_point;
        NestedMap<bool> visited;
        void DFS_Walker(vector<vector<int>>& current_cc,vector<int>& current_node);
};


#endif
