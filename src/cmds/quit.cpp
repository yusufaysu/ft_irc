/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 02:59:28 by alyasar           #+#    #+#             */
/*   Updated: 2023/03/12 23:26:27 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

void    Server::quit(std::string reason, User &user)
{
    std::set<Channel>::iterator first = user.getChannelsBegin();

    while (first != user.getChannelsEnd())
    {
        std::string channel_name = first++->getName();
        if (m_channelMap.find(channel_name)->second.getOperator() == &user)
            m_channelMap.find(channel_name)->second.setOperator(nullptr);
        m_channelMap.find(channel_name)->second.delUserSocket(user.getSocket());
        if (m_channelMap.find(channel_name)->second.isEmpty())
            m_channelMap.erase(m_channelMap.find(channel_name)->second.getName());
    }

    if (user.getLogin())
    {
        for (std::map<int, User>::iterator it = m_userMap.begin(); it != m_userMap.end(); it++)
            sendMessage(it->second, user.getSource() + " QUIT :" + crop(reason));
    }

    std::cout << "=> Socket " << user.getSocket() << " hung up." << std::endl;

    m_userMap.erase(user.getSocket());
}