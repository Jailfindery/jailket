/*
 *
 * Client address class for garden.
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

#ifndef CLIENT_ADDRESS_H_INCLUDED
#define CLIENT_ADDRESS_H_INCLUDED

#include <sys/socket.h>
#include <sys/types.h>

#include "inet_port.h"

namespace jailket {

/* Exceptions:
 * None for now!
 */
class client_address
{
  private:
	sockaddr* address;
	socklen_t length;
  public:
	client_address(sockaddr* a, socklen_t l) : address(a), length(l) {}
	sockaddr* get_address() { return address; }
	socklen_t get_length() { return length; }
	//~client_address()			/* Can address be freed? */
};
/* More methods could be added to retrieve information like IP address, etc */

}

#endif /* CLIENT_ADDRESS_H_INCLUDED */

