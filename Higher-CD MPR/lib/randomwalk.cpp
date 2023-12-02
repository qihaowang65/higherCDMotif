#include "randomwalk.h"

pair<int,int> Restart(vector<int*>& matching,int k,int M){
    int motif = rand() % M;
    int node = rand() % k;
    
    node = matching[motif][node];

    
    return make_pair(motif,node);

}


pair<int,int> OneStep(vector<int>& neigh,int current_node,int current_motif,vector<int*>& matching,int k){
    
    int motif = rand() % neigh.size();
    motif = neigh[motif];
    int node = rand() % k;
    node = matching[motif][node];
    while (node == current_node){
        node = rand() % k;
        node = matching[motif][node];
    }
    return make_pair(motif,node);
}