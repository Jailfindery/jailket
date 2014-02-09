/*
 *
 * jailket exceptions for garden.
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

#ifndef JAILKET_EXCEPT_H_INCLUDED
#define JAILKET_EXCEPT_H_INCLUDED

#include <stdexcept>
#include <string>

using namespace std;

/* These exceptions can either be handled individually
 * or using the jailket_* exceptions. The former allows
 * information specific to the exception to be used, but
 * the latter is much more succinct.
 *
 * Because the derived exceptions currently offer no added
 * information, it is recommended to used the jailket_*
 * exceptions exclusively when checking for exceptions.
 */

namespace jailket {

/* Exception List */
class jailket_error;			/* General runtime error; not typically used */
class jailket_invalid_argument;	/* Used to signal an invalid argument */
class accept_error;				/* Error when using accept() */
class bind_error;				/* Error when using bind() */
class connect_error;			/* Error when using connect() */
class disconnect_error;         /* Error when closing connection */
class getaddrinfo_error;		/* Error when using getaddrinfo() */
class inet_port_error;			/* Error when creating an inet_port object */
class listen_error;				/* Error when using listen() */
class not_connected;			/* Attempting to use an unconnected socket */
class setsockopt_error;			/* Error when using setsockopt() */
class socket_error;				/* Error when using socket() */

/* Exception Definitions */
class jailket_error : public runtime_error
{
  public:
	jailket_error(const string& d) : runtime_error(d) {}
	virtual const char* what()
	{
		string MyWhat = c + runtime_error::what();
		return MyWhat.c_str();
	}
	static string c;
};

class jailket_invalid_argument : public invalid_argument
{
  public:
	jailket_invalid_argument(const string& d) : invalid_argument(d) {}
	virtual const char* what()
	{
		string MyWhat = c + invalid_argument::what();
		return MyWhat.c_str();
	}
	static string c;
};

class accept_error : public jailket_error
{
  public:
	accept_error(const string& d) : jailket_error(d) {}
};

class bind_error : public jailket_error
{
  public:
	bind_error(const string& d) : jailket_error(d) {}
};

class disconnect_error : public jailket_error
{
  public:
    disconnect_error(const string& d) : jailket_error(d) {}
};

class connect_error : public jailket_error
{
  public:
	connect_error(const string& d) : jailket_error(d) {}
};

class getaddrinfo_error : public jailket_error
{
  public:
	getaddrinfo_error(const string& d) : jailket_error(d) {}
};

class inet_port_error : public jailket_invalid_argument
{
  public:
	inet_port_error(const string& d) : jailket_invalid_argument(d) {}
};

class listen_error : public jailket_error
{
  public:
	listen_error(const string& d) : jailket_error(d) {}
};

class not_connected : public jailket_error
{
  public:
	not_connected(const string& d) : jailket_error(d) {}
};

class setsockopt_error : public jailket_error
{
  public:
	setsockopt_error(const string& d) : jailket_error(d) {}
};

class socket_error : public jailket_error
{
  public:
	socket_error(const string& d) : jailket_error(d) {}
};

}

#endif /* JAILKET_EXCEPT_H_INCLUDED */

