#include "RegFileView.h"
#include <QGroupBox>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include "Tools.h"
#include "VAlUE.h"

void RegFileView::updateUI()
{
    edit_eax->setText(Tools::dec2hex(reg[0], 8));
    edit_ecx->setText(Tools::dec2hex(reg[1], 8));
    edit_edx->setText(Tools::dec2hex(reg[2], 8));
    edit_ebx->setText(Tools::dec2hex(reg[3], 8));
    edit_esp->setText(Tools::dec2hex(reg[4], 8));
    edit_ebp->setText(Tools::dec2hex(reg[5], 8));
    edit_esi->setText(Tools::dec2hex(reg[6], 8));
    edit_edi->setText(Tools::dec2hex(reg[7], 8));

    edit_ZF->setText(QString::number(ZF));
    edit_SF->setText(QString::number(SF));
    edit_OF->setText(QString::number(OF));
}

RegFileView::RegFileView(QWidget *parent) :
    QWidget(parent)
{
    QGroupBox *regGroup = new QGroupBox("Register Files");

    edit_eax = new QLineEdit;
    edit_eax->setReadOnly(true);
    edit_ecx = new QLineEdit;
    edit_ecx->setReadOnly(true);
    edit_edx = new QLineEdit;
    edit_edx->setReadOnly(true);
    edit_ebx = new QLineEdit;
    edit_ebx->setReadOnly(true);
    edit_esp = new QLineEdit;
    edit_esp->setReadOnly(true);
    edit_ebp = new QLineEdit;
    edit_ebp->setReadOnly(true);
    edit_esi = new QLineEdit;
    edit_esi->setReadOnly(true);
    edit_edi = new QLineEdit;
    edit_edi->setReadOnly(true);

    QLabel *l_eax = new QLabel("%eax:");
    QLabel *l_ecx = new QLabel("%ecx:");
    QLabel *l_edx = new QLabel("%edx:");
    QLabel *l_ebx = new QLabel("%ebx:");
    QLabel *l_esp = new QLabel("%esp:");
    QLabel *l_ebp = new QLabel("%ebp:");
    QLabel *l_esi = new QLabel("%esi:");
    QLabel *l_edi = new QLabel("%edi:");

    QGridLayout *reglayout = new QGridLayout;
    reglayout->addWidget(l_eax, 0, 0);
    reglayout->addWidget(l_ecx, 1, 0);
    reglayout->addWidget(l_edx, 2, 0);
    reglayout->addWidget(l_ebx, 3, 0);
    reglayout->addWidget(l_esp, 4, 0);
    reglayout->addWidget(l_ebp, 5, 0);
    reglayout->addWidget(l_esi, 6, 0);
    reglayout->addWidget(l_edi, 7, 0);

    reglayout->addWidget(edit_eax, 0, 1);
    reglayout->addWidget(edit_ecx, 1, 1);
    reglayout->addWidget(edit_edx, 2, 1);
    reglayout->addWidget(edit_ebx, 3, 1);
    reglayout->addWidget(edit_esp, 4, 1);
    reglayout->addWidget(edit_ebp, 5, 1);
    reglayout->addWidget(edit_esi, 6, 1);
    reglayout->addWidget(edit_edi, 7, 1);

    regGroup->setLayout(reglayout);

    QGroupBox *conGroup = new QGroupBox("Condition Codes");

    edit_ZF = new QLineEdit;
    edit_ZF->setReadOnly(true);
    edit_SF = new QLineEdit;
    edit_SF->setReadOnly(true);
    edit_OF = new QLineEdit;
    edit_OF->setReadOnly(true);

    QLabel *l_ZF = new QLabel("ZF:");
    QLabel *l_SF = new QLabel("SF:");
    QLabel *l_OF = new QLabel("OF:");

    QGridLayout *codelayout = new QGridLayout;

    codelayout->addWidget(l_ZF, 0, 0);
    codelayout->addWidget(l_SF, 1, 0);
    codelayout->addWidget(l_OF, 2, 0);

    codelayout->addWidget(edit_ZF, 0, 1);
    codelayout->addWidget(edit_SF, 1, 1);
    codelayout->addWidget(edit_OF, 2, 1);

    conGroup->setLayout(codelayout);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(regGroup, 0, 0);
    layout->addWidget(conGroup, 1, 0);

    setLayout(layout);
}
