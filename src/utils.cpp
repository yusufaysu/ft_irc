/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 20:41:35 by alyasar           #+#    #+#             */
/*   Updated: 2023/03/12 23:26:04 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_irc.hpp"
#include "../inc/User.hpp"

bool isNumber(char *s)
{
    while(*s)
        if (!isdigit(*s++))
            return (true);
    return (false);
}

std::vector<std::string>    splitMsg(std::string content)
{
    char *words = new char [content.length()+1];
	std::strcpy(words, content.c_str());
	char *line = strtok(words, " ");
	std::vector<std::string> clientMsg;
	
	while(line != NULL)
	{
		clientMsg.push_back(line);
		line = strtok(NULL, "\r \n");
	}
	delete[] words;
	return (clientMsg);
}

bool    isCrlf(std::string str)
{
    std::string::size_type size = str.size();
    return (size >= 2 && str[size - 2] == '\r' && str[size - 1] == '\n');
}

int receiveMsg(int socket, std::string &buff)
{
    int rd;

    buff.clear();
    char lineRead[4096];
    std::memset(lineRead, 0, 4096);

    while ((rd = recv(socket, lineRead, 4096, 0)) != -1)
    {
        buff += lineRead;
        if (lineRead[rd] == '\0' || isCrlf(buff))
            return (buff.size());
        std::memset(lineRead, 0, 4096);
    }

    return (rd);
}

std::string     toString(int n)
{
    if (n == 1)
        return ("001");
    else
        return (std::to_string(n));
}

std::string     crop(std::string str)
{
    std::string cropped = str;

    if (cropped[0] == ':')
        cropped.erase(0, 1);

    return (cropped);
}