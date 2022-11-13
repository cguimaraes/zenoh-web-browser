/** Brief: Zenoh Protocol Handler
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

#ifndef ZENOH_PROTOCOL_HANDLER__HPP_
#define ZENOH_PROTOCOL_HANDLER__HPP_

#include "handlers/common-handler.hpp"

extern "C" {
  #define ZENOH_LINUX 1
  #define ZENOH_C_STANDARD 99

  #include <zenoh-pico.h>
}

class ZenohHandler : public CommonHandler
{
private:
  z_owned_config_t config;

public:
  static const char* SCHEMA;

  ZenohHandler(QObject *parent = 0);
  void requestStarted(QWebEngineUrlRequestJob *request);
};

#endif /* ZENOH_PROTOCOL_HANDLER__HPP_ */
