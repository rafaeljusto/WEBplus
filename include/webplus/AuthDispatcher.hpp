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

#ifndef __WEBPLUS_AUTH_DISPATCHER_HPP__
#define __WEBPLUS_AUTH_DISPATCHER_HPP__

#include <string>

#include <boost/function.hpp>

#include <dbplus/Database.hpp>

#include <cgiplus/Builder.hpp>

#include "Handler.hpp"
#include "Webplus.hpp"

using std::string;

WEBPLUS_NS_BEGIN

class AuthDispatcher
{
public:
	void run(Handler &handler, 
	         boost::function<dbplus::Database&(void)> databaseFactory,
	         boost::function<string(void)> retrieveSessionName,
	         boost::function<string(void)> retrieveSessionSecret,
	         boost::function<cgiplus::Builder(void)> redirectUnlogged);
};

WEBPLUS_NS_END

#endif // __WEBPLUS_AUTH_DISPATCHER_HPP__
