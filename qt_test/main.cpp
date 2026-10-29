#include "qt_test.h"
#include <QtWidgets/QApplication>
#include <QPushButton>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    qt_test window;
    window.show();
    return app.exec();
}
