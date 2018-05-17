#include "qtTest.h"

qtTest::qtTest(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(OnOKBtn()));
}

void qtTest::OnOKBtn()
{
	exit(0);
}