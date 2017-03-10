/*
 *     This file is part of jerome-status.
 *
 *    jerome-status is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    jerome-status is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with jerome-status, look at LICENSE file.  If not, see <http://www.gnu.org/licenses/>.
 */

import QtQuick 2.0
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import Jerome 1.0

Item {
    id: root
    height: 40
    Button {
        id: connectButton
        onClicked: Jerome.connectToDevice(addrField.text);
        text: qsTr("Connect")
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.leftMargin: 10
    }
    TextField {
        id: addrField
        width: 100
        text: "192.168.0.101"
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.leftMargin: 20
        anchors.rightMargin: 10
        anchors.right: parent.right
        anchors.left: connectButton.right
        Layout.preferredWidth: -1
        horizontalAlignment: Text.AlignHCenter
        inputMask: "000.000.000.000;_"
    }
}
