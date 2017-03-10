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

import QtQuick 2.4
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3

Item {
    property bool typeIn: false
    property alias value: valueSwitch.checked
    property alias idText: idLabel.text

    width: 200
    height: 40

    Item {
        id: rowLayout
        anchors.fill: parent

        Text {
            id: idLabel
            text: qsTr("UNKN")
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 0
            font.pixelSize: 16
        }

        Text {
            id: typeLabel
            text: typeIn ? "IN" : "OUT"
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: 16
        }

        Switch {
            id: valueSwitch
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            enabled: !typeIn
            autoExclusive: false
            checkable: false
        }
    }
}
