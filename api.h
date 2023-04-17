#ifndef API_H
#define API_H

#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QEventLoop>
#include <QObject>

class Api : public QObject
{
    Q_OBJECT
public:
    explicit Api(QObject *parent = nullptr);
    void setupOnePlayer();
    void setupTwoPlayer();

private:
    const QString URL = "http://localhost:3000/api/v1/chess/";
    bool finished;

    QNetworkAccessManager *nm;
    QNetworkReply *res;

    QString gameId;

    QJsonObject getData(QString apiCall);

};

#endif // API_H
