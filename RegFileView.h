#ifndef REGFILEVIEW_H
#define REGFILEVIEW_H

#include <QWidget>

class QLineEdit;
class RegFileView : public QWidget
{
    Q_OBJECT
public:
    explicit RegFileView(QWidget *parent = 0);
    void updateUI();

signals:
    
public slots:

private:
    QLineEdit *edit_eax, *edit_ecx, *edit_edx, *edit_ebx, *edit_esp, *edit_ebp, *edit_esi, *edit_edi;
    QLineEdit *edit_ZF, *edit_SF, *edit_OF;
};

#endif // REGFILEVIEW_H
