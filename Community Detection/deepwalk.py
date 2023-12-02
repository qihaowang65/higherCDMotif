import sys
from itertools import combinations
import random
import numpy as np
import gensim
import pickle
from gensim.models import Word2Vec
from tqdm import tqdm

if (len(sys.argv) != 4):
	print("Usage: python3 deepwalk.py [edgefile] [order] [length]")
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
end_file = file_name.split('.')[0] + "_" + str(r) + "_walk.pkl"
l = int(sys.argv[3])

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


for i in tqdm(range(M)):
	dest = []
	for each_tuple in motifs_to_tuple[i]:
		nearby_motifs = tuple_to_motifs[each_tuple]
		dest += nearby_motifs
	dest = set(dest)
	dest = list(dest)
	if i in dest:
		dest.remove(i)
	motifs_to_motifs.append(list(dest))


def RandomWalk(motifs_to_motifs,source,source_motif,matchings,l,k,M):
	ret = [source]
	current = source_motif
	for i in range(l):
		if len(motifs_to_motifs[current]) == 0:
			current = random.randint(0,M-1)
		else:
			rn = random.randint(0,len(motifs_to_motifs[current])-1)
			current = motifs_to_motifs[current][rn]

		rn = random.randint(0,k-1)
		ret.append(matchings[current][rn])

	return ret

context = []
for _ in range(3):
	o = [i for i in range(n)]
	random.shuffle(o)
	for v in tqdm(o):
		if v not in node_to_motifs:
			continue
		source_motif = random.randint(0,len(node_to_motifs[v])-1)
		source_motif = node_to_motifs[v][source_motif]
		context.append(RandomWalk(motifs_to_motifs,v,source_motif,matchings,l,k,M))


model = Word2Vec(context,vector_size=16,sg=1)
wv = model.wv
embedding = {}
for i in range(n):
	if i in wv:
		embedding[i] = wv[i]

with open(end_file,"wb") as fp:
	pickle.dump([n,embedding],fp)
