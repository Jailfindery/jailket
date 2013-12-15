/*
 *
 * Internet port class definition for garden.
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

#ifndef INET_PORT_H_INCLUDED
#define INET_PORT_H_INCLUDED

#include <string>

using namespace std;

namespace jailket {

/* Exceptions:
 * jailket_invalid_argument		inet_port()
 */
class inet_port
{
  private:
	string port_number;
	int protocol;
  public:
	inet_port(string new_protocol, int new_portno);
	const char* get_port() { return port_number.c_str(); }
	int get_protocol() { return protocol; }
};

}

#endif /* INET_PORT_H_INCLUDED */

