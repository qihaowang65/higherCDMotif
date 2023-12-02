# Higher-CD Motif-Graph Analytic
This project aims to compute two fundamental measures, distance and connections, in motif-graph with higher-CD.
## Compile
For each measure, go to the corresponding folder. Then compile the file with:
```bash
make
```
## Usage (Connected Component Detection)
To execute the program, please run
```bash
./CCD [Motif-Edge File] [Connectivity Degree] [Algorithm Name]
```
For example, if the input file's name is "edge.txt", connectivity degree is 2, and we want to run disjoint set algorithm, then we should use
```bash
./CCD edge.txt 2 0
```
Then each connected component will be printed in each line. At the end, the total number of connected components and running time for the algorithm will also be shown. 
## Algorithm Number
Here is the list of algorithms:

0. Disjoint set Algorithm
1. Motif-edge Algorithm (Print function disabled for efficiency comparison)
2. Path Transformation Algorithm (Print function disabled for efficiency comparison)

## Usage (Higher-CD Shortest Distance)
To execute the program, please run
```bash
./distance [Motif-Edge File] [Connectivity Degree] [Node Pair File]
```
For example, if the input file's name is "edge.txt", connectivity degree is 2, and we want to get the shortest distances for all node pairs in "nodes.txt", then we should use
```bash
./distance edge.txt 2 nodes.txt
```
Then the distances for each pair will be printed. If two nodes are disconnected, a value of "-1" will be printed.


## Input Motif-edge File Format
The input file should be a txt file. Its first line should be the number of nodes in the graph and its second line should be the size of motif. Then each line will list all nodes linked by one motif-edge. Nodes in the same motif-edge will be separated by space. All duplicated motif-edges should be removed, and the indices in each motif-edge should be ordered (e.g 1 2 3 4 instead of 1 3 2 4). Different motif edges do NOT have to be ordered.


## Input Node Pair File Format
The input node pair file should be a txt file. Each line in the file should be a node pair. Each node pair will be separated by space.
