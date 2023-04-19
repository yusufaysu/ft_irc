/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 17:36:31 by alyasar           #+#    #+#             */
/*   Updated: 2023/03/10 22:11:56 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

void    Server::kick(std::vector<std::string> &command, User &user)
{
    Channel *channel = nullptr; 
    User *kicked_user = nullptr;

    if (command.size() < 3)
	{
		numericReply(461, user, &command[0]);
		return;
	}

    if (m_channelMap.find(command[1]) != m_channelMap.end())
        channel = &(m_channelMap.find(command[1])->second);

    if (channel == nullptr)
    {
        numericReply(403, user, &command[1]);
		return;
    }
    else if (channel->getOperator() != &user)
    {
        numericReply(482, user, &command[1]);
		return;
    }

    for (std::map<int, User>::iterator it = m_userMap.begin(); it != m_userMap.end(); it++)
    {
        if (channel->checkUser(it->second.getSocket()) && it->second.getNickname() == command[2])
            kicked_user = &(it->second);
    }

    if (kicked_user == nullptr)
    {
        numericReply(441, user, &command[2]);
		return;
    }

    std::string msg = user.getSource();
    for (std::vector<std::string>::iterator it = command.begin(); it != command.end(); it++)
    {
        msg += " ";
        msg += *it;
    }
    sendMessage(user, command[1], msg, true);

    if (channel->getOperator() == kicked_user)
        channel->setOperator(nullptr);
    channel->delUserSocket(kicked_user->getSocket());
    kicked_user->delChannel(*channel);

    if (channel->isEmpty())
        m_channelMap.erase(command[1]);
}