# include "../../containers/vector.hpp"
# include <vector>

#ifndef NAMESPACE
# define NAMESPACE ft
#endif




int main()
{
	NAMESPACE::vector<int> vct;

	int max = 40000000;

	for (int i = 0; i < max; i++)
		vct.insert(vct.end(), 2, i);


	vct.erase(vct.begin(), vct.end());

	return 0;
}
