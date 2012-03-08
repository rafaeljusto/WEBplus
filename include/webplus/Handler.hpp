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

#ifndef __WEBPLUS_HANDLER_HPP__
#define __WEBPLUS_HANDLER_HPP__

#include <dbplus/Database.hpp>

#include <cgiplus/Builder.hpp>
#include <cgiplus/Cgi.hpp>

#include "Webplus.hpp"

WEBPLUS_NS_BEGIN

class Handler
{
public:
	virtual cgiplus::Builder run(const cgiplus::Cgi cgi, 
	                             dbplus::Database &database) = 0;
};

WEBPLUS_NS_END

#endif // __WEBPLUS_HANDLER_HPP__
