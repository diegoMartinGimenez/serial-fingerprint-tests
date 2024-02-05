#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QQmlContext>
#include <QDebug>

#include "SerialPort.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    SerialPort *serialPort = new SerialPort();

    serialPort->open("/dev/ttyUSB0", QIODevice::ReadWrite);

    QQmlApplicationEngine engine;

    QQmlContext *ctx = engine.rootContext();

    ctx->setContextProperty("serialPort", serialPort);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
