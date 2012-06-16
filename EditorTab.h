#ifndef EDITORTAB_H
#define EDITORTAB_H

#include <QWidget>

class EditorTabPrivate;
class QTextEdit;
class EditorTab: public QWidget
{
        Q_OBJECT

public:
        explicit EditorTab(QWidget *parent = 0);
    ~EditorTab();

    QIcon icon() const;
    void setIcon(const QIcon &icon);
    QString title() const;
    void setTitle(const QString &title);

    QImage renderImage();

    void setASM(QString text);

    bool isEmpty;

signals:
    void titleChanged();
    void iconChanged();

private:
    EditorTabPrivate *d;
    QTextEdit *binaryEdit, *asmEdit;

};
#endif // EDITORTAB_H
