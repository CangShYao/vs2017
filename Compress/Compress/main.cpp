#include "Compress.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Compress w;
	w.show();
	return a.exec();
}
