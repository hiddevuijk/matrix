
def add(u,v):
	assert u.D==v.D
	dic = {}
	for d in u.D:
		if getitem(u,d)+getitem(v,d) != 0:
			dic[d] = getitem(u,d) + getitem(v,d)
	return Vec(u.D,dic)

def scalar_mul(v,alpha):
	return Vec(v.D, {d:alpha*value for d,value in v.f.items()})

def neg(v): return scalar_mul(v,-1)

def list_dot(u,v): return sum([ui*vi for (ui,vi) in zip(u,v)])

def setitem(v,k,val):
	assert k in  v.D
	v.f[k] = val

def getitem(v,d):
	assert d in v.D
	return v.f[d] if d in v.f else 0

def dot(u,v):
	assert u.D == v.D
	s =0
	for k in u.D:
		s+= getitem(u,k)*getitem(v,k)
	return s

def equal(u,v):
	assert u.D == v.D
	for k in u.D:
		if getitem(u,k)!=getitem(v,k):
			return False
	return True

#############################
#####					#####
#####	The Vec class	#####
#####					#####
#############################

class Vec:
	"""
	A vector has two fields:
	D - The domain (a set)
	f - A dictionary mapping( a part of) the domain to fild elements.
		Elements not in D are maped to 0.
	"""
	def __init__(self,labels,function):
		assert isinstance(labels,set)
		assert isinstance(function,dict)
		self.D = labels
		self.f = function

	__getitem__ = getitem
	__setitem__ = setitem
	__neg__ = neg
	__rmul__ = scalar_mul

	def __mul__(self,other):
		if isinstance(other,Vec):
			return dot(self,other)
		else:
			return NotImplemented

	def __truediv__(self,other):
		return (1/other)*self

	__add__ = add

	####
	def __radd__(self,other):
		if other == 0:
			return self

	def __sub__(a,b):
		return a+(-b)

	__eq__ = equal

	def is_almost_zero(self):
		s=0
		for x in sefl.f.values():
			if isinstance(x,int) or isinstance(x.float):
				s+=x*x
			elif instance(x,complex):
				y = abs(x)
				s+=y*y
			else: return false
		return s < 1e-20

	def __str__(v):
		"pretty-printing"
		D_list = sorted(v.D, key=repr)
		numdec = 3
		wd = dict([(k,(1+max(len(str(k)), len('{0:.{1}G}'.format(v[k], numdec))))) if isinstance(v[k], int) or isinstance(v[k], float) else (k,(1+max(len(str(k)), len(str(v[k]))))) for k in D_list])
		s1 = ''.join(['{0:>{1}}'.format(str(k),wd[k]) for k in D_list])
		s2 = ''.join(['{0:>{1}.{2}G}'.format(v[k],wd[k],numdec) if isinstance(v[k], int) or isinstance(v[k], float) else '{0:>{1}}'.format(v[k], wd[k]) for k in D_list])
		return "\n" + s1 + "\n" + '-'*sum(wd.values()) +"\n" + s2

	def __hash__(self):
		"Here we pretend Vecs are immutable so we can form sets of them"
		h = hash(frozenset(self.D))
		for k,v in sorted(self.f.items(), key = lambda x:repr(x[0])):
			if v != 0:
				h = hash((h, hash(v)))
		return h

	def __repr__(self):
		return "Vec(" + str(self.D) + "," + str(self.f) + ")"

	def copy(self):
		"Don't make a new copy of the domain D"
		return Vec(self.D, self.f.copy())

	def __iter__(self):
		raise TypeError('%r object is not iterable' % self.__class__.__name__)

