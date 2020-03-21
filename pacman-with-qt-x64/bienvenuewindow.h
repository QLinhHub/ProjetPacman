#ifndef BIENVENUEWINDOW_H
#define BIENVENUEWINDOW_H

#include <QtCore/QtCore>
#include <QtWidgets/QtWidgets>
#include "jeu.h"

class bienvenuewindow : public QFrame
{
public:
    bienvenuewindow(QWidget* pparent=0, Qt::WindowFlags flags=0);
protected:
    void openOPW1();
    void openOPW2();
};


#endif
