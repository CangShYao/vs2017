#pragma once
#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif
#include <QtWidgets/QMainWindow>
#include <QString>
#include "ui_Compress.h"

class Compress : public QMainWindow
{
	Q_OBJECT

public:
	Compress(QWidget *parent = Q_NULLPTR);
private slots:
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();

private:
	Ui::CompressClass ui;
	QString imgFileName;
	QString imgOutFile;
};
