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

#include <sstream>

#include <boost/bind.hpp>

#include <dbplus/MySql.hpp>

#include <cgiplus/Builder.hpp>
#include <cgiplus/Cgi.hpp>

#include <webplus/Dispatcher.hpp>
#include <webplus/Handler.hpp>

// When you need to run only one test, compile only this file with the
// STAND_ALONE flag.
#ifdef STAND_ALONE
#define BOOST_TEST_MODULE WEBplus
#endif

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

class TestHandler : public webplus::Handler
{
public:
	cgiplus::Builder run(const cgiplus::Cgi cgi, dbplus::Database &database)
	{
		return cgiplus::Builder();
	}
};

class DatabaseFactory
{
public:
	dbplus::Database& create()
	{
		_database.connect("dbplus", "root", "abc123", "127.0.0.1");
		return _database;
	}

private:
	dbplus::MySql _database;
};

BOOST_AUTO_TEST_SUITE(webplusTests)

BOOST_AUTO_TEST_CASE(mustDispatchCorrectly)
{
	TestHandler handler;
	DatabaseFactory databaseFactory;
	std::ostringstream output;

	webplus::Dispatcher dispatcher(handler, output);
	dispatcher.run(boost::bind(&DatabaseFactory::create, &databaseFactory));

	BOOST_CHECK_EQUAL(output.str(), 
	                  "Content-Type: text/html" + cgiplus::Builder::EOL +
	                  "Content-Length: 0" + cgiplus::Builder::EOL +
	                  "Content-Language: en-US" + cgiplus::Builder::EOL +
	                  cgiplus::Builder::EOL);
}

BOOST_AUTO_TEST_SUITE_END()
