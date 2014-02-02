/*
 *
 * Server class implementation for garden.
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

#include <cstring>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "client_address.h"
#include "client_connection.h"
#include "jailket_except.h"
#include "server.h"

using namespace std;
using namespace jailket;

server::server(inet_port service)
{
	addrinfo filter;    /* Used to limit generated addresses */
	addrinfo* address;	/* Stores server address */
	memset(&filter, 0, sizeof(addrinfo) );  /* Empties the filter struct */

	filter.ai_family = AF_UNSPEC;   /* IP-Agnostic */
	filter.ai_flags = AI_PASSIVE;   /* Specifies a server socket */
	filter.ai_socktype = service.get_protocol();

	if(getaddrinfo(NULL, service.get_port(),    /* Fills address_list */
	   &filter, &address) < 0)
		throw getaddrinfo_error("Failed to create server address info");

	/* Create the socket on which we listen for connections */
	listen_fd = socket(address->ai_family, address->ai_socktype,
	                   address->ai_protocol);
	if(listen_fd < 0)
		throw socket_error("Unable to create socket for server");
    is_socket_open = true;

	int yes = 1;
	if(setsockopt(listen_fd, SOL_SOCKET,		/* Ensure the socket is */
	   SO_REUSEADDR, &yes, sizeof(int) ) < 0)	/* not being used. */
		throw setsockopt_error("Unable to set socket options");

	/* Bind the socket to a specific port to allow for server usage */
	if(bind(listen_fd, address->ai_addr, address->ai_addrlen) < 0)
		throw bind_error("Unable to bind to the socket");
}

void server::listen()
{
	if(::listen(listen_fd, QUEUE_LENGTH) < 0)
		throw listen_error("Listen error");
	return;
}

client_connection server::accept()
{
	sockaddr client;	/* Stores information about the client */
	socklen_t client_length;
	int client_fd;		/* Socket for communication with client */

	client_fd = ::accept(listen_fd, &client, &client_length);
	if(client_fd < 0)
		throw accept_error("Unable to accept client");

	/* We need to create a client_address object to retain client info */
	client_address MyClient(&client, client_length);

	return client_connection(client_fd, MyClient);
}

void server::close()
{
    if(is_socket_open)
        if(::close(listen_fd) )
            throw close_error("Unable to close server socket file descriptor");
    is_socket_open = false;
}

