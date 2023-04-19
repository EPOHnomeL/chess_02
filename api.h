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
    void tryMakeMove(Move move);
    Move aiMove();

private:
    const QString URL = "http://localhost:3000/api/v1/chess/";
    bool finished;

    QNetworkAccessManager *nm;
    QNetworkReply *res;

    Pos strToPos(QString s);
    QString gameId;

    QJsonObject get(QString apiCall);
    QJsonObject post(QString apiCall, QString postData);

};

#endif // API_H
