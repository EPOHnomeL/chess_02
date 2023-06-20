#include "api.h"
#include <QHttpPart>
#include <QDebug>

Api::Api(QObject *parent) : QObject(parent)
{
    nm = new QNetworkAccessManager();
    res = nullptr;
}

QJsonObject Api::get(QString apiCall)
{
    QNetworkRequest req{QUrl(URL+apiCall)};
    qInfo() << "GET: " << req.url().toString();
    res = nm->get(req);
    QEventLoop* loop = new QEventLoop;
    connect(res,&QNetworkReply::finished,loop,&QEventLoop::quit);
    loop->exec();
    QString data = res->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
    QJsonObject obj = doc.object();

    qInfo()<< obj;
    return obj;
}

QJsonObject Api::post(QString apiCall, QString postData)
{
    QNetworkRequest req{QUrl(URL+apiCall)};
    QJsonDocument inputDoc = QJsonDocument::fromJson(postData.toUtf8());
    QJsonObject obj = inputDoc.object();
    obj.insert("game_id", gameId);
    QJsonDocument doc(obj);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    qInfo() << "POST: " << req.url().toString() << obj;

    req.setHeader(QNetworkRequest::ContentTypeHeader, QStringLiteral("application/json; charset=utf-8"));

    res = nm->post(req, strJson.toUtf8());
    QEventLoop* loop = new QEventLoop;
    connect(res,&QNetworkReply::finished,loop,&QEventLoop::quit);
    loop->exec();
    QString data = res->readAll();
    QJsonDocument outputDoc = QJsonDocument::fromJson(data.toUtf8());
    QJsonObject outObj = outputDoc.object();
    qInfo() << outObj;
    return outObj;
}

bool Api::setupOnePlayer()
{
    URL = "http://localhost:3000/api/v1/chess/";
    QJsonObject res = get("one");
    if(res.isEmpty()){
        qDebug()<< "Could not initialize server, check DB";
        return false;
    }
    gameId = res.value("game_id").toString();
    return true;
}

void Api::setupLANHost()
{
    URL = "http://0.0.0.0:3000/api/v1/chess/";
}

void Api::setupLANClient(QString url)
{
    URL = url;
}

void Api::tryMakeMove(Move move)
{
    post("one/move/player", move.toJsonString());
}

Move Api::aiMove()
{
    QJsonObject res = post("one/move/ai", "");
    if(res == QJsonObject()){
        return Move{{0, 0}, {0, 0}};
    }
    Move move;
    move.from = strToPos(res.value("from").toString());
    move.to = strToPos(res.value("to").toString());
    return move;
}

Pos Api::strToPos(QString s)
{
    Pos pos;
    pos.y = s.toStdString()[0] - 97 ;
    pos.x = -s.toStdString()[1] + 56;
    return pos;
}
