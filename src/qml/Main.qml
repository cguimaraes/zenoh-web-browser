/** Brief: QML Layout Definition
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

import QtQuick 2.3
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3
import QtQuick.Window 2.2
import QtWebEngine 1.2

import "Constants.js" as Constants

ApplicationWindow {
  id: appWindow
  width: 640
  height: 480
  visible: false

  MessageDialog {
    id: dialog
    title: "Disclaimer"
    text: Constants.disclaimer
    detailedText: Constants.license
    standardButtons: StandardButton.Yes | StandardButton.No
    modality: Qt.WindowModal
    Component.onCompleted: visible = true
    onNo: { Qt.quit(); }
    onYes: { appWindow.visible = true; }
  }

  menuBar: MenuBar {
    Menu {
      title: "About"
      MenuItem {
        text: "Disclaimer"
        onTriggered: {
          appWindow.visible = false;
          dialog.visible = true;
        }
      }
    }
  }

  ColumnLayout {
    anchors.fill: parent
    spacing: 6

    TextField {
      id: tf_inputUrl
      placeholderText: qsTr("Enter URL here...")
      Layout.alignment: Qt.AlignCenter
      Layout.fillWidth: true
      onAccepted: {
        wev_page.url = tf_inputUrl.text;
      }
    }

    WebEngineView {
      id: wev_page
      Layout.alignment: Qt.AlignBottom
      Layout.fillWidth: true
      Layout.fillHeight: true
      settings.javascriptEnabled: false
      onLoadingChanged: {
        if(loadRequest.status == WebEngineView.LoadSucceededStatus) {
          tf_inputUrl.text = loadRequest.url;
        }
      }
    }
  }
}
