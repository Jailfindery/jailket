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

/* Closes the connection, swallowing any exceptions */
client_connection::~client_connection()
{
    try
    {
        disconnect();
    }
    catch(...) { /* Swallow execption */ }
}

int client_connection::send(string mes)
{
	if(socket_fd < 0)	/* Ensure that we really are connected to a client */
		throw not_connected("Socket is not connected to the client");
	return ::send(socket_fd, mes.c_str(), mes.size(), 0);
}

string client_connection::recv()
{
	if(socket_fd < 0)
		throw not_connected("Socket is not connected to the client");
	char buf[1024];
	memset(&buf, 0, 1024);	/* Clear buf of garbage */

	::recv(socket_fd, buf, 1024, 0);	/* Disregards the number of bytes */
	string data = string(buf);
	return data;
}

void client_connection::disconnect()
{
    if(is_socket_open)
	    if(::close(socket_fd) )
            throw disconnect_error("Unable to disconnect from client");
    is_socket_open = false;
}

/* Put-to operator for client_connection::send(). Throws the same exceptions as
 * client_connection::send().
 */
void operator<< (client_connection& cc, string& str)
{
    try
    {
        cc.send(str);
    }
    catch(...) { throw; } // Rethrows exceptions
}

/* C-string overload for the put-to operator for client_connection::send().
 * Throws the same exceptions as client_connection::send().
 */
void operator<< (jailket::client_connection& cc, const char* str)
{
    try
    {
        cc.send(string(str) );
    }
    catch(...) { throw; } // Rethrow exceptions
}

/* Get-from opreator for client_connection::recv(). Throws the same exceptions
 * as client_connection::recv().
 */
void operator>> (client_connection& cc, string& str)
{
    try
    {
        str = cc.recv();
    }
    catch(...) { throw; } // Rethrows exceptions
}

