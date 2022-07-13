#include <iostream>

#include <vector>
#include <stack>
#include <map>

#include <vector.hpp>
#include <stack.hpp>
#include <map.hpp>

#include <unitTest.hpp>

void	testVector(int termWidth)
{
	std::vector<int>	*vstd;
	ft::vector<int>	*vft;

	printHeader("CONSTRUCTOR", "┣", "", termWidth);
	vstd = new std::vector<int>;
	vft = new ft::vector<int>;
	assertLine("empty constructor", vft != NULL, vstd, vft);
	delete vstd;
	delete vft;
	vstd = new std::vector<int>(10, 100);
	vft = new ft::vector<int>(10, 100);
	assertLine("fill constructor", vft != NULL, vstd, vft);
	std::vector<int>::iterator itstd(vstd->begin() + 5);
	ft::vectorIterator<int>	itft(vft->begin());
	assertLine("vectorIterator construct", *itft == *vft->begin(), &itstd, &itft);
	delete vstd;
	delete vft;
	ft::vector<int>	vft2(10,10);
	ft::vectorIterator<int> itft1(vft2.begin());
	ft::vectorIterator<int> itft2(vft2.end());
	vft = new ft::vector<int>(itft1, itft2);
	assertLine("range constructor", vft != NULL, vstd, vft);
	ft::vector<int> vft3(vft2);
	assertLine("copy constructor", &vft3 != &vft2, &vft2, &vft3);
	delete vft;

	printHeader("DESTRUCTOR", "┣", "", termWidth);
	assertLine("destructor", 1, "check leaks", "check leaks");

	printHeader("OPERATOR=", "┣", "", termWidth);
	ft::vector<int>	vftequal1(10,20);
	{
		ft::vector<int> vftequal2 = vftequal1;
	}
	assertLine("operator=",1, "deep copy", "deep copy");

	printHeader("VECTOR", "█", "━", termWidth);

	printHeader("ITERATORS", "┣", "", termWidth);

	ft::vector<int>	vftBegin(10, 10);
	std::vector<int>	vstdBegin(10, 10);
	vftBegin[0] = 20;
	vstdBegin[0] = 20;
	vftBegin[vftBegin.size() - 1] = 42;
	vstdBegin[vstdBegin.size() - 1] = 42;
	assertLine("begin", *vftBegin.begin() == *vstdBegin.begin(),
		*vstdBegin.begin(), *vftBegin.begin());
	assertLine("end", *(vftBegin.end() - 1) == *(vstdBegin.end() - 1),
		*(vstdBegin.end() - 1), *(vftBegin.end() - 1));
	assertLine("rbegin", *vftBegin.rbegin() == *vstdBegin.rbegin(),
		*vstdBegin.rbegin(), *vftBegin.rbegin());
	assertLine("rend", *(vftBegin.rend() - 1) == *(vstdBegin.rend() - 1),
		*(vstdBegin.rend() - 1), *(vftBegin.rend()- 1));
	printHeader("CAPACITY", "┣", "", termWidth);
	std::vector<std::string>	stdEmpty;
	ft::vector<std::string>		ftEmpty;
	std::vector<std::string>	stdsize(42, "coucou");
	ft::vector<std::string>		ftsize(42, "coucou");
	assertLine("size", stdEmpty.size() == ftEmpty.size() &&
		stdsize.size() == ftsize.size(),
		stdEmpty.size() + stdsize.size(), ftEmpty.size() + ftsize.size());
	assertLine("max_size", stdEmpty.max_size() == ftEmpty.max_size(),
		stdEmpty.max_size(), ftEmpty.max_size());
	stdEmpty.resize(42, "oh");
	ftEmpty.resize(42, "oh");
	assertLine("resize", stdEmpty.size() == ftEmpty.size(),
		stdEmpty.size(), ftEmpty.size());
	assertLine("      ", *stdEmpty.begin() == *ftEmpty.begin(),
		*stdEmpty.begin(), *ftEmpty.begin());
	stdEmpty.resize(40, "ah");
	ftEmpty.resize(40, "ah");
	assertLine("      ", stdEmpty.size() == ftEmpty.size(),
		stdEmpty.size(), ftEmpty.size());
	assertLine("      ", *stdEmpty.begin() == *ftEmpty.begin(),
		*stdEmpty.begin(), *ftEmpty.begin());
	assertLine("capacity", stdEmpty.capacity() == ftEmpty.capacity(),
		stdEmpty.capacity(), ftEmpty.capacity());
	assertLine("empty", stdEmpty.empty() == ftEmpty.empty(),
		stdEmpty.empty(), ftEmpty.empty());
	stdEmpty.clear();
	ftEmpty.clear();
	assertLine("     ", stdEmpty.empty() == ftEmpty.empty(),
		stdEmpty.empty(), ftEmpty.empty());
	stdEmpty.reserve(100);
	ftEmpty.reserve(100);
	assertLine("reserve", stdEmpty.capacity() == ftEmpty.capacity(),
		stdEmpty.capacity(), ftEmpty.capacity());
	stdEmpty.reserve(10);
	ftEmpty.reserve(10);
	assertLine("       ", stdEmpty.capacity() == ftEmpty.capacity(),
		stdEmpty.capacity(), ftEmpty.capacity());

	printHeader("ELEMENT ACCESS", "┣", "", termWidth);
	stdEmpty.clear();
	ftEmpty.clear();
	std::string	alphabet = "abcdefghijklmnopqrstuioprstuvwxyz";
	for (int i = 0; i < 26; i++)
	{
		stdEmpty.push_back(&alphabet[i]);
		ftEmpty.push_back(&alphabet[i]);
	}
	assertLine("operator[]", stdEmpty[0] == ftEmpty[0],
		stdEmpty[0], ftEmpty[0]);
	assertLine("          ", stdEmpty[20] == ftEmpty[20],
		stdEmpty[20], ftEmpty[20]);
	assertLine("          ", stdEmpty[25] == ftEmpty[25],
		stdEmpty[25], ftEmpty[25]);
	assertLine("front", stdEmpty.front() == ftEmpty.front(),
		stdEmpty.front(), ftEmpty.front());
	assertLine("back", stdEmpty.back() == ftEmpty.back(),
		stdEmpty.back(), ftEmpty.back());
	printHeader("MODIFIERS", "┣", "", termWidth);
	ftEmpty.clear();
	stdEmpty.clear();
	ftEmpty.assign(42, "hello");
	stdEmpty.assign(21, "goodbye");
	assertLine("assign", *ftEmpty.begin() == *ftEmpty.end(),
		ftEmpty[0], *ftEmpty.end());
	ftEmpty.assign(stdEmpty.begin(), stdEmpty.end());
	assertLine("      ", *ftEmpty.begin() == *(ftEmpty.end() - 1) && ftEmpty.size() == 21,
		*ftEmpty.begin(), *(ftEmpty.end() - 1));
	ftEmpty.push_back("push");
	stdEmpty.push_back("push");
	assertLine("push_back", *ftEmpty.rbegin() == *stdEmpty.rbegin(), *ftEmpty.rbegin(), *stdEmpty.rbegin());
	ftEmpty.pop_back();
	stdEmpty.pop_back();
	assertLine("pop_back", *ftEmpty.rbegin() == *stdEmpty.rbegin(), *ftEmpty.rbegin(), *stdEmpty.rbegin());
	//assertLine("insert", 42, 4);
	//assertLine("erase", 42, 4);
	//assertLine("swap", 42, 4);
	//assertLine("clear", 42, 4);
	//printHeader("ALLOCATOR", "┣", "", termWidth);
	//assertLine("get_allocator", 42, 4);
	//printHeader("NON-MEMBER FUNCTION OVERLOAD", "┣", "", termWidth);
	//assertLine("==", 42, 4);
	//assertLine("!=", 42, 4);
	//assertLine("<", 42, 4);
	//assertLine("<=", 42, 4);
	//assertLine(">", 42, 4);
	//assertLine(">=", 42, 4);
	//assertLine("swap", 42, 4);
};

void	testStack(int termWidth)
{
	(void)termWidth;
	//printHeader("STACK", "█", "━", termWidth);
	//printHeader("CONSTRUCTOR", "┣", "", termWidth);
	//assertLine("constructor", 42, 4);
	//printHeader("DESTRUCTOR", "┣", "", termWidth);
	//assertLine("destructor", 42, 4);
	//printHeader("MEMBER FUNCTIONS", "┣", "", termWidth);
	//assertLine("empty", 42, 4);
	//assertLine("size", 42, 4);
	//assertLine("top", 42, 4);
	//assertLine("push", 42, 4);
	//assertLine("pop", 42, 4);
	//printHeader("OPERATOR OVERLOAD", "┣", "", termWidth);
	//assertLine("==", 42, 4);
	//assertLine("!=", 42, 4);
	//assertLine("<", 42, 4);
	//assertLine("<=", 42, 4);
	//assertLine(">", 42, 4);
	//assertLine(">=", 42, 4);
}

void	testMap(int termWidth)
{
	(void)termWidth;
	//printHeader("MAP", "█", "━", termWidth);
	//printHeader("CONSTRUCTOR", "┣", "", termWidth);
	//assertLine("empty", 42, 4);
	//assertLine("range", 42, 4);
	//assertLine("copy", 42, 4);
	//printHeader("DESTRUCTOR", "┣", "", termWidth);
	//assertLine("destructor", 42, 4);
	//printHeader("OPERATOR=", "┣", "", termWidth);
	//assertLine("operator=", 42, 4);
	//printHeader("ITERATORS", "┣", "", termWidth);
	//assertLine("begin", 42, 4);
	//assertLine("end", 42, 4);
	//assertLine("rbegin", 42, 4);
	//assertLine("rend", 42, 4);
	//printHeader("CAPACITY", "┣", "", termWidth);
	//assertLine("empty", 42, 4);
	//assertLine("size", 42, 4);
	//assertLine("max_size", 42, 4);
	//printHeader("ELEMENT ACCESS", "┣", "", termWidth);
	//assertLine("operator[]", 42, 4);
	//printHeader("MODIFIERS", "┣", "", termWidth);
	//assertLine("insert", 42, 4);
	//assertLine("erase", 42, 4);
	//assertLine("swap", 42, 4);
	//assertLine("clear", 42, 4);
	//printHeader("OBSERVERS", "┣", "", termWidth);
	//assertLine("key_comp", 42, 4);
	//assertLine("value_comp", 42, 4);
	//printHeader("OPERATIONS", "┣", "", termWidth);
	//assertLine("find", 42, 4);
	//assertLine("count", 42, 4);
	//assertLine("lower_bound", 42, 4);
	//assertLine("upper_bound", 42, 4);
	//assertLine("equal_range", 42, 4);
	//printHeader("ALLOCATOR", "┣", "", termWidth);
	//assertLine("get_allocator", 42, 4);
}

//#include "../includes/vector/containers_test/srcs/base.hpp"
#include "../includes/vector/containers_test/srcs/vector/common.hpp"
#include <list>

#define TESTED_TYPE int

int		main(void)
{
	const int size = 5;
	TESTED_NAMESPACE::vector<TESTED_TYPE> vct(size);
	TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator it_ = vct.begin();
	TESTED_NAMESPACE::vector<TESTED_TYPE>::reverse_iterator it(it_);

	for (int i = 0; i < size; ++i)
		vct[i] = (i + 1) * 5;
	printSize(vct);

	std::cout << (it_ == it.base()) << std::endl;
	std::cout << (it_ == (it + 3).base()) << std::endl;

	std::cout << *(it.base() + 1) << std::endl;
	std::cout << *(it - 3) << std::endl;
	std::cout << *(it - 3).base() << std::endl;
	it -= 3;
	std::cout << *it.base() << std::endl;

	std::cout << "TEST OFFSET" << std::endl;
	std::cout << *(it) << std::endl;
	std::cout << *(it).base() << std::endl;
	std::cout << *(it - 0) << std::endl;
	std::cout << *(it - 0).base() << std::endl;
	std::cout << *(it - 1).base() << std::endl;

	return (0);
}

/*
int	main( void )
{
	int		termWidth = get_termWidth();

	testVector(termWidth);
	testStack(termWidth);
	testMap(termWidth);
	printHeader("", "█", "━", termWidth);
	return (0);
}
*/
