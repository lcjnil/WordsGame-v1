#include <QCoreApplication>

#include "src/Controller/Server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Server server(&a);

    return a.exec();
}
