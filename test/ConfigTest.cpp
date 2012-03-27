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

#include <fstream>
#include <vector>

#include <webplus/Config.hpp>

// When you need to run only one test, compile only this file with the
// STAND_ALONE flag.
#ifdef STAND_ALONE
#define BOOST_TEST_MODULE WEBplus
#endif

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

const string configTestFile = "config_test.tmp";

void createFile()
{
  std::ofstream config(configTestFile.c_str());
  config << "{" << std::endl
         << "  \"firstName\" : \"John\"," << std::endl
         << "  \"lastName\"  : \"Smith\"," << std::endl
         << "  \"age\"       : 25," << std::endl
         << "  \"address\"   :" << std::endl
         << "  {" << std::endl
         << "    \"streetAddress\" : \"21 2nd Street\"," << std::endl
         << "    \"city\"          : \"New York\"," << std::endl
         << "    \"state\"         : \"NY\"," << std::endl
         << "    \"postalCode\"    : \"10021\"" << std::endl
         << "  }," << std::endl
         << "  \"phoneNumber\":" << std::endl
         << "  [" << std::endl
         << "    {" << std::endl
         << "      \"type\"   : \"home\"," << std::endl
         << "      \"number\" : \"212 555-1234\"" << std::endl
         << "    }," << std::endl
         << "    {" << std::endl
         << "      \"type\"   : \"fax\"," << std::endl
         << "      \"number\" : \"646 555-4567\"" << std::endl
         << "    }" << std::endl
         << "  ]," << std::endl
         << "  \"code\" : [1, 2, 3, 4, 5]" << std::endl
         << "}" << std::endl;
  config.close();
}

BOOST_AUTO_TEST_SUITE(webplusTests)

BOOST_AUTO_TEST_CASE(mustAccessFirstLevelValue)
{
  createFile();

  webplus::Config config(configTestFile);
  BOOST_CHECK_EQUAL(config.get("firstName"), "John");
  BOOST_CHECK_EQUAL(config.get("lastName"), "Smith");
  BOOST_CHECK_EQUAL(config.get<int>("age"), 25);
}

BOOST_AUTO_TEST_CASE(mustAccessSecondLevelValue)
{
  createFile();

  webplus::Config config(configTestFile);
  BOOST_CHECK_EQUAL(config["address"].get("streetAddress"), "21 2nd Street");
  BOOST_CHECK_EQUAL(config["address"].get("city"), "New York");
  BOOST_CHECK_EQUAL(config["address"].get("state"), "NY");
  BOOST_CHECK_EQUAL(config["address"].get("postalCode"), "10021");
}

BOOST_AUTO_TEST_CASE(mustAccessListValue)
{
  createFile();

  webplus::Config config(configTestFile);
  std::vector<int> values = config["code"].getList<int>();
  BOOST_CHECK_EQUAL(values.size(), 5);
  BOOST_CHECK_EQUAL(values[0], 1);
  BOOST_CHECK_EQUAL(values[1], 2);
  BOOST_CHECK_EQUAL(values[2], 3);
  BOOST_CHECK_EQUAL(values[3], 4);
  BOOST_CHECK_EQUAL(values[4], 5);
}

BOOST_AUTO_TEST_CASE(mustAccessComplexListValue)
{
  createFile();

  webplus::Config config(configTestFile);
  BOOST_CHECK_EQUAL(config["phoneNumber"][0].get("type"), "home");
  BOOST_CHECK_EQUAL(config["phoneNumber"][0].get("number"), "212 555-1234");
  BOOST_CHECK_EQUAL(config["phoneNumber"][1].get("type"), "fax");
  BOOST_CHECK_EQUAL(config["phoneNumber"][1].get("number"), "646 555-4567");
}

BOOST_AUTO_TEST_SUITE_END()
