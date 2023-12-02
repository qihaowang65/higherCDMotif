#include "standard.h"

SingleOrder::SingleOrder(int k){
    size = k;
}

SingleOrder::~SingleOrder(){

}

int SingleOrder::Solve(const vector<int*>& matching){
    for (int i = 0; i < matching.size();i++){
        int* current = matching[i];
        for (int j = 0; j < size; j++){
            visited[current[j]] = false;
        }
        int first_node = current[0];
        if (target.find(first_node) == target.end()){
            target[first_node] = unordered_set<int>();
        }

        for (int j = 1; j < size; j++){
            int next = current[j];
            if (target.find(next) == target.end()){
                target[next] = unordered_set<int>();
            }
            target[first_node].insert(next);
            target[next].insert(first_node);
        }
    }
    //End of initialization
    queue<int> pending;
    vector<vector<int>> all_cc;
    for (auto i = visited.begin(); i != visited.end(); i++){
        if (i->second == false){
            pending.push(i->first);
            visited[i->first] = true;
        }
        vector<int> current_cc;
        current_cc.push_back(i->first);
        while(!pending.empty()){
            int current = pending.front();
            pending.pop();
            current_cc.push_back(current);
            for (auto j = target[current].begin(); j != target[current].end();j++){
                int neighbor = *j;
                if (visited[neighbor] == false){
                    visited[neighbor] = true;
                    pending.push(neighbor);
                }

            }
        }
        if (!current_cc.empty()){
            all_cc.push_back(current_cc);
        }
    }
    return all_cc.size();
}

