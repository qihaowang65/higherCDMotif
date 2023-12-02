import numpy as np 
import sys
import pickle
from sklearn.cluster import KMeans
from scipy.stats import entropy
import pandas as pd

def EntropyCalculate(data):
    pd_series = pd.Series(data)
    counts = pd_series.value_counts()
    entropy_val = entropy(counts,base=2)
    return entropy_val

def NMI(raw):
    hyc = 0
    all_nodes = []
    for each_cc in raw:
        all_nodes += each_cc
    hy = EntropyCalculate(all_nodes)
    all_clusters = []
    for j in range(len(raw)):
        for each in raw[j]:
            all_clusters.append(j)
    hc = EntropyCalculate(all_clusters)
    for j in range(len(raw)):
        each_cc = raw[j]
        hyc += len(each_cc)/len(all_nodes) * EntropyCalculate(each_cc)
    iyc = hy - hyc
    nmi= 2*iyc/(hy+hc)
    return nmi


filename = sys.argv[1]
clusters = int(sys.argv[2])

label_file = filename.split('_')[0] + ".labels"

with open(label_file,"r+") as fp:
	lines = fp.readlines()

gt = {}
for each in lines:
	a,b = each.split( )
	gt[int(a)] = int(b)


with open(filename,"rb") as fp:
	n,embeddings = pickle.load(fp)

indices = []
X = []
for each in embeddings:
	indices.append(each)
	X.append(embeddings[each])

kmeans = KMeans(n_clusters=clusters, random_state=0, n_init="auto").fit(X)

ret = kmeans.labels_
final = {}
for i in range(len(ret)):
	current = ret[i]
	if current not in final:
		final[current] = []
	final[current].append(gt[indices[i]])

raw = []
for each in final:
	raw.append(final[each])

print(NMI(raw))

