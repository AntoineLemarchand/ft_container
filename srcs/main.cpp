#include <iostream>
#include <string>

#include <vector>
#include <ft_vector.hpp>

#include <stack>
#include <ft_stack.hpp>

#include <map>
#include <ft_map.hpp>

#include <unitTest.hpp>

int	main( void )
{
	int		termWidth = get_termWidth();

	printHeader("VECTOR", "┏", "━", termWidth);
	printHeader("CONSTRUCTORS", "┣", "", termWidth);
	assertLine("testgood1", 1, 1);
	assertLine("testgood2", "jean", "jean");
	assertLine("testbad1", 0, 1);
	assertLine("testbad2", "jean", "marc");
	return (0);
}
