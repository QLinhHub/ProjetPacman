#include <iostream>
#include "bienvenuewindow.h"
#include "pacmanwindow.h"
#include "joueurwindow.h"
#include "result.h"

using namespace std;

result::result(QWidget* pparent, Qt::WindowFlags flags) : QFrame(pparent, flags)
{
    QVBoxLayout *vbox = new QVBoxLayout(this);
    vbox->setSpacing(1);

    replay = new QPushButton("Rejouer", this);
    replay->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    saveNote = new QPushButton("Sauvegarder ton mark", this);
    saveNote->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    exit = new QPushButton("Exit", this);
    exit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    vbox->addWidget(replay);
    vbox->addWidget(saveNote);
    vbox->addWidget(exit);

    setLayout(vbox);

    connect(replay, QPushButton::clicked, this, handleReplay);
    connect(saveNote, QPushButton::clicked, this, handleSavenote);
    connect(exit, QPushButton::clicked, this, close);

    resize(500, 500);
}

void result::handleReplay()
{
    bienvenuewindow* bvn = new bienvenuewindow();
    close();
    bvn->show();
}

void result::handleSavenote()
{

}
