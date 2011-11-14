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

#ifndef __WEB_PLUS_DATABASE_RELATIONAL_DATABASE_HPP__
#define __WEB_PLUS_DATABASE_RELATIONAL_DATABASE_HPP__

#include <memory>
#include <string>

#include <webplus/Webplus.hpp>

using std::string;

WEBPLUS_DATABASE_NS_BEGIN

class Result;

/*! \class RelationalDatabase
 *  \brief Relational database interface.
 *
 * Base class to perform operations over a relational database.
 */
class RelationalDatabase
{
public:
	enum TransactionMode {
		AUTO_COMMIT,
		MANUAL_COMMIT
	};

	enum ResultMode {
		// Store all result data in the server
		USE_RESULT,
		// Store all result data in the client
		STORE_RESULT
	};

	virtual void connect(const string &database, 
	                     const string &user, 
	                     const string &password, 
	                     const string &server, 
	                     const unsigned int port = 3306) = 0;
	virtual void disconnect() = 0;

	virtual void setTransactionMode(const TransactionMode mode) = 0;
	virtual TransactionMode getTransactionMode() const = 0;

	virtual void commit() = 0;
	virtual void rollback() = 0;

	virtual std::shared_ptr<Result> 
	execute(const string &query, const ResultMode resultMode = STORE_RESULT) = 0;

	virtual unsigned long long affectedRows() = 0;
	virtual unsigned long long lastInsertedId() = 0;
};

WEBPLUS_DATABASE_NS_END

#endif // __WEBPLUS_DATABASE_DATABASE_HPP__
