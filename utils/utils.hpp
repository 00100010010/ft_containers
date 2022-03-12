#ifndef UTILS_HPP
# define UTILS_HPP

# include <iostream>

namespace ft
{

template <typename InputIt>
size_t distance(InputIt first, InputIt last)
{
	size_t i = 0;
	while (first != last)
	{
		first++;
		i++;
	}
	return i;
}

template < typename T >
void swap_elem(T& a, T& b)
{
	T tmp = a;
	a = b;
	b = tmp;
}

template <class InputIterator1, class InputIterator2>
bool equal (	InputIterator1 lit, InputIterator1 lend,
		InputIterator2 rit, InputIterator2 rend )
{
	while (lit != lend)
	{
		if (rit == rend || *rit != *lit)
			return (false);
		++lit, ++rit;
	}
	return (rit == rend);
}

template <class InputIt1, class InputIt2>
bool lexicographical_compare(	InputIt1 first1, InputIt1 last1,
				InputIt2 first2, InputIt2 last2 )
{
	for ( ; (first1 != last1) && (first2 != last2); ++first1, ++first2 )
	{
		if (*first1 < *first2)
			return true;
		if (*first2 < *first1)
			return false;
	}
	return (first1 == last1) && (first2 != last2);
}

}// namespace ft
#endif
