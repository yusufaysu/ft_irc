/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 18:58:59 by alyasar           #+#    #+#             */
/*   Updated: 2023/03/10 21:21:00 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

bool	isalnumunderscore(char c)
{
	return (!(isalnum(c) || c == '_'));
}

int     checkNickname(std::string &nickname, std::map<int, User> &userMap)
{
    if (nickname.empty())
        return (1);
    else if (nickname.size() > 20 || !isalpha(nickname[0]) || std::find_if(nickname.begin(), nickname.end(), isalnumunderscore) != nickname.end())
        return (2);
    else
    {
        for (std::map<int, User>::iterator it = userMap.begin(); it != userMap.end(); it++)
        {
            if (it->second.hasNickname() && it->second.getNickname() == nickname)
                return (3);
        }
    }
    return (0);
}

void    Server::nick(std::vector<std::string> &command, User &user)
{
    int error_value;

    if (command.size() < 2)
        error_value = 1;
    else
        error_value = checkNickname(command[1], m_userMap);

    if (error_value == 1)
        numericReply(431, user);
    else if (error_value == 2)
        numericReply(432, user, &(command[1]));
    else if (error_value == 3)
        numericReply(433, user, &(command[1]));
    if (error_value != 0)
        return;

    if (!user.hasNickname())
    {
        user.setNickname(command[1]);
        if (user.getLogin())
            numericReply(001, user);
    }
    else
    {
        for (std::set<Channel>::iterator it = user.getChannelsBegin(); it != user.getChannelsEnd(); it++)
        {
            std::string msg = user.getSource();
            for (std::vector<std::string>::iterator it = command.begin(); it != command.end(); it++)
            {
                msg += " ";
                msg += *it;
            }
            sendMessage(user, it->getName(), msg, true);
        }
    }
}