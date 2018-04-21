#if _MSC_VER >= 1600

#pragma execution_character_set("utf-8")

#endif

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"MeowHttpd/MeowHttpd_nossl_nolocal.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void server();
    void inrest(QString what);
    void clsoe();
    QString getHostIpAddress();

protected:
    void closeEvent(QCloseEvent *event);

};



#endif // MAINWINDOW_H
