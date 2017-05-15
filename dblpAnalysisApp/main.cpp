#include "dblpanalysisapp.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	dblpAnalysisApp w;
	w.show();
	
	return a.exec();
}