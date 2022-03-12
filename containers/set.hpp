#ifndef SET_HPP
# define SET_HPP

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <limits>

#include "../utils/rb_tree/RBTree.hpp"
#include "../utils/iterators/RBTree_iterator.hpp"
#include "../utils/pair.hpp"
#include "../utils/utils.hpp"
#include "../utils/enable_if.hpp"
#include "../utils/is_integral.hpp"

#ifdef __linux__
#	define LINUX 1
#else
#	define LINUX 0
#endif

namespace ft
{

template < 	class Key,
           	class Compare	= std::less<Key>,
           	class Allocator	= std::allocator<Key>
	>
class set
{

public:

typedef Key						key_type;
typedef Key						value_type;
typedef std::size_t					size_type;
typedef std::ptrdiff_t					difference_type;
typedef Compare						key_compare;
class   value_compare: public std::binary_function<value_type, value_type, bool>
{
	protected:
		Compare comp;

	public:
		value_compare(Compare c): comp(c) {}
		typedef bool		result_type;
		typedef value_type	first_argument_type;
		typedef value_type	second_argument_type;
		bool operator()(const value_type& x, const value_type& y) const
			{ return comp(x, y); }
};
typedef Allocator					allocator_type;
typedef value_type&					reference;
typedef const value_type&				const_reference;
typedef typename Allocator::pointer			pointer;
typedef typename Allocator::const_pointer		const_pointer;

private:

typedef Node<value_type>*				node_ptr;
typedef Node<value_type>				node;
typedef RBTree<value_type, key_type, value_compare>	tree;

public:

typedef const_RBTree_iterator<node>			iterator;
typedef const_RBTree_iterator<node>			const_iterator;
typedef reverse_iterator<const_iterator>		const_reverse_iterator;
typedef reverse_iterator<iterator>			reverse_iterator;



private:

tree		_tree;
allocator_type	_allocator;
key_compare	_compare;

public:

explicit set (	const Compare&   comp	= Compare(),
		const Allocator& alloc	= Allocator())
		: _tree(tree(value_comp())), _allocator(alloc), _compare(comp)
{}

template <class InputIt>
set (InputIt first, InputIt last,
	const Compare& 	 comp  = Compare(),
	const Allocator& alloc = Allocator())
	: _tree(tree(value_comp())), _allocator(alloc), _compare(comp)
{
	insert(first, last);
};


set (const set& other) : _tree(tree(value_comp()))
{
	*this = other;
}

virtual ~set()
{
	_tree.hardClear();
};

set& operator = (const set& x)
{
	clear();
	_allocator = x._allocator;
	insert(x.begin(), x.end());
	return *this;
};

iterator begin ()
{
	if (!size())
		return end();
	return iterator(_tree.minimum());
};

const_iterator begin () const
{
	if (!size())
		return end();
	return const_iterator(_tree.minimum());
};

iterator end ()
{
	if (!size())
		return iterator(_tree.getRoot());
	return iterator(_tree.maximum()->right);
};

const_iterator	end () const
{
	if (!size())
		return const_iterator(_tree.getRoot());
	return const_iterator(_tree.maximum()->right);
};

reverse_iterator	rbegin ()       { return reverse_iterator      (end()); };
const_reverse_iterator	rbegin () const { return const_reverse_iterator(end()); };
reverse_iterator	rend   ()       { return reverse_iterator      (begin()); };
const_reverse_iterator	rend   () const { return const_reverse_iterator(begin()); };
bool			empty  () const { return _tree.getSize() == 0; };
size_type		size   () const { return _tree.getSize(); };

size_type		max_size()const
{
	if (LINUX)
		return _tree.max_size();

	int size	= sizeof(value_type);
	int new_size	= 16;
	if (size >= 8)
	{
		size    -= 4;
		new_size = 16;
		for (; size > 0 ; size -= 8)
			new_size += 4;
	}
	size = new_size;
	return std::numeric_limits<difference_type>::max() / size;
};

ft::pair<iterator, bool> insert (const value_type& val)
{
	node_ptr node = _tree.searchTree(val);

	if (node != NULL)
		return ft::make_pair(node, false);
	return _tree.insert(val);
}

iterator insert (iterator position, const value_type& val)
{
	(void)position;
	node_ptr node = _tree.searchTree(val);

	if (node != NULL)
		return iterator(node);
	return iterator(_tree.insert(val).first);
}

template <class InputIterator>
void	insert (InputIterator first, InputIterator last)
{
	for (InputIterator it = first; it != last; ++it)
		insert(*it);
};

void      erase (iterator position) { erase(*position); };
size_type erase (const value_type& val) { return _tree.erase(val); }
void      erase (iterator first, iterator last)
{
	for (iterator it = last; it != first; )
	{
		it = last;
		--it;
		erase(it);
	}
}

key_compare   key_comp  () const { return Compare(); }
value_compare value_comp() const { return value_compare(key_comp()); }
void          swap (set& x)      { swap_elem(_tree, x._tree); };
void          clear     ()       { _tree.clear(); };

iterator find (const value_type& val) const
{
	iterator it = _tree.searchTree(val);
	if (it != NULL)
		return it;
	return end();
};

size_type count (const value_type& val) const
{
	if (_tree.searchTree(val))
		return 1;
	return 0;
};

iterator lower_bound (const value_type& val) const
{
	iterator it	= begin();
	iterator limit	= end();
	while (it != limit)
	{
		if (*it >= val)
			break;
		++it;
	}
	return it;
};

iterator upper_bound (const value_type& val) const
{
	iterator it	= begin();
	iterator limit	= end();
	while (it != limit)
	{
		if (*it > val)
			break;
		++it;
	}
	return it;
};

pair<const_iterator,const_iterator>	equal_range (const key_type& val) const
{
	return ft::make_pair(lower_bound(val), upper_bound(val));
};

allocator_type	get_allocator () const
{
	return _allocator;
};

};//set

template <typename Key, typename Compare>
void swap(set<Key, Compare> &x, set<Key, Compare> &y)
{
	x.swap(y);
}

template <typename Key, typename Compare>
bool operator == (const set<Key,Compare> & lhs, const set<Key,Compare> & rhs)
{
	return ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename Key, typename Compare>
bool operator != (  const set<Key,Compare> & lhs, const set<Key,Compare> & rhs)
{
	return !(lhs == rhs);
}

template <typename Key, typename Compare>
bool operator <  (  const set<Key,Compare> & lhs, const set<Key,Compare> & rhs)
{
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename Key, typename Compare>
bool operator <= (  const set<Key,Compare> & lhs, const set<Key,Compare> & rhs)
{
	return !(rhs < lhs);
}

template <typename Key, typename Compare>
bool operator >  (  const set<Key,Compare> & lhs, const set<Key,Compare> & rhs)
{
	return rhs < lhs;
}

template <typename Key, typename Compare>
bool operator >= (  const set<Key,Compare> & lhs, const set<Key,Compare> & rhs)
{
	return !(lhs < rhs);
}

}// namespace ft
#endif
