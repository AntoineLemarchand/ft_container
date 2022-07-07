/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unitTest.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 15:19:43 by alemarch          #+#    #+#             */
/*   Updated: 2022/07/07 15:33:33 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

int		get_termWidth( void );
void	printHeader(std::string header, std::string cornerLeft,
	std::string cornerRight, int termWidth);

template <typename Tstd, typename Tft>
void	assertLine(std::string name, int condition, Tstd res1, Tft res2)
{
	std::cout << "┃ ";
	if (condition)
		std::cout << "\033[32m";
	else
		std::cout << "\033[1;31m";
	std::cout << name << ": " << "std: " << res1 << "| ft: " << res2;
	std::cout << "\033[0m" << std::endl;
}
