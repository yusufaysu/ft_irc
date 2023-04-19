/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 16:17:51 by alyasar           #+#    #+#             */
/*   Updated: 2023/03/11 03:10:49 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"

Server::Server(std::string port, std::string pass)
    :   m_fd_count(0), m_fd_max(5), m_password(pass)
{
    m_pfds = static_cast<struct pollfd *>(malloc(sizeof(*m_pfds) * m_fd_max)); // Burada new dene
    if (!create(port))
        exit(1);
}

Server::~Server(void)
{
    if (m_pfds != nullptr)
        free(m_pfds);
}

int Server::create(std::string port)
{
    int status;
    struct addrinfo hints;
    struct addrinfo *ai;
    struct addrinfo *p;
    int yes = 1;

    std::memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    
    if ((status = getaddrinfo(NULL, port.c_str(), &hints, &ai)) != 0)
    {
        std::cerr << "getaddrinfo error: " << gai_strerror(status) << std::endl;
        return (0);
    }

    for (p = ai; p != NULL; p = p->ai_next)
    {
        m_listener = socket(p->ai_family, p->ai_socktype, p->ai_protocol);

        if (m_listener < 0)
            continue;

        if (setsockopt(m_listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
        {
            std::cerr << "setsockopt error" << std::endl;
            freeaddrinfo(ai);
            exit(1);
        }

        if (bind(m_listener, p->ai_addr, p->ai_addrlen) < 0)
        {
            close(m_listener);
            continue;
        }
        
        break;
    }

    freeaddrinfo(ai);

    if (p == NULL)
    {
        std::cerr << "socket error" << std::endl;
        return (0);
    }

    if (listen(m_listener, SOMAXCONN) == -1)
    {
        std::cerr << "listen error" << std::endl;
        return (0);
    }

    m_pfds[0].fd = m_listener;
    m_pfds[0].events = POLLIN;
    m_fd_count++;

    return (1);
}

int    Server::run(void)
{
    while (true)
    {
        if (poll(m_pfds, m_fd_count, -1) == -1)
        {
            std::cerr << "poll error" << std::endl;
            return (0);
        }

        for (int i = 0; i < m_fd_count; i++)
        {
            if (m_pfds[i].revents & POLLIN)
            {
                if (m_pfds[i].fd == m_listener)
                    newConnection();
                else
                    newMessage(i);
            }
        }
    }
}

void    Server::newConnection(void)
{
    char clientIP[INET_ADDRSTRLEN];
    struct sockaddr_storage clientaddr;
    socklen_t addrlen = sizeof(clientaddr);

    char hostname[NI_MAXHOST];
    char service[NI_MAXSERV];
    std::memset(hostname, 0, NI_MAXHOST);
    std::memset(service, 0, NI_MAXSERV);

    int newfd = accept(m_listener, (struct sockaddr *)(&clientaddr), &addrlen);
    
    if (newfd == -1)
        std::cerr << "accept error" << std::endl;
    else
    {
        addToPfds(newfd);
        getnameinfo((sockaddr *)(&clientaddr), addrlen, hostname, NI_MAXHOST, service, NI_MAXSERV, 0);
        m_userMap[newfd];
        m_userMap[newfd].setSocket(newfd);
        m_userMap[newfd].setHostname(hostname);
        std::cout << "New connection from " << inet_ntop(clientaddr.ss_family, &((struct sockaddr_in *)(&clientaddr))->sin_addr, clientIP, INET_ADDRSTRLEN) << " on socket " << newfd << std::endl;
    }
}

void    Server::newMessage(int index)
{
    std::string buff;
    std::string command;
    int nbytes = receiveMsg(m_pfds[index].fd, buff);
    std::cout << "msg taken: " + buff; // GELEN YAZILAR SERVERDE
    int sender_fd = m_pfds[index].fd;
    User &sender_user = m_userMap[sender_fd];

    if (nbytes <= 0)
    {
        if (nbytes == 0)
            quit("Client Quit", sender_user);
        else
            quit("Client Crashed", sender_user);
        
        close(m_pfds[index].fd);
        delFromPfds(index);
    }
    else
    {
        sender_user.addCommand(buff);
        command = sender_user.drawCommand();
        while (!command.empty())
        {
            std::vector<std::string> split_msg = splitMsg(command);
            commandDirector(split_msg, sender_user);
            command = sender_user.drawCommand();
        }
    }
}

void    Server::addToPfds(int newfd)
{
    if (m_fd_count >= m_fd_max)
    {
        m_fd_max *= 2;
        m_pfds = (struct pollfd *)realloc(m_pfds, sizeof(*m_pfds) * m_fd_max);
    }

    m_pfds[m_fd_count].fd = newfd;
    m_pfds[m_fd_count].events = POLLIN;

    m_fd_count++;
}

void    Server::delFromPfds(int index)
{
    m_pfds[index] = m_pfds[m_fd_count - 1];
    m_fd_count--;
}

void   Server::commandDirector(std::vector<std::string> &cmd, User &user)
{
    if (cmd[0] == "PASS")
        pass(cmd, user);
    if (user.getPasswd())
    {
        if (cmd[0] == "NICK")
            nick(cmd, user);
        else if (cmd[0] == "USER")
            this->user(cmd, user);
    }
    if (user.getLogin())
    {
        if (cmd[0] == "JOIN")
            join(cmd, user);
        else if (cmd[0] == "PRIVMSG")
            privmsg(cmd, user, false);
        else if (cmd[0] == "NOTICE")
            privmsg(cmd, user, true);
        else if (cmd[0] == "PING")
            ping(cmd, user);
        else if (cmd[0] == "KICK")
            kick(cmd, user);
        else if (cmd[0] == "PART")
            part(cmd, user);
        else if (cmd[0] == "QUIT" && cmd.size() == 1)
            quit("", user);
        else if (cmd[0] == "QUIT" && cmd.size() == 2)
            quit(cmd[1], user);
    }
}

void    Server::sendMessage(User &user, std::string msg)
{
    msg += "\r\n";
    std::cout << "msg send: " + msg;
    if (send(user.getSocket(), msg.data(), msg.size(), 0) == -1)
        std::cerr << "send error" << std::endl;
}

void    Server::sendMessage(User &user, std::string channel_name, std::string msg, bool send_to_sender)
{
    msg += "\r\n";
    for (std::set<int>::iterator it = m_channelMap[channel_name].getUsersBegin(); it != m_channelMap[channel_name].getUsersEnd(); it++)
    {
        int dest_fd = *it;
        if (dest_fd != m_listener && (send_to_sender || dest_fd != user.getSocket()))
        {
            std::cout << "msg send: " + msg;
            if (send(dest_fd, msg.data(), msg.size(), 0) == -1)
                std::cerr << "send error" << std::endl;
        }
    } 
}