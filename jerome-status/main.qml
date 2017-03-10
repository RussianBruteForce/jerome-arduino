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

import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import Jerome 1.0

ApplicationWindow {
    id: root
    visible: true
    width: 480
    height: 600
    title: qsTr("Jerome Status")

    Item {
        id: ui
        anchors.rightMargin: 10
        anchors.leftMargin: 10
        anchors.bottomMargin: 10
        anchors.topMargin: 10
        visible: !footerImp.enabled
        anchors.fill: parent

        Item {
            id: item1
            anchors.fill: parent

            ColumnLayout {
                id: c0
                anchors.top: parent.top
                Line {
                    lineNumber: 0
                    value: Line0.value
                    typeIn: Line0.typeIn
                }
                Line {
                    lineNumber: 1
                    value: Line1.value
                    typeIn: Line1.typeIn
                }
                Line {
                    lineNumber: 2
                    value: Line2.value
                    typeIn: Line2.typeIn
                }
                Line {
                    lineNumber: 3
                    value: Line3.value
                    typeIn: Line3.typeIn
                }
                Line {
                    lineNumber: 4
                    value: Line4.value
                    typeIn: Line4.typeIn
                }
                Line {
                    lineNumber: 5
                    value: Line5.value
                    typeIn: Line5.typeIn
                }
                Line {
                    lineNumber: 6
                    value: Line6.value
                    typeIn: Line6.typeIn
                }
                Line {
                    lineNumber: 7
                    value: Line7.value
                    typeIn: Line7.typeIn
                }
                Line {
                    lineNumber: 8
                    value: Line8.value
                    typeIn: Line8.typeIn
                }
                Line {
                    lineNumber: 9
                    value: Line9.value
                    typeIn: Line9.typeIn
                }
                Line {
                    lineNumber: 10
                    value: Line10.value
                    typeIn: Line10.typeIn
                }
            }

            ColumnLayout {
                id: c1
                anchors.right: parent.right
                anchors.top: parent.top
                Line {
                    lineNumber: 11
                    value: Line11.value
                    typeIn: Line11.typeIn
                }
                Line {
                    lineNumber: 12
                    value: Line12.value
                    typeIn: Line12.typeIn
                }
                Line {
                    lineNumber: 13
                    value: Line13.value
                    typeIn: Line13.typeIn
                }
                Line {
                    lineNumber: 14
                    value: Line14.value
                    typeIn: Line14.typeIn
                }
                Line {
                    lineNumber: 15
                    value: Line15.value
                    typeIn: Line15.typeIn
                }
                Line {
                    lineNumber: 16
                    value: Line16.value
                    typeIn: Line16.typeIn
                }
                Line {
                    lineNumber: 17
                    value: Line17.value
                    typeIn: Line17.typeIn
                }
                Line {
                    lineNumber: 18
                    value: Line18.value
                    typeIn: Line18.typeIn
                }
                Line {
                    lineNumber: 19
                    value: Line19.value
                    typeIn: Line19.typeIn
                }
                Line {
                    lineNumber: 20
                    value: Line20.value
                    typeIn: Line20.typeIn
                }
                Line {
                    lineNumber: 21
                    value: Line21.value
                    typeIn: Line21.typeIn
                }
            }
        }
    }

    Connections {
        target: Jerome
        onConnected: {
            footerImp.enabled = false
        }
        onDisconnected: {
            footerImp.enabled = true
        }
    }

    footer: Footer {
        signal x()
        id: footerImp
    }
}
