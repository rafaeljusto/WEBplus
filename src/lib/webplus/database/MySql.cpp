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

#include <webplus/database/DatabaseException.hpp>
#include <webplus/database/MySql.hpp>
#include <webplus/database/MySqlResult.hpp>

WEBPLUS_DATABASE_NS_BEGIN

MySql::MySql() :
	_transactionMode(AUTO_COMMIT)
{
}

MySql::~MySql()
{
	disconnect();
}

void MySql::connect(const string &database,
                    const string &user,
                    const string &password,
                    const string &server,
                    const unsigned int port)
{
	if (mysql_init(&_mysql) == NULL) {
		throw DatabaseException(DatabaseException::CONNECTION_ERROR, 
		                        __FILE__, __FUNCTION__, __LINE__, 
		                        mysql_error(&_mysql));
	}

	if (mysql_real_connect(&_mysql,
	                       server.c_str(), 
	                       user.c_str(), 
	                       password.c_str(), 
	                       database.c_str(), 
	                       port, NULL, 0) != &_mysql) {
		throw DatabaseException(DatabaseException::CONNECTION_ERROR, 
		                        __FILE__, __FUNCTION__, __LINE__, 
		                        mysql_error(&_mysql));
	}

	setTransactionMode(_transactionMode);
}

void MySql::disconnect()
{
	mysql_close(&_mysql);
}

void MySql::setTransactionMode(const TransactionMode mode)
{
	_transactionMode = _transactionMode != mode ? mode : _transactionMode;

	switch(_transactionMode) {
	case MANUAL_COMMIT:
		if (mysql_autocommit(&_mysql, 0) != 0) {
			throw DatabaseException(DatabaseException::STATE_CHANGE_ERROR, 
			                        __FILE__, __FUNCTION__, __LINE__, 
			                        mysql_error(&_mysql));
		}
		break;
	case AUTO_COMMIT:
		if (mysql_autocommit(&_mysql, 1) != 0) {
			throw DatabaseException(DatabaseException::STATE_CHANGE_ERROR, 
			                        __FILE__, __FUNCTION__, __LINE__, 
			                        mysql_error(&_mysql));
		}
		break;
	}
}

MySql::TransactionMode MySql::getTransactionMode() const
{
	return _transactionMode;
}

void MySql::commit()
{
	if (mysql_commit(&_mysql) != 0) {
		throw DatabaseException(DatabaseException::TRANSACTION_ERROR, 
		                        __FILE__, __FUNCTION__, __LINE__, 
		                        mysql_error(&_mysql));
	}
}

void MySql::rollback()
{
	if (mysql_rollback(&_mysql) != 0) {
		throw DatabaseException(DatabaseException::TRANSACTION_ERROR, 
		                        __FILE__, __FUNCTION__, __LINE__, 
		                        mysql_error(&_mysql));
	}
}

boost::shared_ptr<Result> 
MySql::execute(const string &query, const ResultMode resultMode)
{
	if (mysql_real_query(&_mysql, query.c_str(), query.size()) != 0) {
		throw DatabaseException(DatabaseException::EXECUTION_ERROR, 
		                        __FILE__, __FUNCTION__, __LINE__, 
		                        mysql_error(&_mysql));
	}

	if (mysql_field_count(&_mysql) == 0) {
		return boost::shared_ptr<Result>();
	}

	MYSQL_RES *result = NULL;
	
	switch(resultMode) {
	case USE_RESULT:
		result = mysql_use_result(&_mysql);
		break;
	case STORE_RESULT:
		result = mysql_store_result(&_mysql);
		break;
	}

	if (result == NULL) {
		throw DatabaseException(DatabaseException::RESULT_ERROR, 
		                        __FILE__, __FUNCTION__, __LINE__, 
		                        mysql_error(&_mysql));
	}

	return boost::shared_ptr<Result>(new MySqlResult(result));
}

unsigned long long MySql::getAffectedRows()
{
	return mysql_affected_rows(&_mysql);
}

unsigned long long MySql::getLastInsertedId()
{
	return mysql_insert_id(&_mysql);
}

WEBPLUS_DATABASE_NS_END
