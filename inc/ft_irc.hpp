/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 16:18:19 by alyasar           #+#    #+#             */
/*   Updated: 2023/03/12 23:26:14 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IRC_HPP
# define FT_IRC_HPP

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <poll.h>
#include <map>
#include <vector>
#include "Server.hpp"
#include <cstring>

bool isNumber(char *s);
std::vector<std::string>    splitMsg(std::string content);
bool    isCrlf(std::string str);
int receiveMsg(int socket, std::string &buff);
std::string     toString(int n);
std::string     crop(std::string str);

#endif