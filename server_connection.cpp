/*
 *
 * Server connection class implementation for garden.
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

#include "server_connection.h"
#include "jailket_except.h"

using namespace jailket;

/* After constructor is run, the connection to the server is active. */
server_connection::server_connection(string node, inet_port port)
{
	socket_fd = -1;

    addrinfo filter;    /* Used to limit generated addresses */
    memset(&filter, 0, sizeof(addrinfo) );  /* Clears garbage from filter */

    filter.ai_family = AF_UNSPEC;   /* IP-version agnostic */
    filter.ai_socktype = port.get_protocol();
    if(getaddrinfo(node.c_str(), port.get_port(),
                   &filter, &server_address) < 0)
        throw getaddrinfo_error("Failed to get server info");

	socket_fd = socket(server_address->ai_family, server_address->ai_socktype,
	                   server_address->ai_protocol);
	if(socket_fd < 0)
		throw socket_error("Unable to create socket");
    is_socket_open = true;

    connect();
}

/* Closes the actually socket and frees the server_address member. If either
 * task fails, the exceptions are swallowed.
 */
server_connection::~server_connection()
{
    try
    {
        disconnect();
        freeaddrinfo(server_address);
    }
    catch(...) { /* Shallow exceptions */ }
}


void server_connection::connect()
{
	if(::connect(socket_fd, server_address->ai_addr,
                 server_address->ai_addrlen) < 0)
		throw connect_error(string("Unable to connect to server") );
}

int server_connection::send(string d)
{
	if(socket_fd < 0)	/* Checks that the socket is set up */
		throw not_connected("Socket is not connected to a server");
	return ::send(socket_fd, d.c_str(), d.size(), 0);
}

string server_connection::recv()
{
	if(socket_fd < 0)	/* Checks that the socket is set up */
		throw not_connected("Socket is not connected to a server");
	char buf[1024];
	memset(&buf, 0, 1024);		/* Clear buf of any garbage */

	::recv(socket_fd, buf, 1024, 0);	/* Disregards the number of bytes */
	string data = string(buf);
	return data;
}

void server_connection::disconnect()
{
    if(is_socket_open)
		if(::close(socket_fd) )
            throw disconnect_error("Unable to close client socket");
    socket_fd = -1;
    is_socket_open = false;
}

