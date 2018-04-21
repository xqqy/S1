#if _MSC_VER >= 1600

#pragma execution_character_set("utf-8")

#endif

#include "license.h"
#include "ui_license.h"

license::license(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::license)
{
    ui->setupUi(this);
}

license::~license()
{
    delete ui;
}

void license::on_buttonBox_rejected()
{
    exit(0);
}

void license::on_buttonBox_accepted()
{
    accept();
}
