#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

#include <cstddef>
#include <iostream>
#include "iterators.hpp"

namespace ft {

template<class T>
class vector_iterator : public iterator < random_access_iterator_tag,
					T,
					ptrdiff_t,
					T*,
					T&
					>
{
public :

    typedef typename iterator_traits<T*>::iterator_category	iterator_category;
    typedef typename iterator_traits<T*>::value_type		value_type;
    typedef typename iterator_traits<T*>::difference_type	difference_type;
    typedef typename iterator_traits<T*>::pointer		pointer;
    typedef typename iterator_traits<T*>::reference		reference;
    typedef          vector_iterator				iterator;

private:

	pointer            _ptr;

public:

	vector_iterator()                       : _ptr(NULL)     {}
	vector_iterator(pointer ptr)            : _ptr(ptr)      {}
	vector_iterator(iterator const & src)   : _ptr(src._ptr) {}
	virtual ~vector_iterator()                               {}

	iterator &              operator =  (iterator const & rhs) {_ptr = rhs._ptr; return *this;}

	reference               operator *  ()                  const {return *(this->_ptr);}
	pointer                 operator -> ()                  const {return this->_ptr;}
	reference               operator [] (difference_type n) const {return *(this->_ptr + n);}

	iterator &		operator ++ ()    {++_ptr; return *this;}
	iterator &		operator -- ()    {--_ptr; return *this;}
	iterator		operator ++ (int) {iterator tmp(*this); ++_ptr; return tmp;}
	iterator		operator -- (int) {iterator tmp(*this); --_ptr; return tmp;}

	friend iterator		operator +  (difference_type n, iterator const &rhs)    {return rhs._ptr + n;};
	difference_type		operator -  (iterator const &rhs) const   {return _ptr - rhs._ptr;};
	iterator		operator +  (difference_type n)   const   {return _ptr + n;};
	iterator		operator -  (difference_type n)   const   {return _ptr - n;};
	iterator &		operator += (difference_type n) {_ptr += n; return *this;};
	iterator &		operator -= (difference_type n) {_ptr -= n; return *this;};

	 bool                   operator == (iterator const & rhs) const { return _ptr == rhs._ptr; }
	 bool                   operator != (iterator const & rhs) const { return _ptr != rhs._ptr; }
	 bool                   operator <  (iterator const & rhs) const { return _ptr < rhs._ptr; }
	 bool                   operator <= (iterator const & rhs) const { return _ptr <= rhs._ptr; }
	 bool                   operator >  (iterator const & rhs) const { return _ptr > rhs._ptr; }
	 bool                   operator >= (iterator const & rhs) const { return _ptr >= rhs._ptr; }
};



template<class T>
class const_vector_iterator : public iterator < random_access_iterator_tag,
						T,
						ptrdiff_t,
						T*,
						T&
						>
{
public :

    typedef typename iterator_traits<T*>::iterator_category	iterator_category;
    typedef typename iterator_traits<const T*>::value_type	value_type;
    typedef typename iterator_traits<T*>::difference_type	difference_type;
    typedef typename iterator_traits<const T*>::pointer		pointer;
    typedef typename iterator_traits<const T*>::reference	reference;
    typedef          const_vector_iterator			iterator;


private:

	pointer          _ptr;

public:

	const_vector_iterator()                              : _ptr(NULL)             {}
	const_vector_iterator(pointer ptr)                   : _ptr(ptr)              {}
	const_vector_iterator(iterator const & src)          : _ptr(src._ptr)         {}
	const_vector_iterator(vector_iterator<T> const & src): _ptr(src.operator->()) {}
	virtual ~const_vector_iterator()                                              {}

	iterator &              operator =  (iterator const & rhs) {_ptr = rhs._ptr; return *this;}

	reference               operator *  ()                  const {return *(this->_ptr);}
	pointer                 operator -> ()                  const {return this->_ptr;}
	reference               operator [] (difference_type n) const {return *(this->_ptr + n);}

	iterator &		operator ++ ()    {++_ptr; return *this;}
	iterator &		operator -- ()    {--_ptr; return *this;}
	iterator		operator ++ (int) {iterator tmp(*this); ++_ptr; return tmp;}
	iterator		operator -- (int) {iterator tmp(*this); --_ptr; return tmp;}

	friend difference_type  operator -  (iterator const & x, iterator const & y)    {return x._ptr - y._ptr;}
	friend iterator		operator +  (difference_type n, iterator const &rhs)    {return rhs._ptr + n;}
	iterator		operator +  (difference_type n)   const   {return _ptr + n;};
	iterator		operator -  (difference_type n)   const   {return _ptr - n;};
	iterator &		operator += (difference_type n) {_ptr += n; return *this;};
	iterator &		operator -= (difference_type n) {_ptr -= n; return *this;};

	friend bool             operator == (iterator const & lsh, iterator const & rhs) { return lsh._ptr == rhs._ptr; }
	friend bool             operator != (iterator const & lsh, iterator const & rhs) { return lsh._ptr != rhs._ptr; }
	friend bool             operator <  (iterator const & lsh, iterator const & rhs) { return lsh._ptr <  rhs._ptr; }
	friend bool             operator <= (iterator const & lsh, iterator const & rhs) { return lsh._ptr <= rhs._ptr; }
	friend bool             operator >  (iterator const & lsh, iterator const & rhs) { return lsh._ptr >  rhs._ptr; }
	friend bool             operator >= (iterator const & lsh, iterator const & rhs) { return lsh._ptr >= rhs._ptr; }
};

}; // namespace ft
#endif
