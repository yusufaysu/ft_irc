/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 18:52:48 by alyasar           #+#    #+#             */
/*   Updated: 2023/03/10 18:17:06 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

void    Server::privmsg(std::vector<std::string> &command, User &user, bool notice)
{
    bool user_found = false;

    if (command.size() < 3)
    {
        numericReply(461, user, &(command[0]));
        return;
    }
    if (command[1][0] == '#') // CHANNEL PRIVMSG
    {
        if (user.findChannel(command[1]))
        {
            std::string msg = user.getSource();
            for (std::vector<std::string>::iterator it = command.begin(); it != command.end(); it++)
            {
                msg += " ";
                msg += *it;
            }
            sendMessage(user, command[1], msg, false);
        }
        else
        {
            if (m_channelMap.find(command[1]) == m_channelMap.end())
            {
                if (!notice)
                    numericReply(403, user, &(command[1]));
            }
            else
                numericReply(404, user, &(command[1]));
        }
    }
    else // USER PRIVMSG
    {
        for (std::map<int, User>::iterator i = m_userMap.begin(); i != m_userMap.end(); i++)
        {
            if (command[1] == i->second.getNickname())
            {
                user_found = true;
                std::string msg = user.getSource();
                for (std::vector<std::string>::iterator it = command.begin(); it != command.end(); it++)
                {
                    msg += " ";
                    msg += *it;
                }
                sendMessage(i->second, msg);
            }
        }
        if (!user_found && !notice)
            numericReply(401, user, &(command[1]));
    }
}