#ifndef GUARD_vec_h
#define GUARD_vec_h

#include <set>
#include <map>
#include <iostream>
#include <math.h>

template<class Di, class Fi>
class VecSpace{
private:
	std::set<Di> D;
	Fi z;
public:
	VecSpace(std::set<Di> DD, Fi zz)
		: D(DD), z(zz) {}

	typename std::set<Di>::const_iterator domain_begin() const { return D.begin();}
	typename std::set<Di>::const_iterator domain_end() const { return D.end(); }
	typename std::set<Di>::const_iterator find(const Di& key) const { return D.find(key);}
	std::set<Di> domain() const {return D;}
	Fi zero() const { return z; }
	int domain_size() const { return D.size();}
};


template<class Di, class Fi>
class Vec {
private:
	VecSpace<Di,Fi>* s;
	std::map<Di,Fi> f;

public:
	// constructor
	Vec(VecSpace<Di,Fi>* ss, std::map<Di,Fi> ff) 
		: s(ss), f(ff) {}
	// construct empty vec
	Vec(VecSpace<Di,Fi>* ss)
		: s(ss) {}
	// construct vec with all elems set to a
	Vec(VecSpace<Di,Fi>* ss, Fi a);

	// accessor fuction
	VecSpace<Di,Fi> space() const { return *s;}
	VecSpace<Di,Fi>* space_ptr() const { return s;}


	typedef typename std::set<Di>::const_iterator domain_iterator;
	domain_iterator domain_begin() const { return s->domain_begin(); }
	domain_iterator domain_end() const { return s->domain_end(); }
	domain_iterator find_domain(const Di& key) const{ return s->find(key); }
	Fi zero() const { return s->zero(); }
	std::set<Di> domain() const { return s->domain();}
	int domain_size() const { return s->domain_size(); }

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
Vec<Di,Fi>::Vec(VecSpace<Di,Fi>* ss, Fi a)
: s(ss)
{
	domain_iterator it;
	for(it = this->domain_begin();it!=this->domain_end();++it)
		f[*it] = a;
}

template<class Di, class Fi>
void Vec<Di,Fi>::set_elem(const Di& key , const Fi& val)
{
	if(s == NULL)
		throw " Uninitialzed domain.";
	domain_iterator it = this->find_domain(key);
	if(it == this->domain_end() ) throw "Key no in domain.";
	else (*this).f[key] = val;
}
template<class Di, class Fi>
Vec<Di,Fi>& Vec<Di,Fi>::operator+=(const Vec<Di,Fi>& rhs)
{
	if( s != rhs.space_ptr() ) {
		throw "Domain error.";
	}
	else if (s == NULL){
		throw " Uninitialized domain.";
	}
	else {
			for(domain_iterator it=this->domain_begin();
					it!=this->domain_end();++it)
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
	if( this->find_domain(key) == this->domain_end())
		throw "Key not in domain";
	typename std::map<Di,Fi>::const_iterator it = f.find(key);

	if(it == f.end() ) return this->zero();
	else return it->second;
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
	if( vec1.space_ptr() != vec2.space_ptr() )
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
	if(lhs.domain_ptr()==NULL or rhs.domain_ptr()==NULL)
		throw "Comparison if uninitialized vectors";
	if(&lhs==&rhs) return true;
	if(lhs.domain_ptr()!=rhs.domain_ptr()) return false;
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
