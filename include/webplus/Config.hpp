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

#ifndef __WEBPLUS_CONFIG_HPP__
#define __WEBPLUS_CONFIG_HPP__

#include <string>
#include <vector>

#include <boost/optional.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include "Webplus.hpp"

using std::string;

WEBPLUS_NS_BEGIN

class Config
{
public:
  Config()
  {
  }

  Config(const string &filename)
  {
    read(filename);
  }

  Config& operator[](const string &section)
  {
    using namespace boost::property_tree;

    if (boost::optional<ptree&> child = _node.get_child_optional(section)) {
      _node = *child;
    }

    return *this;
  }

  Config& operator[](const int index)
  {
    using namespace boost::property_tree;
    int i = 0;

    for(const ptree::value_type &child : _node.get_child("")) {
      if (i == index) {
        _node = child.second;
        break;
      }

      i++;
    }

    return *this;
  }

  void read(const string &filename)
  {
    read_json(filename, _root);
    _node = _root;
  }

  template<class T = string>
  boost::optional<T> get(const string &field)
  {
    boost::optional<T> value = _node.get_optional<T>(field);
    _node = _root;
    return value;
  }

  template<class T = string>
  std::vector<T> getList()
  {
    using namespace boost::property_tree;
    std::vector<T> values;

    for(const ptree::value_type &child : _node.get_child("")) {
      values.push_back(child.second.get_value<T>());
    }

    _node = _root;
    return values;
  }

private:
  boost::property_tree::ptree _node;
  boost::property_tree::ptree _root;
};

WEBPLUS_NS_END

#endif // __WEBPLUS_CONFIG_HPP__
