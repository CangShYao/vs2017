#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_qtTest.h"

class qtTest : public QMainWindow
{
	Q_OBJECT

public:
	qtTest(QWidget *parent = Q_NULLPTR);

private:
	Ui::qtTestClass ui;
private slots:
	void OnOKBtn();
};
