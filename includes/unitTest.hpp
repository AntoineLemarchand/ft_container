/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unitTest.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 15:19:43 by alemarch          #+#    #+#             */
/*   Updated: 2022/07/06 15:21:54 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

int		get_termWidth( void );
void	printHeader(std::string header, std::string cornerLeft,
	std::string cornerRight, int termWidth);
void	assertLine(std::string name, std::string result1, std::string result2);
void	assertLine(std::string name, int result1, int result2);
