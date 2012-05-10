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

#include <functional>
#include <iostream>
#include <ostream>
#include <string>

#include <dbplus/Database.hpp>

#include <cgiplus/Builder.hpp>

#include "Dispatcher.hpp"
#include "Handler.hpp"
#include "Webplus.hpp"

using std::string;

WEBPLUS_NS_BEGIN

typedef std::function<string(void)> RetrieveSessionName;
typedef std::function<string(void)> RetrieveSessionSecret;
typedef std::function<cgiplus::Builder(void)> RedirectUnlogged;

class AuthDispatcher
{
public:
    AuthDispatcher(Handler &handler, std::ostream &output = std::cout);

    void run(DatabaseFactory databaseFactory,
             RetrieveSessionName retrieveSessionName,
             RetrieveSessionSecret retrieveSessionSecret,
             RedirectUnlogged redirectUnlogged);

private:
    Dispatcher _dispatcher;
    std::ostream *_output;
};

WEBPLUS_NS_END

#endif // __WEBPLUS_AUTH_DISPATCHER_HPP__
