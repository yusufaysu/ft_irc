/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 21:44:57 by alyasar           #+#    #+#             */
/*   Updated: 2023/03/10 21:39:06 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

void    Server::user(std::vector<std::string> &command, User &user)
{
    if (command.size() < 5)
	{
		numericReply(461, user, &(command[0]));
		return;
	}
    else if (user.hasUsername())
    {
        numericReply(462, user);
        return;
    }

    user.setUsername(command[1]);
    user.setRealname(command[4]);
    
    if (user.getLogin())
        numericReply(001, user);
}