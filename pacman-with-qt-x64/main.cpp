#include <time.h>

#include<QtWidgets/qapplication.h>

#include "pacmanwindow.h"
#include "bienvenuewindow.h"
#include "onePlayerwindow.h"

Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin);

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    srand(time(0));

    bienvenuewindow bvn;
    bvn.show();


    return app.exec();
}
