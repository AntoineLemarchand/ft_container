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

	printHeader("START", "┏", "━", termWidth);
	printHeader("FRONTEND TEST", "┣", "", termWidth);
	assertLine("intGood", 42, 42);
	assertLine("intBad", 42, 21);
	assertLine("floatGood", 42.42, 42.42);
	assertLine("floatBad", 42.42, 42.21);
	assertLine("stringGood", "ClapTrap", "ClapTrap");
	assertLine("stringBad", "FragTrap", "ScavTrap");
	return (0);
}
