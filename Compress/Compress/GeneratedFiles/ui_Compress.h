/********************************************************************************
** Form generated from reading UI file 'Compress.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMPRESS_H
#define UI_COMPRESS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CompressClass
{
public:
    QWidget *centralWidget;
    QLabel *imgLabel;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CompressClass)
    {
        if (CompressClass->objectName().isEmpty())
            CompressClass->setObjectName(QStringLiteral("CompressClass"));
        CompressClass->resize(429, 495);
        centralWidget = new QWidget(CompressClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        imgLabel = new QLabel(centralWidget);
        imgLabel->setObjectName(QStringLiteral("imgLabel"));
        imgLabel->setGeometry(QRect(20, 60, 391, 391));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(9, 9, 411, 29));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(14);
        pushButton->setFont(font);

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(layoutWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        sizePolicy.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy);
        pushButton_2->setFont(font);

        horizontalLayout->addWidget(pushButton_2);

        CompressClass->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(CompressClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        CompressClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(CompressClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        CompressClass->setStatusBar(statusBar);

        retranslateUi(CompressClass);

        QMetaObject::connectSlotsByName(CompressClass);
    } // setupUi

    void retranslateUi(QMainWindow *CompressClass)
    {
        CompressClass->setWindowTitle(QApplication::translate("CompressClass", "Compress", Q_NULLPTR));
        imgLabel->setText(QString());
        pushButton->setText(QApplication::translate("CompressClass", "\345\216\213\347\274\251", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("CompressClass", "\350\247\243\345\216\213", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CompressClass: public Ui_CompressClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMPRESS_H
