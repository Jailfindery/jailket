/*
 *
 * Client connection class definition for garden.
 * Copyright (C) 2013 Joshua Schell (joshua.g.schell@gmail.com)
 *
 * garden is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * garden is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with garden. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef CLIENT_CONNECTION_H_INCLUDED
#define CLIENT_CONNECTION_H_INCLUDED

#include <string>

#include "client_address.h"

using namespace std;

namespace jailket {

class server;

/* Exceptions:
 * close_error      close()
 * not_connected	recv(), send()
 */
class client_connection
{
  friend server;

  private:
    bool is_socket_open;    /* Tracks state of int socket_fd member */
	client_address address;
	client_connection(int fd, client_address c)
        : socket_fd(fd), address(c), is_socket_open(true) {}
	int socket_fd;
  public:
	int send(string mes);
	string recv();
	void disconnect();
	virtual ~client_connection();
};

}

#endif /* CLIENT_CONNECTION_H_INCLUDED */

