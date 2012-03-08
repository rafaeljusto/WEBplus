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

#ifndef __WEBPLUS_SESSION_HPP__
#define __WEBPLUS_SESSION_HPP__

#include <string>

#include "Webplus.hpp"

using std::string;

WEBPLUS_NS_BEGIN

class Session
{
public:
	string create(const string &id, const string &ip, const string &secret);
	bool check(const string &data, const string &ip, const string &secret);

private:
	string buildHash(const string &id, const string &ip, const string &secret);
	string toHexadecimal(const unsigned char *data, unsigned int size);
};

WEBPLUS_NS_END

#endif // __WEBPLUS_SESSION_HPP__
