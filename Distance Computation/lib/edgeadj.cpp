#include "edgeadj.h"

EdgeAdj::EdgeAdj(const vector<int*>& matching,int order,int size){
    int* q = new int;
    r = order;
    k = size;
	int** history = Ckr(k,r,q);
    vector<vector<vector<int>>> MotifTuple;
    NestedMap<vector<int>> TupleMotif(r);
    //Build the bidirectional relationship between motif and node tuple
    for (size_t i = 0;i<matching.size();i++){
        vector<vector<int>> all_tuples = IndicesToNodeTuple(matching[i],history,r,*q);
        MotifTuple.push_back(all_tuples);
        for (size_t j = 0; j < all_tuples.size();j++){
            TupleMotif.append(all_tuples[j],i);
        }
    }
    //Construct motif-edge adjacency matrix
    for (size_t i = 0;i<matching.size();i++){
        vector<vector<int>> all_tuples = MotifTuple[i];
        vector<int> connected;
        for (size_t j = 0; j < all_tuples.size();j++){
            vector<int> temp = TupleMotif.read(all_tuples[j]);
            for (size_t x = 0; x < temp.size();x++){
                connected.push_back(temp[x]);
            }
        }
        adj.push_back(connected);
    }
    delete q;
}

EdgeAdj::~EdgeAdj(){}

int EdgeAdj::BFS(const vector<int*>& matching, int start, int end){
    queue<pair<int,int>> q;
    vector<bool> visited;
    for (size_t i = 0;i<matching.size();i++){
        visited.push_back(false);
        for (int j = 0; j < k; j++){
            if (matching[i][j] == start){
                pair<int,int> new_edge = make_pair(i,1);
                q.push(new_edge);
                visited[i] = true;
                break;
            }
        }
    }

    pair<int,int> edge_pair;
    int edge;
    int depth;
    int count = 0;
    while(!q.empty()){
        edge_pair = q.front();
        edge = edge_pair.first;
        depth = edge_pair.second;
        q.pop();
        for (int j = 0; j < k; j++){
            int nodeid = matching[edge][j];
            if (nodeid == end){
                return depth;
            }
        }

        for (int j = 0; j < adj[edge].size();j++){
            int next = adj[edge][j];
            if (visited[next]==false){
                visited[next]=true;
                pair<int,int> new_edge = make_pair(next,depth+1);
                q.push(new_edge);
            }
        }
    }
    return -1;
}



