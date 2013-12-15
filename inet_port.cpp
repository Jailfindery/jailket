/*
 *
 * Internet port class implementation for garden.
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

#include <cctype>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "inet_port.h"
#include "jailket_except.h"

using namespace std;
using namespace jailket;

inet_port::inet_port(string new_protocol, int new_portno)
{
	port_number = to_string(new_portno);
	string::iterator iter;		/* Compare new_protocol to assign a protocol */
	for(iter = new_protocol.begin(); iter < new_protocol.end(); iter++)
		*iter = toupper(*iter);		/* Make new_protocol uppercase to compare */
	if(new_protocol == "TCP")
		protocol = SOCK_STREAM;
	else if(new_protocol == "UDP")
		protocol = SOCK_DGRAM;
	else		/* Can only be TCP or UDP */
		throw jailket_invalid_argument(new_protocol +
		                       " is not a valid transport protocol");
}

