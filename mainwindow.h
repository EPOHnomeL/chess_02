#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QLabel>
#include <QTextEdit>

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
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void turnChange(QString move, bool player);
    void gameFinished(QString reason, bool player);

private:
    Ui::MainWindow *ui;
    QProcess *apiProcess;
    QLabel *turnLabel;
    QTextEdit *te;
};
#endif // MAINWINDOW_H
