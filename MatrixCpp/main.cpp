#include "vec.h"
#include "triangular.h"

#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <math.h>
#include <typeinfo>

using namespace::std;

int main()
{

	set<int> s;
	for(int i=0;i<10;++i) s.insert(i);
	Vec<int,double> sq(s,0.0);
	for(set<int>::const_iterator it=sq.domain_begin(); it!=sq.domain_end();++it) {
		sq.set_elem(*it,sqrt(*it));
		cout << sq[*it] << endl;
	}
	

	return 0;
}

