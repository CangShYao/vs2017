/********************************************************************************
** Form generated from reading UI file 'qtTest.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTTEST_H
#define UI_QTTEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_qtTestClass
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *qtTestClass)
    {
        if (qtTestClass->objectName().isEmpty())
            qtTestClass->setObjectName(QStringLiteral("qtTestClass"));
        qtTestClass->resize(600, 400);
        centralWidget = new QWidget(qtTestClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(10, 10, 93, 28));
        qtTestClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(qtTestClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 26));
        qtTestClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(qtTestClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        qtTestClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(qtTestClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        qtTestClass->setStatusBar(statusBar);

        retranslateUi(qtTestClass);
        QObject::connect(pushButton, SIGNAL(clicked()), qtTestClass, SLOT(close()));

        QMetaObject::connectSlotsByName(qtTestClass);
    } // setupUi

    void retranslateUi(QMainWindow *qtTestClass)
    {
        qtTestClass->setWindowTitle(QApplication::translate("qtTestClass", "qtTest", Q_NULLPTR));
        pushButton->setText(QApplication::translate("qtTestClass", "PushButton", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class qtTestClass: public Ui_qtTestClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTTEST_H
