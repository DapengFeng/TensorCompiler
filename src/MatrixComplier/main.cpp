#include "MatrixComplier.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MatrixComplier w;
	w.show();
	return a.exec();
}
