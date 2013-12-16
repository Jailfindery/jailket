/*
 *
 * Client socket class implementation for garden.
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

#include <stdexcept>
#include <string>

#include <cstring>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "client_socket.h"
#include "jailket_except.h"

using namespace jailket;

client_socket::client_socket(server_address& s)
{
	socket_fd = -1;

	server = s.get_address_info();
	socket_fd = socket(server->ai_family, server->ai_socktype,
	                   server->ai_protocol);
	if(socket_fd < 0)
		throw socket_error("Unable to create socket");
    is_socket_open = true;
}

void client_socket::connect()
{
	if(::connect(socket_fd, server->ai_addr, server->ai_addrlen) < 0)
		throw connect_error(string("Unable to connect to server") );
}

int client_socket::send(string d)
{
	if(socket_fd < 0)	/* Checks that the socket is set up */
		throw not_connected("Socket is not connected to a server");
	return ::send(socket_fd, d.c_str(), d.size(), 0);
}

string client_socket::recv()
{
	if(socket_fd < 0)	/* Checks that the socket is set up */
		throw not_connected("Socket is not connected to a server");
	char buf[1024];
	memset(&buf, 0, 1024);		/* Clear buf of any garbage */

	::recv(socket_fd, buf, 1024, 0);	/* Disregards the number of bytes */
	string data = string(buf);
	return data;
}

void client_socket::close()
{
    if(is_socket_open)
		if(::close(socket_fd) )
            throw close_error("Unable to close client socket");
    socket_fd = -1;
    is_socket_open = false;
}

