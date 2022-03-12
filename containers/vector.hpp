#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <sstream>

#include "../utils/iterators/vector_iterator.hpp"
#include "../utils/is_integral.hpp"
#include "../utils/enable_if.hpp"
#include "../utils/utils.hpp"

#define RESERVE_NBR 2
#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

#ifdef	__linux__
#	define LINUX 1
#else
#	define LINUX 0
#endif

namespace ft
{

template <typename T, typename Allocator = std::allocator<T> >
class vector
{

public:

typedef T					value_type;
typedef Allocator				allocator_type;
typedef value_type &				reference;
typedef const value_type &			const_reference;
typedef typename Allocator::pointer		pointer;
typedef typename Allocator::const_pointer	const_pointer;
typedef vector_iterator<value_type>		iterator;
typedef const_vector_iterator<value_type>	const_iterator;
typedef reverse_iterator<const_iterator>	const_reverse_iterator;
typedef reverse_iterator<iterator>		reverse_iterator;
typedef ptrdiff_t				difference_type;
typedef size_t					size_type;

private:

pointer						_vector;
size_type					_size;
size_type					_capacity;
allocator_type					_alloc;

private:

int	_control_reserve (size_t n, const T& val)
{
	if (capacity() == 0)
	{
		_reserve_for_insert(n, n + size(), val);
	}
	else if ((size() + n) > (capacity() * RESERVE_NBR))
	{
		_reserve_for_insert(size() + n, n + size(), val);
	}
	else if (size() + n > capacity())
	{
		if (size() * RESERVE_NBR >= n + size() && LINUX)
			_reserve_for_insert(size() * RESERVE_NBR, n + size(), val);
		else
			_reserve_for_insert(capacity() * RESERVE_NBR, n + size(), val);
	}
	else if (n)
	{
		_construct_elem(0, n, val, _vector + size());
		return 1;
	}
	return 0;
}

void	_reserve_for_insert ( size_type n , size_type n2, const T& val = T())
{
	if (n > max_size())
	{
		if (LINUX)
			throw std::length_error("vector::reserve");
		else
			throw std::length_error("allocator<T>::allocate(size_t n)\
			 'n' exceeds maximum supported size");
	}
	pointer tmp = NULL;
	tmp = _alloc_and_construct(tmp, n, 0, n2, val);
	_add_values(tmp, _vector, size());
	_destroy_and_dealloc(0, size(), capacity());
	_vector    = tmp;
	_capacity  = n;
}

void _move_memory (size_type start, size_type end, size_type step,
						bool reverse = false)
{
	if (reverse == false)
	{
		for (size_type z = start + step - 1; z != end + step - 1; z--)
			_vector[z] = _vector[z - step];
	}
	else
	{
		for (size_type i = start; i != end - step; i++)
			_vector[i] = _vector[i + step];
	}
}

void _add_values (pointer dst, pointer src, size_type len)
{
	for (size_type i = 0; i < len; i++)
		dst[i] = src[i];
}

void _add_values (pointer dst, const value_type& val, size_type len,
					bool size_modifier = false)
{
	for (size_type i = 0; i < len; i++)
	{
		dst[i] = val;
		if (size_modifier == true)
			_size++;
	}
}

template <class InputIt>
void _add_values (pointer dst, typename ft::enable_if<!ft::is_integral<InputIt>::value,
		InputIt>::type first, InputIt last, bool size_modifier = false)
{
	size_type i = 0;
	for (InputIt it = first; it != last; it++)
	{
		dst[i++] = *it;
		if (size_modifier == true)
			_size++;
	}
}

pointer _alloc_and_construct (pointer ptr, size_type alloc_size, size_type start,
			size_type end, const T& val, bool capacity_modif = false)
{
	ptr = _alloc.allocate(alloc_size);
	if (capacity_modif == true)
		_capacity  = alloc_size;
	_construct_elem(start, end, val, ptr);
	return ptr;
}

void _construct_elem (size_type start, size_type end, const T& val, pointer ptr)
{
	for (size_type i = start; i < end; i++)
		_alloc.construct(ptr + i, val);
}

void _destroy_elements (size_type start, size_type end, bool size_modifier = false)
{
	for (size_type i = start; i < end; i++)
	{
		_alloc.destroy(_vector + i);
		if (size_modifier == true)
			_size--;
	}
}

void _destroy_and_dealloc (size_type start, size_type end, size_type deall_size)
{
	_destroy_elements(start, end);
	_alloc.deallocate(_vector, deall_size);
}

public:

explicit vector ( const Allocator& alloc = allocator_type() )
	: _vector(NULL), _size(0), _capacity(0), _alloc(alloc)
{}

explicit vector ( size_type count, 	const T& val = T(),
					const Allocator& alloc = Allocator())
	: _vector(NULL), _size(0), _capacity(0), _alloc(alloc)
{
	assign(count, val);
}

template <class InputIt>
vector ( typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type
	first, InputIt last, const Allocator& alloc = Allocator())
	: _vector(NULL), _size(0), _capacity(0), _alloc(alloc)
{
	assign(first, last);
}

vector ( const vector& other)
	: _vector(NULL), _size(0), _capacity(0), _alloc(other.get_allocator())
{
	assign(other.begin(), other.end());
}

virtual ~vector ()
{
	_destroy_and_dealloc(0, size(), capacity());
}

vector&	operator = ( const vector& other )
{
	if (*this == other)
		return *this;

	if (other.size() < size())
		resize(other.size());

	assign(other.begin(), other.end());

	return *this;
}

void	assign ( size_type n, const T& val )
{
	if (n > capacity())
	{
		_destroy_and_dealloc(0, size(), capacity());
		_vector = _alloc_and_construct(_vector, n, 0, n, val, true);
	}
	else
	{
		_destroy_elements(n, size());
		_construct_elem(size(), n, val, _vector);
	}
	_size = 0;
	_add_values(_vector, val, n, true);
}

template <class InputIt>
void	assign ( typename ft::enable_if<!ft::is_integral<InputIt>::value,
					InputIt>::type first, InputIt last )
{
	size_t n = ft::distance(first, last);

	if (n > capacity())
	{
		pointer tmp = NULL;
		tmp = _alloc_and_construct(tmp, n, 0, n, *first);
		_destroy_and_dealloc(0, size(), capacity());
		_vector 	= tmp;
		_capacity 	= n;
	}
	else
	{
		_destroy_elements (n, size());
		_construct_elem	  (size(), n, *first, _vector);
	}
	_size = 0;
	_add_values(_vector, first, last, true);
}

reference	at ( size_type n )
{
	if (n >= size())
		throw std::out_of_range( SSTR( "vector::_M_range_check: __n \
		(which is " << n << ") >= this->size() (which is " << size() << ")" ));
	return _vector[n];
}

const_reference	at ( size_type n ) const
{
	if (n >= size())
		throw std::out_of_range( SSTR( "vector::_M_range_check: __n \
		(which is " << n << ") >= this->size() (which is " << size() << ")" ));
	return _vector[n];
}

allocator_type	       get_allocator ()		   const { return _alloc; }

reference	       operator [] ( size_type n )	 { return _vector[n]; }
const_reference        operator [] ( size_type n ) const { return _vector[n]; }

reference              front   ()       { return *_vector; }
const_reference        front   () const { return *_vector; }
reference              back    ()       { return *(_vector + size() - 1); }
const_reference        back    () const { return *(_vector + size() - 1); }
T*                     data    ()       { return _vector; };
const T*               data    () const { return _vector; };

iterator               begin   ()       { return iterator              ( _vector); }
const_iterator         begin   () const { return const_iterator        ( _vector); }
iterator               end     ()       { return iterator              ( _vector + size()); }
const_iterator         end     () const { return const_iterator        ( _vector + size()); }
reverse_iterator       rbegin  ()       { return reverse_iterator      ( end()); }
const_reverse_iterator rbegin  () const { return const_reverse_iterator( end()); }
reverse_iterator       rend    ()       { return reverse_iterator      ( begin()); }
const_reverse_iterator rend    () const { return const_reverse_iterator( begin()); }

bool                   empty   () const { return size() == 0; }
size_type              size    () const { return _size; }
size_type              max_size() const { return _alloc.max_size(); }
size_type              capacity() const { return _capacity; }

void	reserve ( size_type n )
{
	if (n <= capacity())
		return ;
	if (n > max_size())
	{
		if (LINUX)
			throw std::length_error("vector::reserve");
		else
			throw std::length_error("allocator<T>::allocate(size_t n)\
			 'n' exceeds maximum supported size");
	}
	pointer tmp = NULL;
	tmp = _alloc_and_construct(tmp, n, 0, size(), *_vector);
	_add_values(tmp, _vector, size());
	_destroy_and_dealloc(0, size(), capacity());
	_vector		= tmp;
	_capacity	= n;
}

void	resize ( size_type n, T value = T() )
{
	if (n < size())
		_destroy_elements(n, size(), true);
	if (n > size())
		insert(end(), n - size(), value);
}

void	push_back     ( const value_type& val ) { insert(end(), val); }

void 	pop_back()
{
	if (size())
		_destroy_elements(size() - 1, size(), true);
}

iterator	insert ( iterator pos, const T& value )
{
	size_type target_index = pos - begin();

	_control_reserve(1, value);

	_move_memory(size(), target_index, 1);
	_add_values (_vector + target_index, value, 1, true);

	return iterator(begin() + target_index);
}

void		insert ( iterator pos, size_type count, const value_type& value )
{
	size_type target_index = pos - begin();

	if (_control_reserve(count, value))
	{
		_alloc.construct(_vector + size(), *_vector);
		_alloc.destroy	(_vector + size());
	}
	_move_memory(size(), target_index, count);
	_add_values (_vector + target_index, value, count, true);
}

template <class InputIt>
void		insert ( iterator pos,
			typename ft::enable_if<!ft::is_integral<InputIt>::value,
			InputIt>::type first, InputIt last )
{
	size_type target_index	= pos - begin();
	size_type count		= ft::distance(first, last);

	_control_reserve(count, *first);
	_move_memory	(size(), target_index, count);
	_add_values	(_vector + target_index, first, last, true);
}

iterator	erase ( iterator pos )
{
	return erase(pos, pos + 1);
}

iterator	erase ( iterator first, iterator last )
{
	size_type target_index1	= first - begin();
	size_type count		= (last  - begin()) - target_index1;

	_move_memory	 (target_index1, size(), count, true);
	_destroy_elements(size() - count, size(), true);

	return first;
}

void		swap ( vector& other )
{
	swap_elem(_vector,   other._vector);
	swap_elem(_capacity, other._capacity);
	swap_elem(_size,     other._size);
	swap_elem(_alloc,    other._alloc);
}

void		clear ()
{
	_destroy_elements(0, size(), true);
}

};//class vector

template < class T, class Alloc >
bool operator == ( const vector<T, Alloc>& l, const vector<T, Alloc>& r )
{
	return 	l.size() == r.size() && ft::equal(l.begin(), l.end(), r.begin(), r.end());
}
template < class T, class Alloc >
bool operator != ( const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs )
{
	return !(lhs == rhs);
}
template < class T, class Alloc >
bool operator <  ( const vector<T, Alloc>& l, const vector<T, Alloc>& r )
{
	return ft::lexicographical_compare(l.begin(), l.end(), r.begin(), r.end());
}
template < class T, class Alloc >
bool operator <= ( const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs )
{
	return !(lhs > rhs);
}
template < class T, class Alloc >
bool operator >  ( const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs )
{
	return (rhs < lhs);
}
template < class T, class Alloc >
bool operator >= ( const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs )
{
	return !(lhs < rhs);
}
template < class T, class Alloc >
void swap 	 ( vector<T, Alloc>& lhs, vector<T, Alloc>& rhs )
{
	lhs.swap(rhs);
}

}//namespace ft
#endif
