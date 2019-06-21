/********************************************************************************
** Form generated from reading UI file 'debug.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEBUG_H
#define UI_DEBUG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_debug
{
public:
    QPushButton *closeButton;
    QGraphicsView *graphicsView;

    void setupUi(QWidget *debug)
    {
        if (debug->objectName().isEmpty())
            debug->setObjectName(QStringLiteral("debug"));
        debug->resize(523, 309);
        closeButton = new QPushButton(debug);
        closeButton->setObjectName(QStringLiteral("closeButton"));
        closeButton->setGeometry(QRect(220, 270, 75, 23));
        graphicsView = new QGraphicsView(debug);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(5, 10, 511, 251));

        retranslateUi(debug);
        QObject::connect(closeButton, SIGNAL(clicked()), debug, SLOT(close()));

        QMetaObject::connectSlotsByName(debug);
    } // setupUi

    void retranslateUi(QWidget *debug)
    {
        debug->setWindowTitle(QApplication::translate("debug", "Form", nullptr));
        closeButton->setText(QApplication::translate("debug", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class debug: public Ui_debug {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEBUG_H
