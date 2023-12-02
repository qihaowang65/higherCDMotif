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
	cout << "./main [EdgeFile] [connectivity degree] [node pairs file]"<<endl;
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
	int r = stoi(string(argv[2]));
	string nodefile = string(argv[3]);
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
	myfile.close();
	vector<vector<int>> node_pairs;
	ifstream myfile2(nodefile);

	while(getline(myfile2,line)){
			istringstream is(line);
			int number;
			vector<int> current_pair;
			int counter = 0;
			while(is >> number){
				current_pair.push_back(number);
			}
			node_pairs.push_back(current_pair);
	}



	all_motifs.pop_back();
	chrono::steady_clock::time_point finish_reading_time = std::chrono::steady_clock::now();
	M = all_motifs.size();
	//Finish reading input files
	//Begin to solve the problem 
	vector<int> results;

	EdgeAdj current_order(all_motifs,r,k);





	double matrix_time = count_time(finish_reading_time);

	
	for (int i = 0; i < node_pairs.size();i++){
		int start = node_pairs[i][0];
		int end = node_pairs[i][1];
		int finalresult = current_order.BFS(all_motifs,start,end);
		cout << finalresult << endl;
		results.push_back(finalresult);

	}




	double total_time = count_time(start_time);
	double computation_time = count_time(finish_reading_time);

	
	cout << filename << ":" << r << "," << ","  << matrix_time << "," << total_time <<endl;
	//cout << filename << ":" << r << "," << numbers << ","  << matrix_time  << "," << computation_time << "," << total_time << endl;
	for (int i = 0; i < all_motifs.size();i++){
		delete all_motifs[i];
	}

	return 0;
}

