# include "../../containers/stack.hpp"
# include <stack>
# include <iostream>
# include <cstdlib>
# include <list>
# include <deque>
# include <vector>


#ifndef NAMESPACE
# define NAMESPACE ft
#endif



void constructor()
{
	NAMESPACE::stack<int> mystack;
        int sum (0);

        for (int i=1;i<=10;i++) mystack.push(i);

        while (!mystack.empty())
        {
           sum += mystack.top();
           mystack.pop();
        }

        std::cout << "total: " << sum << '\n';
}

void empty()
{

}

void size()
{
	NAMESPACE::stack<int> myints;
        std::cout << "0. size: " << myints.size() << '\n';

        for (int i=0; i<5; i++) myints.push(i);
        std::cout << "1. size: " << myints.size() << '\n';

        myints.pop();
        std::cout << "2. size: " << myints.size() << '\n';
}

void top()
{
	NAMESPACE::stack<int> mystack;

        mystack.push(10);
        mystack.push(20);

        mystack.top() -= 5;

        std::cout << "mystack.top() is now " << mystack.top() << '\n';
}

void push()
{
	NAMESPACE::stack<int> mystack;

        for (int i=0; i<5; ++i) mystack.push(i);

        std::cout << "Popping out elements...";
        while (!mystack.empty())
        {
           std::cout << ' ' << mystack.top();
           mystack.pop();
        }
        std::cout << '\n';
}

void pop()
{
	NAMESPACE::stack<int> mystack;

	for (int i=0; i<5; ++i) mystack.push(i);

	std::cout << "Popping out elements...";
	while (!mystack.empty())
	{
		std::cout << ' ' << mystack.top();
		mystack.pop();
	}
	std::cout << '\n';
}

void relationnal_ope()
{
	NAMESPACE::stack<int> alice;
	alice.push(1);
	alice.push(2);
	alice.push(3);

        NAMESPACE::stack<int> bob;
	bob.push(7);
	bob.push(8);
	bob.push(9);
	bob.push(10);

        NAMESPACE::stack<int> eve;
	eve.push(1);
	eve.push(2);
	eve.push(3);

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

void underlying_list()
{
	NAMESPACE::stack<int, std::list<int> > alice;
	alice.push(5);
	alice.push(15);
	alice.push(54);
	alice.push(35);

	alice.pop();
	while (!alice.empty())
	{
		std::cout << ' ' << alice.top();
		alice.pop();
	}
}

void underlying_deque()
{
	NAMESPACE::stack<int, std::deque<int> > alice;
	alice.push(5);
	alice.push(15);
	alice.push(54);
	alice.push(35);

	alice.pop();
	while (!alice.empty())
	{
		std::cout << ' ' << alice.top();
		alice.pop();
	}
}

void underlying_std_vector()
{
	NAMESPACE::stack<char, std::vector<char> > alice;
	alice.push(5);
	alice.push(15);
	alice.push(54);
	alice.push(35);

	alice.pop();
	while (!alice.empty())
	{
		std::cout << ' ' << alice.top();
		alice.pop();
	}
}

void iterator_test()
{
	//NAMESPACE::stack<int>::iterator; // <-- ERROR
}

int main()
{
	constructor();

	empty();
	size();
	top();
	push();
	pop();

	relationnal_ope();

	underlying_list();
	underlying_deque();
	underlying_std_vector();

	iterator_test();
}
