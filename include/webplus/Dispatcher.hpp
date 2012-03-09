/*
  WEBplus Copyright (C) 2012 Rafael Dantas Justo

  This file is part of WEBplus.

  WEBplus is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  WEBplus is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with WEBplus.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __WEBPLUS_DISPATCHER_HPP__
#define __WEBPLUS_DISPATCHER_HPP__

#include <iostream>
#include <ostream>
#include <string>

#include <boost/function.hpp>

#include <dbplus/Database.hpp>

#include <cgiplus/Cgi.hpp>

#include "Handler.hpp"
#include "Webplus.hpp"

using std::string;

WEBPLUS_NS_BEGIN

typedef boost::function<dbplus::Database&(void)> DatabaseFactory;

class Dispatcher
{
public:
	Dispatcher(Handler &handler, std::ostream &output = std::cout);
	
	void run(DatabaseFactory databaseFactory, cgiplus::Cgi cgi = cgiplus::Cgi());

private:
	Handler &_handler;
	std::ostream *_output;
};

WEBPLUS_NS_END

#endif // __WEBPLUS_DISPATCHER_HPP__
