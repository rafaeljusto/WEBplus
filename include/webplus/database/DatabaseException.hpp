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

#ifndef __WEB_PLUS_DATABASE_DATABASE_EXCEPTION_HPP__
#define __WEB_PLUS_DATABASE_DATABASE_EXCEPTION_HPP__

#include <exception>
#include <string>

#include <webplus/Webplus.hpp>

using std::string;

WEBPLUS_DATABASE_NS_BEGIN

class DatabaseException : public std::exception
{
public:
	enum Code {
		CONNECTION_ERROR,
		EXECUTION_ERROR,
		RESULT_ERROR,
		STATE_CHANGE_ERROR,
		TRANSACTION_ERROR,
		UNKNOW_KEY_ERROR
	};

	DatabaseException(const Code code, 
	                  const string &file, 
	                  const string &function, 
	                  const int line, 
	                  const string &message) throw();
	~DatabaseException() throw();

	const char* what() const throw();

private:
	string _message;
};

WEBPLUS_DATABASE_NS_END

#endif // __WEB_PLUS_DATABASE_DATABASE_EXCEPTION_HPP__
