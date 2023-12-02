import glob
files = glob.glob("./data/*.edge")


with open("run.sh","w+") as fp:
	fp.write("#!/bin/bash\n")
	for eachfile in files:
		k = eachfile.split('/data/')[1]
		k = k.split('.')[0]
		k = int(k.split('_')[1])
		for i in range(1,k):
			cmd = "./main " + eachfile + " " + str(i) + " 1000\n"
			fp.write(cmd)