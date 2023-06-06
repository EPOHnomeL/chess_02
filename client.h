#ifndef CLIENT_H
#define CLIENT_H


#include <QtCore>
#include <QtNetwork/QTcpSocket>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);

signals:
    void dataReceived(QByteArray);

public slots:
    bool connectToHost(QString host);
    bool writeData(QByteArray data);

private:
    QTcpSocket *socket;
    QByteArray rbuf;
    qint32 rsize;

private slots:
    void readyRead();
};

#endif // CLIENT_H
