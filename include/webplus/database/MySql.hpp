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

#ifndef __WEB_PLUS_DATABASE_MYSQL_HPP__
#define __WEB_PLUS_DATABASE_MYSQL_HPP__

extern "C" {
#include <mysql/mysql.h>
}

#include <webplus/Webplus.hpp>

#include "RelationalDatabase.hpp"

WEBPLUS_DATABASE_NS_BEGIN

/*! \class Mysql
 *  \brief MySQL client interface.
 *
 * Connect to MySQL database.
 */
class MySql : public RelationalDatabase
{
public:
	MySql();
	~MySql();

	void connect(const string &database, 
	             const string &user, 
	             const string &password, 
	             const string &server, 
	             const unsigned int port = 3306);
	void disconnect();

	void setTransactionMode(const TransactionMode mode);
	TransactionMode getTransactionMode() const;

	void commit();
	void rollback();

	boost::shared_ptr<Result>
	execute(const string &query, const ResultMode resultMode = STORE_RESULT);

	unsigned long long getAffectedRows();
	unsigned long long getLastInsertedId();

private:
	MYSQL _mysql;
	TransactionMode _transactionMode;
};

WEBPLUS_DATABASE_NS_END

#endif // __WEB_PLUS_DATABASE_MYSQL_HPP__
