/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 16:18:01 by alyasar           #+#    #+#             */
/*   Updated: 2023/03/10 20:52:13 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_irc.hpp"

int main(int argc, char **argv)
{
    if (argc != 3){
        std::cout << "Error: ./ircserv <port> <password>" << std::endl;
        return (1);
    }
    else if (isNumber(argv[1]) || std::atoi(argv[1]) < 0 || std::atoi(argv[1]) > 65535)
    {
        std::cout << "Error: Invalid port number !" << std::endl;
        return (1);
    }

    Server server(argv[1], argv[2]);
    std::cout << "=> Server has been created\nPort: " << argv[1] << " Password: " << argv[2] << std::endl;
    server.run();
}