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

#include <functional>

#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <Jerome.h>
#include <jeromeline.h>

static Jerome jerome;

static QObject* jerome_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
	Q_UNUSED(engine)
	Q_UNUSED(scriptEngine)
	return &jerome;
}

static QObject* line_provider_helper(Jerome::line_t lineNumber, QQmlEngine *engine, QJSEngine *scriptEngine)
{
	Q_UNUSED(scriptEngine)

	auto line = new JeromeLine{lineNumber, engine};

	engine->connect(&jerome, &Jerome::lineValueChanged, [=] (Jerome::line_t l, Jerome::Line::Value v) {
		if (l == lineNumber)
			line->onValueChanged(v);
	});

	engine->connect(&jerome, &Jerome::lineTypeChanged, [=] (Jerome::line_t l, Jerome::Line::Type t) {
		if (l == lineNumber)
			line->onTypeChanged(t);
	});

	return line;
}

namespace {
using namespace std::placeholders;
#define LINE_PROVIDER(L__) \
std::function<QObject*(QQmlEngine *engine, QJSEngine *scriptEngine)> $lp_callback##L__ \
	= std::bind(line_provider_helper, L__, _1, _2); \
static QObject* line_provider##L__(QQmlEngine *engine, QJSEngine *scriptEngine) { \
    return $lp_callback##L__(engine, scriptEngine); \
}

LINE_PROVIDER(0)
LINE_PROVIDER(1)
LINE_PROVIDER(2)
LINE_PROVIDER(3)
LINE_PROVIDER(4)
LINE_PROVIDER(5)
LINE_PROVIDER(6)
LINE_PROVIDER(7)
LINE_PROVIDER(8)
LINE_PROVIDER(9)
LINE_PROVIDER(10)
LINE_PROVIDER(11)
LINE_PROVIDER(12)
LINE_PROVIDER(13)
LINE_PROVIDER(14)
LINE_PROVIDER(15)
LINE_PROVIDER(16)
LINE_PROVIDER(17)
LINE_PROVIDER(18)
LINE_PROVIDER(19)
LINE_PROVIDER(20)
LINE_PROVIDER(21)

#undef LINE_PROVIDER
}

int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QGuiApplication app(argc, argv);

	jerome.connect(&jerome, &Jerome::connected, [] () {
		qDebug() << "connected";
	});

	jerome.connect(&jerome, &Jerome::disconnected, [] () {
		qDebug() << "disconnected";
	});

//	jerome.connectToDevice("192.168.0.101");
	qmlRegisterSingletonType<Jerome>("Jerome", 1, 0, "Jerome", jerome_provider);

#define REG_LINE(L__) \
	qmlRegisterSingletonType<JeromeLine>("Jerome", 1, 0, "Line" #L__, line_provider##L__);

	REG_LINE(0)
	REG_LINE(1)
	REG_LINE(2)
	REG_LINE(3)
	REG_LINE(4)
	REG_LINE(5)
	REG_LINE(6)
	REG_LINE(7)
	REG_LINE(8)
	REG_LINE(9)
	REG_LINE(10)
	REG_LINE(11)
	REG_LINE(12)
	REG_LINE(13)
	REG_LINE(14)
	REG_LINE(15)
	REG_LINE(16)
	REG_LINE(17)
	REG_LINE(18)
	REG_LINE(19)
	REG_LINE(20)
	REG_LINE(21)
#undef REG_LINE

	QQmlApplicationEngine engine;
	engine.load(QUrl(QLatin1String("qrc:/main.qml")));

	return app.exec();
}
