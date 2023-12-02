#Input file:
#	Data graph, Query Graph, Round
#Procedure:
#	1. Read data graph
#	2. Construct Adjacency list
#	3. For each round
#		Remove one pair of edge, write the new gfu file, run subgraph matching, run preprocess, do link prediction
import sys
import numpy as np
import os
import pickle
data = str(sys.argv[1])
with open(data,"r") as fp:
	n = int(fp.readline())
	k = int(fp.readline())
	raw = list(range(k))
	matchings = []
	current = fp.readline()
	while (current != 'end\n'):
		map_obj = map(int,current.split())
		matchings.append(list(map_obj))
		current = fp.readline()

M = len(matchings)
adj = [[] for i in range(n)]
for each_motif in matchings:
	for i in range(k):
		for j in range(i+1,k):
			adj[each_motif[i]].append(each_motif[j])
			adj[each_motif[j]].append(each_motif[i])


for i in range(len(adj)):
	adj[i] = list(set(adj[i]))


def DFS(adj,v,visited):
	temp = []
	queue = [v]
	visited[v] = True
	while(queue):
		current = queue.pop()
		for each in adj[current]:
			if visited[each] == False:
				visited[each] = True
				queue.append(each)
				temp.append(each)
	return temp

def CCD(adj):
	visited = []
	cc= []
	for i in range(len(adj)):
		visited.append(False)
	for v in range(len(adj)):
		if visited[v] == False:
			if (len(adj[v]) != 0):
				temp = DFS(adj,v,visited)
				cc.append(temp)
			else:
				visited[v] = True
	return cc

ccs = CCD(adj)
size = []
for each_cc in ccs:
	size.append(len(each_cc))

loc = np.argmax(size)
percentage = [0.1,0.3,0.5,0.7]
center = min(ccs[loc])
upper = size[loc]

for each_percentage in percentage:
	target = int(upper * each_percentage)
	cmd = "./main " + data + " " + str(center) + " " + str(target) + " "
	cmd1 = cmd + "0 >> result.log"
	cmd2 = cmd + "1 >> result.log"
	os.system(cmd1)
	os.system(cmd2)


