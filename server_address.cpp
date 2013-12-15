/*
 *
 * Server address class implementation for garden.
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
#include <string>

#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "inet_port.h"
#include "jailket_except.h"
#include "server_address.h"

using namespace std;
using namespace jailket;

/* Used to connect to a server */
server_address::server_address(string node, inet_port service)
{
	addrinfo filter;		/* Used to limit generated addresses */
	memset(&filter, 0, sizeof(addrinfo) );		/* Empties all members */

	filter.ai_family = AF_UNSPEC;				/* IP-Agnostic */
	filter.ai_socktype = service.get_protocol();

	if(getaddrinfo(node.c_str(), service.get_port(),	/* Fills address_list */
	   &filter, &address_list) != 0)
		throw getaddrinfo_error("Failed to get server info");
	return;
}

server_address::~server_address()
{
	freeaddrinfo(address_list);
	return;
}

