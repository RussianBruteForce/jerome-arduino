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

#include "Jerome.h"

#include <functional>

#include <QAbstractSocket>
#include <QTcpSocket>
#include <QVector>
#include <QList>

Jerome::Jerome(QObject *parent):
        QObject(parent),
        socket{new QTcpSocket(this)},
        lines{LINE_COUNT}
{
	using namespace std::placeholders;
	auto value_confirmator = std::bind(&Jerome::valueConfirmator, this, _1, _2);
	valueConfirmationQueue = std::make_unique<ValueConfirmationQueue>(value_confirmator);

	auto type_confirmator = std::bind(&Jerome::typeConfirmator, this, _1, _2);
	typeConfirmationQueue = std::make_unique<TypeConfirmationQueue>(type_confirmator);

	connect(socket, &QTcpSocket::connected, this, &Jerome::onSocketConnected);
	connect(socket, &QTcpSocket::disconnected, this, &Jerome::onSocketDisconnected);
	connect(socket, &QTcpSocket::readyRead, this, &Jerome::onSocketReadyRead);
	connect(socket, static_cast<void(QAbstractSocket::*)(QAbstractSocket::SocketError)>(&QAbstractSocket::error), this, &Jerome::onSocketError);
	connect(this, &Jerome::lineTypeChanged, this, &Jerome::onLineTypeChanged);
	connect(this, &Jerome::lineValueChanged, this, &Jerome::onLineValueChanged);
}

void Jerome::print(const QVector<Jerome::Line> &lines)
{
	auto c = 0;

	for (const Line& l : lines) {
		qDebug() << "line: " << c++ << "\t" << l;
	}
}

void Jerome::connectToDevice(const QString &host, uint16_t port)
{
	socket->connectToHost(host, port);
}

void Jerome::check() const
{
	send(QByteArray("$KE\r\n"));
}

void Jerome::high(line_t line)
{
	qDebug() << "high " << line;
	valueConfirmationQueue->enqueue(line, Jerome::Line::Value::HIGH);
	command("WR", toJeromeLineNumber(line), "1");
}

void Jerome::low(line_t line)
{
	qDebug() << "low " << line;
	valueConfirmationQueue->enqueue(line, Jerome::Line::Value::LOW);
	command("WR", toJeromeLineNumber(line), "0");
}

void Jerome::setIn(Jerome::line_t line)
{
	qDebug() << "set in " << line;
	typeConfirmationQueue->enqueue(line, Jerome::Line::Type::IN);
	command("IO", "SET", toJeromeLineNumber(line), "1");
}

void Jerome::setOut(Jerome::line_t line)
{
	qDebug() << "set out " << line;
	typeConfirmationQueue->enqueue(line, Jerome::Line::Type::OUT);
	command("IO", "SET", toJeromeLineNumber(line), "0");
}

void Jerome::setLine(Jerome::line_t line, Jerome::Line::Value value)
{
	switch (value) {
	case Line::Value::HIGH:
		high(line);
		break;
	case Line::Value::LOW:
		low(line);
		break;
	default:
		throw JeromeWrongArgumentError("wrong value");
		break;
	}
}

void Jerome::setLine(Jerome::line_t line, Jerome::Line::Type type)
{
	switch (type) {
	case Line::Type::IN:
		setIn(line);
		break;
	case Line::Type::OUT:
		setOut(line);
		break;
	default:
		throw JeromeWrongArgumentError("wrong type");
		break;
	}
}

void Jerome::onSocketConnected()
{
	updateState();
	emit connected();
}

void Jerome::onSocketDisconnected()
{
	emit disconnected();
}

void Jerome::onSocketReadyRead()
{
	QList<QByteArray> answers = socket->readAll().split('#');
	qDebug() << "onSocketReadyRead" << answers;
	for (auto&& answer: answers)
		handleAnswer(answer);
}

void Jerome::onSocketError(QAbstractSocket::SocketError socketError)
{
	Q_UNUSED(socketError);
	throw JeromeConnectionError(socket->errorString().toStdString());
}

void Jerome::onLineTypeChanged(Jerome::line_t line, Jerome::Line::Type type)
{
#define LINE_TC(L__) \
	case L__: emit line##L__##TypeChanged(type); break;

	switch (line) {
	LINE_TC(0);
	LINE_TC(1);
	LINE_TC(2);
	LINE_TC(3);
	LINE_TC(4);
	LINE_TC(5);
	LINE_TC(6);
	LINE_TC(7);
	LINE_TC(8);
	LINE_TC(9);
	LINE_TC(10);
	LINE_TC(11);
	LINE_TC(12);
	LINE_TC(13);
	LINE_TC(14);
	LINE_TC(15);
	LINE_TC(16);
	LINE_TC(17);
	LINE_TC(18);
	LINE_TC(19);
	LINE_TC(20);
	LINE_TC(21);
	default:
		break;
	}
#undef LINE_TC
}

void Jerome::onLineValueChanged(Jerome::line_t line, Jerome::Line::Value value)
{
#define LINE_VC(L__) \
	case L__: emit line##L__##ValueChanged(value); break;

	switch (line) {
	LINE_VC(0);
	LINE_VC(1);
	LINE_VC(2);
	LINE_VC(3);
	LINE_VC(4);
	LINE_VC(5);
	LINE_VC(6);
	LINE_VC(7);
	LINE_VC(8);
	LINE_VC(9);
	LINE_VC(10);
	LINE_VC(11);
	LINE_VC(12);
	LINE_VC(13);
	LINE_VC(14);
	LINE_VC(15);
	LINE_VC(16);
	LINE_VC(17);
	LINE_VC(18);
	LINE_VC(19);
	LINE_VC(20);
	LINE_VC(21);
	default:
		break;
	}
#undef LINE_VC
}

void Jerome::valueConfirmator(Jerome::line_t line, Jerome::Line::Value value)
{
	auto& l = lines[line];
	l.doIfNot(value, [&] () {
		l.value = value;
		emit lineValueChanged(line, value);
	});
}

void Jerome::typeConfirmator(Jerome::line_t line, Jerome::Line::Type type)
{
	auto& l = lines[line];
	l.doIfNot(type, [&] () {
		l.type = type;
		emit lineTypeChanged(line, type);
		updateState();
	});
}

void Jerome::updateState()
{
	command("RID", "IN");
	command("RID", "OUT");
}

void Jerome::handleAnswer(const QByteArray &data)
{
	auto answer = data.split(',');
	qDebug() << "handleAnswer" << answer;
	if (answer.size() == 1) {
		handleOneArg(answer.first());
	} else {
		auto arg = answer.begin();
		auto cmd = [&arg] (QByteArray&& str) { return arg->endsWith(str.toUpper()); };
		if (cmd("RID")) {
			++arg;
			auto type = *arg == "IN" ? Line::Type::IN : Line::Type::OUT;
			++arg;
			handleRID(type, *arg);
		} else if (cmd("WR")) {
			++arg;
			confirm(*arg, valueConfirmationQueue);
		} else if (cmd("IO")) {
			++arg;
			if (cmd("SET")) {
				++arg;
				confirm(*arg, typeConfirmationQueue);
			}
		}
	}
}

void Jerome::handleOneArg(const QByteArray& answer)
{
	if (answer.endsWith("OK\r\n")) {
		emit ok();
	} else if (answer == "ERR\r\n") {
		throw JeromeDeviceError("unknown");
	}
}

void Jerome::handleRID(Jerome::Line::Type type, const QByteArray &answer)
{
	for (auto i = 0; i < lines.size(); ++i) {
		auto value = Line::Value::UNKNOWN;
		if (answer[i] == '1') {
			value = Line::Value::HIGH;
		} else if (answer[i] == '0') {
			value = Line::Value::LOW;
		}

		if (value != Line::Value::UNKNOWN) {
			auto& line = lines[i];
			line.doIfNot(type, [&] () {
				line.type = type;
				emit lineTypeChanged(i, type);
			});
			line.doIfNot(value, [&] () {
				line.type = type;
				emit lineValueChanged(i, value);
			});
		}
	}
}

QByteArray Jerome::toJeromeLineNumber(Jerome::line_t line)
{
	return QByteArray::number(line + 1);
}
