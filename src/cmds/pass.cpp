/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 16:38:35 by alyasar           #+#    #+#             */
/*   Updated: 2023/03/06 21:26:32 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

void    Server::pass(std::vector<std::string> &command, User &user)
{
    if (command.size() < 2)
    {
        numericReply(461, user, &(command[0]));
        return;
    }
    else if (user.getPasswd())
    {
        numericReply(462, user);
        return;
    }

    if (command[1] == m_password)
        user.setPasswd(true);
    else
        numericReply(464, user);
}