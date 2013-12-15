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

class server_socket;

/* Exceptions:
 * not_connected	recv(), send()
 */
class client_connection
{
  friend server_socket;

  private:
	client_connection(int fd, client_address c) : socket_fd(fd), address(c) {}
	int socket_fd;
	client_address address;
  public:
	int send(string mes);
	string recv();
	void close();
	virtual ~client_connection();
};

}

#endif /* CLIENT_CONNECTION_H_INCLUDED */

