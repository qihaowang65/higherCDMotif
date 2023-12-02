/*
A nested map class similar to sparse tensor representation.
Object can be initialized as NestedMap<type>(int order)
*/
#ifndef NESTEDMAP_H
#define NESTEDMAP_H

#include <unordered_map>
#include <vector>
#include <iostream>
#include "node.h"
#include <unordered_set>
#include <set>
using namespace std;

template <class T>
class NestedMap{
	public:
		NestedMap(int r);//Constructor
		~NestedMap();
		void write(vector<int>& indices,T val,int depth=0);//Write function
		void append(vector<int>& indices,int val,int depth=0);//Write function for TwoTask Algorithm
		T read(vector<int>& indices,int depth=0);//Read function
		bool CheckExistance(vector<int>& indices,int depth=0);//Read function to check if an indices exist
		void Free(int depth=0);//Free memomry for disjointset algorithm
		void ScanMap(vector<int>& indices,unordered_map<Node*,set<int>>& ret,int depth=0);//Scan the entire nested map, used for disjointset algorithm
		void DisjointSet_helper(unordered_map<Node*,set<int>>& ret);//A helper function for disjointset algorithm
		void pend(vector<int>& indices,vector<int>& val,int depth=0);//Write function for DFS algorithm
		void FetchAllTuples(vector<vector<int>>& ret_tuples);
		void FetchHelper(vector<vector<int>>& ret_tuples,vector<int>& indices,int depth=0);
		bool CheckAndWrite(vector<int>& indices, int depth =0);
		bool ReadAndWrite(vector<int>& indices, int depth =0);
	private:
		int order;//The depth of the nested map
		unordered_map<int,T> TrueMap;//This map will be used to store the actual value
		unordered_map<int,NestedMap*> Child;//This map will be used to store the next level of nested map 

};


#endif