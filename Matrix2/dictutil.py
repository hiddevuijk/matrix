# Copyright 2013 Philip N. Klein
def dict2list(dct, keylist): return [ dct[k] for k in keylist]

def list2dict(L, keylist): return {keylist[i]:L[i] for i in range(len(L))}

def listrange2dict(L): return {i:L[i] for i in range(len(L))}

def makeInverseIndex(strlist):
	# d: {<word>:<set of doc nrs containing word>}
	d = dict()
	
	for docNr,doc in enumerate(strlist):
		for word in doc.split():
			if word in d: d[word].add(docNr)
			else: d[word] = {docNr}
	return d	

def orSearch(inverseIndex,query):
	s = set()
	for q in query:
		if q in inverseIndex.keys():
			s = s | inverseIndex[q]
	return s


def andSearch(inverseIndex,query):
	s = set()
	first = True
	for q in query:
		if q in inverseIndex.keys():
			if first:
				first = False
				s = inverseIndex[q]
			else:
				s = s & inverseIndex[q]
	return s


