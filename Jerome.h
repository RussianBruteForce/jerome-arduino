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

#include <string>
#include <functional>
#include <memory>

#include <QObject>
#include <QString>
#include <QVector>
#include <QQueue>
#include <QTcpSocket>

struct JeromeError: public std::runtime_error {
	explicit JeromeError(std::string what_str):
	        std::runtime_error(what_str) {}
};

struct JeromeConnectionError: public JeromeError {
	explicit JeromeConnectionError(std::string what_str):
	        JeromeError("connection: " + what_str) {}
};

struct JeromeDeviceError: public JeromeError {
	explicit JeromeDeviceError(std::string what_str):
	        JeromeError("device: " + what_str) {}
};

struct JeromeWrongArgumentError: public JeromeError {
	explicit JeromeWrongArgumentError(std::string what_str):
	        JeromeError("wrong argument: " + what_str) {}
};

class Jerome: public QObject
{
public:
	using line_t = uint_fast8_t;
	struct Line {
		enum class Type {
			OUT,
			IN
		};
		enum class Value {
			UNKNOWN = -1,
			LOW,
			HIGH,
			LAST_LOW,
			LAST_HIGH
		};

		Type type{Type::OUT};
		Value value{Value::LOW};

		Type reverse(Type t) {
			return t == Type::IN ? Type::OUT : Type::IN;
		}

		Value reverse(Value l) {
			switch (l) {
			case Value::LOW:
				return Value::HIGH;
				break;
			case Value::HIGH:
				return Value::LOW;
				break;
			case Value::LAST_LOW:
				return Value::LAST_HIGH;
				break;
			case Value::LAST_HIGH:
				return Value::LAST_LOW;
				break;
			default:
				return Value::UNKNOWN;
				break;
			}
		}

		void doIf(Value v, auto f) {
			if (value == v) f();
		}

		void doIf(Type t, auto f) {
			if (type == t) f();
		}

		template<class T, class F>
		void doIfNot(T v, F&& f) {
			doIf(reverse(v), std::forward<F>(f));
		}

		QString typeStr() const {
			QString buf;
			switch (type) {
			case Line::Type::IN:
				buf = QStringLiteral("IN");
				break;
			case Line::Type::OUT:
				buf = "IN";
				break;
			default:
				break;
			}
			return buf;
		}

		QString valueStr() const {
			QString buf;
			switch (value) {
			case Line::Value::UNKNOWN:
				buf = QStringLiteral("UNKNOWN");
				break;
			case Line::Value::HIGH:
				buf = QStringLiteral("HIGH");
				break;
			case Line::Value::LOW:
				buf = QStringLiteral("LOW");
				break;
			case Line::Value::LAST_HIGH:
				buf = QStringLiteral("LAST HIGH");
				break;
			case Line::Value::LAST_LOW:
				buf = QStringLiteral("LAST LOW");
				break;
			default:
				break;
			}
			return buf;
		}

		operator QString() const {
			return "type: " + typeStr() + " value: " + valueStr();
		}
	};

private:
	Q_OBJECT

	static constexpr uint16_t DEFAULT_PORT = 2424;
	static constexpr line_t LINE_COUNT = 22;

	template<class K, class T>
	class ConfirmationQueue {
		struct Element { K key; T value; };
	public:
		explicit ConfirmationQueue(std::function<void(K, T)> f):
		        confirm(f) {}

		void enqueue(K key, T value) {
			queue.enqueue({key, value});
		}

		void dequeue() {
			if (queue.isEmpty())
				throw JeromeDeviceError("unexpected confirmation");
			auto e = queue.dequeue();
			confirm(e.key, e.value);
		}

	private:
		std::function<void(K, T)> confirm;
		QQueue<Element> queue;
	};

public:
	explicit Jerome(QObject* parent = nullptr);
	Jerome(const Jerome&) = delete;
	Jerome(Jerome&&) = default;

	const QVector<Line>& getLines() const { return lines; }

	static void print(const QVector<Line>& lines);
	void print() const { print(getLines()); }
	bool autoUpdate() { return autoUpdate_; }

#define LINE(L__) \
	Line::Type line##L__##Type() const { return lines[L__].type; } \
	Line::Value line##L__##Value() const { return lines[L__].value; }

	LINE(0)
	LINE(1)
	LINE(2)
	LINE(3)
	LINE(4)
	LINE(5)
	LINE(6)
	LINE(7)
	LINE(8)
	LINE(9)
	LINE(10)
	LINE(11)
	LINE(12)
	LINE(13)
	LINE(14)
	LINE(15)
	LINE(16)
	LINE(17)
	LINE(18)
	LINE(19)
	LINE(20)
	LINE(21)
	LINE(22)
#undef LINE

signals:
	void connected();
	void disconnected();
	void ok();
	void lineTypeChanged(line_t line, Line::Type type);
	void lineValueChanged(line_t line, Line::Value value);

#define LINE_CHANGED(L__) \
	void line##L__##TypeChanged(Line::Type type); \
	void line##L__##ValueChanged(Line::Value value);

	LINE_CHANGED(0)
	LINE_CHANGED(1)
	LINE_CHANGED(2)
	LINE_CHANGED(3)
	LINE_CHANGED(4)
	LINE_CHANGED(5)
	LINE_CHANGED(6)
	LINE_CHANGED(7)
	LINE_CHANGED(8)
	LINE_CHANGED(9)
	LINE_CHANGED(10)
	LINE_CHANGED(11)
	LINE_CHANGED(12)
	LINE_CHANGED(13)
	LINE_CHANGED(14)
	LINE_CHANGED(15)
	LINE_CHANGED(16)
	LINE_CHANGED(17)
	LINE_CHANGED(18)
	LINE_CHANGED(19)
	LINE_CHANGED(20)
	LINE_CHANGED(21)
#undef LINE_CHANGED

public slots:
	void connectToDevice(const QString &host, uint16_t port = DEFAULT_PORT);
	void setAutoUpdate(bool status);
	void check() const;
	void manualUpdate() { print(); updateState(); }
	void high(line_t line);
	void low(line_t line);
	void setIn(line_t line);
	void setOut(line_t line);
	void setLine(line_t line, Line::Value value);
	void setLine(line_t line, Line::Type type);

private slots:
	void onSocketConnected();
	void onSocketDisconnected();
	void onSocketReadyRead();
	void onSocketError(QAbstractSocket::SocketError socketError);
	void onLineTypeChanged(line_t line, Line::Type type);
	void onLineValueChanged(line_t line, Line::Value value);

private:
	QTcpSocket *socket;
	QVector<Line> lines;
	using TypeConfirmationQueue = ConfirmationQueue<line_t, Line::Type>;
	using ValueConfirmationQueue = ConfirmationQueue<line_t, Line::Value>;
	std::unique_ptr<TypeConfirmationQueue> typeConfirmationQueue;
	std::unique_ptr<ValueConfirmationQueue> valueConfirmationQueue;
	bool autoUpdate_{true};

	void valueConfirmator(line_t line, Line::Value value);
	void typeConfirmator(line_t line, Line::Type type);

	void updateState();


	void handleAnswer(const QByteArray & data);

	void handleOneArg(const QByteArray &answer);

	void handleRID(Jerome::Line::Type type, const QByteArray& answer);

	static QByteArray toJeromeLineNumber(line_t line);

	template <class Q>
	static void confirm(const QByteArray& status, Q&& queue) {
		if (status.startsWith("OK")) {
			queue->dequeue();
		} else {
			throw JeromeDeviceError("unknown status " + status.toStdString());
		}
	}

	template <class T>
	static QByteArray $commandHelper(T&& t) {
		return QByteArray{std::forward<T>(t)};
	}

	template <class T, class... Rest>
	static QByteArray $commandHelper(T t, Rest... rest) {
		return QByteArray{std::forward<T>(t)} + ',' + $commandHelper(rest...);
	}

	template <class ...T>
	void command(T&&... t) {
		QByteArray data = $commandHelper(t...);
		data.prepend("$KE,");
		data.append("\r\n");
		qDebug() << data;
		send(std::move(data));
	}

	template<class T>
	void send(T&& data...) const {
		qDebug() << "sending: '" << data << "'";
		socket->write(std::forward<T>(data));
		socket->flush();
	}
};

