#ifndef GUARD_triangular_h
#define GUARD_triangular_h

#include "vec.h"

#include <vector>

Vec<int,double> triangular_solve_n(const std::vector<Vec<int, double> >& rowlist,const Vec<int,double>& b)
{
	// check if domain is {0,1,2,3,4,...,n}
	int n = rowlist[0].domain_size();

	std::set<int>::const_iterator it = rowlist[0].domain_begin();
	for(int i=0;i<n;++i){
		if( (*it)!= i) throw "Domain error.";
	}
		
	Vec<int,double> x(rowlist[0].domain(),0.0);
	for(int i=(n-1);i>=0;--i) 
		x.set_elem(i,(b[i]-rowlist[i]*x)/rowlist[i][i]);

	return x;
}


#endif
