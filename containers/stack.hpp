#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft
{

template < 	class T,
		class Container = ft::vector<T>
	>
class stack
{

protected:

	Container      c;

public:

	typedef T		value_type;
	typedef Container	container_type;
	typedef size_t		size_type;

	explicit 		stack(const container_type &ctnr = container_type()) : c(ctnr) {};
	
	void 			push(const value_type& x) { c.push_back(x); }

	bool 			empty()   const { return c.empty();}
	size_type 		size ()   const { return c.size(); }
	value_type& 		top  ()         { return c.back(); }
	const value_type& 	top  ()   const { return c.back(); }
	void 			pop  () 	{ c.pop_back(); }

	friend bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
		return lhs.c == rhs.c; };
	friend bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
		return lhs.c != rhs.c; };
	friend bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
		return lhs.c <  rhs.c; };
	friend bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
		return lhs.c <= rhs.c; };
	friend bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
		return lhs.c >  rhs.c; };
	friend bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
		return lhs.c >= rhs.c; };
}; // stack
}; //namespace ft
#endif
