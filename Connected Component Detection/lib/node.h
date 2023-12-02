#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <vector>

using namespace std;

class Node{
	public:

Node(vector<int> tuple,Node* up=NULL){
	value = tuple;
	parent = up;
}

~Node(){
}

inline void SetParent(Node* newparent){
	parent = newparent;
}

inline vector<int> GetValue(){
	return value;
}

Node* GetRoot(vector<Node*> &compression){
	if (parent == NULL){
		//current node is the root
		return this;
	}else{
		compression.push_back(this);
		return parent->GetRoot(compression);
	}
}

Node* Find_Compression(vector<Node*> &compression){
	if (parent == NULL){
		//current node is the root
		for (int i = 0; i < compression.size(); i++){
			compression[i]->SetParent(this);
		}
		return this;
	}else{
		compression.push_back(this);
		return parent->GetRoot(compression);
	}
}

	


	private:
		vector<int> value;
		Node* parent;
};


#endif