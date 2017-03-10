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

#pragma once

#include <QObject>
#include "Jerome.h"

class JeromeLine: public QObject
{
	Q_OBJECT

	Q_PROPERTY(int lineNumber READ lineNumber)
	Q_PROPERTY(bool value READ value NOTIFY valueChanged)
	Q_PROPERTY(bool typeIn READ in NOTIFY inChanged)
public:
	explicit JeromeLine(Jerome::line_t lineNumber, QObject * parent = nullptr);
	JeromeLine(JeromeLine&&) = default;
	JeromeLine(const JeromeLine&) = delete;

	Jerome::line_t lineNumber() const { return lineNumber_; }

	bool value() const { return value_; }
	bool in() const { return in_; }

signals:
	void valueChanged();
	void inChanged();

public slots:
	void onValueChanged(Jerome::Line::Value value);
	void onTypeChanged(Jerome::Line::Type type);

private:
	Jerome::line_t lineNumber_;
	bool value_;
	bool in_;
};
