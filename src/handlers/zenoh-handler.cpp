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

#include "handlers/zenoh-handler.hpp"
extern "C" {
  #include <zenoh-pico/net.h>
}

#include <QDebug>

const char*
ZenohHandler::SCHEMA = "zenoh";

ZenohHandler::ZenohHandler(QObject *parent)
  : CommonHandler(parent)
{
  config = zn_config_default();
  zn_properties_insert(config, ZN_CONFIG_MODE_KEY, z_string_make("client"));
  zn_properties_insert(config, ZN_CONFIG_PEER_KEY, z_string_make("tcp/127.0.0.1:7447"));
};

void
ZenohHandler::requestStarted(QWebEngineUrlRequestJob *request)
{
  qDebug() << request->requestUrl().toDisplayString(QUrl::RemoveScheme).toStdString().c_str();
  zn_session_t *s = zn_open(config);
  if(s == NULL) {
    return;
  }

  znp_start_read_task(s);
  znp_start_lease_task(s);
  zn_reply_data_array_t replies = zn_query_collect(s,
                                    zn_rname(request->requestUrl().toDisplayString(QUrl::RemoveScheme).toStdString().c_str()),
                                    "",
                                    zn_query_target_default(),
                                    zn_query_consolidation_default());

  if(replies.len > 0) {
    sendDataToRendering(request,
                        reinterpret_cast<const char*>(replies.val[0].data.value.val),
                        replies.val[0].data.value.len);
  }

  zn_reply_data_array_free(replies);
  znp_stop_lease_task(s);
  znp_stop_read_task(s);
  zn_close(s);
}

