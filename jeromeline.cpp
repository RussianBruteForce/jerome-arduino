/*
 *     This file is part of jerome-arduino.
 *
 *    jerome-arduino is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    jerome-arduino is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with jerome-arduino, look at LICENSE file.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "jeromeline.h"

JeromeLine::JeromeLine(Jerome::line_t lineNumber, QObject *parent):
        QObject(parent),
        lineNumber_{lineNumber}
{
	qDebug() << "line created: " << lineNumber;
}

void JeromeLine::onValueChanged(Jerome::Line::Value value)
{
	switch (value) {
	case Jerome::Line::Value::HIGH:
		value_ = true;
		break;
	case Jerome::Line::Value::LOW:
	default:
		value_ = false;
		break;
	}
	emit valueChanged();
}

void JeromeLine::onTypeChanged(Jerome::Line::Type type)
{
	switch (type) {
	case Jerome::Line::Type::IN:
		in_ = true;
		onValueChanged(Jerome::Line::Value::LOW);
		break;
	case Jerome::Line::Type::OUT:
		in_ = false;
		break;
	default:
		break;
	}
	emit inChanged();
}
