#include "nestedmap.h"

/*
Constructor for nestedmap object
Input:
	r: the order of this nested map
Output:
	The object of nestedmap
*/
template <class T>
NestedMap<T>::NestedMap(int r){
	order = r;
}

/*
Destructor for nestedmap object
Input: 
	None
Output:
	The allocated child nested map will be freed
*/
template <class T>
NestedMap<T>::~NestedMap(){
	for (auto it : Child){
		delete it.second; 
	}
}

/*
NestedMap::write
	A function to write a value to the nestedmap function
	Input:
		indices: The indices to write the value
		val: The value to be written
		depth: The level of recursion
	Output:
		The value will be written to the given indices
	Return value: 
		None
*/
template <class T>
void NestedMap<T>::write(vector<int>& indices,T val,int depth){
	
	if (depth == (order-1)){
		TrueMap[indices[depth]] = val;
		return;
	}
	else{
		int current_index = indices[depth];
		NestedMap* next_map;
		auto it = Child.find(current_index);
		if (it == Child.end()){
			next_map = new NestedMap<T>(order);
			Child[current_index] = next_map;
			next_map->write(indices,val,depth+1);
		}else{
			next_map = Child[current_index];
			next_map->write(indices,val,depth+1);
		}
	}
	return;
}

/*
NestedMap::read:
	A fucntion to read the value of NestedMap at the given indices
	Input:
		indices: The position to read the value of nested map
		depth: The level of recurison
	Output:
		None
	Return value:
		The value stored at the given position
*/
template <class T>
T NestedMap<T>::read(vector<int>& indices,int depth){
	if (depth == (order-1)){
		return TrueMap[indices[depth]];
	}
	int current_index = indices[depth];
	NestedMap* next_map = Child[current_index];
	return next_map->read(indices,depth+1);

}

/*
NestedMap::CheckExistance:
	A fucntion to check if a given indices is a valid key in the nested map
	Input:
		indices: The key for the nestedmap
		depth: the level of recursion
	Output:
		None
	Return value:
		True if the key is valid. Otherwise, return false
*/
template<class T>
bool NestedMap<T>::CheckExistance(vector<int>& indices,int depth){
	if (depth ==(order-1)){
		auto got = TrueMap.find(indices[depth]);
		if (got ==TrueMap.end())
			return false;
		else
			return true;
	}
	auto got = Child.find(indices[depth]);
	if (got == Child.end())
		return false;
	else{
		NestedMap* next_map = Child[indices[depth]];
		return next_map->CheckExistance(indices,depth+1);
	}

}
/*
NestedMap<Node*>::Free
	A function used to free the allocated memory for disjointset algorithm
	Input:
		depth: The level of recurison
	Output:
		The allocated memory for the node object will be freed
	Return value:
		None
*/
template <>
void NestedMap<Node*>::Free(int depth){
	if (depth == (order-1)){
		for (auto it : TrueMap){
			delete it.second;
		}
		return;
	}

	for (auto it : Child){
		NestedMap* next_map = it.second;
		next_map->Free(depth+1);
	}
	return;
}

/*
NestedMap<Node*>::ScanMap
	This function is for disjointset algorithm only. This function will scan the entire nestedmap object, and get the root for each node
	Input:
		indices: the indices to find the value in the nestedmap
		ret: the map to connect the node to its root
		depth: the level of recursion
	Output:
		The disjointset will be compressed such that the tree will have a height close to 1
		The map will store the root for each ndoe
	Return value:
		None 
*/
template<>
void NestedMap<Node*>::ScanMap(vector<int>& indices,unordered_map<Node*,set<int>>& ret,int depth){
	if (depth == (order-1)){
		for (auto it: TrueMap){
			int current_idx = it.first;
			Node* current_node = it.second;
			vector<Node*> compression;
			Node* root = current_node->Find_Compression(compression);
			if (ret.find(root) == ret.end()){
				ret[root] = set<int>();
			}
			for (int i = 0; i < indices.size();i++){
			ret[root].insert(indices[i]);
			}
			ret[root].insert(current_idx);
		}
		return;
	}
	for (auto it : Child){
		NestedMap* next_map = it.second;
		int current_idx = it.first;
		indices.push_back(current_idx);
		next_map->ScanMap(indices,ret,depth+1);
		indices.pop_back();
	}
	return;
}

/*
NestedMap<Node8>::DisjointSet_helper:
	A helper function for the disjointset algorithm. This function will get the root for each node
	Input:
		None
	Output:
		None
	Return value:
		A map from nodes to their roots will be computed
*/
template<>
void NestedMap<Node*>::DisjointSet_helper(unordered_map<Node*,set<int>>& ret){

for (auto it : Child){
	NestedMap* next_map = it.second;
	int current_idx = it.first;
	vector<int> indices;
	indices.push_back(current_idx);
	next_map->ScanMap(indices,ret,1);
	indices.pop_back();
}


return;
}

/*
NestedMap<vector<int>>::append:
	A fucntion for the TwoTask Algorithm only. This function will append a value to the given indices
	Input:
		indices: the indices to add this new motif index
		val: the value (motif index) to be added to the vector
		depth: the level of recursion
	Output:
		The motif index will be added to the vector of given indices
	Return value:
		None
*/
template <>
void NestedMap<vector<int>>::append(vector<int>& indices,int val,int depth){
	
	if (depth == (order-1)){
		auto it = TrueMap.find(indices[depth]);
		if (it == TrueMap.end()){
			TrueMap[indices[depth]] = vector<int>();
		}
		TrueMap[indices[depth]].push_back(val);
		return;
	}
	else{
		int current_index = indices[depth];
		NestedMap* next_map;
		auto it = Child.find(current_index);
		if (it == Child.end()){
			next_map = new NestedMap<vector<int>>(order);
			Child[current_index] = next_map;
			next_map->append(indices,val,depth+1);
		}else{
			next_map = Child[current_index];
			next_map->append(indices,val,depth+1);
		}
	}
	return;
}

/*
NestedMap<vector<int>>::pend:
	A fucntion for the DFS Algorithm only. This function will append a node tuple to the given indices
	Input:
		indices: the indices to add this new motif index
		val: the value (node tuple) to be added to the vector
		depth: the level of recursion
	Output:
		The node tuple will be added to the vector of given indices
	Return value:
		None
*/
template <>
void NestedMap<vector<vector<int>>>::pend(vector<int>& indices,vector<int>& val,int depth){
	
	if (depth == (order-1)){
		auto it = TrueMap.find(indices[depth]);
		if (it == TrueMap.end()){
			TrueMap[indices[depth]] = vector<vector<int>>();
		}
		TrueMap[indices[depth]].push_back(val);
		return;
	}
	else{
		int current_index = indices[depth];
		NestedMap* next_map;
		auto it = Child.find(current_index);
		if (it == Child.end()){
			next_map = new NestedMap<vector<vector<int>>>(order);
			Child[current_index] = next_map;
			next_map->pend(indices,val,depth+1);
		}else{
			next_map = Child[current_index];
			next_map->pend(indices,val,depth+1);
		}
	}
	return;
}


/*
NestedMap<T>::FetchHelper
	A function for DFS walker only.
*/
template<class T>
void NestedMap<T>::FetchHelper(vector<vector<int>>& ret_tuples,vector<int>& indices,int depth){
	if (depth == (order-1)){
		for (auto it: TrueMap){
			int current_idx = it.first;
			indices.push_back(current_idx);
			ret_tuples.push_back(indices);
			indices.pop_back();
		}
	return;
	}
	for (auto it : Child){
		NestedMap* next_map = it.second;
		int current_idx = it.first;
		indices.push_back(current_idx);
		next_map->FetchHelper(ret_tuples,indices,depth+1);
		indices.pop_back();
	}
	return;
}


template<class T>
void NestedMap<T>::FetchAllTuples(vector<vector<int>>& ret_tuples){
	for (auto it : Child){
		NestedMap* next_map = it.second;
		int current_idx = it.first;
		vector<int> indices;
		indices.push_back(current_idx);
		next_map->FetchHelper(ret_tuples,indices,1);
		indices.pop_back();
	}
	return;
}

template <>
bool NestedMap<bool>::CheckAndWrite(vector<int>& indices,int depth){
	
	if (depth == (order-1)){

		auto it = TrueMap.find(indices[depth]);
		if (it == TrueMap.end()){
			TrueMap[indices[depth]] = true;
			return false;
		}else
		{
			return true;
		}
		
	}
	else{
		int current_index = indices[depth];
		NestedMap* next_map;
		auto it = Child.find(current_index);
		if (it == Child.end()){
			next_map = new NestedMap<bool>(order);
			Child[current_index] = next_map;
			return next_map->CheckAndWrite(indices,depth+1);
		}else{
			next_map = Child[current_index];
			return next_map->CheckAndWrite(indices,depth+1);
		}
	}
}


template <>
bool NestedMap<bool>::ReadAndWrite(vector<int>& indices,int depth){
	if (depth == (order-1)){
		bool ret = TrueMap[indices[depth]];
		TrueMap[indices[depth]] = true;
		return ret;
	}
	int current_index = indices[depth];
	NestedMap* next_map = Child[current_index];
	return next_map->ReadAndWrite(indices,depth+1);

}



template class NestedMap<int>;
template class NestedMap<bool>;
template class NestedMap<Node*>;
template class NestedMap<vector<int>>;
template class NestedMap<vector<vector<int>>>;