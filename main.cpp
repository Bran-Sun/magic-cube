#include <QApplication>
#include<iostream>
#include "cube.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QCube w;
    w.resize(400, 300);
    w.show();

    return app.exec();
}

