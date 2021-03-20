/** Brief: Request Interceptor
 *  Copyright (C) 2021  Carlos Guimarães <carlos.em.guimaraes@gmail.com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "request_interceptor.hpp"

RequestInterceptor::RequestInterceptor(QObject *parent)
  : QWebEngineUrlRequestInterceptor(parent)
{ }

void RequestInterceptor::interceptRequest(QWebEngineUrlRequestInfo &info)
{
  info.setHttpHeader("accept-encoding", "gzip;q=0,deflate;q=0");
}

#include "moc_request_interceptor.cpp"
