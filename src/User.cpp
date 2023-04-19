/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 16:49:10 by alyasar           #+#    #+#             */
/*   Updated: 2023/03/10 21:38:40 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/User.hpp"

User::User()
    :   m_correctPassword(false), m_nicknameSet(false), m_usernameSet(false)
{
}

void    User::setSocket(int socket)
{
    m_socket = socket;
}

int User::getSocket(void) const
{
    return (m_socket);
}

bool    User::getLogin(void) const
{
    return (m_correctPassword && m_nicknameSet && m_usernameSet);
}

void    User::setPasswd(bool type)
{
    m_correctPassword = type;
}

bool    User::getPasswd(void) const
{
    return (m_correctPassword);
}

void    User::setNickname(std::string nickname)
{
    m_nickname = nickname;
    m_nicknameSet = true;
}

std::string    User::getNickname(void) const
{
    return (m_nickname);
}

void    User::setUsername(std::string username)
{
    m_username = username;
    m_usernameSet = true;
}

std::string    User::getUsername(void) const
{
    return (m_username);
}

void    User::setHostname(std::string hostname)
{
    m_hostname = hostname;
}

std::string    User::getHostname(void) const
{
    return (m_hostname);
}

void        User::setRealname(std::string realname)
{
    m_realname = realname;
}

std::string User::getRealname(void) const
{
    return (m_realname);
}

bool    User::operator<(const User &other) const
{
    return (m_socket < other.m_socket);
}

void    User::addChannel(const Channel &channel)
{
    m_channelSet.insert(channel);
}

bool    User::findChannel(std::string str)
{
    for (std::set<Channel>::iterator it = m_channelSet.begin(); it != m_channelSet.end(); it++)
    {
        if ((*it).getName() == str)
            return true;
    }
    return false;
}

std::string User::getSource(void) const
{
    std::string source = ":";
    source += getNickname();
    source += "!";
    source += getUsername();
    source += "@";
    source += getHostname();
    return (source);
}

bool    User::hasNickname(void) const
{
    return (m_nicknameSet);
}

bool    User::hasUsername(void) const
{
    return (m_usernameSet);
}

std::string User::getCommand(void) const
{
    return (m_command);
}

void    User::addCommand(std::string command)
{
    m_command += command;
}

std::string User::drawCommand(void)
{
    std::string newCommand;
    size_t found = m_command.find("\r\n");
    if (found != std::string::npos)
    {
        newCommand.assign(m_command, 0, found);
        m_command.erase(0, found + 2);
    }
    return (newCommand);
}

void    User::delChannel(const Channel &channel)
{
    m_channelSet.erase(channel);
}

std::set<Channel>::iterator   User::getChannelsBegin(void) const
{
    return (m_channelSet.begin());
}

std::set<Channel>::iterator   User::getChannelsEnd(void) const
{
    return (m_channelSet.end());
}