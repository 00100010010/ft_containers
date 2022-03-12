#ifndef RBTREE_ITERATOR_HPP
# define RBTREE_ITERATOR_HPP

#include <cstddef>
#include "iterators.hpp"

namespace ft
{

template<class NODE>
class RBTree_iterator : public iterator< bidirectional_iterator_tag,
					NODE,
					ptrdiff_t,
					NODE*,
					NODE&
					>
{

public :

    typedef typename iterator_traits<NODE*>::value_type		node_value_type;
    typedef typename iterator_traits<NODE*>::pointer		node_ptr;
    typedef typename iterator_traits<NODE*>::iterator_category	iterator_category;
    typedef typename node_value_type::value_type		value_type;
    typedef          RBTree_iterator				iterator;

private:

    node_ptr                    _ptr;

public:

  	RBTree_iterator()                       : _ptr(NULL)     {}
  	RBTree_iterator(node_ptr ptr)           : _ptr(ptr)      {}
  	RBTree_iterator(iterator const & src)   : _ptr(src._ptr) {}
  	virtual ~RBTree_iterator()                               {}

    iterator   &  operator =  (iterator const & rhs){ _ptr = rhs._ptr; return *this; }
    node_ptr      getPtr()        const { return _ptr; };
    value_type &  operator *  ()  const { return (*_ptr).data; }
    value_type *  operator -> ()  const { return &_ptr->data; }

    iterator   &  operator ++ () { _ptr = _ptr->post_bound(_ptr); return *this; }
    iterator   &  operator -- () { _ptr = _ptr->pre_bound(_ptr);  return *this; }
    iterator      operator ++ (int) { iterator tmp = *this; ++*this; return tmp; }
    iterator      operator -- (int) { iterator tmp = *this; --*this; return tmp; }

    bool          operator != (iterator const & rhs) const { return _ptr != rhs._ptr; };
    bool          operator == (iterator const & rhs) const { return _ptr == rhs._ptr; };
};

template<class NODE>
class const_RBTree_iterator : public iterator<bidirectional_iterator_tag,
                                            NODE, ptrdiff_t, NODE*, NODE&>
{

public :

    typedef typename iterator_traits<NODE*>::value_type		node_value_type;
    typedef typename iterator_traits<NODE*>::pointer		node_ptr;
    typedef typename iterator_traits<NODE*>::iterator_category	iterator_category;
    typedef const typename node_value_type::value_type		value_type;
    typedef const_RBTree_iterator				iterator;

private:

    node_ptr                    _ptr;

public:

    const_RBTree_iterator()				  : _ptr(NULL)        {}
    const_RBTree_iterator(node_ptr ptr)			  : _ptr(ptr)         {}
    const_RBTree_iterator(iterator const & src)		  : _ptr(src._ptr)    {}
    template <class T>
    const_RBTree_iterator(RBTree_iterator<T> const & src) : _ptr(src.getPtr()){}
    virtual ~const_RBTree_iterator()                                          {}

    iterator   &   operator =  (iterator const & rhs) { _ptr = rhs._ptr; return *this; }
    node_ptr       getPtr()        const { return _ptr; };
    value_type &   operator *  ()  const { return (_ptr)->data; }
    value_type *   operator -> ()  const { return &_ptr->data; }

    iterator   &   operator ++ () { _ptr = _ptr->post_bound(_ptr); return *this; }
    iterator   &   operator -- () { _ptr = _ptr->pre_bound(_ptr);  return *this; }
    iterator       operator ++ (int) { iterator tmp = *this; ++*this; return tmp; }
    iterator       operator -- (int) { iterator tmp = *this; --*this; return tmp; }

    bool           operator != (iterator const & rhs) const { return _ptr != rhs._ptr; };
    bool           operator == (iterator const & rhs) const { return _ptr == rhs._ptr; };
};

}// namespace ft
#endif
