#Input file:
#	Data graph, Query Graph, Round
#Procedure:
#	1. Read data graph
#	2. Construct Adjacency list
#	3. For each round
#		Remove one pair of edge, write the new gfu file, run subgraph matching, run preprocess, do link prediction
import sys
import random
import numpy as np
import os
import pickle



edgename = str(sys.argv[1])
outfile = edgename.split('.')[0] + "_1.rank"
steps = int(sys.argv[2])

with open(edgename,"r") as fp:
	n = int(fp.readline())
	k = int(fp.readline())
	raw = list(range(k))
	matchings = {}
	current = fp.readline()
	while (current != 'end\n'):
		map_obj = map(int,current.split())
		current_motif = list(map_obj)
		for i in range(k):
			for j in range(i+1,k):
				key = tuple((current_motif[i],current_motif[j]))
				if key in matchings:
					matchings[key] += 1
				else:
					matchings[key] = 1

		current = fp.readline()

nonzeros = list(matchings.keys())

adj = {}
for each in nonzeros:
	n1 = each[0]
	n2 = each[1]
	if n1 in adj:
		adj[n1].append(n2)
	else:
		adj[n1] = [n2]
	if n2 in adj:
		adj[n2].append(n1)
	else:
		adj[n2] = [n1]

del nonzeros
nodes = list(adj.keys())

z = 0
n = len(nodes)
current = random.randint(0,n-1)
current = nodes[current]
node_pr = {}
node_pr[current] = 1
while (z < steps):
	t = random.randint(0,99)
	if (t > 84):
		current = random.randint(0,n-1)
		current = nodes[current]
	else:
		temp = adj[current]
		weight = []
		for each in temp:
			if each < current:
				key = tuple((each,current))
			else:
				key = tuple((current,each))
			weight.append(matchings[key])
		point = random.choices(temp,weights=weight,k=1)[0]
	if current in node_pr:
		node_pr[current] += 1
	else:
		node_pr[current] = 1
	z += 1


with open(outfile,"w+") as fp:
	for key in node_pr:
		outstring = ''
		outstring += str(key)
		outstring += ','
		outstring += str(node_pr[key])
		outstring += '\n'
		fp.write(outstring)

