/********************************************************************************
** Form generated from reading UI file 'license.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LICENSE_H
#define UI_LICENSE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_license
{
public:
    QLabel *label;
    QFrame *line;
    QLabel *label_2;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *license)
    {
        if (license->objectName().isEmpty())
            license->setObjectName(QStringLiteral("license"));
        license->resize(400, 300);
        label = new QLabel(license);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, 0, 191, 61));
        QFont font;
        font.setPointSize(44);
        label->setFont(font);
        line = new QFrame(license);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(0, 66, 401, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        label_2 = new QLabel(license);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(60, 80, 281, 111));
        buttonBox = new QDialogButtonBox(license);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(230, 270, 166, 28));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        retranslateUi(license);

        QMetaObject::connectSlotsByName(license);
    } // setupUi

    void retranslateUi(QDialog *license)
    {
        license->setWindowTitle(QApplication::translate("license", "license", nullptr));
        label->setText(QApplication::translate("license", "\350\256\270\345\217\257\350\257\201", nullptr));
        label_2->setText(QApplication::translate("license", "<html><head/><body><p>\344\275\277\347\224\250\346\234\254\347\250\213\345\272\217\357\274\214\345\215\263\344\273\243\350\241\250\346\202\250\345\220\214\346\204\217\350\256\270\345\217\257\345\215\217\350\256\256</p><p>\346\234\254\347\250\213\345\272\217\344\276\235\347\205\247GPLv3\345\222\214Apache2.0\345\217\221\345\270\203</p><p>Qt\345\272\223\344\276\235\347\205\247(L)GPL\346\216\210\346\235\203\344\275\277\347\224\250</p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class license: public Ui_license {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LICENSE_H
