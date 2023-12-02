#include "counter.h"

Counter::~Counter(){

}

int Counter::Solve(const vector<int*>& matching, int** history,int q){
    for (int i = 0; i < matching.size();i++){
        vector<vector<int>> all_tuples = IndicesToNodeTuple(matching[i],history,r,q);
        for (int j = 0; j < all_tuples.size();j++){
            vector<int> current_tuple = all_tuples[j];
            visited.write(current_tuple,false);
        }
    }
    vector<vector<int>> all_tuples;
    visited.FetchAllTuples(all_tuples);
    return all_tuples.size();
}

