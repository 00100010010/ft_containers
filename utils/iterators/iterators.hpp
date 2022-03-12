#ifndef ITERATORS_HPP
# define ITERATORS_HPP

#include <cstddef>
#include <iostream>

namespace ft {
////////////////////////////////////////////////////////////////////////////////
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag       : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};
////////////////////////////////////////////////////////////////////////////////
template < class Category,
		class T,
		class Distance	= std::ptrdiff_t,
		class Pointer	= T*,
		class Reference = T&
	>
struct iterator
{
	typedef T					value_type;
	typedef Distance				difference_type;
	typedef Pointer					pointer;
	typedef Reference				reference;
	typedef Category				iterator_category;
};
////////////////////////////////////////////////////////////////////////////////
template<class InputIt>
struct iterator_traits
{
	typedef typename InputIt::difference_type	difference_type;
	typedef typename InputIt::value_type		value_type;
	typedef typename InputIt::pointer		pointer;
	typedef typename InputIt::reference		reference;
	typedef typename InputIt::iterator_category	iterator_category;
};
////////////////////////////////////////////////////////////////////////////////
template<class T>
struct iterator_traits<T*>
{
	typedef ptrdiff_t			difference_type;
	typedef T				value_type;
	typedef T*				pointer;
	typedef T&				reference;
	typedef random_access_iterator_tag	iterator_category;
};
////////////////////////////////////////////////////////////////////////////////
template<class Iterator>
class reverse_iterator
{

public:

	typedef          Iterator					iterator_type;
	typedef typename iterator_traits<Iterator>::difference_type	difference_type;
	typedef typename iterator_traits<Iterator>::value_type		value_type;
	typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;

private:

	iterator_type              _it;

public:

	reverse_iterator()						   : _it(NULL)          {}
	reverse_iterator(value_type * ptr)				   : _it(Iterator(ptr)) {}
	reverse_iterator(iterator_type const & x) 			   { _it = x; --_it;     }
	template <class T> reverse_iterator(reverse_iterator<T> const & x) : _it(x.getPtr())    {}
	virtual ~reverse_iterator()                                                             {}

	template <class T>
	reverse_iterator &       operator =  ( reverse_iterator<T> const & rhs)
	{
		_it = rhs.getPtr();
		return *this;
	}

	Iterator        	base()         const { return ++Iterator(_it); }
	iterator_type		getPtr()       const { return _it; }
	value_type &		operator *  () const { return *_it; }
	value_type *		operator -> () const { return &(*_it.operator->()); }

	value_type &            operator [] (difference_type n) const { return *(_it - n); }

	reverse_iterator &      operator ++ ()    { --_it; return *this;}
	reverse_iterator &      operator -- ()    { ++_it; return *this;}
	reverse_iterator        operator ++ (int) { reverse_iterator tmp(*this); --_it; return tmp; }
	reverse_iterator        operator -- (int) { reverse_iterator tmp(*this); ++_it; return tmp; }

	template <class T>
	difference_type		operator -  (reverse_iterator<T> const & x)                 { return x.base() - base(); };
	reverse_iterator        operator -  (difference_type n) const                       { return _it + n + 1;; }
	reverse_iterator        operator +  (difference_type n) const                       { return _it - n + 1; }
	friend reverse_iterator operator +  (difference_type n, reverse_iterator const &rhs){ return(reverse_iterator(rhs.base() - n)); }
	reverse_iterator &      operator += (difference_type n)                             { _it -= n; return *this; }
	reverse_iterator &      operator -= (difference_type n)                             { _it += n; return *this; }

	template <class T> bool	operator == (reverse_iterator<T> const &rhs) const { return base()==(rhs.base()); };
	template <class T> bool	operator != (reverse_iterator<T> const &rhs) const { return base()!=(rhs.base()); };
	template <class T> bool	operator <  (reverse_iterator<T> const &rhs) const { return base()> (rhs.base()); };
	template <class T> bool	operator <= (reverse_iterator<T> const &rhs) const { return base()>=(rhs.base()); };
	template <class T> bool	operator >  (reverse_iterator<T> const &rhs) const { return base()< (rhs.base()); };
	template <class T> bool	operator >= (reverse_iterator<T> const &rhs) const { return base()<=(rhs.base()); };
};
////////////////////////////////////////////////////////////////////////////////
}
#endif
