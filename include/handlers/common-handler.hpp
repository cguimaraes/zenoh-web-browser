/** Brief: Common Protocol Handler 
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

#ifndef COMMON_PROTOCOL_HANDLER__HPP_
#define COMMON_PROTOCOL_HANDLER__HPP_

#include <QWebEngineUrlSchemeHandler>
#include <QWebEngineUrlRequestJob>

class CommonHandler : public QWebEngineUrlSchemeHandler
{
protected:
  CommonHandler(QObject *parent = 0);
  virtual void requestStarted(QWebEngineUrlRequestJob *request) = 0;
  void sendDataToRendering(QWebEngineUrlRequestJob *request,
                           const char* data,
                           size_t data_len);
};

#endif /* COMMON_PROTOCOL_HANDLER__HPP_ */
