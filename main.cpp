#include <QCoreApplication>
#include <QDir>

#include "src/model/Connection.h"
#include "src/model/User.h"
#include "src/model/Question.h"
#include "src/controller/app.h"

#include <vector>

int main(int argc, char *argv[])
{
    QCoreApplication application(argc, argv);

    // SET DATABASE CONNECTION
    QString db_path = application.applicationDirPath() + QDir::separator() + "data.db";
    Connection connection(db_path);
    User::setConnection(&connection);
    Question::setConnection(&connection);

    App app;
    app.start();

    return 0;
}
