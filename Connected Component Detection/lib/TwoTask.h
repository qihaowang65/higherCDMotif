#ifndef TWOTASK_H
#define TWOTASK_H
#include <vector>
#include <stdio.h>
#include <iostream>
#include "util.h"
#include "nestedmap.h"

class TwoTask{
    public:
        TwoTask(int motifs,int r): tuple_to_motif(r), tuple_visited(r), M(motifs), order(r) {};
        ~TwoTask();
        int Solve(const vector<int*>& matching, int** history,int q);
    private:
        int CheckMotif(int motif_iter);
        void CheckTuple(vector<vector<int>>& current_cc);
        NestedMap<vector<int>> tuple_to_motif;
        NestedMap<bool> tuple_visited;
        vector<bool> motif_visited;
        vector<vector<vector<int>>> motif_to_tuple;//M(number of motifs) x Ckr (number of tuples in this motif) x r (order)
        vector<int> motif_queue;
        vector<vector<int>> tuple_queue;
        int M;
        int order;
};


#endif