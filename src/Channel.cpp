/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 18:12:04 by alyasar           #+#    #+#             */
/*   Updated: 2023/03/10 22:24:43 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Channel.hpp"

Channel::Channel()
{
}

Channel::Channel(std::string name, User &user)
    :   m_name(name), m_operator(&user)
{
    m_userSockets.insert(user.getSocket());
}

bool    Channel::operator<(const Channel &other) const
{
    return (m_name < other.m_name);
}

Channel     &Channel::operator=(const Channel &other)
{
    m_name = other.m_name;
    m_operator = other.m_operator;
    m_userSockets = other.m_userSockets;
    return (*this);
}

std::string                Channel::getName(void) const
{
    return (m_name);
}

void    Channel::addUserSocket(int socket)
{
    m_userSockets.insert(socket);
}

User    *Channel::getOperator(void) const
{
    return (m_operator);
}

void    Channel::setOperator(User *user)
{
    m_operator = user;
}

std::set<int>              Channel::getUsers(void) const
{
    return (m_userSockets);
}

bool Channel::checkUser(int socket)
{
    if (m_userSockets.find(socket) == m_userSockets.end())
        return (false);
    return (true);
}

void Channel::delUserSocket(int socket)
{
    m_userSockets.erase(socket);
}

bool Channel::isEmpty(void)
{
    return (m_userSockets.empty());
}

std::set<int>::iterator     Channel::getUsersBegin(void) const
{
    return (m_userSockets.begin());
}

std::set<int>::iterator     Channel::getUsersEnd(void) const
{
    return (m_userSockets.end());
}