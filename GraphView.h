#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H

#include <QWidget>
#include <QVector>

class QImage;
class QLabel;
class GraphView : public QWidget
{
    Q_OBJECT
public:
    explicit GraphView(QWidget *parent = 0);
    void updateUI();
    void reset();

protected:
    void resizeEvent(QResizeEvent *event);

signals:
    
public slots:

private:
    QImage _image;
    QLabel *Label_Stat, *Label_W_stat, *Label_W_icode, *Label_W_valE, *Label_W_valM, *Label_W_dstE, *Label_W_dstM,
    *Label_M_stat, *Label_M_icode, *Label_M_Cnd, *Label_M_valE, *Label_M_valA, *Label_M_dstE, *Label_M_dstM,
    *Label_E_stat, *Label_E_icode, *Label_E_ifun, *Label_E_valC, *Label_E_valA, *Label_E_valB, *Label_E_dstE, *Label_E_dstM, *Label_E_srcA, *Label_E_srcB,
    *Label_D_stat, *Label_D_icode, *Label_D_ifun, *Label_D_rA, *Label_D_rB, *Label_D_valC, *Label_D_valP, *Label_predPC;
    QVector<QLabel*> labels;
    QVector<QRect> rects;
    QVector<QString> titles;
};

#endif // GRAPHVIEW_H
