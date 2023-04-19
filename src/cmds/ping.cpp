/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 13:49:01 by alyasar           #+#    #+#             */
/*   Updated: 2023/03/10 21:40:56 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

void    Server::ping(std::vector<std::string> &command, User &user)
{
    if (command.size() < 2)
	{
		numericReply(461, user, &command[0]);
		return;
	}

    sendMessage(user, ":irc PONG IRC " + command[1]);
}