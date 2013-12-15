/*
 *
 * Client connection class implementation for garden.
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

#include <string>

#include <cstring>
#include <unistd.h>

#include "client_connection.h"
#include "jailket_except.h"

using namespace std;
using namespace jailket;

int client_connection::send(string mes)
{
	if(socket_fd <= 0)	/* Ensure that we really are connected to a client */
		throw not_connected("Socket is not connected to the client");
	return ::send(socket_fd, mes.c_str(), mes.size(), 0);
}

string client_connection::recv()
{
	if(socket_fd <= 0)
		throw not_connected("Socket is not connected to the client");
	char buf[1024];
	memset(&buf, 0, 1024);	/* Clear buf of garbage */

	::recv(socket_fd, buf, 1024, 0);	/* Disregards the number of bytes */
	string data = string(buf);
	return data;
}

void client_connection::close()
{
	::close(socket_fd);
	return;
}

client_connection::~client_connection()
{
	close();
}

