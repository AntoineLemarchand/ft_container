/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unitTest.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 15:18:52 by alemarch          #+#    #+#             */
/*   Updated: 2022/07/06 15:22:00 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>

int	get_termWidth( void )
{
#ifdef TIOCGSIZE
    struct ttysize ts;
    ioctl(STDIN_FILENO, TIOCGSIZE, &ts);
    return (ts.ts_cols);
#elif defined(TIOCGWINSZ)
    struct winsize ts;
    ioctl(STDIN_FILENO, TIOCGWINSZ, &ts);
    return (ts.ws_col);
#endif /* TIOCGSIZE */
	return (80);
}

void	printHeader(std::string header, std::string cornerLeft,
	std::string cornerRight, int termWidth)
{
	std::cout << cornerLeft;
	if (cornerRight.compare("") != 0)
		for (unsigned long i = 0; i < (termWidth - header.size()) / 2
			- cornerLeft.size() - 2; i++)
			std::cout << "━";
	std::cout << " " << header << " ";
	if (cornerRight.compare("") != 0)
		for (unsigned long i = 0; i < (termWidth - header.size()
			+ (termWidth - header.size()) % 2 ) / 2 - cornerRight.size() - 2;
			i++)
		std::cout << "━";
	std::cout << cornerRight << std::endl;
}

void	assertLine(std::string name, std::string result1, std::string result2)
{
	std::cout << "┃ ";
	if (result1.compare(result2) == 0)
		std::cout << "\033[32m";
	else
		std::cout << "\033[1;31m";
	std::cout << name << ": " << "std: " << result1 << "| ft: " << result2;
	std::cout << "\033[0m" << std::endl;
}

void	assertLine(std::string name, int result1, int result2)
{
	std::cout << "┃ ";
	if (result1 == result2)
		std::cout << "\033[32m";
	else
		std::cout << "\033[1;31m";
	std::cout << name << ": " << result1 << "|" << result2 << "\033[0m";
	std::cout << std::endl;
}
