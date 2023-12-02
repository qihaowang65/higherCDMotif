#include "TwoTask.h"

TwoTask::~TwoTask(){

}

int TwoTask::CheckMotif(int motif_iter){
    while(tuple_queue.empty()){

        while(motif_queue.empty()){

            if (motif_iter >= M){
                return -1;
            }
            if (motif_visited[motif_iter] == false){
                motif_visited[motif_iter] = true;
                motif_queue.push_back(motif_iter);
            }
            motif_iter++;
        }
        for (int i = 0; i < motif_queue.size();i++){
            vector<vector<int>> current_tuple_set = motif_to_tuple[motif_queue[i]];
            for (int j =0; j < current_tuple_set.size();j++){
                if (tuple_visited.CheckAndWrite(current_tuple_set[j]) == false){
                    tuple_queue.push_back(current_tuple_set[j]);
                }
            }
        }
    motif_queue.clear();
    }
    return motif_iter;
}

void TwoTask::CheckTuple(vector<vector<int>>& current_cc){
    for (int i = 0; i < tuple_queue.size(); i++){
        current_cc.push_back(tuple_queue[i]);
        vector<int> connected_motifs = tuple_to_motif.read(tuple_queue[i]);

        for (int j = 0; j < connected_motifs.size();j++){
            int current_motif = connected_motifs[j];
            if (motif_visited[current_motif] == false){
                motif_queue.push_back(current_motif);
                motif_visited[current_motif] = true;
            }
        }
    }
    tuple_queue.clear();
    return;
}

int TwoTask::Solve(const vector<int*>& matching, int** history,int q){
    for (int i = 0; i < M; i++){
        int* current_motif = matching[i];
        motif_visited.push_back(false);
        vector<vector<int>> all_tuples = IndicesToNodeTuple(current_motif,history,order,q);
        
        for (int j = 0; j < all_tuples.size(); j++){
            //tuple_visited.write(all_tuples[j],false);
            tuple_to_motif.append(all_tuples[j],i);
        }
        motif_to_tuple.push_back(all_tuples);
    }
    //Finish initialization
    int motif_iter = 0;
    int last_iter = 0;
    vector<unordered_set<int>> all_cc;
    vector<vector<int>> current_cc;


    while(motif_iter != -1){

        motif_iter = CheckMotif(motif_iter);
        if (motif_iter != last_iter){
            last_iter = motif_iter;
            unordered_set<int> s;
            TupleListToNodeList(current_cc,s);
            all_cc.push_back(s);
            current_cc.clear();
        }
        CheckTuple(current_cc);
    }

   
    return (all_cc.size()-1);
}
