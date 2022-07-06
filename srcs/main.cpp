#include <iostream>
#include <string>

#include <vector>
#include <ft_vector.hpp>

#include <stack>
#include <ft_stack.hpp>

#include <map>
#include <ft_map.hpp>

#include <unitTest.hpp>

void	testVector(int termWidth)
{
	printHeader("VECTOR", "█", "━", termWidth);
	printHeader("CONSTRUCTOR", "┣", "", termWidth);
	assertLine("empty constructor", 42, 4);
	assertLine("fill constructor", 42, 4);
	assertLine("range constructor", 42, 4);
	assertLine("copy constructor", 42, 4);
	printHeader("DESTRUCTOR", "┣", "", termWidth);
	assertLine("destructor", 42, 4);
	printHeader("OPERATOR=", "┣", "", termWidth);
	assertLine("operator=", 42, 4);
	printHeader("ITERATORS", "┣", "", termWidth);
	assertLine("begin", 42, 4);
	assertLine("end", 42, 4);
	assertLine("rbegin", 42, 4);
	assertLine("rend", 42, 4);
	printHeader("CAPACITY", "┣", "", termWidth);
	assertLine("size", 42, 4);
	assertLine("max_size", 42, 4);
	assertLine("resize", 42, 4);
	assertLine("capacity", 42, 4);
	assertLine("empty", 42, 4);
	assertLine("reserve", 42, 4);
	printHeader("ELEMENT ACCESS", "┣", "", termWidth);
	assertLine("operator[]", 42, 4);
	assertLine("at", 42, 4);
	assertLine("front", 42, 4);
	assertLine("back", 42, 4);
	printHeader("MODIFIERS", "┣", "", termWidth);
	assertLine("assign", 42, 4);
	assertLine("push_bach", 42, 4);
	assertLine("pop_back", 42, 4);
	assertLine("insert", 42, 4);
	assertLine("erase", 42, 4);
	assertLine("swap", 42, 4);
	assertLine("clear", 42, 4);
	printHeader("ALLOCATOR", "┣", "", termWidth);
	assertLine("get_allocator", 42, 4);
	printHeader("NON-MEMBER FUNCTION OVERLOAD", "┣", "", termWidth);
	assertLine("==", 42, 4);
	assertLine("!=", 42, 4);
	assertLine("<", 42, 4);
	assertLine("<=", 42, 4);
	assertLine(">", 42, 4);
	assertLine(">=", 42, 4);
	assertLine("swap", 42, 4);
};

void	testStack(int termWidth)
{
	printHeader("STACK", "█", "━", termWidth);
	printHeader("CONSTRUCTOR", "┣", "", termWidth);
	assertLine("constructor", 42, 4);
	printHeader("DESTRUCTOR", "┣", "", termWidth);
	assertLine("destructor", 42, 4);
	printHeader("MEMBER FUNCTIONS", "┣", "", termWidth);
	assertLine("empty", 42, 4);
	assertLine("size", 42, 4);
	assertLine("top", 42, 4);
	assertLine("push", 42, 4);
	assertLine("pop", 42, 4);
	printHeader("OPERATOR OVERLOAD", "┣", "", termWidth);
	assertLine("==", 42, 4);
	assertLine("!=", 42, 4);
	assertLine("<", 42, 4);
	assertLine("<=", 42, 4);
	assertLine(">", 42, 4);
	assertLine(">=", 42, 4);
}

void	testMap(int termWidth)
{
	printHeader("MAP", "█", "━", termWidth);
	printHeader("CONSTRUCTOR", "┣", "", termWidth);
	assertLine("empty", 42, 4);
	assertLine("range", 42, 4);
	assertLine("copy", 42, 4);
	printHeader("DESTRUCTOR", "┣", "", termWidth);
	assertLine("destructor", 42, 4);
	printHeader("OPERATOR=", "┣", "", termWidth);
	assertLine("operator=", 42, 4);
	printHeader("ITERATORS", "┣", "", termWidth);
	assertLine("begin", 42, 4);
	assertLine("end", 42, 4);
	assertLine("rbegin", 42, 4);
	assertLine("rend", 42, 4);
	printHeader("CAPACITY", "┣", "", termWidth);
	assertLine("empty", 42, 4);
	assertLine("size", 42, 4);
	assertLine("max_size", 42, 4);
	printHeader("ELEMENT ACCESS", "┣", "", termWidth);
	assertLine("operator[]", 42, 4);
	printHeader("MODIFIERS", "┣", "", termWidth);
	assertLine("insert", 42, 4);
	assertLine("erase", 42, 4);
	assertLine("swap", 42, 4);
	assertLine("clear", 42, 4);
	printHeader("OBSERVERS", "┣", "", termWidth);
	assertLine("key_comp", 42, 4);
	assertLine("value_comp", 42, 4);
	printHeader("OPERATIONS", "┣", "", termWidth);
	assertLine("find", 42, 4);
	assertLine("count", 42, 4);
	assertLine("lower_bound", 42, 4);
	assertLine("upper_bound", 42, 4);
	assertLine("equal_range", 42, 4);
	printHeader("ALLOCATOR", "┣", "", termWidth);
	assertLine("get_allocator", 42, 4);
}

int	main( void )
{
	int		termWidth = get_termWidth();

	testVector(termWidth);
	testStack(termWidth);
	testMap(termWidth);
	printHeader("", "█", "━", termWidth);
	return (0);
}
