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

#ifndef REQUEST_INTERCEPTOR__HPP_
#define REQUEST_INTERCEPTOR__HPP_

#include <QWebEngineUrlRequestInterceptor>
#include <QWebEngineUrlRequestInfo>

class RequestInterceptor: public QWebEngineUrlRequestInterceptor
{
  Q_OBJECT
public:
  RequestInterceptor(QObject* parent = 0);
  virtual void interceptRequest(QWebEngineUrlRequestInfo &info) Q_DECL_OVERRIDE;
};

#endif /* REQUEST_INTERCEPTOR__HPP_ */
