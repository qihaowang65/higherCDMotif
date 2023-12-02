#ifndef STANDARD_H
#define STANDARD_H
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;
class SingleOrder{
    public:
        SingleOrder(int k);
        ~SingleOrder();
        int Solve(const vector<int*>& matching);
    private:
        int size;
        unordered_map<int,bool> visited;
        unordered_map<int,unordered_set<int>> target;

};



#endif