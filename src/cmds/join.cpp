/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 18:32:29 by alyasar           #+#    #+#             */
/*   Updated: 2023/03/12 23:19:08 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

void    Server::sendNames(std::string name, User &user)
{
    std::string buffer = ":127.0.0.1 353 = " + name + " :";
    std::set<int>::iterator begin = m_channelMap.find(name)->second.getUsersBegin();
    std::set<int>::iterator end = m_channelMap.find(name)->second.getUsersEnd();
    while (begin != end)
    {
        buffer = buffer + " " + (((m_channelMap.find(name)->second.getOperator()) == &user) ? "@" : "") +  m_userMap[*begin].getNickname();
        ++begin;
    }
    sendMessage(user, buffer);
    sendMessage(user, ":127.0.0.1 366 = " + name + " :End of /NAMES list");
}

void    Server::join(std::vector<std::string> &command, User &user)
{
    bool already_in_channel = false;

    if (command.size() < 2)
	{
		numericReply(461, user, &command[0]);
		return;
	}

    std::string &name = command[1];

    if (name[0] != '#')
        name.insert(0, "#");

    if (m_channelMap.find(name) == m_channelMap.end()) // Channel Yoksa
    {
        Channel currentChannel(name, user);
        m_channelMap[name] = currentChannel;
    }
    else
    {
        if (m_channelMap[name].checkUser(user.getSocket()))
            already_in_channel = true;
        m_channelMap[name].addUserSocket(user.getSocket());
    }

    user.addChannel(m_channelMap[name]);
    
    if (!already_in_channel)
    {
        std::string msg = user.getSource();
        for (std::vector<std::string>::iterator it = command.begin(); it != command.end(); it++)
        {
            msg += " ";
            msg += *it;
        }
        sendMessage(user, name, msg, true);
        sendNames(name, user);
    }
}