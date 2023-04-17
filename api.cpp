#include "api.h"
#include <QDebug>

Api::Api(QObject *parent) : QObject(parent)
{
    nm = new QNetworkAccessManager();
    res = nullptr;
}

QJsonObject Api::getData(QString apiCall)
{
    QNetworkRequest req{QUrl(URL+apiCall)};
    res = nm->get(req);
    QEventLoop* loop = new QEventLoop;
    connect(res,&QNetworkReply::finished,loop,&QEventLoop::quit);
    loop->exec();
    QString data = res->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
    QJsonObject obj = doc.object();

    return obj;
}

void Api::setupOnePlayer()
{
    QJsonObject res = getData("one");
    gameId = res.value("game_id").toString();
}

void Api::setupTwoPlayer()
{

}
