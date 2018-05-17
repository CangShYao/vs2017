#include "Compress.h"
#include "BmpAlgorithm.h"
#include <QPixmap>
#include <QFileDialog>
#include <QImage>
#include <QMessageBox>

Compress::Compress(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	this->setWindowTitle("306Ñ¹Ëõ");
}
void Compress::on_pushButton_clicked()
{
	imgFileName = QFileDialog::getOpenFileName(this, tr("Open file"), "", tr("*.bmp"));
	if (imgFileName == NULL) return;
	string strFile = imgFileName.toStdString();
	imgOutFile = QFileDialog::getSaveFileName(this, tr("Save file"), "", tr("*cnm"));
	if (imgOutFile == NULL) return;
	string strOutFile = imgOutFile.toStdString();
	strOutFile += ".cnm";
	ifstream fin(strFile, ios::binary);
	ofstream fout(strOutFile, ios::binary);
	BmpCompress myCom;
	myCom.CompressBitmap(fin, fout);
	fin.close();
	fout.close();
}

void Compress::on_pushButton_2_clicked()
{
	imgFileName = QFileDialog::getOpenFileName(this, tr("Open file"), "", tr("*cnm"));
	if (imgFileName == NULL) return;
	string strFile = imgFileName.toStdString();
	imgOutFile = QFileDialog::getSaveFileName(this, tr("Save file"), "", tr("*bmp"));
	if (imgOutFile == NULL) return;
	imgOutFile += ".bmp";
	string strOutFile = imgOutFile.toStdString();
	ifstream fin(strFile, ios::binary);
	ofstream fout(strOutFile, ios::binary);
	BmpCompress myDeCom;
	myDeCom.DeCompressBitmap(fin, fout);
	QImage qImage;
	if (!qImage.load(imgOutFile))
	{
		QMessageBox::warning(this, "Warning!", "Load failed!");
	}
	else
	{
		int imgWidth = ui.imgLabel->width();
		int imgHeight = ui.imgLabel->height();
		QPixmap labelImage = QPixmap::fromImage(qImage);
		labelImage = labelImage.scaled(imgWidth, imgHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
		ui.imgLabel->setPixmap(labelImage);
	}
}
