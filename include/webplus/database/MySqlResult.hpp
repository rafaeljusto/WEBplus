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

#ifndef __WEB_PLUS_DATABASE_MYSQL_RESULT_HPP__
#define __WEB_PLUS_DATABASE_MYSQL_RESULT_HPP__

extern "C" {
#include <mysql/mysql.h>
}

#include <map>

#include <boost/lexical_cast.hpp>

#include <webplus/database/DatabaseException.hpp>
#include <webplus/Webplus.hpp>

#include "Result.hpp"

WEBPLUS_DATABASE_NS_BEGIN

/*! \class MySqlResult
 *  \brief Store result of database queries (interface).
 *
 * Base class to store results of a database query.
 */
class MySqlResult : public Result
{
public:
	explicit MySqlResult(MYSQL_RES *result);
	~MySqlResult();

	unsigned int size() const;
	bool fetch();
	
	string get(const string &key) const;
	
	template<class T> 
	T get(const string &key, T (*converter)(const string&) = 
	      boost::lexical_cast<T>) const
	{
		return converter(get(key));
	}

private:
	MYSQL_RES *_result;
	std::map<string, string> _row;
};

WEBPLUS_DATABASE_NS_END

#endif // __WEB_PLUS_DATABASE_MYSQL_RESULT_HPP__
