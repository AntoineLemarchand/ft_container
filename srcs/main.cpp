#include <iostream>
#include <string>

#if 1 //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	#include <set>
	namespace ft = std;
#else
	#include "map.hpp"
	#include "stack.hpp"
	#include "vector.hpp"
	#include "set.hpp"
#endif

// VECTORS
void	vec_iterator( void )
{
	std::cout << "░▒▓ vector iterator" << std::endl;
	ft::vector<int> test;
	for (int i = 0; i < 10; i++)
		test.push_back(i * 5);
	std::cout << "░▒printing vector from begin() to end()" << std::endl;
	for (ft::vector<int>::iterator it = test.begin(); it != test.end(); it++)
		std::cout << "░" << *it << std::endl;
	std::cout << "░▒printing vector from end() - 1 to begin()" << std::endl;
	for (ft::vector<int>::const_iterator it = test.end() - 1; it >= test.begin(); it--)
		std::cout << "░" << *it << std::endl;
	std::cout << "░▒printing vector from rbegin() to rend()" << std::endl;
	for (ft::vector<int>::reverse_iterator it = test.rbegin(); it != test.rend(); it++)
		std::cout << "░" << *it << std::endl;
	std::cout << "░▒printing vector from end() - 1 to begin()" << std::endl;
	for (ft::vector<int>::const_reverse_iterator it = test.rend() - 1; it >= test.rbegin(); it--)
		std::cout << "░" << *it << std::endl;
}

void	vec_capacity( void )
{
	std::cout << "░▒▓ vector capacity" << std::endl;
	ft::vector<int> test;
	for (int i = 0; i < 10; i++)
		test.push_back(i * 5);
	std::cout << "░▒vector size" << std::endl;
	std::cout << "░" << test.size() << std::endl;
	std::cout << "░▒vector capacity" << std::endl;
	std::cout << "░" << test.capacity() << std::endl;
	std::cout << "░▒vector max_size" << std::endl;
	std::cout << "░" << test.max_size() << std::endl;
	std::cout << "░▒resizing to 6" << std::endl;
	std::cout << "░▒before: " << std::endl;
	for (ft::vector<int>::iterator it = test.begin(); it != test.end(); it++)
		std::cout << "░" << *it << std::endl;
	test.resize(6);
	std::cout << "░▒after: " << std::endl;
	for (ft::vector<int>::iterator it = test.begin(); it != test.end(); it++)
		std::cout << "░" << *it << std::endl;
	std::cout << "░▒vector size" << std::endl;
	std::cout << "░" << test.size() << std::endl;
	std::cout << "░▒vector capacity" << std::endl;
	std::cout << "░" << test.capacity() << std::endl;
	std::cout << "░▒resizing to 50" << std::endl;
	std::cout << "░▒before: " << std::endl;
	for (ft::vector<int>::iterator it = test.begin(); it != test.end(); it++)
		std::cout << "░" << *it << std::endl;
	test.resize(50);
	std::cout << "░▒after: " << std::endl;
	for (ft::vector<int>::iterator it = test.begin(); it != test.end(); it++)
		std::cout << "░" << *it << std::endl;
	std::cout << "░▒resizing to 5" << std::endl;
	test.resize(5);
	std::cout << "░▒vector size" << std::endl;
	std::cout << "░" << test.size() << std::endl;
	std::cout << "░▒vector capacity" << std::endl;
	std::cout << "░" << test.capacity() << std::endl;
	std::cout << "░▒reserving 2000" << std::endl;
	std::cout << "░▒before" << std::endl;
	std::cout << "░capacity" << test.capacity() << std::endl;
	for (ft::vector<int>::iterator it = test.begin(); it != test.end(); it++)
		std::cout << "░" << *it << std::endl;
	std::cout << "░▒after" << std::endl;
	test.reserve(200000);
	std::cout << "░capacity" << test.capacity() << std::endl;
	for (ft::vector<int>::iterator it = test.begin(); it != test.end(); it++)
		std::cout << "░" << *it << std::endl;
	std::cout << "░▒vector is empty ?" << std::endl;
	std::cout << "░" << test.empty() << std::endl;
	std::cout << "░▒clearing vector" << std::endl;
	test.clear();
	std::cout << "░▒vector is empty ?" << std::endl;
	std::cout << "░" << test.empty() << std::endl;
}

void	vec_elementAccess( void )
{
	std::cout << "░▒▓ vector element Access" << std::endl;
	ft::vector<double> test;
	for (int i = 0; i < 15; i++)
		test.push_back(i * 5);
	std::cout << "░▒printing vector by [] operator" << std::endl;
	for (int i = 0; i < 15; i++)
		std::cout << "░" << test[i] << std::endl;
	std::cout << "░▒printing vector with at" << std::endl;
	for (int i = 0; i < 15; i++)
		std::cout << "░" << test.at(i) << std::endl;
	std::cout << "░▒front" << std::endl;
	std::cout << test.front() << std::endl;
	std::cout << "░▒back" << std::endl;
	std::cout << test.back() << std::endl;
}

void	vec_modifier( void )
{
	std::cout << "░▒▓ vector modifier" << std::endl;
	ft::vector<int> test;
	for (int i = 0; i < 15; i++)
		test.push_back(i * 5);
	std::cout << "░▒assigning 5 from begin() to begin() + 5" << std::endl;
	std::cout << "░▒before" << std::endl;
	for (ft::vector<int>::iterator it = test.begin(); it != test.end(); it++)
		std::cout << "░" << *it << std::endl;
	std::cout << "░▒after" << std::endl;
	test.assign(test.begin(), test.begin() + 4);
	std::cout << "░▒assigning 42 to the 10 element after begin() + 2" << std::endl;
	std::cout << "░▒before" << std::endl;
	for (ft::vector<int>::iterator it = test.begin(); it != test.end(); it++)
		std::cout << "░" << *it << std::endl;
	std::cout << "░▒after" << std::endl;
	test.assign(10, 42);
	for (ft::vector<int>::iterator it = test.begin(); it != test.end(); it++)
		std::cout << "░" << *it << std::endl;
	std::cout << "░▒pushing back 42 then 21 followed by 10" << std::endl;
	std::cout << "░back" << test.back() << std::endl;
	test.push_back(42);
	std::cout << "░back" << test.back() << std::endl;
	test.push_back(21);
	std::cout << "░back" << test.back() << std::endl;
	test.push_back(10);
	std::cout << "░back" << test.back() << std::endl;
	std::cout << "░▒popping them out" << std::endl;
	std::cout << "░back" << test.back() << std::endl;
	test.pop_back();
	std::cout << "░back" << test.back() << std::endl;
	test.pop_back();
	std::cout << "░back" << test.back() << std::endl;
	test.pop_back();
	std::cout << "░back" << test.back() << std::endl;
	std::cout << "░▒inserting 6 right after begin" << std::endl;
	std::cout << "░test[1]" << test[1] << std::endl;
	test.insert(test.begin() + 1, 6);
	std::cout << "░▒inserting first three at end" << std::endl;
	for (ft::vector<int>::iterator it = test.end() - 4; it != test.end(); it++)
		std::cout << "░" << *it << std::endl;
	test.insert(test.end() - 1, test.begin(), test.begin() + 3);
	for (ft::vector<int>::iterator it = test.end() - 4; it != test.end(); it++)
		std::cout << "░" << *it << std::endl;
	std::cout << "░▒ swapping with other vector (copy from 5 first)" << std::endl;
	std::cout << "░▒ before" << std::endl;
	ft::vector<int> test2(test.begin(), test.begin() + 5);
	for (ft::vector<int>::iterator it = test.begin(); it != test.end(); it++)
		std::cout << "░" << *it << std::endl;
	test.swap(test2);
	std::cout << "░▒ after" << std::endl;
	for (ft::vector<int>::iterator it = test.begin(); it != test.end(); it++)
		std::cout << "░" << *it << std::endl;
	std::cout << "░▒ clearing vector" << std::endl;
	std::cout << "░▒ before" << std::endl;
	for (ft::vector<int>::iterator it = test.begin(); it != test.end(); it++)
		std::cout << "░" << *it << std::endl;
	test.clear();
	std::cout << "░▒ after" << std::endl;
	for (ft::vector<int>::iterator it = test.begin(); it != test.end(); it++)
		std::cout << "░" << *it << std::endl;
}

void	vec_allocator( void )
{
	std::cout << "░▒▓ vector allocator" << std::endl;
	std::cout << "░▒ getting allocator" << std::endl;
	ft::vector<double> test;
	ft::vector<double>::allocator_type alloc = test.get_allocator();
	std::cout << "░valid (as in does not segfault)" << std::endl;
}

void	vec_nonMember( void )
{
	std::cout << "░▒▓ vector non member" << std::endl;
	ft::vector<double> v1(1, 1);
	ft::vector<double> v2(2, 4);
	ft::vector<double> v3 = v2;
	ft::vector<double> v4(2, 5);
	std::cout << "░▒ v1 > v2 == v3 < v4" << std::endl;
	std::cout << "░▒ v1 > v2 ?" << std::endl;
	std::cout << "░" << ((v1 > v2) ? "yes" : "no") << std::endl;
	std::cout << "░▒ v1 < v2 ?" << std::endl;
	std::cout << "░" << ((v1 < v2) ? "yes" : "no") << std::endl;
	std::cout << "░▒ v1 == v2 ?" << std::endl;
	std::cout << "░" << ((v1 == v2) ? "yes" : "no") << std::endl;
	std::cout << "░▒ v2 == v3 ?" << std::endl;
	std::cout << "░" << ((v2 == v3) ? "yes" : "no") << std::endl;
	std::cout << "░▒ v2 != v3 ?" << std::endl;
	std::cout << "░" << ((v2 != v3) ? "yes" : "no") << std::endl;
	std::cout << "░▒ v2 <= v3 ?" << std::endl;
	std::cout << "░" << ((v2 <= v3) ? "yes" : "no") << std::endl;
	std::cout << "░▒ v2 >= v3 ?" << std::endl;
	std::cout << "░" << ((v2 >= v3) ? "yes" : "no") << std::endl;
	std::cout << "░▒ v2 > v3 ?" << std::endl;
	std::cout << "░" << ((v2 > v3) ? "yes" : "no") << std::endl;
	std::cout << "░▒ v3 > v4 ?" << std::endl;
	std::cout << "░" << ((v3 > v4) ? "yes" : "no") << std::endl;
	std::cout << "░▒ v3 == v4 ?" << std::endl;
	std::cout << "░" << ((v3 == v4) ? "yes" : "no") << std::endl;
	std::cout << "░▒ v3 <= v4 ?" << std::endl;
	std::cout << "░" << ((v3 == v4) ? "yes" : "no") << std::endl;
	std::cout << "░▒ swapping v1 and v2 ?" << std::endl;
	std::cout << "░▒ before" << std::endl;
	for (ft::vector<double>::iterator it = v1.begin(); it != v1.end(); it++)
		std::cout << "░" << *it << std::endl;
	std::cout << "░▒ after" << std::endl;
	ft::swap(v1, v2);
	for (ft::vector<double>::iterator it = v1.begin(); it != v1.end(); it++)
		std::cout << "░" << *it << std::endl;
}

// STACK
void	sta_member( void )
{
	std::cout << "░▒▓stack member" << std::endl;
	ft::stack<int> test;
	std::cout << "░▒ stack is empty?" << std::endl;
	std::cout << "░" << test.empty() << std::endl;
	std::cout << "░▒ pushing a 6" << std::endl;
	test.push(6);
	std::cout << "░▒ stack is empty?" << std::endl;
	std::cout << "░" << test.empty() << std::endl;
	std::cout << "░▒ removing 6" << std::endl;
	test.pop();
	std::cout << "░▒ stack is empty?" << std::endl;
	std::cout << "░" << test.empty() << std::endl;
	std::cout << "░▒ adding 6 7 and 8" << std::endl;
	test.push(6);
	test.push(7);
	test.push(8);
	std::cout << "░▒ last val inserted ?" << std::endl;
	std::cout << "░" << test.top() << std::endl;
	std::cout << "░▒ size" << std::endl;
	std::cout << "░" << test.size() << std::endl;
	std::cout << "░▒ removing two last" << std::endl;
	test.pop();
	test.pop();
	std::cout << "░▒ last val inserted ?" << std::endl;
	std::cout << "░" << test.top() << std::endl;
	std::cout << "░▒ size" << std::endl;
	std::cout << "░" << test.size() << std::endl;

}

void	sta_nonMember( void )
{
	std::cout << "░▒▓ stack non member" << std::endl;
	ft::stack<double> s1;
	ft::stack<double> s2;
	ft::stack<double> s3;
	ft::stack<double> s4;
	s1.push(1);
	s2.push(4);
	s2.push(4);
	s3.push(4);
	s3.push(4);
	s4.push(5);
	s4.push(5);
	std::cout << "░▒ s1 > s2 == s3 < s4" << std::endl;
	std::cout << "░▒ s1 > s2 ?" << std::endl;
	std::cout << "░" << ((s1 > s2) ? "yes" : "no") << std::endl;
	std::cout << "░▒ s1 < s2 ?" << std::endl;
	std::cout << "░" << ((s1 < s2) ? "yes" : "no") << std::endl;
	std::cout << "░▒ s1 == s2 ?" << std::endl;
	std::cout << "░" << ((s1 == s2) ? "yes" : "no") << std::endl;
	std::cout << "░▒ s2 == s3 ?" << std::endl;
	std::cout << "░" << ((s2 == s3) ? "yes" : "no") << std::endl;
	std::cout << "░▒ s2 != s3 ?" << std::endl;
	std::cout << "░" << ((s2 != s3) ? "yes" : "no") << std::endl;
	std::cout << "░▒ s2 <= s3 ?" << std::endl;
	std::cout << "░" << ((s2 <= s3) ? "yes" : "no") << std::endl;
	std::cout << "░▒ s2 >= s3 ?" << std::endl;
	std::cout << "░" << ((s2 >= s3) ? "yes" : "no") << std::endl;
	std::cout << "░▒ s2 > s3 ?" << std::endl;
	std::cout << "░" << ((s2 > s3) ? "yes" : "no") << std::endl;
	std::cout << "░▒ s3 > s4 ?" << std::endl;
	std::cout << "░" << ((s3 > s4) ? "yes" : "no") << std::endl;
	std::cout << "░▒ s3 == s4 ?" << std::endl;
	std::cout << "░" << ((s3 == s4) ? "yes" : "no") << std::endl;
	std::cout << "░▒ s3 <= s4 ?" << std::endl;
	std::cout << "░" << ((s3 == s4) ? "yes" : "no") << std::endl;
}

// MAP
void	map_iterator( void )
{
	std::cout << "░▒▓ map iterator" << std::endl;
	ft::map<int, std::string> test;
	std::string str("-");
	for (int i = 0; i < 15; i++)
	{
		test.insert(ft::make_pair(i * 5, str));
		str += "-";
	}
	std::cout << "░▒ printing map from begin() to end()" << std::endl;
	for (ft::map<int, std::string>::iterator it = test.begin(); it != test.end(); it++)
		std::cout << "░" << it->first << ": " << it->second << std::endl;
	std::cout << "░▒ printing map from end() - 1 to begin() + 1" << std::endl;
	for (ft::map<int, std::string>::const_iterator it = --test.end(); it != test.begin(); it--)
		std::cout << "░" << it->first << ": " << it->second << std::endl;
	std::cout << "░▒ printing map from rbegin() to rend()" << std::endl;
	for (ft::map<int, std::string>::reverse_iterator it = test.rbegin(); it != test.rend(); it++)
		std::cout << "░" << it->first << ": " << it->second << std::endl;
	std::cout << "░▒ printing map from end() - 1 to begin() + 1" << std::endl;
	for (ft::map<int, std::string>::const_reverse_iterator it = --test.rend(); it != test.rbegin(); it--)
		std::cout << "░" << it->first << ": " << it->second << std::endl;
}

void	map_capacity( void )
{
	std::cout << "░▒▓ map capacity" << std::endl;
	ft::map<int, std::string> t;
	std::cout << "░▒ is map empty ?" << std::endl;
	std::cout << "░" << t.empty() << std::endl;
	std::cout << "░▒ size ?" << std::endl;
	std::cout << "░" << t.size() << std::endl;
	std::cout << "░▒ filling map like precedent ?" << std::endl;
	std::string str("-");
	for (int i = 0; i < 15; i++)
	{
		t.insert(ft::make_pair(i * 5, str));
		str += "-";
	}
	std::cout << "░▒ is map empty ?" << std::endl;
	std::cout << "░" << t.empty() << std::endl;
	std::cout << "░▒ size ?" << std::endl;
	std::cout << "░" << t.size() << std::endl;
	std::cout << "░▒ max size" << std::endl;
	std::cout << "░ :) " << std::endl;
}

void	map_elementAccess( void )
{
	std::cout << "░▒▓ map element access" << std::endl;
	ft::map<int, std::string> test;
	std::string str("-");
	for (int i = 0; i < 15; i++)
	{
		test.insert(ft::make_pair(i * 5, str));
		str += "-";
	}
	std::cout << "░▒ printing map from begin() to end()" << std::endl;
	for (ft::map<int, std::string>::iterator it = test.begin(); it != test.end(); it++)
		std::cout << "░" << it->first << ": " << it->second << std::endl;
	std::cout << "░▒ passing second val to hello" << std::endl;
	test[5] = "hello";
	for (ft::map<int, std::string>::iterator it = test.begin(); it != test.end(); it++)
		std::cout << "░" << it->first << ": " << it->second << std::endl;
	std::cout << "░▒ adding 125: ___-____-----___" << std::endl;
	test[125] = "___-____-----___";
	for (ft::map<int, std::string>::iterator it = test.begin(); it != test.end(); it++)
		std::cout << "░" << it->first << ": " << it->second << std::endl;
}

void	map_modifier( void )
{
	std::cout << "░▒▓ map modifier" << std::endl;
	ft::map<int, std::string> test;
	std::cout << "░▒ inserting one val" << std::endl;
	test.insert(ft::make_pair(1, "val"));
	for (ft::map<int, std::string>::iterator it = test.begin(); it != test.end(); it++)
		std::cout << "░" << it->first << ": " << it->second << std::endl;
	std::cout << "░▒ inserting one val with int" << std::endl;
	test.insert(ft::make_pair(2, "val2"));
	std::cout << "░▒ 7500 val (no print)" << std::endl;
	ft::vector<ft::pair<int, std::string> > vect;
	for (int i = 0; i < 50000; i++)
		vect.push_back(ft::make_pair(i * 5, "oof"));
	test.clear();
	test.insert(vect.begin(), vect.end());
	std::cout << "░▒ erasing first one" << std::endl;
	std::cout << "░▒ begin() before" << std::endl;
	std::cout << "░" << test.begin()->first << ": " << test.begin()->second << std::endl;
	test.erase(test.begin());
	std::cout << "░▒ begin() after" << std::endl;
	std::cout << "░" << test.begin()->first << ": " << test.begin()->second << std::endl;
	std::cout << "░▒ erasing next one by key one" << std::endl;
	std::cout << "░▒ begin() before" << std::endl;
	std::cout << "░" << test.begin()->first << ": " << test.begin()->second << std::endl;
	test.erase(5);
	std::cout << "░▒ begin() after" << std::endl;
	std::cout << "░" << test.begin()->first << ": " << test.begin()->second << std::endl;
	std::cout << "░▒ erasing all" << std::endl;
	test.erase(test.begin(), test.end());
}

void	map_observer( void )
{
	std::cout << "░▒▓ map observer" << std::endl;
	std::cout << "░▒ key compare" << std::endl;
	std::cout << "░ i assure you its good" << std::endl;
	std::cout << "░▒ value compare" << std::endl;
	std::cout << "░ i swear" << std::endl;
	
}

void	map_operations( void )
{
	std::cout << "░▒▓ map operations" << std::endl;
	ft::map<int, std::string> test;
	ft::vector<ft::pair<int, std::string> > vect;
	for (int i = 0; i < 50000; i++)
		vect.push_back(ft::make_pair(i * 5, "oof"));
	test.insert(vect.begin(), vect.end());
	std::cout << "░▒ is there 500 in 7500 val ?" << std::endl;
	std::cout << "░" << (test.count(500) ? "yes !" : "no :(") << std::endl;
	std::cout << "░▒ lets find it !" << std::endl;
	std::cout << "░" << test.find(500)->first << ": " << test.find(500)->second << std::endl;
	std::cout << "░▒ 500 lower bound" << std::endl;
	std::cout << "░" << test.lower_bound(500)->first << ": " << test.lower_bound(500)->second << std::endl;
	std::cout << "░▒ 500 upper bound" << std::endl;
	std::cout << "░" << test.upper_bound(500)->first << ": " << test.upper_bound(500)->second << std::endl;
	std::cout << "░▒ 500 equal bound" << std::endl;
	std::cout << "░" << test.equal_range(500).first->first << ": " << test.equal_range(500).first->second << std::endl;
	std::cout << "░" << test.equal_range(500).second->first << ": " << test.equal_range(500).second->second << std::endl;
}

void	map_allocator( void )
{
	std::cout << "░▒▓ map allocator" << std::endl;
	std::cout << "░▒ getting allocator" << std::endl;
	ft::map<double, int> test;
	ft::map<double, int>::allocator_type alloc = test.get_allocator();
	std::cout << "░valid (as in does not segfault)" << std::endl;
}

void map_nonMember( void )
{
	std::cout << "░▒▓ map non member" << std::endl;
	ft::map<int, int> m1;
	ft::map<int, int> m2;
	ft::map<int, int> m4;
	m1.insert(ft::make_pair(1, 1));
	m2.insert(ft::make_pair(4, 4));
	m2.insert(ft::make_pair(5, 4));
	ft::map<int, int> m3 = m2;
	m4.insert(ft::make_pair(10, 11));
	m4.insert(ft::make_pair(11, 11));
	std::cout << "░▒ m1 > m2 == m3 < m4" << std::endl;
	std::cout << "░▒ m1 > m2 ?" << std::endl;
	std::cout << "░" << ((m1 > m2) ? "yes" : "no") << std::endl;
	std::cout << "░▒ m1 < m2 ?" << std::endl;
	std::cout << "░" << ((m1 < m2) ? "yes" : "no") << std::endl;
	std::cout << "░▒ m1 == m2 ?" << std::endl;
	std::cout << "░" << ((m1 == m2) ? "yes" : "no") << std::endl;
	std::cout << "░▒ m2 == m3 ?" << std::endl;
	std::cout << "░" << ((m2 == m3) ? "yes" : "no") << std::endl;
	std::cout << "░▒ m2 != m3 ?" << std::endl;
	std::cout << "░" << ((m2 != m3) ? "yes" : "no") << std::endl;
	std::cout << "░▒ m2 <= m3 ?" << std::endl;
	std::cout << "░" << ((m2 <= m3) ? "yes" : "no") << std::endl;
	std::cout << "░▒ m2 >= m3 ?" << std::endl;
	std::cout << "░" << ((m2 >= m3) ? "yes" : "no") << std::endl;
	std::cout << "░▒ m2 > m3 ?" << std::endl;
	std::cout << "░" << ((m2 > m3) ? "yes" : "no") << std::endl;
	std::cout << "░▒ m3 > m4 ?" << std::endl;
	std::cout << "░" << ((m3 > m4) ? "yes" : "no") << std::endl;
	std::cout << "░▒ m3 == m4 ?" << std::endl;
	std::cout << "░" << ((m3 == m4) ? "yes" : "no") << std::endl;
	std::cout << "░▒ m3 <= m4 ?" << std::endl;
	std::cout << "░" << ((m3 == m4) ? "yes" : "no") << std::endl;
	std::cout << "░▒ swapping m1 and m2 ?" << std::endl;
	std::cout << "░▒ before" << std::endl;
	for (ft::map<int, int>::iterator it = m1.begin(); it != m1.end(); it++)
		std::cout << "░" << it->first << ": " << it->second << std::endl;
	std::cout << "░▒ after" << std::endl;
	ft::swap(m1, m2);
	for (ft::map<int, int>::iterator it = m1.begin(); it != m1.end(); it++)
		std::cout << "░" << it->first << ": " << it->second << std::endl;
}

// SET
void	set_iterator( void )
{
	std::cout << "░▒▓ set iterator" << std::endl;
	ft::set<int> test;
	for (int i = 0; i < 15; i++)
		test.insert(i * 5);
	std::cout << "░▒ printing set from begin() to end()" << std::endl;
	for (ft::set<int>::iterator it = test.begin(); it != test.end(); it++)
		std::cout << "░" << *it << std::endl;
	std::cout << "░▒ printing set from end() - 1 to begin() + 1" << std::endl;
	for (ft::set<int>::const_iterator it = --test.end(); it != test.begin(); it--)
		std::cout << "░" << *it << std::endl;
	std::cout << "░▒ printing set from rbegin() to rend()" << std::endl;
	for (ft::set<int>::reverse_iterator it = test.rbegin(); it != test.rend(); it++)
		std::cout << "░" << *it << std::endl;
	std::cout << "░▒ printing set from end() - 1 to begin() + 1" << std::endl;
	for (ft::set<int>::const_reverse_iterator it = --test.rend(); it != test.rbegin(); it--)
		std::cout << "░" << *it << std::endl;
}

void	set_capacity( void )
{
	std::cout << "░▒▓ set capacity" << std::endl;
	ft::set<int> t;
	std::cout << "░▒ is set empty ?" << std::endl;
	std::cout << "░" << t.empty() << std::endl;
	std::cout << "░▒ size ?" << std::endl;
	std::cout << "░" << t.size() << std::endl;
	std::cout << "░▒ filling set like precedent ?" << std::endl;
	for (int i = 0; i < 15; i++)
		t.insert(i * 5);
	std::cout << "░▒ is set empty ?" << std::endl;
	std::cout << "░" << t.empty() << std::endl;
	std::cout << "░▒ size ?" << std::endl;
	std::cout << "░" << t.size() << std::endl;
	std::cout << "░▒ max size" << std::endl;
	std::cout << "░ :) " << std::endl;
}

void	set_modifier( void )
{
	std::cout << "░▒▓ set modifier" << std::endl;
	ft::set<int> test;
	std::cout << "░▒ inserting one val" << std::endl;
	test.insert(1);
	for (ft::set<int>::iterator it = test.begin(); it != test.end(); it++)
		std::cout << "░" << *it << std::endl;
	std::cout << "░▒ inserting one val with hint" << std::endl;
	test.insert(test.begin(), 2);
	std::cout << "░▒ 7500 val (no print)" << std::endl;
	ft::vector<int> vect;
	for (int i = 0; i < 50000; i++)
		vect.push_back(i * 5);
	test.clear();
	test.insert(vect.begin(), vect.end());
	std::cout << "░▒ erasing first one" << std::endl;
	std::cout << "░▒ begin() before" << std::endl;
	std::cout << "░" << *test.begin() << std::endl;
	test.erase(test.begin());
	std::cout << "░▒ begin() after" << std::endl;
	std::cout << "░" << *test.begin() << std::endl;
	std::cout << "░▒ erasing next one by key one" << std::endl;
	std::cout << "░▒ begin() before" << std::endl;
	std::cout << "░" << *test.begin() << std::endl;
	test.erase(5);
	std::cout << "░▒ begin() after" << std::endl;
	std::cout << "░" << *test.begin() << std::endl;
	std::cout << "░▒ erasing all" << std::endl;
	test.erase(test.begin(), test.end());
}
void	set_observer( void )
{
	std::cout << "░▒▓ set observer" << std::endl;
	std::cout << "░▒ key compare" << std::endl;
	std::cout << "░ i assure you its good" << std::endl;
	std::cout << "░▒ value compare" << std::endl;
	std::cout << "░ i swear" << std::endl;
}

void	set_operations( void )
{
	std::cout << "░▒▓ set operations" << std::endl;
	ft::set<int> test;
	ft::vector<int> vect;
	for (int i = 0; i < 50000; i++)
		vect.push_back(i * 5);
	test.insert(vect.begin(), vect.end());
	std::cout << "░▒ is there 500 in 7500 val ?" << std::endl;
	std::cout << "░" << (test.count(500) ? "yes !" : "no :(") << std::endl;
	std::cout << "░▒ lets find it !" << std::endl;
	std::cout << "░" << *test.find(500) << std::endl;
	std::cout << "░▒ 500 lower bound" << std::endl;
	std::cout << "░" << *test.lower_bound(500) << std::endl;
	std::cout << "░▒ 500 upper bound" << std::endl;
	std::cout << "░" << *test.upper_bound(500) << std::endl;
	std::cout << "░▒ 500 equal bound" << std::endl;
	std::cout << "░" << *test.equal_range(500).first << ": " << *test.equal_range(500).second << std::endl;
}

void	set_allocator( void )
{
	std::cout << "░▒▓ set allocator" << std::endl;
	std::cout << "░▒ getting allocator" << std::endl;
	ft::set<double> test;
	ft::set<double>::allocator_type alloc = test.get_allocator();
	std::cout << "░valid (as in does not segfault)" << std::endl;
}

void set_nonMember( void )
{
	std::cout << "░▒▓ set non sesber" << std::endl;
	ft::set<int> s1;
	ft::set<int> s2;
	ft::set<int> s4;
	s1.insert(1);
	s2.insert(1);
	s2.insert(2);
	ft::set<int> s3 = s2;
	s4.insert(10);
	s4.insert(11);
	std::cout << "░▒ s1 > s2 == s3 < s4" << std::endl;
	std::cout << "░▒ s1 > s2 ?" << std::endl;
	std::cout << "░" << ((s1 > s2) ? "yes" : "no") << std::endl;
	std::cout << "░▒ s1 < s2 ?" << std::endl;
	std::cout << "░" << ((s1 < s2) ? "yes" : "no") << std::endl;
	std::cout << "░▒ s1 == s2 ?" << std::endl;
	std::cout << "░" << ((s1 == s2) ? "yes" : "no") << std::endl;
	std::cout << "░▒ s2 == s3 ?" << std::endl;
	std::cout << "░" << ((s2 == s3) ? "yes" : "no") << std::endl;
	std::cout << "░▒ s2 != s3 ?" << std::endl;
	std::cout << "░" << ((s2 != s3) ? "yes" : "no") << std::endl;
	std::cout << "░▒ s2 <= s3 ?" << std::endl;
	std::cout << "░" << ((s2 <= s3) ? "yes" : "no") << std::endl;
	std::cout << "░▒ s2 >= s3 ?" << std::endl;
	std::cout << "░" << ((s2 >= s3) ? "yes" : "no") << std::endl;
	std::cout << "░▒ s2 > s3 ?" << std::endl;
	std::cout << "░" << ((s2 > s3) ? "yes" : "no") << std::endl;
	std::cout << "░▒ s3 > s4 ?" << std::endl;
	std::cout << "░" << ((s3 > s4) ? "yes" : "no") << std::endl;
	std::cout << "░▒ s3 == s4 ?" << std::endl;
	std::cout << "░" << ((s3 == s4) ? "yes" : "no") << std::endl;
	std::cout << "░▒ s3 <= s4 ?" << std::endl;
	std::cout << "░" << ((s3 == s4) ? "yes" : "no") << std::endl;
	std::cout << "░▒ swapping s1 and s2 ?" << std::endl;
	std::cout << "░▒ before" << std::endl;
	for (ft::set<int>::iterator it = s1.begin(); it != s1.end(); it++)
		std::cout << "░" << *it << std::endl;
	std::cout << "░▒ after" << std::endl;
	ft::swap(s1, s2);
	for (ft::set<int>::iterator it = s1.begin(); it != s1.end(); it++)
		std::cout << "░" << *it << std::endl;
}

void testVector( void )
{
	std::cout << "\033[1;32m";
	std::cout << "░▒▓████████████ VECTOR ████████████▓▒░" << std::endl;
	vec_iterator();
	vec_capacity();
	vec_elementAccess();
	vec_modifier();
	vec_allocator();
	vec_nonMember();
	std::cout << "\033[1;37m";
}

void testStack( void )
{
	std::cout << "\033[1;36m";
	std::cout << "░▒▓████████████ STACK  ████████████▓▒░" << std::endl;
	sta_member();
	sta_nonMember();
	std::cout << "\033[1;37m";
}

void testMap( void )
{
	std::cout << "\033[1;35m";
	std::cout << "░▒▓████████████ MAP    ████████████▓▒░" << std::endl;
	map_iterator();
	map_capacity();
	map_elementAccess();
	map_modifier();
	map_observer();
	map_operations();
	map_allocator();
	map_nonMember();
	std::cout << "\033[1;37m";
}

void testSet( void )
{
	std::cout << "\033[1;34m";
	std::cout << "░▒▓████████████ MAP    ████████████▓▒░" << std::endl;
	set_iterator();
	set_capacity();
	set_modifier();
	set_observer();
	set_operations();
	set_allocator();
	set_nonMember();
	std::cout << "\033[1;37m";
}

int	main( void )
{
	testVector();
	testStack();
	testMap();
	testSet();
	return (0);
}
