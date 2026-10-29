#include <iostream>
#include <QCoreApplication>
#include "01.h"
#include "02.h"


int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);
    Newspaper newspaper("A");
    Sub reader;
    QObject::connect(&newspaper, &Newspaper::newPaper, &reader, &Sub::receiveNewspaper);
    newspaper.send();

    return app.exec();
}