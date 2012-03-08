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

#include <webplus/Session.hpp>

// When you need to run only one test, compile only this file with the
// STAND_ALONE flag.
#ifdef STAND_ALONE
#define BOOST_TEST_MODULE WEBplus
#endif

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(webplusTests)

BOOST_AUTO_TEST_CASE(mustCreateSessionCorrectly)
{
	webplus::Session session;
	string hash = session.create("1", "127.0.0.1", "abc123");

	string expected = 
		"1-4928D2920EC018ED7597B4C0285B9045C618255BCE8DFF58E9F17664335C4275";
	BOOST_CHECK_EQUAL(hash, expected);
}

BOOST_AUTO_TEST_CASE(mustCheckCreatedSessionCorrectly)
{
	webplus::Session session;
	string hash = session.create("1", "127.0.0.1", "abc123");
	BOOST_CHECK_EQUAL(session.check(hash, "127.0.0.1", "abc123"), true);
}

BOOST_AUTO_TEST_SUITE_END()
