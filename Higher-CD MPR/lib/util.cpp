#include "util.h"
inline vector<int> Remove_by_Value(vector<int> vec,int value){
    vec.erase(remove(vec.begin(), vec.end(), value), vec.end());
    return vec;
}

inline bool vector_in(vector<int> vec,int value){
    return binary_search(vec.begin(), vec.end(), value);
}

void Ckr_helper(int n,vector<int> chosen, int remain, int last,vector<vector<int>>& ret){
    if (remain == 0){
        ret.push_back(chosen);
        return;
    }
    for (int i=last;i<n;i++){
        if (vector_in(chosen,i) == false){
            chosen.push_back(i);
            Ckr_helper(n,chosen,remain-1,i+1,ret);
            chosen.pop_back();
        }
    }
    return;
}

int** Ckr(int n, int r, int* pos){
    vector<vector<int>> ret;
    Ckr_helper(n,vector<int>(),r,0,ret);
    int q = ret.size();
    //We will return a q by r history
    int** holder;
    holder = new int*[q];
    for (int i =0; i < q; i++){
        holder[i] = new int[r];
        for (int j =0; j < r; j++){
            holder[i][j] = ret[i][j];
        }
    }
    *pos = q;
    return holder;
}

vector<vector<int>> IndicesToNodeTuple(int* motif,int** indices,int r,int q){
    vector<vector<int>> ret_list;
    for(size_t i = 0; i< q;i++){
        NodeTuple current_tuple;
        for (size_t j = 0; j < r;j++){
            current_tuple.push_back(motif[indices[i][j]]);
        }
        ret_list.push_back(current_tuple);
    }
    return ret_list;
}

void TupleListToNodeList(vector<vector<int>>& tuple_list,unordered_set<int>& node_list){
    for (int i = 0; i < tuple_list.size();i++){
        for (int j =0; j <tuple_list[j].size();j++){
            node_list.insert(tuple_list[i][j]);
        }
    }
}

void RemoveDuplicate(vector<int> &v){
    auto end = v.end();
    for (auto it = v.begin(); it != end; ++it) {
        end = remove(it + 1, end, *it);
    }
 
    v.erase(end, v.end());
}
