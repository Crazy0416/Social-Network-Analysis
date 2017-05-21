#include "dblpanalysisapp.h"
#include <QtWidgets/QApplication>

using namespace std;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	dblpAnalysisApp w;
	w.show();
	
	return a.exec();
}
