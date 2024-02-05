#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QObject>
#include <QSerialPort>
#include <QDebug>

class SerialPort : public QObject
{
    Q_OBJECT
public:
    explicit SerialPort(QObject *parent = nullptr);
    bool open(QString portName, QIODevice::OpenMode mode);
    Q_INVOKABLE bool write(QByteArray commandToSend, bool isHex = true);
    QString errorString() const;


signals:
    void dataChanged();

private:
    QSerialPort m_serialPort;
    QByteArray m_data;

private slots:
    void readData();
    QString getData();

};

#endif // SERIALPORT_H
