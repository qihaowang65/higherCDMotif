#include "disjointset.h"

DisjointSet::~DisjointSet(){
	address.Free();
}


Node* DisjointSet::Find(vector<int>& tuple){
	Node* root_node = address.read(tuple);
	vector<Node*> compression;
	Node* ret_val = root_node->GetRoot(compression);
	for (int i = 0; i < compression.size();i++){
		Node* change = compression[i];
		change->SetParent(ret_val);

	}
	return ret_val;
}


int DisjointSet::CheckCase(vector<vector<int>>& tuples,vector<Node*>& groups){
	int cases = 0;
	bool none_flag = false;
	for (int i = 0; i<tuples.size();i++){
		vector<int> current_tuple = tuples[i];
		if (address.CheckExistance(current_tuple)){
			Node* root_value = this->Find(current_tuple);			
			groups.push_back(root_value);
		}else{
			groups.push_back(NULL);
			none_flag = true;
		}
	}
	set<Node*> s;
	for (int i = 0;i<groups.size();i++){
		s.insert(groups[i]);
	}
	int count = s.size();
	if (none_flag){
		if (count == 1){
			return 0;//0 indicates that there is only NULL pointer, call AddAllToOne()
		}else if (count == 2){
			return 1;//1 indicates that there are some NULL pointers, and one existing group, call AppendAllToOne
		}else{
			return 3;//3 indicates that there are some NULL pointers, and at least two existing groups, call UnionMoreGroups
		}
	}else{
		if (count == 1){
			return 2;//2 indicates that there is only one group, we should not do anything
		}else{
			return 4;//4 indicates that there are more than 2 groups, call UnionMoreGroups
		}
	}
	
}

void DisjointSet::AddAllToOne(vector<vector<int>>& tuples){
	vector<int> first = tuples[0];
	Node* root = new Node(first);
	address.write(first,root);
	for (int i =1; i < tuples.size();i++){
		Node* new_leaf = new Node(tuples[i],root);
		address.write(tuples[i],new_leaf);
	}
	rank.write(first,0);

}

void DisjointSet::AppendAllToOne(vector<vector<int>>& tuples,const vector<Node*>& groups){
	Node* root;
	for (int i = 0; i< groups.size();i++){
		if (groups[i] != NULL){
			root = groups[i];
			break;
		}
	}
	for (int i = 0; i < groups.size();i++){
		if (groups[i] == NULL){
			Node* new_leaf = new Node(tuples[i],root);
			address.write(tuples[i],new_leaf);
		}
	}
}

void DisjointSet::UnionMoreGroups(vector<vector<int>>& tuples, const vector<Node*>& groups){
	vector<int> NullIndices;
	vector<int> Existing;
	vector<int> ranking;

	int max_value = -1;
	Node* root_address;
	for (int i = 0; i < groups.size();i++){
		if (groups[i] == NULL){
			NullIndices.push_back(i);
			continue;
		}
		Existing.push_back(i);
		vector<int> current_tuple = groups[i]->GetValue();
		int current_rank = rank.read(current_tuple);
		ranking.push_back(current_rank);
		if (current_rank > max_value){
			max_value = current_rank;
			root_address = address.read(current_tuple);
		}
	}
	for (int i = 0; i < NullIndices.size();i++){
		vector<int> current_tuple = tuples[NullIndices[i]];
		Node* new_leaf = new Node(current_tuple,root_address);
		address.write(current_tuple,new_leaf);
	}

	int adding = 0;
	for (int i = 0; i < Existing.size();i++){
		Node* current_node = groups[Existing[i]];
		int current_rank = ranking[i];
		if (current_node != root_address){
			current_node->SetParent(root_address);
			if (current_rank == max_value){
				adding++;
			}
		}

	}
	adding += max_value;
	vector<int> root_tuple = root_address->GetValue();
	rank.write(root_tuple,adding);

}


void DisjointSet::HandleMotif(vector<vector<int>>& tuples){
	vector<Node*> groups;
	int check = CheckCase(tuples,groups);
	switch(check){
		case 0:
			AddAllToOne(tuples);
			break;
		case 1:
			AppendAllToOne(tuples,groups);
			break;
		case 2:
			break;
		case 3:
			UnionMoreGroups(tuples,groups);
			break;
		case 4:
			UnionMoreGroups(tuples,groups);
			break;
	}
}

int DisjointSet::Solve(const vector<int*>& matching, int** history,int q){

	for (int i = 0; i < matching.size();i++){
		auto results = IndicesToNodeTuple(matching[i],history,r,q);
		HandleMotif(results);
	}


	unordered_map<Node*,set<int>> root_indices_map;
	address.DisjointSet_helper(root_indices_map);

	vector<set<int>> ret;
	for (auto it : root_indices_map){
		ret.push_back(it.second);
		for (auto it2 = it.second.begin(); it2 != it.second.end();it2++){
			cout << *it2 << " ";
		}
		cout << endl;
	}
	
	return ret.size();
}

vector<int> DisjointSet::ResultSolver(const vector<int*>& matching, int** history,int q){

	for (int i = 0; i < matching.size();i++){
		auto results = IndicesToNodeTuple(matching[i],history,r,q);
		HandleMotif(results);
	}


	unordered_map<Node*,set<int>> root_indices_map;
	address.DisjointSet_helper(root_indices_map);

	vector<int> ret;
	for (auto it : root_indices_map){
		ret.push_back(it.second.size());
	}
	
	return ret;
}

