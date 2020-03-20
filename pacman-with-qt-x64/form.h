#ifndef FORM_H_INCLUDED
#define FORM_H_INCLUDED

#include <QtCore/QtCore>
#include <QtWidgets/QtWidgets>


class Form : public QWidget {

  public:
    Form(QWidget *parent = 0);
};

Form::Form(QWidget *parent)
    : QWidget(parent) {

  QLineEdit *nameEdit = new QLineEdit(this);
  QLineEdit *addrEdit = new QLineEdit(this);
  QLineEdit *occpEdit = new QLineEdit(this);

  QFormLayout *formLayout = new QFormLayout;
  formLayout->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter);
  formLayout->addRow("Name:", nameEdit);
  formLayout->addRow("Email:", addrEdit);
  formLayout->addRow("Age:", occpEdit);

  setLayout(formLayout);
}
#endif // FORM_H_INCLUDED
