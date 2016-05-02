#ifndef GUARD_vec_h
#define GUARD_vec_h

#include <set>
#include <map>
#include <iostream>
#include <math.h>


template<class Di, class Fi>
class Vec {
private:
	std::set<Di> D;
	std::map<Di,Fi> f;
	Fi z;
public:
	// constructor
	Vec(std::set<Di> DD, std::map<Di,Fi> ff, Fi zz) 
		: D(DD), f(ff), z(zz) {}
	// construct empty vec
	Vec(std::set<Di> DD, Fi zz)
		: D(DD), z(zz) {}
	// construct vec with all elems set to a
	Vec(std::set<Di> ,Fi, Fi);


	typedef typename std::set<Di>::const_iterator domain_iterator;
	domain_iterator domain_begin() const { return D.begin(); }
	domain_iterator domain_end() const { return D.end(); }
	domain_iterator find_domain(const Di& key) const{ return D.find(key); }
	Fi zero() const { return z; }
	std::set<Di> domain() const { return D;}
	int domain_size() const { return D.size(); }

	// overload the [] only const version
	Fi operator[](const Di&) const;

	// add elem to vec
	void set_elem(const Di&, const Fi&);

	// add elementwise
	Vec<Di,Fi>& operator+=(const Vec<Di,Fi>&);
	Vec<Di,Fi>& operator-=(const Vec<Di,Fi>&);

	// multiply all elements
	Vec<Di,Fi>& operator*=(const Di&);
	Vec<Di,Fi>& operator/=(const Di&);


};

template<class Di, class Fi>
Vec<Di,Fi>::Vec(std::set<Di> DD,Fi zz, Fi a)
: D(DD), z(zz), f()
{
	domain_iterator it;
	for(it = D.begin();it!=D.end();++it)
		f[*it] = a;
}

template<class Di, class Fi>
Vec<Di,Fi>& Vec<Di,Fi>::operator+=(const Vec<Di,Fi>& rhs)
{
	if( D != rhs.domain() ) {
		throw "Domain error.";
	}
	else {
		for(domain_iterator it=D.begin();it!=D.end();++it)
			f[*it] += rhs[*it];
	}
	return *this;
}

template<class Di,class Fi>
Vec<Di,Fi>& Vec<Di,Fi>::operator-=(const Vec<Di,Fi>& rhs)
{
	(*this) += -1*rhs;
	return *this;
}

template<class Di, class Fi>
Fi Vec<Di,Fi>::operator[](const Di& key) const
{
	if( D.find(key) == D.end())
		throw "Key not in domain";
	typename std::map<Di,Fi>::const_iterator it = f.find(key);

	if(it == f.end() ) return z;
	else return it->second;
}

template<class Di, class Fi>
void Vec<Di,Fi>::set_elem(const Di& key , const Fi& val)
{
	domain_iterator it = D.find(key);
	if(it == D.end() ) throw "Key no in domain.";
	else (*this).f[key] = val;
}

//////////////////////////////////////////////////
//												//
// 		non-member function						//
//      * (dotproduct), abs, average,			//
//		median, sum							  	//
//												//
//////////////////////////////////////////////////

template<class Di, class Fi>
Fi operator*(const Vec<Di,Fi>& vec1, const Vec<Di,Fi>& vec2)
{
	if( vec1.domain() != vec2.domain() )
		throw "Dotproduct of vectors in differetn spaces.";

	Fi sum = 0;
	for(typename std::set<Di>::const_iterator it=vec1.domain_begin();it!=vec1.domain_end();++it)
		sum += vec1[*it]*vec2[*it];
	return sum;
}


template<class Di, class Fi>
Fi abs(const Vec<Di,Fi>& vec)
{
	return sqrt(dot(vec,vec));
}

template<class Di,class Fi>
Fi sum(const Vec<Di,Fi>& vec)
{
	Fi s;
	typename std::set<Di>::const_iterator it;
	for(it=vec.domain_begin();it!=vec.domain_end();++it)
		s += vec[*it];
	return s;
}

template<class Di,class Fi>
Fi average(const Vec<Di,Fi>& v)
{
	return sum(v)/(v.domain_size());
}
//////////////////////////////////////////////////
//												//
// 		arithmatic operators (w/o =)			//
//      these are not member functions         	//
//												//
//////////////////////////////////////////////////
template<class Di,class Fi>
Vec<Di,Fi> operator+(Vec<Di,Fi> lhs, const Vec<Di,Fi>& rhs)
{
	lhs += rhs;
	return lhs;
}

template<class Di,class Fi>
Vec<Di,Fi> operator-(Vec<Di,Fi> lhs, const Vec<Di,Fi>& rhs)
{
	lhs -= rhs;
	return lhs;
}



//////////////////////////////////////////////////
//												//
// 		comparison operators					//
//      these are not member functions         	//
//												//
//////////////////////////////////////////////////

template<class Di,class Fi>
bool operator==(const Vec<Di,Fi>& lhs, const Vec<Di,Fi>& rhs)
{
	if(&lhs==&rhs) return true;
	if(lhs.domain()!=rhs.domain()) return false;
	for(typename std::set<Di>::const_iterator it= lhs.domain_begin();
			it!=lhs.domain_end();++it)
		if(lhs[*it]!=rhs[*it])
			return false;
	return true;
}

template<class Di,class Fi>
bool operator!=(const Vec<Di,Fi>& lhs, const Vec<Di,Fi>& rhs)
{
	return !operator==(lhs,rhs);
}

#endif
