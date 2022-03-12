# include "../../containers/map.hpp"
# include <map>


#ifndef NAMESPACE
# define NAMESPACE ft
#endif




int main()
{
	NAMESPACE::map<int, int> map;

	int max = 2000000;

	for (int i = -100; i < max; i++)
		map.insert(NAMESPACE::make_pair(i, i));

	for (int i = -100; i < max/3; i++)
		map.find(i);


	NAMESPACE::map<int, int> map_cpy;

	for (int i = -100; i < max; i++)
		map.erase(i);


	for (int i = 0; i < 300; i++)
		map.swap(map_cpy);

	return 0;
}
