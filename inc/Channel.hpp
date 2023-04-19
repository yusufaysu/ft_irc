/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 16:18:25 by alyasar           #+#    #+#             */
/*   Updated: 2023/03/10 21:58:37 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <set>
# include "User.hpp"

class User;

class Channel
{
private:
    std::string     m_name;
    std::set<int>   m_userSockets;
    User            *m_operator;

public:
    Channel();
    Channel(std::string name, User &user);
    bool operator<(const Channel &other) const;
    Channel &operator=(const Channel &other);

    std::set<int>               getUsers(void) const;
    std::set<int>::iterator     getUsersBegin(void) const;
    std::set<int>::iterator     getUsersEnd(void) const;
    std::string                 getName(void) const;
    User                        *getOperator(void) const;
    void                        setOperator(User *user);
    void                        addUserSocket(int socket);
    bool                        checkUser(int socket);
    void                        delUserSocket(int socket);
    bool                        isEmpty(void);
};

#endif