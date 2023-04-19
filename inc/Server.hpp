/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 16:18:12 by alyasar           #+#    #+#             */
/*   Updated: 2023/03/11 03:06:09 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

#include "ft_irc.hpp"
#include "User.hpp"
#include "Channel.hpp"
#include <algorithm>

class Server
{
private:
    int                             m_listener;
    int                             m_fd_count;
    int                             m_fd_max;
    struct pollfd                   *m_pfds;

    std::string                     m_password;

    std::map<int, User>             m_userMap;
    std::map<std::string, Channel>  m_channelMap;

private:
    int     create(std::string port);

    void    numericReply(int error, User &user, std::string *context = nullptr);

    void    newConnection(void);
    void    newMessage(int index);
    void    addToPfds(int newfd);
    void    delFromPfds(int index);
    void    disconnectUser(int user_fd);

    void    pass(std::vector<std::string> &command, User &user);
    void    nick(std::vector<std::string> &command, User &user);
    void    user(std::vector<std::string> &command, User &user);
    void    join(std::vector<std::string> &command, User &user);
    void    privmsg(std::vector<std::string> &command, User &user, bool notice);
    void    ping(std::vector<std::string> &command, User &user);
    void    kick(std::vector<std::string> &command, User &user);
    void    part(std::vector<std::string> &command, User &user);
    void    quit(std::string reason, User &user);

    void   commandDirector(std::vector<std::string> &msg, User &user);
    
    void   sendMessage(User &user, std::string msg);
    void   sendMessage(User &user, std::string channel_name, std::string msg, bool send_to_sender);

    void    sendNames(std::string name, User &user);

public:
    Server(std::string port, std::string pass);
    ~Server();

    int run(void);
};

#endif