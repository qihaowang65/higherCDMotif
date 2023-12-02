from sknetwork.clustering import Louvain
import sys
from itertools import combinations
import random
import pickle
import numpy as np
from scipy.sparse import coo_matrix
from statistics import mode

TOP = 999
#Step 1: Load edge file and motif edge file
REMOVE_DUP = True

if (len(sys.argv) != 3):
	print("Usage: python3 edmot.py [edgefile] [cd]")
	exit(-1)


def indices_to_tuples(indices,motif):
	ret = []
	for each_tuple in indices:
		temp = []
		for i in range(len(each_tuple)):
			temp.append(motif[each_tuple[i]])
		ret.append(tuple(temp))
	return ret


file_name = sys.argv[1]
r = int(sys.argv[2])
end_file = file_name.split('.')[0] + "_" + str(r) + "_edmot.pkl"
label_file = file_name.split('_')[0] + '.labels'
edge = file_name.split('_')[0] + ".gfd"

with open(edge,'r') as fp:
	fp.readline()
	n = int(fp.readline())
	adjacency = np.zeros((n,n))
	for i in range(n):
		fp.readline()
	m = int(fp.readline())
	for i in range(m):
		edge = fp.readline().split(' ')
		src = int(edge[0])
		dst = int(edge[1])
		adjacency[src][dst] = 1


labels = {}
with open(label_file,'r') as fp:
	lines = fp.readlines()
	for each in lines:
		temp = each.split(' ')
		n = int(temp[0])
		l = int(temp[1])
		labels[n] = l


with open(file_name,"r") as fp:
	n = int(fp.readline())
	k = int(fp.readline())
	raw = list(range(k))
	indices = list(combinations(raw, r))
	matchings = []
	current = fp.readline()
	while (current != 'end\n'):
		map_obj = map(int,current.split())
		matchings.append(list(map_obj))
		current = fp.readline()

#Step 2: Find connected components in motif-edge file
motifs_to_motifs = []
motifs_to_tuple = []
tuple_to_motifs = {}
node_to_motifs = {}

M = len(matchings)
for i in range(M):
	for each_node in matchings[i]:
		if each_node in node_to_motifs:
			node_to_motifs[each_node].append(i)
		else:
			node_to_motifs[each_node] = [i]

	tuples = indices_to_tuples(indices,matchings[i])
	for each_tuple in tuples:
		if each_tuple not in tuple_to_motifs:
			tuple_to_motifs[each_tuple] = [i]
		else:
			tuple_to_motifs[each_tuple].append(i)
	motifs_to_tuple.append(tuples)


for i in range(M):
	dest = []
	for each_tuple in motifs_to_tuple[i]:
		nearby_motifs = tuple_to_motifs[each_tuple]
		dest += nearby_motifs
	dest = set(dest)
	dest = list(dest)
	if i in dest:
		dest.remove(i)
	motifs_to_motifs.append(list(dest))


def CCD(adj):
	#Input: motifs to motifs 2d list
	visited = [False for i in range(len(adj))]
	waiting_queue = []
	all_cc = []
	for i in range(len(visited)):
		if visited[i] == False:
			visited[i] = True
			current_cc = [i]
			for each_neigh in adj[i]:
				waiting_queue.append(each_neigh)
				current_cc.append(each_neigh)
				visited[each_neigh] = True
			while(waiting_queue):
				current = waiting_queue.pop()
				for each_neigh in adj[current]:
					if visited[each_neigh] == False:
						visited[each_neigh] = True
						waiting_queue.append(each_neigh)
						current_cc.append(each_neigh)
			all_cc.append(current_cc)
	return all_cc

all_cc = CCD(motifs_to_motifs)

def ComputeCC(all_cc,matchings):
	all_cc_node = []
	for each_cc in all_cc:
		current_node_cc = []
		for each_motif in each_cc:
			current_node_cc += matchings[each_motif]
		current_node_cc = list(set(current_node_cc))
		all_cc_node.append(current_node_cc)
	return all_cc_node


all_cc_node = ComputeCC(all_cc,matchings)

TOP = min(len(all_cc_node),TOP)
cc_size = []
for each_cc in all_cc_node:
	cc_size.append(-len(each_cc))
selector = np.argsort(cc_size)[0:TOP]
top_cc = []
for idx in selector:
	top_cc.append(all_cc_node[idx])

#Step 3: Get Adjacency for top components and apply louvain
def PerComponentLouvain(adjacency,current_cc):
	new_adj = []
	for i in range(len(current_cc)):
		temp = []
		for j in range(len(current_cc)):
			temp.append(adjacency[current_cc[i]][current_cc[j]])
		new_adj.append(temp)
	
	louvain = Louvain()
	new_adj = np.array(new_adj)
	ll = louvain.fit_predict(new_adj)
	clusters = {}
	for i in range(len(current_cc)):
		if ll[i] not in clusters:
			clusters[ll[i]] = []
		clusters[ll[i]].append(current_cc[i])
	ret = []
	for key in clusters:
		ret.append(clusters[key])
	return ret
#Step 4: Do the rewiring
for each_cc in top_cc:
	#ret = PerComponentLouvain(adjacency,each_cc)
	ret = each_cc
	for enh in [ret]:
		for a in enh:
			for b in enh:
				if a != b:
					adjacency[a][b] = 1
#Step 5: Find the final clusterin result
louvain = Louvain()
ll = louvain.fit_predict(adjacency)
clusters = {}
for i in range(len(adjacency)):
	if ll[i] not in clusters:
		clusters[ll[i]] = []
	clusters[ll[i]].append(labels[i])

final_results = []
for key in clusters:
	final_results.append(clusters[key])

final_results2 = []
for each_cc in all_cc_node:
	temp = []
	for each_node in each_cc:
		temp.append(labels[each_node])
	final_results2.append(temp)

#print(final_results)
with open(end_file,"wb") as fp:
	pickle.dump([final_results,final_results2],fp)
