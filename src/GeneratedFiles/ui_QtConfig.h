/********************************************************************************
** Form generated from reading UI file 'QtConfig.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTCONFIG_H
#define UI_QTCONFIG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtConfig
{
public:
    QPushButton *pushButton;
    QCheckBox *enableBox;
    QPushButton *pushButton_2;
    QSlider *limitSlider;
    QLabel *limitLabel;

    void setupUi(QWidget *QtConfig)
    {
        if (QtConfig->objectName().isEmpty())
            QtConfig->setObjectName(QStringLiteral("QtConfig"));
        QtConfig->resize(284, 170);
        pushButton = new QPushButton(QtConfig);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(24, 140, 101, 23));
        pushButton->setCheckable(false);
        enableBox = new QCheckBox(QtConfig);
        enableBox->setObjectName(QStringLiteral("enableBox"));
        enableBox->setGeometry(QRect(20, 20, 81, 17));
        enableBox->setToolTipDuration(10);
        pushButton_2 = new QPushButton(QtConfig);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(150, 140, 101, 23));
        limitSlider = new QSlider(QtConfig);
        limitSlider->setObjectName(QStringLiteral("limitSlider"));
        limitSlider->setGeometry(QRect(9, 90, 261, 22));
        limitSlider->setMaximum(20000);
        limitSlider->setSingleStep(200);
        limitSlider->setPageStep(2000);
        limitSlider->setOrientation(Qt::Horizontal);
        limitLabel = new QLabel(QtConfig);
        limitLabel->setObjectName(QStringLiteral("limitLabel"));
        limitLabel->setGeometry(QRect(16, 60, 251, 20));
        limitLabel->setAlignment(Qt::AlignCenter);

        retranslateUi(QtConfig);
        QObject::connect(pushButton, SIGNAL(clicked()), QtConfig, SLOT(saveToConfig()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), QtConfig, SLOT(close()));
        QObject::connect(pushButton, SIGNAL(clicked()), QtConfig, SLOT(close()));
        QObject::connect(limitSlider, SIGNAL(valueChanged(int)), QtConfig, SLOT(updateLimitLabel()));

        QMetaObject::connectSlotsByName(QtConfig);
    } // setupUi

    void retranslateUi(QWidget *QtConfig)
    {
        QtConfig->setWindowTitle(QApplication::translate("QtConfig", "Test Plugin", Q_NULLPTR));
        pushButton->setText(QApplication::translate("QtConfig", "Annehmen", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        enableBox->setToolTip(QApplication::translate("QtConfig", "<html><head/><body><p><span style=\" font-weight:600;\">shit</span></p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        enableBox->setText(QApplication::translate("QtConfig", "Enable", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("QtConfig", "Abbrechen", Q_NULLPTR));
        limitLabel->setText(QApplication::translate("QtConfig", "limit", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QtConfig: public Ui_QtConfig {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTCONFIG_H
