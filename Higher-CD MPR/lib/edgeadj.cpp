#include "edgeadj.h"

EdgeAdj::EdgeAdj(const vector<int*>& matching,int order,int size): TupleMotif(order){
    int* q = new int;
    r = order;
    k = size;
	history = Ckr(k,r,q);
    total = *q;
    //Build the map from tuple to motif
    for (size_t i = 0; i<matching.size() ;i++){
        vector<vector<int>> all_tuples = IndicesToNodeTuple(matching[i],history,r,*q);

        for (size_t j = 0; j < all_tuples.size();j++){
            TupleMotif.append(all_tuples[j],i);
        }
    }
    delete q;
}

vector<int> EdgeAdj::GetNeighour(int* motif){
    vector<vector<int>> all_tuples = IndicesToNodeTuple(motif,history,r,total);
    vector<int> ret;
    for (size_t j = 0; j < all_tuples.size();j++){
        vector<int> temp = TupleMotif.read(all_tuples[j]);

        for (size_t x = 0; x < temp.size();x++){
            ret.push_back(temp[x]);
        }
    }


    

    RemoveDuplicate(ret);
    return ret;
}

EdgeAdj::~EdgeAdj(){}





