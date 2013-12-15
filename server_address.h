/*
 *
 * Server address class definition for garden.
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

#ifndef SERVER_ADDRESS_H_INCLUDED
#define SERVER_ADDRESS_H_INCLUDED

#include <string>

#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "inet_port.h"

using namespace std;

namespace jailket {
/* Exceptions:
 * getaddrinfo_error	server_address()
 */
class server_address
{
  private:
	addrinfo* address_list;
  public:
	server_address(string node, inet_port service);
	addrinfo* get_address_info() { return address_list; }
	virtual ~server_address();
};

}

#endif /* SERVER_ADDRESS_H_INCLUDED */

