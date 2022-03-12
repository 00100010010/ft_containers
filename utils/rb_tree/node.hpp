#ifndef NODE_HPP
# define NODE_HPP

#include <iostream>

namespace ft
{

enum node_color { Black, Red };

template <class T>
struct Node
{
typedef T		value_type;
typedef value_type	second_type;
typedef T*		pointer;
typedef T&		reference;

value_type		data;
Node			*parent;
Node			*left;
Node			*right;
bool			color;
bool			isLeaf;

Node(T data) :	data(data),
		parent(NULL),
		left(NULL),
		right(NULL),
		color(Red),
		isLeaf(true) {};

bool    isLeft()		{ return (parent && this == this->parent->left); }
bool    isLeft() const		{ return (parent && this == this->parent->left); }

Node* fromTheRootToTheMax()
{
	Node* tmp = this;
	while (tmp->parent)
		tmp = tmp->parent;
	while (!tmp->right->isLeaf)
		tmp = tmp->right;
	return tmp;
}

Node* fromTheRootToTheMin()
{
	Node* tmp = this;
	while (tmp->left && !tmp->left->isLeaf)
		tmp = tmp->left;
	return tmp;
}

Node*   pre_bound(Node *ptr)
{
	if (ptr->isLeaf)
	{
		if (ptr->parent && !ptr->parent->isLeaf)
			ptr = ptr->parent->fromTheRootToTheMax();
	}
	else if (!ptr->left->isLeaf)
	{
		ptr = ptr->left;
		while (!ptr->right->isLeaf)
			ptr = ptr->right;
	}
	else if (ptr->parent && !ptr->isLeft())
		ptr = ptr->parent;
	else
	{
		while (ptr->parent && !ptr->parent->isLeaf && ptr->isLeft())
			ptr = ptr->parent;
		if (ptr->parent)
			ptr = ptr->parent;
		else
			ptr = ptr->fromTheRootToTheMax()->right;
	}
	return ptr;
}

Node*   post_bound(Node *ptr)
{
	Node* old = ptr;
	if (ptr && ptr->isLeaf)
		ptr = ptr->parent->fromTheRootToTheMin();
	else if (ptr && ptr->right && !ptr->right->isLeaf)
	{
		ptr = ptr->right;
		while (!ptr->left->isLeaf)
			ptr = ptr->left;
	}
	else if (ptr && ptr->parent && ptr->parent && ptr->isLeft())
		ptr = ptr->parent;
	else
	{
		while (ptr && ptr->parent && !ptr->parent->isLeaf && !ptr->isLeft())
			ptr = ptr->parent;
		ptr = ptr->parent;
		if (!ptr)
		{
			ptr = old;
			while (ptr && ptr->right && !ptr->right->isLeaf)
				ptr = ptr->right;
			ptr = ptr->right;
		}
	}
	return ptr;
}


};//struct node

}//namespace ft

#endif
