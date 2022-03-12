#ifndef RBTREE_HPP
# define RBTREE_HPP

#include <iostream>

#include "node.hpp"
#include "../pair.hpp"

#define COLORED "\e[0;31m"
#define RESET 	"\e[0;0m"

namespace ft
{

template    <class T,
            class Key,
            class Compare	= std::less<Key>,
            class Alloc		= std::allocator<Node<T> >
	    >
class RBTree
{

private:

	typedef Node<T>*					nodePtr;

public:

	typedef Alloc						allocator_type;
	typedef Node<T>						value_type;
	typedef Compare						key_compare;
	typedef key_compare					value_compare;
	typedef value_type&					reference;
	typedef const value_type&				const_reference;
	typedef value_type*					pointer;
	typedef const value_type*				const_pointer;
	typedef std::size_t					size_type;
	typedef std::ptrdiff_t					difference_type;

private:

	nodePtr			_root;
	nodePtr			leaf;
	allocator_type		_allocator;
	size_type		_size;
	key_compare		_compare;

private:

void _setRoot(nodePtr x)
{
	_root		= x;
	leaf->parent	= _root;
}

nodePtr _newNode(T data)
{
	nodePtr node       = _createNode(data);
	node->parent       = NULL;
	node->left         = leaf;
	node->right        = leaf;
	node->color        = Red;
	node->isLeaf       = true;
	return node;
}

nodePtr	_createNode(T data)
{
	nodePtr	node = _allocator.allocate(1);
	_allocator.construct(node, data);

	return node;
}

void 	_eraseNode(nodePtr node)
{
	_allocator.destroy(node);
	_allocator.deallocate(node, 1);
}

bool    _isLeft(nodePtr node) { return node == node->parent->left; }


nodePtr _searchTreeHelperKey(nodePtr node, T data) const
{
	if (node == leaf || node == NULL)
		return NULL;

	if (!value_comp()(data, node->data)
	 && !value_comp()(node->data, data))
		return node;

	if (value_comp()(data, node->data))
		return _searchTreeHelperKey(node->left, data);

	return _searchTreeHelperKey(node->right, data);
}

void _eraseBalance(nodePtr x)
{
	nodePtr         s;

	while (x != _root  && x->color == Black)
	{
		bool side = x == x->parent->left ? 1 : 0;

		side ? s = x->parent->right
		     : s = x->parent->left;

		if (s->color == Red)
		{
			s->color         = Black;
			x->parent->color = Red;

			side ? leftRotate (x->parent)
			     : rightRotate(x->parent);

			side ? s = x->parent->right
			     : s = x->parent->left;
		}
		if (s->left->color == Black && s->right->color == Black)
		{
			s->color = Red;
			x        = x->parent;
		}
		else
		{
			if ((side && s->right->color == Black)
			|| (!side && s->left->color == Black))
			{
				side ? s->left->color = Black
				     : s->right->color = Black;

				s->color = Red;

				side ? rightRotate(s)
				     : leftRotate(s);

				side ? s = x->parent->right
				     : s = x->parent->left;
			}
			s->color         = x->parent->color;
			x->parent->color = Black;

			side ? s->right->color = Black
			     : s->left->color  = Black;

			side ? leftRotate (x->parent)
			     : rightRotate(x->parent);
			x = _root;
		}
	}
	x->color = Black;
}

// side 0 == left rotate
// side 1 == right rotate
void _rotate(nodePtr n, bool side)
{
	nodePtr z = side ? n->left
			 : n->right;

	side ? n->left  = z->right
	     : n->right = z->left;

	if ((side && z->right != leaf) || (!side && z->left != leaf))
		side ? z->right->parent = n
		     : z->left->parent  = n;

	z->parent = n->parent;

	if (n->parent == NULL)
		_root = z;
	else
	{
		if (side)
			n == n->parent->right ? n->parent->right = z
					      : n->parent->left  = z;
		else
			n == n->parent->left  ? n->parent->left  = z
					      : n->parent->right = z;
	}
	side ? z->right = n
	     : z->left  = n;
	n->parent = z;
}

ft::pair<nodePtr, bool> _insertBalance(nodePtr k)
{
	nodePtr	u;
	int	flag;
	nodePtr	target_lock = k;

	while (k->parent->color == Red)
	{
		k->parent == k->parent->parent->right ? flag = 0
						      : flag = 1;
		!flag ?	u = k->parent->parent->left
		      : u = k->parent->parent->right;
		if (u->color == Red)
		{
			u->color                    = Black;
			k->parent->color            = Black;
			k->parent->parent->color    = Red;
			k                           = k->parent->parent;
		}
		else
		{
			if ((!flag && k == k->parent->left)
			|| (flag && k == k->parent->right))
			{
				k = k->parent;
				!flag ? rightRotate(k)
				      : leftRotate(k);
			}
			k->parent->color            = Black;
			k->parent->parent->color    = Red;
			!flag ? leftRotate (k->parent->parent)
			      : rightRotate(k->parent->parent);
		}
		if (k == _root)
			break ;
	}
	_root->color = Black;
	return ft::make_pair(target_lock, true);
}

nodePtr _maximum(nodePtr node) const
{
	if (_root->right == leaf && _root->left == leaf)
		return node;

	while (node && node->right != leaf)
		node = node->right;

	return node;
}

nodePtr _minimum(nodePtr node) const
{
	while (node && node->left != leaf)
		node = node->left;

	return node;
}

void _displayHelper(nodePtr node, std::string space)
{
	if (node == leaf)
		return ;

	std::string color = node->color ? COLORED : "";

	if (node->left != leaf)
		_displayLeft(node->left, space, 0);

	std::cout << space << "─────│" << color
		  << "[" << node->data << "]" << RESET << std::endl;

	if (node->right != leaf)
		_displayRight(node->right, space, 0);
}

void _displayLeft(nodePtr node, std::string space, int x)
{
	std::string s;
	std::string color = node->color ? COLORED : "";

	x ? s = space + "    "
	  : s = space + "     ";

	if (node->left != leaf)
		_displayLeft(node->left, s, 0);

	std::cout << s << "┌────│" << color
		  << "[" << node->data << "]" << RESET << std::endl;

	if (node->right != leaf)
	{
		x ? space += "    │" : space += "     │";
		_displayRight(node->right, space, 1);
	}
}

void _displayRight(nodePtr node, std::string space, int x)
{
	std::string s;
	std::string color = node->color ? COLORED : "";

	x ? s = space + "    "
	  : s = space + "     ";

	if (node->left != leaf)
	{
		x ? space += "    │" : space += "     │";
		_displayLeft(node->left, space, 1);
	}

	std::cout << s << "└────│" << color
		  << "[" << node->data << "]" << RESET << std::endl;

	if (node->right != leaf)
		_displayRight(node->right, s, 0);
}

void _spiral(nodePtr node)
{
	if (!node || node == leaf)
		return;
	if (node->left != leaf)
		_spiral(node->left);
	if (node->right != leaf)
		_spiral(node->right);

	_eraseNode(node);
	_size--;
	node = NULL;
}

public:

explicit RBTree(const Compare& comp = Compare(), const Alloc& alloc = Alloc())
		: _allocator(alloc),
		  _size(0),
		  _compare(comp)
{
	leaf          = _createNode(T());
	leaf->color   = Black;
	leaf->left    = NULL;
	leaf->right   = NULL;
	leaf->parent  = NULL;
	leaf->isLeaf   = true;
	_root        = leaf;
}

RBTree (const RBTree& other):	_allocator(other._allocator),
				_size(0),
				_compare(other._compare)
{
	*this = other;
}

RBTree& operator = (const RBTree& x)
{
	_root 		= x._root;
	leaf 		= x.leaf;
	_allocator 	= x._allocator;
	_size 		= x._size;
	_compare 	= x._compare;
	return *this;
}

virtual ~RBTree() {};

value_compare value_comp()  const { return _compare; }

nodePtr	  getRoot() 	    const { return this->_root; }

bool	  isLeaf(nodePtr x) 	  { return (x == leaf); }

nodePtr   searchTree(T val) const { return _searchTreeHelperKey(this->_root, val); }
nodePtr   searchTree(T val)	  { return _searchTreeHelperKey(this->_root, val); }

size_type max_size()	    const { return _allocator.max_size(); };

nodePtr   next_bound(nodePtr n)	  { return n->post_bound(n); }
nodePtr   prev_boud (nodePtr n)	  { return n->pre_bound(n); }

nodePtr   minimum() 	    const { return _minimum(getRoot()); }
nodePtr   maximum() 	    const { return _maximum(getRoot()); }

size_type getSize()	    const { return _size; }

void	  leftRotate (nodePtr x)  { _rotate(x, 0); }
void 	  rightRotate(nodePtr x)  { _rotate(x, 1); }

void hardClear()
{
	clear();
	_eraseNode(leaf);
}

void clear()
{
	_spiral(_root);
	_size = 0;
	_setRoot(leaf);
}

ft::pair<nodePtr, bool> insert(T data)
{
	_size++;
	nodePtr node   = _newNode(data);
	node->isLeaf   = false;
	nodePtr tmp    = _root;
	while (tmp != leaf)
	{
		node->parent = tmp;
		value_comp()(node->data, tmp->data) ? tmp = tmp->left
						    : tmp = tmp->right;
	}

	if (node->parent == NULL)
		_setRoot(node);
	else
	{
		value_comp()(node->data, node->parent->data) ?
			  node->parent->left  = node
			: node->parent->right = node;
	}
	if (node->parent == NULL)
		node->color = Black;

	else if (node->parent->parent != NULL)
		return _insertBalance(node);
	return ft::make_pair(node, true);
}

size_type erase(T val)
{
	nodePtr z	= NULL;
	z		= _searchTreeHelperKey(getRoot(), val);
	if (z == NULL)
		return 0;

	_size--;

	nodePtr x;
	int flag = z->color;

	if (z->left != leaf && z->right != leaf)
	{
		nodePtr y 	= _minimum(z->right);
		flag 		= y->color;
		x 		= y->right;

		if (y->parent == z)
			x->parent = y;
		else
		{
			if (y->parent == NULL)
				_root = y->right;
			else if (y == y->parent->left)
				y->parent->left = y->right;
			else
				y->parent->right = y->right;
			y->right->parent = y->parent;
			y->right 	 = z->right;
			y->right->parent = y;
		}

		if (z->parent == NULL)
			_root = y;
		else
			z == z->parent->left ? z->parent->left  = y
					     : z->parent->right = y;

		y->parent 	= z->parent;
		y->left 	= z->left;
		y->left->parent = y;
		y->color 	= z->color;
	}

	else if (z->left == leaf || z->right == leaf)
	{
		bool side = z->left == leaf ? 1 : 0;

		x = side ? z->right
			 : z->left;

		if (z->parent ==  NULL)
			_root = side ? z->right
				     : z->left;

		else if (z->parent->left == z)
			z->parent->left = side ? z->right
					       : z->left;
		else
			z->parent->right = side ? z->right
						: z->left;

		side ? z->right->parent = z->parent
		     : z->left->parent  = z->parent;
	}

	_eraseNode(z);

	if (flag == Black)
		_eraseBalance(x);

	_setRoot(getRoot());
	return 1;
}

void display()
{
	if (!_root)
		return ;
	_displayHelper(this->_root, "");
}

}; // rb_tree
} // namespace
#endif
