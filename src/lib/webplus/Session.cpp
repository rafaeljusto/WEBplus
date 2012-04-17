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

extern "C" {
#include <openssl/sha.h>
}

#include <iomanip>
#include <sstream>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>

#include <webplus/Session.hpp>

WEBPLUS_NS_BEGIN

string Session::create(const string &id, const string &ip, const string &secret)
{
  return id + "-" + buildHash(id, ip, secret);
}

bool Session::check(const string &data, const string &ip, const string &secret)
{
  std::vector<string> dataParts;
  boost::split(dataParts, data, boost::is_any_of("-"));

  if (dataParts.size() != 2) {
    return false;
  }

  string id = dataParts[0];
  string hash = dataParts[1];
  string calculatedHash = buildHash(id, ip, secret);

  return (hash == calculatedHash);
}

string Session::buildHash(const string &id,
                          const string &ip,
                          const string &secret)
{
  string data = id + ip + secret;
  auto rawData = reinterpret_cast<const unsigned char*>(data.c_str());

  unsigned char hash[SHA256_DIGEST_LENGTH];
  SHA256(rawData, data.size(), hash);

  return toHexadecimal(hash, SHA256_DIGEST_LENGTH);
}

string Session::toHexadecimal(const unsigned char *data, unsigned int size)
{
  std::stringstream output;
  output << std::hex;

  for (unsigned int i = 0; i < size; i++) {
    output << std::setw(2) << std::setfill('0')
           << static_cast<unsigned>(data[i]);
  }

  return boost::to_upper_copy(output.str());
}

WEBPLUS_NS_END
