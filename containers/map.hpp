#ifndef MAP_HPP
# define MAP_HPP

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

#ifdef	__linux__
#	define LINUX 1
#else
#	define LINUX 0
#endif

namespace ft
{

template < 	class Key,
		class T,
		class Compare = std::less<Key>,
		class Alloc   = std::allocator<ft::pair<const Key,T> >
	>
class map
{

public:

typedef Key						key_type;
typedef T						mapped_type;
typedef Alloc						allocator_type;
typedef Compare						key_compare;
typedef ft::pair<const key_type,mapped_type>		value_type;
typedef typename allocator_type::reference		reference;
typedef typename allocator_type::const_reference	const_reference;
typedef typename allocator_type::pointer		pointer;
typedef typename allocator_type::const_pointer		const_pointer;
typedef typename allocator_type::size_type		size_type;
typedef typename allocator_type::difference_type	difference_type;

private:

typedef Node<value_type>*				node_ptr;
typedef Node<value_type>				node;

public:

typedef RBTree_iterator<node>				iterator;
typedef const_RBTree_iterator<node>			const_iterator;
typedef reverse_iterator<const_iterator>		const_reverse_iterator;
typedef reverse_iterator<iterator>			reverse_iterator;
class	value_compare: public std::binary_function<value_type, value_type, bool>
{
	protected:
		Compare comp;

	public:
		value_compare (Compare c): comp(c) {}
		typedef	bool		result_type;
		typedef	value_type	first_argument_type;
		typedef	value_type	second_argument_type;
		bool operator() (const value_type& x, const value_type& y) const
			{ return comp(x.first, y.first); }
};
private:

typedef RBTree<value_type, key_type, value_compare>	tree;

private:

tree			_tree;
allocator_type		_allocator;
key_compare		_compare;

private:

value_type _onlyKeyPair (const key_type & k) const
			{ return ft::make_pair(k, mapped_type()); }

value_type _onlyKeyPair (const key_type & k)
			{ return ft::make_pair(k, mapped_type()); }

public:

explicit map (	const key_compare& comp	    = key_compare(),
		const allocator_type& alloc = allocator_type())
		: _tree(tree(value_comp())), _allocator(alloc), _compare(comp)
{}

template <class InputIterator>
map (InputIterator first, InputIterator last,
	const key_compare    &comp  = key_compare(),
	const allocator_type &alloc = allocator_type())
	: _tree(tree(value_comp())), _allocator(alloc), _compare(comp)
{
	insert(first, last);
};

map (const map& other) : _tree(tree(value_comp()))
{
	*this = other;
}

virtual ~map ()
{
	_tree.hardClear();
};

map& operator = (const map& x)
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

mapped_type& operator [] (const Key& k)
{
	node_ptr node = _tree.searchTree(_onlyKeyPair(k));

	if (!node)
		return insert(_onlyKeyPair(k)).first->second;

	return node->data.second;
}

mapped_type& at (const key_type& k)
{
	node_ptr node = _tree.searchTree(_onlyKeyPair(k));

	if (!node)
	{
		if (LINUX)
			throw std::out_of_range("map::at");
		else
			throw std::out_of_range("map::at:  key not found");
	}
	return node->data.second;
};

const mapped_type& at (const key_type& k) const
{
	node_ptr node = _tree.searchTree(_onlyKeyPair(k));

	if (!node)
	{
		if (LINUX)
			throw std::out_of_range("map::at");
		else
			throw std::out_of_range("map::at:  key not found");
	}
	return node->data.second;
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

void      erase (iterator position) { erase(position->first); };
size_type erase (const key_type& k) { return _tree.erase(_onlyKeyPair(k)); }
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
void          swap (map& x)      { swap_elem(_tree, x._tree); };
void          clear     ()       { _tree.clear(); };


iterator	find (const key_type& k)
{
	iterator it = _tree.searchTree(_onlyKeyPair(k));
	if (it != NULL)
		return it;
	return end();
};

const_iterator	find (const key_type& k) const
{
	iterator it = _tree.searchTree(_onlyKeyPair(k));
	if (it != NULL)
		return it;
	return end();
};

size_type count (const key_type& k) const
{
	if (_tree.searchTree(_onlyKeyPair(k)))
		return 1;
	return 0;
};

iterator lower_bound (const key_type& k)
{
	iterator it	= begin();
	iterator limit	= end();
	while (it != limit)
	{
		if (it->first >= k)
			break;
		++it;
	}
	return it;
};

const_iterator lower_bound (const key_type& k) const
{
	const_iterator it	= begin();
	const_iterator limit	= end();
	while (it != limit)
	{
		if (it->first >= k)
			break;
		++it;
	}
	return it;
};

iterator upper_bound (const key_type& k)
{
	iterator it	= begin();
	iterator limit	= end();
	while (it != limit)
	{
		if (it->first > k)
			break;
		++it;
	}
	return it;
};

const_iterator upper_bound (const key_type& k) const
{
	const_iterator it	= begin();
	const_iterator limit	= end();
	while (it != limit)
	{
		if (it->first > k)
			break;
		++it;
	}
	return it;
};

pair<const_iterator,const_iterator>	equal_range (const key_type& k) const
{
	return ft::make_pair(lower_bound(k), upper_bound(k));
};
pair<iterator,iterator>			equal_range (const key_type& k)
{
	return ft::make_pair(lower_bound(k), upper_bound(k));
};

allocator_type	get_allocator () const
{
	return _allocator;
};



};//map

template <typename Key, typename T, typename Compare>
void swap (map<Key, T, Compare> &x, map<Key, T, Compare> &y)
{
	x.swap(y);
}

template <class Key, class T, class Compare, class Alloc>
bool operator == ( const map<Key,T,Compare,Alloc> & lhs, const map<Key,T,Compare,Alloc> & rhs)
{
	return ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class Key, class T, class Compare, class Alloc>
bool operator != (const map<Key,T,Compare,Alloc> & lhs, const map<Key,T,Compare,Alloc> & rhs)
{
	return !(lhs == rhs);
}

template <class Key, class T, class Compare, class Alloc>
bool operator <  (const map<Key,T,Compare,Alloc> & lhs, const map<Key,T,Compare,Alloc> & rhs)
{
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class Key, class T, class Compare, class Alloc>
bool operator <= (const map<Key,T,Compare,Alloc> & lhs, const map<Key,T,Compare,Alloc> & rhs)
{
	return !(rhs < lhs);
}

template <class Key, class T, class Compare, class Alloc>
bool operator >  (const map<Key,T,Compare,Alloc> & lhs, const map<Key,T,Compare,Alloc> & rhs)
{
	return rhs < lhs;
}

template <class Key, class T, class Compare, class Alloc>
bool operator >= (const map<Key,T,Compare,Alloc> & lhs, const map<Key,T,Compare,Alloc> & rhs)
{
	return !(lhs < rhs);
}


}// namespace ft
#endif
