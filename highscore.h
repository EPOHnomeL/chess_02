#ifndef HIGHSCORE_H
#define HIGHSCORE_H
#include <QTextBrowser>
#include <QFile>
#include <QtDebug>
#include <QString>
#include <QList>
#include <QVector>
class highscore :public QTextBrowser
{
public:
    highscore(QWidget *parent = nullptr);

    QTextBrowser *high;
    bool writeFile(QString filename, QString text);
    QStringList readFile(QString filename);
    QStringList findMostWins(QStringList list);
    QString buatify(QStringList list);
private:
    QList<QString*> names;

};

#endif // HIGHSCORE_H
