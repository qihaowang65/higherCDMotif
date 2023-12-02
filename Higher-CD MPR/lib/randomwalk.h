#ifndef RANDOM_WALK
#define RANDOM_WALK

#include "util.h"
#include "edgeadj.h"
#include <iostream>
#include <utility>
#include <stdlib.h>

using namespace std;

pair<int,int> Restart(vector<int*>& matching,int k,int M);
pair<int,int> OneStep(vector<int>& neigh,int current_node,int current_motif,vector<int*>& matching,int k);



#endif