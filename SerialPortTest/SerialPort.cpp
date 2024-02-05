#include "SerialPort.h"

SerialPort::SerialPort(QObject *parent) : QObject(parent)
{
    connect(&m_serialPort, &QIODevice::readyRead, this, &SerialPort::readData);
    connect(this, &SerialPort::dataChanged, this, &SerialPort::getData);
}

bool SerialPort::open(QString portName, QIODevice::OpenMode mode)
{
    m_serialPort.setPortName(portName);
    if (m_serialPort.open(mode)){
        qDebug() << "Serial port opened successfully.";
        m_serialPort.setBaudRate(QSerialPort::Baud57600);
        m_serialPort.setDataBits(QSerialPort::Data8);
        m_serialPort.setParity(QSerialPort::NoParity);
        m_serialPort.setStopBits(QSerialPort::TwoStop);
        m_serialPort.setFlowControl(QSerialPort::NoFlowControl);
    } else {
        qDebug() << "Failed to open serial port:" << m_serialPort.errorString();
    }

    return m_serialPort.isOpen();
}

bool SerialPort::write(QByteArray commandToSend, bool isHex)
{
    m_data.clear();
    m_serialPort.clear();
    QByteArray data;
    data.append(isHex?QByteArray::fromHex(commandToSend):commandToSend);
    if (!isHex)
        data.append(QByteArray::fromHex("0D"));
    qint64 bytesWritten;

    qDebug() << "Received data:" << data;
    qDebug() << "Received data:" << data.toHex();

    bytesWritten = m_serialPort.write(data);

    if (bytesWritten == -1) {
        qWarning() << "Failed to write to the serial port:" << m_serialPort.errorString();
    } else {
        qDebug() << "Bytes written:" << bytesWritten;
    }

    return (bytesWritten != -1);

}

QString SerialPort::errorString() const
{
    return m_serialPort.errorString();
}

void SerialPort::readData()
{
    m_data.append(m_serialPort.readAll());
    emit dataChanged();
}

QString SerialPort::getData()
{
    qDebug() << "response: " << m_data.toHex();
    return QString(m_data.toHex());
}
