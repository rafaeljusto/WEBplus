/*
  WEBplus Copyright (C) 2011 Rafael Dantas Justo

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

#ifndef __WEB_PLUS_DATABASE_RESULT_HPP__
#define __WEB_PLUS_DATABASE_RESULT_HPP__

#include <string>

#include <webplus/Webplus.hpp>

using std::string;

WEBPLUS_DATABASE_NS_BEGIN

/*! \class Result
 *  \brief Store result of database queries (interface).
 *
 * Base class to store results of a database query.
 */
class Result
{
public:
	virtual unsigned int size() const = 0;
	virtual bool fetch() = 0;
	virtual string get(const string &key) const = 0;
};

WEBPLUS_DATABASE_NS_END

#endif // __WEB_PLUS_DATABASE_RESULT_HPP__
