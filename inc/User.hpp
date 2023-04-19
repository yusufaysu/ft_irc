/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 16:18:08 by alyasar           #+#    #+#             */
/*   Updated: 2023/03/11 02:13:53 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP

# include <iostream>
# include "Channel.hpp"

class Channel;

class User
{
private:
    int             m_socket;
    std::string     m_nickname;
    std::string     m_username;
    std::string     m_realname;
    std::string     m_hostname;

    std::string     m_command;

    bool            m_correctPassword;
    bool            m_nicknameSet;
    bool            m_usernameSet;

    std::set<Channel>   m_channelSet;

public:
    User();
    bool operator<(const User &other) const;

    void        setSocket(int socket);
    int         getSocket(void) const;
    void        setPasswd(bool type);
    bool        getPasswd(void) const;
    bool        getLogin(void) const;
    void        setNickname(std::string nickname);
    std::string getNickname(void) const;
    void        setUsername(std::string username);
    std::string getUsername(void) const;
    void        setHostname(std::string hostname);
    std::string getHostname(void) const;
    void        setRealname(std::string realname);
    std::string getRealname(void) const;
    void        addChannel(const Channel &channel);
    bool        findChannel(std::string str);
    void        delChannel(const Channel &channel);
    std::string getSource(void) const;
    bool        hasNickname(void) const;
    bool        hasUsername(void) const;
    std::string getCommand(void) const;
    void        addCommand(std::string command);
    std::string drawCommand(void);
    std::set<Channel>::iterator   getChannelsBegin(void) const;
    std::set<Channel>::iterator   getChannelsEnd(void) const;
};

#endif