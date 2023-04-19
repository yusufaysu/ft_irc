/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numericReply.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:59:07 by alyasar           #+#    #+#             */
/*   Updated: 2023/03/10 21:56:27 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"

void    Server::numericReply(int error, User &user, std::string *context)
{
    std::string msg = ":irc " + toString(error) + " ";
    if (context != nullptr)
        msg += *context + " ";

    switch (error)
    {
        case 001:
            msg +=  user.getNickname() + " :Welcome to the IRC Network, " + user.getNickname();
            break;
        case 401:
            msg += ":No such nick";
            break;
        case 403:
            msg += ":No such channel";
            break;
        case 404:
            msg += ":Cannot send to channel";
            break;
        case 431:
            msg += ":Nickname is empty";
            break;
        case 432:
            if (context->size() > 20)
                msg += ":Nickname is too long";
            else if (!isalpha((*context)[0]))
                msg += ":Nickname has to begin with a letter";
            else
                msg += ":Nickname must only contain alphanum characters or underscores";
            break;
        case 433:
            msg += ":This nickname is already in use, try another nickname";
            break;
        case 441:
            msg += ":They aren't on that channel";
            break;
        case 442:
            msg += ":You're not on that channel";;
            break;
        case 461:
            msg += "Not enough parameters";
            break;
        case 462:
            msg += ":You may not reregister";
            break;
        case 464:
            msg += "Password incorrect";
            break;
        case 482:
            msg += ":You're not channel operator";
            break;
    }

    sendMessage(user, msg);
}