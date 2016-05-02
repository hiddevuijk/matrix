from vec import Vec
from vecutil import zero_vec

def triangular_solve_n(rowlist,b):
	D = rowlist[0].D
	n = len(D)
	assert D == set(range(n))
	x = zero_vec(D)
	for i in reversed(range(n)):
		x[i] = (b[i]-rowlist[i]*x)/rowlist[i][i]
	return x

def triangular_solve(rowlist, label_list,b):
	D = rowlist[0].D
	x = sero_vec(D)
	for j in reversed(range(len(D))):
		c = label_list[j]
		row = rowlist[j]
		x[c] = (b[j]-x*row)/row[c]
	return x

