/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 21:47:40 by alyasar           #+#    #+#             */
/*   Updated: 2023/03/10 22:35:24 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

void    Server::part(std::vector<std::string> &command, User &user)
{
    if (command.size() < 2) 
	{
        numericReply(461, user, &(command[0]));
		return;
    }

    if (command[1][0] == '#')
    {
        if (m_channelMap.find(command[1]) == m_channelMap.end())
        {
            numericReply(403, user, &(command[1]));
            return;
        }
        Channel &channel = m_channelMap.find(command[1])->second;
        if (!channel.checkUser(user.getSocket()))
        {
            numericReply(442, user, &(command[1]));
            return;
        }

        std::string msg = user.getSource();
        for (std::vector<std::string>::iterator it = command.begin(); it != command.end(); it++)
        {
            msg += " ";
            msg += *it;
        }
        sendMessage(user, command[1], msg, true);

        if (channel.getOperator() == &user)
            channel.setOperator(nullptr);
        channel.delUserSocket(user.getSocket());
        user.delChannel(channel);

        if (channel.isEmpty())
            m_channelMap.erase(command[1]);
    }
}