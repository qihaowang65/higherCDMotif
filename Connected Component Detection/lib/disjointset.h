/*
A disjointset-based solver for higher-order connected component detection.
*/
#ifndef DISJOINTSET_H
#define DISJOINTSET_H

#include <vector>
#include <algorithm>
#include <set>
#include <iostream>
#include "nestedmap.h"
#include "util.h"
#include "node.h"


using namespace std;


class DisjointSet{
	public:
		DisjointSet(int order): rank(order),address(order),r(order){};//Constructor for disjointset
		~DisjointSet();//Destructor for disjointset
		int Solve(const vector<int*>& matching,int** history,int q);//A solve function to find the number of connected components
	private:
		NestedMap<Node*> address;//A nested map to store the node object of each node tuple
		NestedMap<int> rank;//The rank of each group. This will be used to implement Union-by-Rank
		int r;//The order of the graph
		//int last = 0;
		int CheckCase(vector<vector<int>>& tuples,vector<Node*>& groups);//A function to check which function should be called to handle cunrrent motif
		Node* Find(vector<int>& tuple);//A find function in Disjointset algorithm. Path compression will also be implemented
		void AddNewNode(vector<int>& tuple, Node* parent);//A function to add new node to the disjointset algorithm
		void UnionByRank(vector<int>& first, vector<int>& second);//Union two more groups in the disjointset
		void AddAllToOne(vector<vector<int>>& tuples);//
		void AppendAllToOne(vector<vector<int>>& tuples,const vector<Node*>& groups);
		void UnionMoreGroups(vector<vector<int>>& tuples, const vector<Node*>& groups);
		void HandleMotif(vector<vector<int>>& tuples);
		vector<int> ResultSolver(const vector<int*>& matching, int** history,int q);

};


#endif