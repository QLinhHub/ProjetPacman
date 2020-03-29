#ifndef RESULT_H
#define RESULT_H

#include <QtCore/QtCore>
#include <QtWidgets/QtWidgets>
#include "jeu.h"
#include "pacmanwindow.h"
#include "joueurwindow.h"

class result : public QFrame
{
protected:
    QPushButton *replay;
    QPushButton *saveNote;
    QPushButton *exit;
public:
    result(QWidget* pparent=0, Qt::WindowFlags flags=0);
    void handleReplay();
    void handleSavenote();
    void handleExit();
};

#endif
