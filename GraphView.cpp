#include "GraphView.h"
#include <QPalette>
#include <QResizeEvent>
#include "VAlUE.h"
#include <QLabel>
#include <QDebug>
#include "Tools.h"

void GraphView::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    QPalette pal(palette());
    pal.setBrush(QPalette::Window,
                    QBrush(_image.scaled(event->size(), Qt::IgnoreAspectRatio,
                            Qt::SmoothTransformation)));
    setPalette(pal);
    for (int i = 0; i < labels.size(); ++i)
    {
        QRect rect = rects[i];
        labels[i]->setGeometry(rect.x() * event->size().width() / 852, rect.y() * event->size().height() / 1194,
                               rect.width() * event->size().width() / 852, rect.height() * event->size().height() / 1194);
    }
}

GraphView::GraphView(QWidget *parent) :
    QWidget(parent)
{
    labels.clear();
    rects.clear();
    titles.clear();
    QRect rect;

    Label_Stat = new QLabel(this);
    rect = QRect(81, 0, 54, 41);
    labels.push_back(Label_Stat);
    rects.push_back(rect);
    titles.push_back("SAOK");

    Label_W_stat = new QLabel(this);
    rect = QRect(83, 104, 48, 40);
    labels.push_back(Label_W_stat);
    rects.push_back(rect);
    titles.push_back("SAOK");

    Label_W_icode = new QLabel(this);
    rect = QRect(131, 104, 48, 40);
    labels.push_back(Label_W_icode);
    rects.push_back(rect);
    titles.push_back("icode");

    Label_W_valE = new QLabel(this);
    rect = QRect(323, 104, 96, 40);
    labels.push_back(Label_W_valE);
    rects.push_back(rect);
    titles.push_back("valE");

    Label_W_valM = new QLabel(this);
    rect = QRect(419, 104, 96, 40);
    labels.push_back(Label_W_valM);
    rects.push_back(rect);
    titles.push_back("valM");

    Label_W_dstE = new QLabel(this);
    rect = QRect(563, 104, 48, 40);
    labels.push_back(Label_W_dstE);
    rects.push_back(rect);
    titles.push_back("dstE");

    Label_W_dstM = new QLabel(this);
    rect = QRect(611, 104, 48, 40);
    labels.push_back(Label_W_dstM);
    rects.push_back(rect);
    titles.push_back("dstM");

    Label_M_stat = new QLabel(this);
    rect = QRect(83, 352, 48, 40);
    labels.push_back(Label_M_stat);
    rects.push_back(rect);
    titles.push_back("SAOK");

    Label_M_icode = new QLabel(this);
    rect = QRect(131, 352, 48, 40);
    labels.push_back(Label_M_icode);
    rects.push_back(rect);
    titles.push_back("icode");

    Label_M_Cnd = new QLabel(this);
    rect = QRect(227, 352, 48, 40);
    labels.push_back(Label_M_Cnd);
    rects.push_back(rect);
    titles.push_back("Cnd");

    Label_M_valE = new QLabel(this);
    rect = QRect(323, 352, 96, 40);
    labels.push_back(Label_M_valE);
    rects.push_back(rect);
    titles.push_back("valE");

    Label_M_valA = new QLabel(this);
    rect = QRect(419, 352, 96, 40);
    labels.push_back(Label_M_valA);
    rects.push_back(rect);
    titles.push_back("valA");

    Label_M_dstE = new QLabel(this);
    rect = QRect(563, 352, 48, 40);
    labels.push_back(Label_M_dstE);
    rects.push_back(rect);
    titles.push_back("dstE");

    Label_M_dstM = new QLabel(this);
    rect = QRect(611, 352, 48, 40);
    labels.push_back(Label_M_dstM);
    rects.push_back(rect);
    titles.push_back("dstM");

    Label_E_stat = new QLabel(this);
    rect = QRect(79, 568, 52, 40);
    labels.push_back(Label_E_stat);
    rects.push_back(rect);
    titles.push_back("SAOK");

    Label_E_icode = new QLabel(this);
    rect = QRect(131, 568, 52, 40);
    labels.push_back(Label_E_icode);
    rects.push_back(rect);
    titles.push_back("icode");

    Label_E_ifun = new QLabel(this);
    rect = QRect(183, 568, 52, 40);
    labels.push_back(Label_E_ifun);
    rects.push_back(rect);
    titles.push_back("ifun");

    Label_E_valC = new QLabel(this);
    rect = QRect(235, 568, 104, 40);
    labels.push_back(Label_E_valC);
    rects.push_back(rect);
    titles.push_back("valC");

    Label_E_valA = new QLabel(this);
    rect = QRect(339, 568, 104, 40);
    labels.push_back(Label_E_valA);
    rects.push_back(rect);
    titles.push_back("valA");

    Label_E_valB = new QLabel(this);
    rect = QRect(443, 568, 104, 40);
    labels.push_back(Label_E_valB);
    rects.push_back(rect);
    titles.push_back("valB");

    Label_E_dstE = new QLabel(this);
    rect = QRect(547, 568, 52, 40);
    labels.push_back(Label_E_dstE);
    rects.push_back(rect);
    titles.push_back("dstE");

    Label_E_dstM = new QLabel(this);
    rect = QRect(599, 568, 52, 40);
    labels.push_back(Label_E_dstM);
    rects.push_back(rect);
    titles.push_back("dstM");

    Label_E_srcA = new QLabel(this);
    rect = QRect(651, 568, 52, 40);
    labels.push_back(Label_E_srcA);
    rects.push_back(rect);
    titles.push_back("srcA");

    Label_E_srcB = new QLabel(this);
    rect = QRect(703, 568, 52, 40);
    labels.push_back(Label_E_srcB);
    rects.push_back(rect);
    titles.push_back("srcB");

    Label_D_stat = new QLabel(this);
    rect = QRect(83, 888, 48, 40);
    labels.push_back(Label_D_stat);
    rects.push_back(rect);
    titles.push_back("SAOK");

    Label_D_icode = new QLabel(this);
    rect = QRect(131, 888, 48, 40);
    labels.push_back(Label_D_icode);
    rects.push_back(rect);
    titles.push_back("icode");

    Label_D_ifun = new QLabel(this);
    rect = QRect(179, 888, 48, 40);
    labels.push_back(Label_D_ifun);
    rects.push_back(rect);
    titles.push_back("ifun");

    Label_D_rA = new QLabel(this);
    rect = QRect(227, 888, 48, 40);
    labels.push_back(Label_D_rA);
    rects.push_back(rect);
    titles.push_back("rA");

    Label_D_rB = new QLabel(this);
    rect = QRect(275, 888, 48, 40);
    labels.push_back(Label_D_rB);
    rects.push_back(rect);
    titles.push_back("rB");

    Label_D_valC = new QLabel(this);
    rect = QRect(323, 888, 96, 40);
    labels.push_back(Label_D_valC);
    rects.push_back(rect);
    titles.push_back("valC");

    Label_D_valP = new QLabel(this);
    rect = QRect(451, 888, 96, 40);
    labels.push_back(Label_D_valP);
    rects.push_back(rect);
    titles.push_back("valP");

    Label_predPC = new QLabel(this);
    rect = QRect(251, 1128, 96, 40);
    labels.push_back(Label_predPC);
    rects.push_back(rect);
    titles.push_back("0");

    for (int i = 0; i < labels.size(); ++i)
        labels[i]->setStyleSheet("background-color:cyan;border-width: 1px;border-color: black;border-style: solid;");

    _image.load(":/pipeline.bmp");
    setAutoFillBackground(true);
}

void GraphView::reset()
{
    for (int i = 0; i < labels.size(); ++i)
        labels[i]->setText(titles[i]);
}

void setState(QLabel *label, int stat)
{
    switch (stat)
    {
    case SAOK: label->setText("SAOK"); break;
    case SADR: label->setText("SADR"); break;
    case SINS: label->setText("SINS"); break;
    case SHLT: label->setText("SHLT"); break;
    }
}

void GraphView::updateUI()
{
    Label_predPC->setText(Tools::dec2hex(F_predPC, 3));

    Label_D_icode->setText(QString::number(D_icode));
    Label_D_ifun->setText(QString::number(D_ifun));
    Label_D_rA->setText(QString::number(D_rA));
    Label_D_rB->setText(QString::number(D_rB));
    Label_D_valC->setText(QString::number(D_valC));
    Label_D_valP->setText(QString::number(D_valP));

    Label_E_icode->setText(QString::number(E_icode));
    Label_E_ifun->setText(QString::number(E_ifun));
    Label_E_valC->setText(QString::number(E_valC));
    Label_E_valA->setText(QString::number(E_valA));
    Label_E_valB->setText(QString::number(E_valB));
    Label_E_dstE->setText(QString::number(E_dstE));
    Label_E_dstM->setText(QString::number(E_dstM));
    Label_E_srcA->setText(QString::number(E_srcA));
    Label_E_srcB->setText(QString::number(E_srcB));

    Label_M_icode->setText(QString::number(M_icode));
    if (M_Cnd)
        Label_M_Cnd->setText("True");
    else Label_M_Cnd->setText("false");
    Label_M_valE->setText(QString::number(M_valE));
    Label_M_valA->setText(QString::number(M_valA));
    Label_M_dstE->setText(QString::number(M_dstE));
    Label_M_dstM->setText(QString::number(M_dstM));

    Label_W_icode->setText(QString::number(W_icode));
    Label_W_valE->setText(QString::number(W_valE));
    Label_W_valM->setText(QString::number(W_valM));
    Label_W_dstE->setText(QString::number(W_dstE));
    Label_W_dstM->setText(QString::number(W_dstM));

    setState(Label_D_stat, D_stat);
    setState(Label_E_stat, E_stat);
    setState(Label_M_stat, M_stat);
    setState(Label_W_stat, W_stat);
    setState(Label_Stat, Final_stat);
}
