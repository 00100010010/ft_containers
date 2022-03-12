# include "../../containers/map.hpp"
# include <map>
# include <iostream>
# include <cstdlib>
# include <list>

#ifndef NAMESPACE
# define NAMESPACE ft
#endif

////////////////////////////////////////////////////////////////////////////////
template <typename T>
std::string	printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
{
	o << "key: " << iterator->first << " | value: " << iterator->second;
	if (nl)
		o << std::endl;
	return ("");
}

template <typename T_MAP>
void	printSize(T_MAP const &mp, bool print_content = 1)
{
	std::cout << "size: " << mp.size() << std::endl;
	std::cout << "max_size: " << mp.max_size() << std::endl;
	if (print_content)
	{
		typename T_MAP::const_iterator it = mp.begin(), ite = mp.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << printPair(it, false) << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}

struct ft_more {
	bool	operator()(const int &first, const int &second) const {
		return (first > second);
	}
};
////////////////////////////////////////////////////////////////////////////////

void constructor()
{
	// (1) Default constructor
        NAMESPACE::map<std::string, int> map1;
        map1["something"] = 69;
        map1["anything"] = 199;
        map1["that thing"] = 50;
        std::cout << "map1 = "; printSize(map1);

	// with comp
	NAMESPACE::map<int, std::string, ft_more> map_cmp;
	map_cmp[42] = "fgzgxfn";
	map_cmp[25] = "funny";
	map_cmp[80] = "hey";
	map_cmp[12] = "no";
	map_cmp[27] = "bee";
	map_cmp[90] = "8";
	printSize(map_cmp);


	std::cout << (map_cmp[42] < map_cmp[90]) << std::endl;

        // (2) Range constructor
        NAMESPACE::map<std::string, int> iter(map1.find("anything"), map1.end());
        std::cout << "\niter = "; printSize(iter);
        std::cout << "map1 = "; printSize(map1);

        // (3) Copy constructor
        NAMESPACE::map<std::string, int> copied(map1);
        std::cout << "\ncopied = "; printSize(copied);
        std::cout << "map1 = "; printSize(map1);
}

void operator_equal() // operator =
{
	NAMESPACE::map<char,int> first;
	NAMESPACE::map<char,int> second;

	first['x']=8;
	first['y']=16;
	first['z']=32;

	second=first;                // second now contains 3 ints
	first=NAMESPACE::map<char,int>();  // and first is now empty

	std::cout << "Size of first: " << first.size() << '\n';
	std::cout << "Size of second: " << second.size() << '\n';
}

void begin()
{
	NAMESPACE::map<char,int> mymap;

	mymap['b'] = 100;
	mymap['a'] = 200;
	mymap['c'] = 300;

	// show content:
	for (NAMESPACE::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
}

void end()
{
	NAMESPACE::map<char,int> mymap;

	mymap['b'] = 100;
	mymap['a'] = 200;
	mymap['c'] = 300;

	// show content:
	for (NAMESPACE::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
}

void rbegin()
{
	NAMESPACE::map<char,int> mymap;

	mymap['x'] = 100;
	mymap['y'] = 200;
	mymap['z'] = 300;

	// show content:
	NAMESPACE::map<char,int>::reverse_iterator rit;
	for (rit=mymap.rbegin(); rit!=mymap.rend(); ++rit)
		std::cout << rit->first << " => " << rit->second << '\n';
}

void rend()
{
	NAMESPACE::map<char,int> mymap;

	mymap['x'] = 100;
	mymap['y'] = 200;
	mymap['z'] = 300;

	// show content:
	NAMESPACE::map<char,int>::reverse_iterator rit;
	for (rit=mymap.rbegin(); rit!=mymap.rend(); ++rit)
		std::cout << rit->first << " => " << rit->second << '\n';
}


void empty()
{
	NAMESPACE::map<char,int> mymap;

	mymap['a']=10;
	mymap['b']=20;
	mymap['c']=30;

	while (!mymap.empty())
	{
		std::cout << mymap.begin()->first << " => " << mymap.begin()->second << '\n';
		mymap.erase(mymap.begin());
	}
}

void size()
{
	NAMESPACE::map<char,int> mymap;
	mymap['a']=101;
	mymap['b']=202;
	mymap['c']=302;

	std::cout << "mymap.size() is " << mymap.size() << '\n';
}

void max_size()
{
	int i;
	NAMESPACE::map<int,int> mymap;

	if (mymap.max_size()>1000)
	{
		for (i=0; i<1000; i++) mymap[i]=0;
		std::cout << "The map contains 1000 elements.\n";
	}
	else std::cout << "The map could not hold 1000 elements.\n";
}

void operator_hook() // operator []
{
	NAMESPACE::map<char,std::string> mymap;

	mymap['a']="an element";
	mymap['b']="another element";
	mymap['c']=mymap['b'];

	std::cout << "mymap['a'] is " << mymap['a'] << '\n';
	std::cout << "mymap['b'] is " << mymap['b'] << '\n';
	std::cout << "mymap['c'] is " << mymap['c'] << '\n';
	std::cout << "mymap['d'] is " << mymap['d'] << '\n';

	std::cout << "mymap now contains " << mymap.size() << " elements.\n";
}

void at()
{
	NAMESPACE::map<int, int> mp;
	for (int i = 0; i < 10; i++)
		mp[i] = i * 3;

	for (int i = 0; i < 10; i++)
		std::cout << mp.at(i) << std::endl;

	try
	{
		mp.at(mp.size() + 1);
	}
	catch(std::out_of_range &le)
	{
		std::cout << "out of range : "  << le.what() << std::endl;
	}

	catch(std::exception &e)
	{
		std::cout << "error : " << e.what() << std::endl;
	}
}


void insert()
{
	NAMESPACE::map<char,int> mymap;

	// first insert function version (single parameter):
	mymap.insert ( NAMESPACE::pair<char,int>('b',100) );
	mymap.insert ( NAMESPACE::pair<char,int>('z',200) );

	NAMESPACE::pair<NAMESPACE::map<char,int>::iterator,bool> ret;
	ret = mymap.insert ( NAMESPACE::pair<char,int>('z',500) );
	if (ret.second==false) {
		std::cout << "element 'z' already existed";
		std::cout << " with a value of " << ret.first->second << '\n';
	}

	// second insert function version (with hint position):
	NAMESPACE::map<char,int>::iterator it = mymap.begin();
	mymap.insert (it, NAMESPACE::pair<char,int>('c',300));
	mymap.insert (it, NAMESPACE::pair<char,int>('d',400));

	// third insert function version (range insertion):
	NAMESPACE::map<char,int> anothermap;
	anothermap.insert(mymap.begin(),mymap.find('c'));

	// showing contents:
	std::cout << "mymap contains:\n";
	for (it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	std::cout << "anothermap contains:\n";
	for (it=anothermap.begin(); it!=anothermap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
}
void iterator_validity()
{
	NAMESPACE::map<char,int> mymap;
	mymap.insert ( NAMESPACE::pair<char,int>('b',100) );
	mymap.insert ( NAMESPACE::pair<char,int>('c', 50) );
	mymap.insert ( NAMESPACE::pair<char,int>('d', 510) );

	NAMESPACE::map<char,int>::iterator it1 = ++(mymap.begin());
	NAMESPACE::map<char,int>::iterator it2 = ++(++(mymap.begin()));

	mymap.insert (NAMESPACE::pair<char,int>('z',300));

	NAMESPACE::map<char,int>::iterator it11 = ++(mymap.begin());
	NAMESPACE::map<char,int>::iterator it22 = ++(++(mymap.begin()));

	if (it1 == it11 && it2 == it22)
		std::cout << "it insert validity OK" << std::endl;

	mymap.erase ('z');

	it11 = ++(mymap.begin());
	it22 = ++(++(mymap.begin()));

	if (it1 == it11 && it2 == it22)
		std::cout << "it erase validity OK" << std::endl;
}

void erase()
{
	NAMESPACE::map<char,int> mymap;
	NAMESPACE::map<char,int>::iterator it;

	// insert some values:
	mymap['a']=10;
	mymap['b']=20;
	mymap['c']=30;
	mymap['d']=40;
	mymap['e']=50;
	mymap['f']=60;

	it=mymap.find('b');
	mymap.erase (it);                   // erasing by iterator

	mymap.erase ('c');                  // erasing by key

	it=mymap.find ('e');
	mymap.erase ( it, mymap.end() );    // erasing by range

	// show content:
	for (it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
}

void swap()
{
	NAMESPACE::map<char,int> foo,bar;

	foo['x']=100;
	foo['y']=200;

	bar['a']=11;
	bar['b']=22;
	bar['c']=33;

	NAMESPACE::map<char,int>::iterator it_foo = foo.begin();
	NAMESPACE::map<char,int>::iterator it_bar = bar.begin();

	foo.swap(bar);


	if (foo.begin() == it_bar)
		std::cout << "IT_BAR OK" << std::endl;
	if (bar.begin() == it_foo)
		std::cout << "IT_FOO OK" << std::endl;

	std::cout << "foo contains:\n";
	for (NAMESPACE::map<char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	std::cout << "bar contains:\n";
	for (NAMESPACE::map<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
}

void clear()
{
	NAMESPACE::map<char,int> mymap;

	mymap['x']=100;
	mymap['y']=200;
	mymap['z']=300;

	std::cout << "mymap contains:\n";
	for (NAMESPACE::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	mymap.clear();
	mymap['a']=1101;
	mymap['b']=2202;

	std::cout << "mymap contains:\n";
	for (NAMESPACE::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
}


void key_comp()
{
	NAMESPACE::map<char,int> mymap;

	NAMESPACE::map<char,int>::key_compare mycomp = mymap.key_comp();

	mymap['a']=100;
	mymap['b']=200;
	mymap['c']=300;

	std::cout << "mymap contains:\n";

	char highest = mymap.rbegin()->first;     // key value of last element

	NAMESPACE::map<char,int>::iterator it = mymap.begin();
	do {
		std::cout << it->first << " => " << it->second << '\n';
	} while ( mycomp((*it++).first, highest) );

	std::cout << '\n';
}

void value_comp()
{
	NAMESPACE::map<char,int> mymap;

	mymap['x']=1001;
	mymap['y']=2002;
	mymap['z']=3003;

	std::cout << "mymap contains:\n";

	NAMESPACE::pair<char,int> highest = *mymap.rbegin();          // last element

	NAMESPACE::map<char,int>::iterator it = mymap.begin();
	do {
		std::cout << it->first << " => " << it->second << '\n';
	} while ( mymap.value_comp()(*it++, highest) );
}


void find()
{
	NAMESPACE::map<char,int> mymap;
	NAMESPACE::map<char,int>::iterator it;

	mymap['a']=50;
	mymap['b']=100;
	mymap['c']=150;
	mymap['d']=200;

	it = mymap.find('b');
	if (it != mymap.end())
		mymap.erase (it);

	// print content:
	std::cout << "elements in mymap:" << '\n';
	std::cout << "a => " << mymap.find('a')->second << '\n';
	std::cout << "c => " << mymap.find('c')->second << '\n';
	std::cout << "d => " << mymap.find('d')->second << '\n';
}

void count()
{
	NAMESPACE::map<char,int> mymap;
	char c;

	mymap ['a']=101;
	mymap ['c']=202;
	mymap ['f']=303;

	for (c='a'; c<'h'; c++)
	{
		std::cout << c;
		if (mymap.count(c)>0)
			std::cout << " is an element of mymap.\n";
		else
			std::cout << " is not an element of mymap.\n";
	}
}

void lower_bound()
{
	NAMESPACE::map<char,int> mymap;
	NAMESPACE::map<char,int>::iterator itlow,itup;

	mymap['a']=20;
	mymap['b']=40;
	mymap['c']=60;
	mymap['d']=80;
	mymap['e']=100;

	itlow=mymap.lower_bound ('b');  // itlow points to b
	itup=mymap.upper_bound ('d');   // itup points to e (not d!)

	mymap.erase(itlow,itup);        // erases [itlow,itup)

	// print content:
	for (NAMESPACE::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
}

void upper_bound()
{
	NAMESPACE::map<char,int> mymap;
	NAMESPACE::map<char,int>::iterator itlow,itup;

	mymap['a']=20;
	mymap['b']=40;
	mymap['c']=60;
	mymap['d']=80;
	mymap['e']=100;

	itlow=mymap.lower_bound ('b');  // itlow points to b
	itup=mymap.upper_bound ('d');   // itup points to e (not d!)

	mymap.erase(itlow,itup);        // erases [itlow,itup)

	// print content:
	for (NAMESPACE::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
}

void equal_range()
{
	NAMESPACE::map<char,int> mymap;

	mymap['a']=10;
	mymap['b']=20;
	mymap['c']=30;

	NAMESPACE::pair<NAMESPACE::map<char,int>::iterator,NAMESPACE::map<char,int>::iterator> ret;
	ret = mymap.equal_range('b');

	std::cout << "lower bound points to: ";
	std::cout << ret.first->first << " => " << ret.first->second << '\n';

	std::cout << "upper bound points to: ";
	std::cout << ret.second->first << " => " << ret.second->second << '\n';
}


void get_allocator()
{
	int psize;
	NAMESPACE::map<char,int> mymap;
	NAMESPACE::pair<const char,int>* p;

	// allocate an array of 5 elements using mymap's allocator:
	p=mymap.get_allocator().allocate(5);

	// assign some values to array
	psize = sizeof(NAMESPACE::map<char,int>::value_type)*5;

	std::cout << "The allocated array has a size of " << psize << " bytes.\n";

	mymap.get_allocator().deallocate(p,5);
}

template <class MAP>
void	cmp(const MAP &lhs, const MAP &rhs)
{
	static int i = 0;

	std::cout << "############### [" << i++ << "] ###############"  << std::endl;
	std::cout << "eq: " << (lhs == rhs) << " | ne: " << (lhs != rhs) << std::endl;
	std::cout << "lt: " << (lhs <  rhs) << " | le: " << (lhs <= rhs) << std::endl;
	std::cout << "gt: " << (lhs >  rhs) << " | ge: " << (lhs >= rhs) << std::endl;
}

void relationnal_ope()
{

	NAMESPACE::map<char, int> mp1;
	NAMESPACE::map<char, int> mp2;

	mp1['a'] = 2; mp1['b'] = 3; mp1['c'] = 4; mp1['d'] = 5;
	mp2['a'] = 2; mp2['b'] = 3; mp2['c'] = 4; mp2['d'] = 5;

	cmp(mp1, mp1); // 0
	cmp(mp1, mp2); // 1

	mp2['e'] = 6; mp2['f'] = 7; mp2['h'] = 8; mp2['h'] = 9;

	cmp(mp1, mp2); // 2
	cmp(mp2, mp1); // 3

	(++(++mp1.begin()))->second = 42;

	cmp(mp1, mp2); // 4
	cmp(mp2, mp1); // 5

	swap(mp1, mp2);

	cmp(mp1, mp2); // 6
	cmp(mp2, mp1); // 7
}

void swap_non_member()
{
	NAMESPACE::map<char,int> foo,bar;

	foo['x']=100;
	foo['y']=200;

	bar['a']=11;
	bar['b']=22;
	bar['c']=33;

	swap(bar, foo);

	std::cout << "foo contains:\n";
	for (NAMESPACE::map<char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	std::cout << "bar contains:\n";
	for (NAMESPACE::map<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

}



int main()
{
	constructor();
	operator_equal(); // operator =

	begin();
	end();
	rbegin();
	rend();

	empty();
	size();
	max_size();

	operator_hook(); // operator []
	at();

	insert();
	erase();
	swap();
	clear();

	key_comp();
	value_comp();

	find();
	count();
	lower_bound();
	upper_bound();
	equal_range();

	get_allocator();

	relationnal_ope();
	swap_non_member();

	iterator_validity();

}
