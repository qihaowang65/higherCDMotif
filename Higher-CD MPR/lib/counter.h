#ifndef COUNTER_H
#define COUNTER_H

#include "util.h"
#include "nestedmap.h"
#include <iostream>
#include <vector>

using namespace std;

class Counter{
    public:
        Counter(int order):r(order),visited(order) {};
        ~Counter();
        int Solve(const vector<int*>& matching, int** history,int q);
    private:
        int r;
        NestedMap<bool> visited;
};


#endif
