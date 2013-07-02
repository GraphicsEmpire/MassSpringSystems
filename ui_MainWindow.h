/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created: Tue Jun 11 21:53:57 2013
**      by: Qt User Interface Compiler version 5.0.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_frmMain
{
public:
    QScrollArea *glWidgetArea;
    QWidget *scrollAreaWidgetContents;
    QGroupBox *groupBox;
    QPushButton *btnClose;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QDoubleSpinBox *spKSpring;
    QDoubleSpinBox *spKDamper;
    QDoubleSpinBox *spKMass;
    QLabel *label_4;
    QDoubleSpinBox *spInterval;

    void setupUi(QWidget *frmMain)
    {
        if (frmMain->objectName().isEmpty())
            frmMain->setObjectName(QStringLiteral("frmMain"));
        frmMain->resize(964, 588);
        glWidgetArea = new QScrollArea(frmMain);
        glWidgetArea->setObjectName(QStringLiteral("glWidgetArea"));
        glWidgetArea->setGeometry(QRect(9, 9, 711, 571));
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(glWidgetArea->sizePolicy().hasHeightForWidth());
        glWidgetArea->setSizePolicy(sizePolicy);
        glWidgetArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        glWidgetArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        glWidgetArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 709, 569));
        glWidgetArea->setWidget(scrollAreaWidgetContents);
        groupBox = new QGroupBox(frmMain);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(730, 0, 231, 571));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy1);
        btnClose = new QPushButton(groupBox);
        btnClose->setObjectName(QStringLiteral("btnClose"));
        btnClose->setGeometry(QRect(150, 440, 75, 23));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(5, 40, 21, 20));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(5, 70, 20, 20));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(9, 100, 20, 20));
        spKSpring = new QDoubleSpinBox(groupBox);
        spKSpring->setObjectName(QStringLiteral("spKSpring"));
        spKSpring->setGeometry(QRect(30, 40, 171, 27));
        spKSpring->setSingleStep(0.01);
        spKSpring->setValue(1);
        spKDamper = new QDoubleSpinBox(groupBox);
        spKDamper->setObjectName(QStringLiteral("spKDamper"));
        spKDamper->setGeometry(QRect(30, 70, 171, 27));
        spKDamper->setSingleStep(0.01);
        spKDamper->setValue(0.5);
        spKMass = new QDoubleSpinBox(groupBox);
        spKMass->setObjectName(QStringLiteral("spKMass"));
        spKMass->setGeometry(QRect(30, 100, 171, 27));
        spKMass->setValue(1);
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(9, 150, 20, 20));
        spInterval = new QDoubleSpinBox(groupBox);
        spInterval->setObjectName(QStringLiteral("spInterval"));
        spInterval->setGeometry(QRect(30, 150, 171, 27));
        spInterval->setMinimum(0.01);
        spInterval->setMaximum(10);
        spInterval->setSingleStep(0.01);
        spInterval->setValue(0.2);

        retranslateUi(frmMain);

        QMetaObject::connectSlotsByName(frmMain);
    } // setupUi

    void retranslateUi(QWidget *frmMain)
    {
        frmMain->setWindowTitle(QApplication::translate("frmMain", "Computer Graphics LAB FrameWork", 0));
        groupBox->setTitle(QApplication::translate("frmMain", "Tool Box", 0));
        btnClose->setText(QApplication::translate("frmMain", "Close", 0));
        label->setText(QApplication::translate("frmMain", "KS", 0));
        label_2->setText(QApplication::translate("frmMain", "KD", 0));
        label_3->setText(QApplication::translate("frmMain", "M", 0));
        label_4->setText(QApplication::translate("frmMain", "Dt", 0));
    } // retranslateUi

};

namespace Ui {
    class frmMain: public Ui_frmMain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
