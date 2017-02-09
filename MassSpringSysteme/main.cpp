#include "massspringsysteme.h"
#include <QtWidgets/QApplication>

//#pragma comment (linker, "/subsystem:console") 

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MassSpringSysteme w;
	w.show();
	return a.exec();
}
