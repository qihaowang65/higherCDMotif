#ifndef UTILITS_H
#define UTILITS_H
#include <vector>
#include <algorithm>
#include <iostream>
#include <unordered_set>
using namespace std;

typedef vector<int> NodeTuple;
int** Ckr(int n, int r,int* q);
template<class T>
void Print2DVector(vector<vector<T>> vec){
    for (size_t i = 0; i < vec.size(); i++){
        for (size_t j=0; j < vec[i].size(); j++)
            cout << vec[i][j] << " ";
        cout << endl;
    }
}

void TupleListToNodeList(vector<vector<int>>& tuple_list,unordered_set<int>& node_list);

vector<vector<int>> IndicesToNodeTuple(int* motif,int** indices,int r, int q);
#endif