# include "../../containers/set.hpp"
# include <set>
# include <iostream>
# include <cstdlib>
# include <list>

#ifndef NAMESPACE
# define NAMESPACE ft
#endif

template <typename SET>
void	printSize(SET const &mp, bool print_content = 1)
{
	std::cout << "size: " << mp.size() << std::endl;
	std::cout << "max_size: " << mp.max_size() << std::endl;
	if (print_content)
	{
		typename SET::const_iterator it = mp.begin(), ite = mp.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << *it << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}


struct ft_more {
	bool	operator()(const int &first, const int &second) const {
		return (first > second);
	}
};

void constructor()
{
	// (1) Default constructor
        NAMESPACE::set<int> map1;
	map1.insert(13);
	map1.insert(25);
	map1.insert(36);
	map1.insert(18);
        std::cout << "map1 = "; printSize(map1);


	// with comp
	NAMESPACE::set<int, ft_more> map_cmp;
	map_cmp.insert(3);
	map_cmp.insert(5);
	map_cmp.insert(6);
	map_cmp.insert(8);

	printSize(map_cmp);



        // (2) Range constructor
        NAMESPACE::set<int> iter(map1.find(13), map1.end());
        std::cout << "\niter = "; printSize(iter);
        std::cout << "map1 = "; printSize(map1);

        // (3) Copy constructor
        NAMESPACE::set<int> copied(map1);
        std::cout << "\ncopied = "; printSize(copied);
        std::cout << "map1 = "; printSize(map1);
}

void operator_equal() // operator =
{
	int myints[]={ 12,82,37,64,15 };
	NAMESPACE::set<int> first (myints,myints+5);   // set with 5 ints
	NAMESPACE::set<int> second;                    // empty set

	second = first;                          // now second contains the 5 ints
	first = NAMESPACE::set<int>();                 // and first is empty

	std::cout << "Size of first: " << int (first.size()) << '\n';
	std::cout << "Size of second: " << int (second.size()) << '\n';
}


void begin()
{
	int myints[] = {75,23,65,42,13};
	NAMESPACE::set<int> myset (myints,myints+5);

	std::cout << "myset contains:";
	for (NAMESPACE::set<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
		std::cout << ' ' << *it;

	std::cout << '\n';
}

void end()
{
	int myints[] = {75,23,65,42,13};
	NAMESPACE::set<int> myset (myints,myints+5);

	std::cout << "myset contains:";
	for (NAMESPACE::set<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
		std::cout << ' ' << *it;

	std::cout << '\n';
}

void rbegin()
{
	int myints[] = {21,64,17,78,49};
	NAMESPACE::set<int> myset (myints,myints+5);

	NAMESPACE::set<int>::reverse_iterator rit;

	std::cout << "myset contains:";
	for (rit=myset.rbegin(); rit != myset.rend(); ++rit)
		std::cout << ' ' << *rit;

	std::cout << '\n';
}

void rend()
{
	int myints[] = {21,64,17,78,49};
	NAMESPACE::set<int> myset (myints,myints+5);

	NAMESPACE::set<int>::reverse_iterator rit;

	std::cout << "myset contains:";
	for (rit=myset.rbegin(); rit != myset.rend(); ++rit)
		std::cout << ' ' << *rit;

	std::cout << '\n';
}


void empty()
{
	NAMESPACE::set<int> myset;

	myset.insert(20);
	myset.insert(30);
	myset.insert(10);

	std::cout << "myset contains:";
	while (!myset.empty())
	{
		std::cout << ' ' << *myset.begin();
		myset.erase(myset.begin());
	}
	std::cout << '\n';
}

void size()
{
	NAMESPACE::set<int> myints;
	std::cout << "0. size: " << myints.size() << '\n';

	for (int i=0; i<10; ++i) myints.insert(i);
	std::cout << "1. size: " << myints.size() << '\n';

	myints.insert (100);
	std::cout << "2. size: " << myints.size() << '\n';

	myints.erase(5);
	std::cout << "3. size: " << myints.size() << '\n';
}

void max_size()
{
	int i;
	NAMESPACE::set<int> myset;

	if (myset.max_size()>1000)
	{
		for (i=0; i<1000; i++) myset.insert(i);
		std::cout << "The set contains 1000 elements.\n";
	}
	else std::cout << "The set could not hold 1000 elements.\n";
}


void insert()
{
	NAMESPACE::set<int> myset;
	NAMESPACE::set<int>::iterator it;
	NAMESPACE::pair<NAMESPACE::set<int>::iterator,bool> ret;

	// set some initial values:
	for (int i=1; i<=5; ++i) myset.insert(i*10);    // set: 10 20 30 40 50

	ret = myset.insert(20);               // no new element inserted

	if (ret.second==false) it=ret.first;  // "it" now points to element 20

	myset.insert (it,25);                 // max efficiency inserting
	myset.insert (it,24);                 // max efficiency inserting
	myset.insert (it,26);                 // no max efficiency inserting

	int myints[]= {5,10,15};              // 10 already in set, not inserted
	myset.insert (myints,myints+3);

	std::cout << "myset contains:";
	for (it=myset.begin(); it!=myset.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

void erase()
{
	NAMESPACE::set<int> myset;
	NAMESPACE::set<int>::iterator it;

	// insert some values:
	for (int i=1; i<10; i++) myset.insert(i*10);  // 10 20 30 40 50 60 70 80 90

	it = myset.begin();
	++it;                                         // "it" points now to 20

	myset.erase (it);

	myset.erase (40);

	it = myset.find (60);
	myset.erase (it, myset.end());

	std::cout << "myset contains:";
	for (it=myset.begin(); it!=myset.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

void swap()
{
	int myints[]={12,75,10,32,20,25};
	NAMESPACE::set<int> first (myints,myints+3);     // 10,12,75
	NAMESPACE::set<int> second (myints+3,myints+6);  // 20,25,32

	first.swap(second);

	std::cout << "first contains:";
	for (NAMESPACE::set<int>::iterator it=first.begin(); it!=first.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << "second contains:";
	for (NAMESPACE::set<int>::iterator it=second.begin(); it!=second.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

void clear()
{
	NAMESPACE::set<int> myset;

	myset.insert (100);
	myset.insert (200);
	myset.insert (300);

	std::cout << "myset contains:";
	for (NAMESPACE::set<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	myset.clear();
	myset.insert (1101);
	myset.insert (2202);

	std::cout << "myset contains:";
	for (NAMESPACE::set<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}


void key_comp()
{
	NAMESPACE::set<int> myset;
	int highest;

	NAMESPACE::set<int>::key_compare mycomp = myset.key_comp();

	for (int i=0; i<=5; i++) myset.insert(i);

	std::cout << "myset contains:";

	highest=*myset.rbegin();
	NAMESPACE::set<int>::iterator it=myset.begin();
	do {
		std::cout << ' ' << *it;
	} while ( mycomp(*(++it),highest) );

	std::cout << '\n';
}

void value_comp()
{
	NAMESPACE::set<int> myset;

	NAMESPACE::set<int>::value_compare mycomp = myset.value_comp();

	for (int i=0; i<=5; i++) myset.insert(i);

	std::cout << "myset contains:";

	int highest=*myset.rbegin();
	NAMESPACE::set<int>::iterator it=myset.begin();
	do {
		std::cout << ' ' << *it;
	} while ( mycomp(*(++it),highest) );

	std::cout << '\n';
}


void find()
{
	NAMESPACE::set<int> myset;
	NAMESPACE::set<int>::iterator it;

	// set some initial values:
	for (int i=1; i<=5; i++) myset.insert(i*10);    // set: 10 20 30 40 50

	it=myset.find(20);
	myset.erase (it);
	myset.erase (myset.find(40));

	std::cout << "myset contains:";
	for (it=myset.begin(); it!=myset.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

void count()
{
	NAMESPACE::set<int> myset;

	// set some initial values:
	for (int i=1; i<5; ++i) myset.insert(i*3);    // set: 3 6 9 12

	for (int i=0; i<10; ++i)
	{
		std::cout << i;
		if (myset.count(i)!=0)
			std::cout << " is an element of myset.\n";
		else
			std::cout << " is not an element of myset.\n";
	}
}

void lower_bound()
{
	NAMESPACE::set<int> myset;
	NAMESPACE::set<int>::iterator itlow,itup;

	for (int i=1; i<10; i++) myset.insert(i*10); // 10 20 30 40 50 60 70 80 90

	itlow=myset.lower_bound (30);                //       ^
	itup=myset.upper_bound (60);                 //                   ^

	myset.erase(itlow,itup);                     // 10 20 70 80 90

	std::cout << "myset contains:";
	for (NAMESPACE::set<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

void upper_bound()
{
	NAMESPACE::set<int> myset;
	NAMESPACE::set<int>::iterator itlow,itup;

	for (int i=1; i<10; i++) myset.insert(i*10); // 10 20 30 40 50 60 70 80 90

	itlow=myset.lower_bound (30);                //       ^
	itup=myset.upper_bound (60);                 //                   ^

	myset.erase(itlow,itup);                     // 10 20 70 80 90

	std::cout << "myset contains:";
	for (NAMESPACE::set<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

void equal_range()
{
	NAMESPACE::set<int> myset;

	for (int i=1; i<=5; i++) myset.insert(i*10);   // myset: 10 20 30 40 50

	NAMESPACE::pair<NAMESPACE::set<int>::const_iterator,NAMESPACE::set<int>::const_iterator> ret;
	ret = myset.equal_range(30);

	std::cout << "the lower bound points to: " << *ret.first << '\n';
	std::cout << "the upper bound points to: " << *ret.second << '\n';
}


void get_allocator()
{
	NAMESPACE::set<int> myset;
        int * p;
        unsigned int i;

        // allocate an array of 5 elements using myset's allocator:
        p=myset.get_allocator().allocate(5);

        // assign some values to array
        for (i=0; i<5; i++) p[i]=(i+1)*10;

        std::cout << "The allocated array contains:";
        for (i=0; i<5; i++) std::cout << ' ' << p[i];
        std::cout << '\n';

        myset.get_allocator().deallocate(p,5);
}



void relationnal_ope()
{
	NAMESPACE::set<int> alice;
	alice.insert(1);
	alice.insert(2);
	alice.insert(3);

        NAMESPACE::set<int> bob;
	bob.insert(7);
	bob.insert(8);
	bob.insert(9);
	bob.insert(10);

        NAMESPACE::set<int> eve;
	eve.insert(1);
	eve.insert(2);
	eve.insert(3);

        std::cout << std::boolalpha;

        // Compare non equal containers
        std::cout << "alice == bob returns " << (alice == bob) << '\n';
        std::cout << "alice != bob returns " << (alice != bob) << '\n';
        std::cout << "alice <  bob returns " << (alice < bob) << '\n';
        std::cout << "alice <= bob returns " << (alice <= bob) << '\n';
        std::cout << "alice >  bob returns " << (alice > bob) << '\n';
        std::cout << "alice >= bob returns " << (alice >= bob) << '\n';

        std::cout << '\n';

        // Compare equal containers
        std::cout << "alice == eve returns " << (alice == eve) << '\n';
        std::cout << "alice != eve returns " << (alice != eve) << '\n';
        std::cout << "alice <  eve returns " << (alice < eve) << '\n';
        std::cout << "alice <= eve returns " << (alice <= eve) << '\n';
        std::cout << "alice >  eve returns " << (alice > eve) << '\n';
        std::cout << "alice >= eve returns " << (alice >= eve) << '\n';
}

void swap_non_member()
{
	int myints[]={12,75,10,32,20,25};
	NAMESPACE::set<int> first (myints,myints+3);     // 10,12,75
	NAMESPACE::set<int> second (myints+3,myints+6);  // 20,25,32

	swap(first, second);

	std::cout << "first contains:";
	for (NAMESPACE::set<int>::iterator it=first.begin(); it!=first.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << "second contains:";
	for (NAMESPACE::set<int>::iterator it=second.begin(); it!=second.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

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

}
