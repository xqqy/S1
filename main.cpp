#if _MSC_VER >= 1600

#pragma execution_character_set("utf-8")

#endif

#include "license.h"
#include"mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    license l;

    if(l.exec()==QDialog::Accepted){
        MainWindow w;
        w.show();
        return a.exec();
    }else{
        exit(-1);
    }
}
