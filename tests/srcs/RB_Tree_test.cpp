#include "../../utils/rb_tree/RBTree.hpp"
#include "../../utils/rb_tree/node.hpp"


void erase(ft::RBTree<int, int> &tree, int val)
{
	std::cout << "erase - " << val << std::endl;

	tree.erase(val);
}

void insert(ft::RBTree<int, int> &tree, int val)
{
	std::cout << "insert - " << val << std::endl;

	tree.insert(val);
}

void display(ft::RBTree<int, int> &tree)
{
	tree.display(); std::cout << "\n\n";
}


int main()
{
	ft::RBTree<int, int> tree;

	insert(tree, 31);
	insert(tree, 144);
	insert(tree, 16);
	display(tree);


	insert(tree, 11);
	insert(tree, 24);
	insert(tree, 22);
	display(tree);


	insert(tree, 19);
	insert(tree, 14);
	insert(tree, 61);
	insert(tree, 42);
	display(tree);



	insert(tree, 39);
	insert(tree, 32);
	insert(tree, 29);
	insert(tree, 10);
	insert(tree, 12);
	display(tree);

	erase(tree, 31);
	display(tree);

	erase(tree, 61);
	display(tree);


	erase(tree, 42);
	display(tree);

	return 0;


}
