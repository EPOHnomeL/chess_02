#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QLabel>
#include <QTextEdit>
#include <QGraphicsView>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(int gameType, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void turnChange(QString move, bool player);
    void gameFinished(QString reason, bool player);

private:
    Ui::MainWindow *ui;
    int moveCount;
    bool onePlayer, LAN;
    QProcess *apiProcess;
    QProcess *dbProcess;
    QLabel *turnLabel;
    QTextEdit *te;
    QGraphicsView *piecesLostView;
};
#endif // MAINWINDOW_H
