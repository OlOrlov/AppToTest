#include <QCoreApplication>
#include <QUdpSocket>
#include <QThread>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QUdpSocket rcv_sock;
    QHostAddress myAddr = QHostAddress::LocalHost;
    quint16 myPortRCV = 1800;
    if (rcv_sock.bind(myAddr, myPortRCV, QAbstractSocket::ShareAddress))
        qDebug() << "RCV bind success:" << myAddr.toString() << myPortRCV;
    else
        qDebug() << "RCV bind failure:" << rcv_sock.errorString();



    QUdpSocket xmt_sock;
    quint16 myPortXMT = 1801;
    if (xmt_sock.bind(myAddr, myPortXMT, QAbstractSocket::ShareAddress))
        qDebug() << "XMT bind success:" << myAddr.toString() << myPortXMT;
    else
        qDebug() << "XMT bind failure:" << xmt_sock.errorString();



    QHostAddress senderAddr = QHostAddress::LocalHost;
    quint16 senderPort = 1801;
    QByteArray received;

    qDebug() << "Reading...";
    while (true)
    {
        if (rcv_sock.hasPendingDatagrams())
        {
            received.clear();
            received.resize(rcv_sock.pendingDatagramSize());
            rcv_sock.readDatagram(received.data(), rcv_sock.pendingDatagramSize(), &senderAddr, &senderPort);

            QThread::sleep(1);

            qDebug() << "REC" << received << "from" << senderPort;
            xmt_sock.writeDatagram(received, senderAddr, senderPort + 1);
            qDebug() << "XMT" << received << "to" << senderPort + 1;
        }

        QThread::msleep(100);
    }

    return a.exec();
}
