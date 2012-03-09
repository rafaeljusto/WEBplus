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

#include <webplus/AuthDispatcher.hpp>
#include <webplus/Session.hpp>

WEBPLUS_NS_BEGIN

AuthDispatcher::AuthDispatcher(Handler &handler, std::ostream &output) :
	_dispatcher(handler, output),
	_output(&output)
{
}

void AuthDispatcher::run(DatabaseFactory databaseFactory,
                         RetrieveSessionName retrieveSessionName,
                         RetrieveSessionSecret retrieveSessionSecret,
                         RedirectUnlogged redirectUnlogged)
{
	cgiplus::Cgi cgi;
	string cookieData = cgi(retrieveSessionName());
	string address = cgi.getRemoteAddress();
	string secret = retrieveSessionSecret();

	Session session;
	if (session.check(cookieData, address, secret) == false) {
		*_output << redirectUnlogged().build();
	
	} else {
		_dispatcher.run(databaseFactory, cgi);
	}
}

WEBPLUS_NS_END
