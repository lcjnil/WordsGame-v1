#include <QCoreApplication>

#include "src/controller/app.h"

#include "src/service/ClientService.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    App app;
    app.start();

    return 0;
}
