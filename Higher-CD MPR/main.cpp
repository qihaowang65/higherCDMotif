#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <algorithm>
#include <chrono>
#include "lib/util.h"
#include "lib/nestedmap.h"
#include "lib/debugger.h"
#include "lib/edgeadj.h"
#include "lib/randomwalk.h"
#include <time.h>

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
	cout << "Windows Usage: main.exe [EdgeFile] [connectivity degree] [number of steps] [output file]"<<endl;
	cout << "Linux Usage: ./main [EdgeFile] [connectivity degree] [number of steps] [output file]"<<endl;
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
	if (argc != 5){
		usage();
		return -1;
	}

	chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
	string filename = string(argv[1]);
	int r = stoi(string(argv[2]));
	int steps = stoi(string(argv[3]));
	int alpha = 85;
	string outfile = string(argv[4]);
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
	M = all_motifs.size();
	//Finish reading input files
	//Begin to solve the problem 
	EdgeAdj current_order(all_motifs,r,k);

	int counter = 0;
	map<int,int> point;
	srand (time(NULL));
	pair<int,int> result = Restart(all_motifs,k,M);
	int current_motif = result.first; 
	int current_node = result.second;
	point[current_node] = 1;
	vector<int> neigh =current_order.GetNeighour(all_motifs[current_motif]);
	for (auto it = neigh.begin(); it != neigh.end(); it++){
		if (*it ==current_motif){
			neigh.erase(it);
			break;
		}
	}

	while (counter < steps){
		counter++;
		cout << counter <<endl;
		int t = rand() % 100;
		if (t >= alpha || neigh.size() == 0){
			result = Restart(all_motifs,k,M);
			current_motif = result.first; 
			current_node = result.second;
			
		}else{
			result = OneStep(neigh,current_node,current_motif,all_motifs,k);
			current_motif = result.first; 
			current_node = result.second;
			//cout << current_motif << endl;
		}
		neigh = current_order.GetNeighour(all_motifs[current_motif]);
		for (auto it = neigh.begin(); it != neigh.end(); it++){
			if (*it ==current_motif){
				neigh.erase(it);
				break;
			}
		}

		//cout << current_motif << endl;
		auto it = point.find(current_node);
		if (it == point.end()){
			point[current_node] = 1;
		}else{
			it->second++;
		}
	}
	
	ofstream stream(outfile);
	for(auto& kv : point) {
  		stream << kv.first << "," << kv.second << endl;
	}
	stream.close();
	

	for (int i = 0; i < all_motifs.size();i++){
		delete all_motifs[i];
	}

	return 0;
}

