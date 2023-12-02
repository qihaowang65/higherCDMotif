#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <chrono>
#include "lib/util.h"
#include "lib/nestedmap.h"
#include "lib/debugger.h"
#include "lib/disjointset.h"
#include "lib/TwoTask.h"
#include "lib/dfs.h"
#include "lib/dfs2.h"
#include "lib/counter.h"

Debugger deb;//A debuuger to print the position of program

using namespace std;

/*
Usage:
	A function to print correct usage of the program
	Input:
		None
	Output:
		Print the correct usage to stdout
	Return value: 
		None
*/
void usage(){
	cout << "./main [EdgeFile] [Connectivity Degree] [algorithm]"<<endl;
	cout << "Algorithm 0: DisjointSet Algorithm; 1: Motif-edge Incidence; Algorithm 2: Path-Transformation" <<endl;
}

/*
count_time:
	A function to compute time elapsed since start time
	Input:
		Start_time: the starting time
	Output: 
		None
	Return value: 
		The time elapsed in seconds after the start time
*/
double count_time(chrono::steady_clock::time_point start_time){
	chrono::steady_clock::time_point my_time = std::chrono::steady_clock::now();
	int time_in_ms =std::chrono::duration_cast<std::chrono::microseconds>(my_time - start_time).count();
	double time_in_sec = double(time_in_ms)/1000000;
	return time_in_sec;
}

int main(int argc, char ** argv){
	if (argc != 4){
		usage();
		return -1;
	}

	chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
	string filename = string(argv[1]);
	int order = stoi(string(argv[2]));
	string line;
	ifstream myfile(filename);
	vector<int*> all_motifs;
	int N,M,k;
	if (myfile.is_open()){
		getline(myfile,line);
		N = stoi(line);
		getline(myfile,line);
		k = stoi(line);
		while(getline(myfile,line)){
			istringstream is(line);
			int number;
			int* motif_edge = new int[k];
			int counter = 0;
			while(is >> number){
				motif_edge[counter] = number;
				counter++;
			}
			all_motifs.push_back(motif_edge);
		}
	}else{
		cout << "Unable to open the file." << endl;
		return -1;
	}
	all_motifs.pop_back();
	chrono::steady_clock::time_point finish_reading_time = std::chrono::steady_clock::now();
	M = all_motifs.size();
	//Finish reading input files
	//Get the indices of node tuple
	int* q = new int;
	int** history = Ckr(k,order,q);
	int result = 0;
	//Begin to solve the connected component problem 
	DisjointSet Solver1(order);
	TwoTask Solver2(M,order);
	DFS Solver3(order);
	int algorithm =stoi(argv[3]);
	switch(algorithm){
		case 0:
			result = Solver1.Solve(all_motifs,history,*q);
			break;
		case 1:
			result = Solver2.Solve(all_motifs,history,*q);
			break;
		case 2:
			result = Solver3.Solve(all_motifs,history,*q);
			break;
		default:
			cout << "Wrong Algorithm Number" << endl;
			return -1;
	}
	
	double total_time = count_time(start_time);
	double detection_time = count_time(finish_reading_time);


	cout << filename << ":" << order << "," << algorithm << "," << result << ","<< detection_time << "," << total_time << endl;
	for (int i = 0; i < all_motifs.size();i++){
		delete all_motifs[i];
	}

	return 0;
}
