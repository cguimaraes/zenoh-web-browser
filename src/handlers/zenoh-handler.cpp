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

#include <QDebug>
#include <unistd.h>

typedef struct {
  QWebEngineUrlRequestJob *request;
  ZenohHandler *handler;
} __Callback_Context;

void reply_dropper(void *ctx) {
    (void)(ctx);
}

void reply_handler(z_owned_reply_t *reply, void *ctx) {
    __Callback_Context *context = static_cast<__Callback_Context *>(ctx);

    if (z_reply_is_ok(reply)) {
        z_sample_t sample = z_reply_ok(reply);
//        char *keystr = z_keyexpr_to_string(sample.keyexpr);
//        printf(">> Received ('%s': '%.*s')\n", keystr, (int)sample.payload.len, sample.payload.start);
        context->handler->sendDataToRendering(context->request,
                            reinterpret_cast<const char*>(sample.payload.start),
                            sample.payload.len);

//        free(keystr);
    } else {
//        printf(">> Received an error\n");
    }
}

const char*
ZenohHandler::SCHEMA = "zenoh";

ZenohHandler::ZenohHandler(QObject *parent)
  : CommonHandler(parent)
{ };

void
ZenohHandler::requestStarted(QWebEngineUrlRequestJob *request)
{
  qDebug() << request->requestUrl().toDisplayString(QUrl::RemoveScheme).toStdString().c_str();

  config = z_config_default();
  zp_config_insert(z_config_loan(&config), Z_CONFIG_MODE_KEY, z_string_make("client"));
  zp_config_insert(z_config_loan(&config), Z_CONFIG_PEER_KEY, z_string_make("tcp/127.0.0.1:7447"));

  z_owned_session_t s = z_open(z_config_move(&config));
  if(!z_session_check(&s)) {
    return;
  }

  zp_start_read_task(z_session_loan(&s), NULL);
  zp_start_lease_task(z_session_loan(&s), NULL);

  __Callback_Context ctx = {.request = request, .handler = this};

  z_get_options_t opts = z_get_options_default();
  opts.target = Z_QUERY_TARGET_ALL;
  z_owned_closure_reply_t callback = z_closure_reply(reply_handler, reply_dropper, &ctx);
  if (z_get(z_session_loan(&s), z_keyexpr(request->requestUrl().toDisplayString(QUrl::RemoveScheme).toStdString().c_str()), "", z_closure_reply_move(&callback), &opts) < 0) {
    qDebug() << "Unable to send query.\n"; 
  }

  sleep(5);

  zp_stop_lease_task(z_session_loan(&s));
  zp_stop_read_task(z_session_loan(&s));
  z_close(z_session_move(&s));
}

