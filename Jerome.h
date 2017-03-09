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
#include <QString>

class Jerome: public QObject
{
	Q_OBJECT

public:
	Jerome(QObject* parent);
	Jerome(const Jerome&) = delete;
	Jerome(Jerome&&) = default;
};

