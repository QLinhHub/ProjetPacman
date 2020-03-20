#include <time.h>

#include<QtWidgets/qapplication.h>

#include "pacmanwindow.h"

Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin);

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    srand(time(0));

   // PacmanWindow wnd;

    Form window;


    window.setWindowTitle("Form example");
    window.show();


    return app.exec();
}
