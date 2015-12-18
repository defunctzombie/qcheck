#include <QApplication>

#include "QCheck.hpp"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	
	QCheck form;
	form.show();
	
	return app.exec();
}
