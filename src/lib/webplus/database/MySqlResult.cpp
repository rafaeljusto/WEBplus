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
#include <webplus/database/MySqlResult.hpp>
#include <webplus/database/Result.hpp>

WEBPLUS_DATABASE_NS_BEGIN

MySqlResult::MySqlResult(MYSQL_RES *result) :
	_result(result)
{
}

MySqlResult::~MySqlResult()
{
	mysql_free_result(_result);
}

unsigned int MySqlResult::size() const
{
	return mysql_num_rows(_result);
}

bool MySqlResult::fetch()
{
	_row.clear();

	MYSQL_ROW row = mysql_fetch_row(_result);
	if (row == NULL) {
		return false;
	}

	unsigned int numberOfFields = mysql_num_fields(_result);
	for (unsigned int i = 0; i < numberOfFields; i++) {
		MYSQL_FIELD *field = mysql_fetch_field_direct(_result, i);
		_row[field->name] = (string) row[i];
	}

	return true;
}

string MySqlResult::get(const string &key) const
{
	auto result = _row.find(key);
	if (result == _row.end()) {
		throw DatabaseException(DatabaseException::UNKNOW_KEY_ERROR, 
		                        __FILE__, __FUNCTION__, __LINE__, 
		                        "Column " + key + " not found in result set");
	}

	return result->second;
}

WEBPLUS_DATABASE_NS_END
