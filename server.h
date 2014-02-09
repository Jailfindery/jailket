/*
 *
 * Server class definition for garden.
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

#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED

#include "client_connection.h"
#include "inet_port.h"

/* This should be overridable */
#ifndef QUEUE_LENGTH
#define QUEUE_LENGTH 5	/* Amount of connections to keep in background */
#endif

namespace jailket {

/* Exceptions:
 * accept_error			accept()
 * bind_error			server()
 * close_error          disconnect()
 * getaddrinfo_error	server()
 * listen_error			listen()
 * socket_error			server()
 */
class server
{
  private:
    bool is_socket_open;
	int listen_fd;
  public:
	server(inet_port service);
    virtual ~server();
	void listen();
	client_connection accept();
	void disconnect();
};

}

#endif /* SERVER_H_INCLUDED */

