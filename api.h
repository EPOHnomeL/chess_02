#ifndef API_H
#define API_H

#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QEventLoop>
#include <QObject>
#include "types.h"

class Api : public QObject
{
    Q_OBJECT
public:
    explicit Api(QObject *parent = nullptr);
    void setupOnePlayer();
    void setupLANHost();
    void setupLANClient(QString url);
    void tryMakeMove(Move move);
    Move aiMove();

private:
    QString URL;
    bool finished;

    QNetworkAccessManager *nm;
    QNetworkReply *res;

    Pos strToPos(QString s);
    QString gameId;

    QJsonObject get(QString apiCall);
    QJsonObject post(QString apiCall, QString postData);

};

#endif // API_H
