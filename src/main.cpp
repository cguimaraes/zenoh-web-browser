/** Brief: Initial Program Execution Point
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

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QWebEngineProfile>

#include <qtwebengineglobal.h>

#include "request_interceptor.hpp"
#include "handlers/zenoh-handler.hpp"

int
main(int argc, char* argv[])
{
  QGuiApplication app(argc, argv);

  QtWebEngine::initialize();
  QWebEngineProfile *defaultProfile = QWebEngineProfile::defaultProfile();

  RequestInterceptor *interceptor = new RequestInterceptor();
  defaultProfile->setRequestInterceptor(interceptor);

  // No cache by default
  defaultProfile->setHttpCacheType(QWebEngineProfile::NoCache);

  // Register handlers
  ZenohHandler* zenohHandler = new ZenohHandler(NULL);
  defaultProfile->installUrlSchemeHandler(ZenohHandler::SCHEMA, zenohHandler);

  QQmlApplicationEngine qae_engine;
  qae_engine.load(QUrl("qrc:/Main.qml"));

  return app.exec();
}
