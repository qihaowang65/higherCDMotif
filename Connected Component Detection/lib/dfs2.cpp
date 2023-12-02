#include "dfs2.h"

DFS2::~DFS2(){
    
}

void DFS2::DFS_Walker(vector<vector<int>>& current_cc,vector<int>& current_node){
    stack<vector<int>> pending_stack;
    
    pending_stack.push(current_node);
    while(!pending_stack.empty()){
        vector<int> current = pending_stack.top();
        current_cc.push_back(current);
        pending_stack.pop();
        vector<vector<int>> next_tuples = next_point.read(current);
        for (int i = 0; i < next_tuples.size();i++){
            vector<int> current_next = next_tuples[i];
            if (visited.ReadAndWrite(current_next) == false){
                
                pending_stack.push(current_next);
            }
        }
    }
    return;
}

int DFS2::Solve(const vector<int*>& matching, int** history,int q){
    for (int i = 0; i < matching.size();i++){
        vector<vector<int>> all_tuples = IndicesToNodeTuple(matching[i],history,r,q);
        vector<int> root = all_tuples[0];
        visited.write(root,false);
        for (int j = 1; j < all_tuples.size();j++){
            vector<int> current_tuple = all_tuples[j];
            visited.write(current_tuple,false);
            
            next_point.pend(root,current_tuple);
            next_point.pend(current_tuple,root);
            root = current_tuple;
        }
    }
    
    vector<vector<int>> all_tuples;
    vector<unordered_set<int>> all_cc;
    visited.FetchAllTuples(all_tuples);


    for (int i = 0; i < all_tuples.size();i++){
        vector<int> current_tuple = all_tuples[i];
        if (visited.read(current_tuple) == false){
            visited.write(current_tuple,true);
            vector<vector<int>> current_cc;
            DFS_Walker(current_cc,current_tuple);
            unordered_set<int> s;
            TupleListToNodeList(current_cc,s);

            all_cc.push_back(s);
        }
    }
    return all_cc.size();
}


