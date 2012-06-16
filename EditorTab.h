#ifndef EDITORTAB_H
#define EDITORTAB_H

#include <QWidget>
#include "Constants.h"

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

    bool compile();

    bool isEmpty, isCompiled;
    QString getASM();
    QString getBinary();
    char* getMemory();

signals:
    void titleChanged();
    void iconChanged();

private slots:
    void changeState();
private:
    EditorTabPrivate *d;
    QTextEdit *binaryEdit, *asmEdit;
    char memory[MAX_ADD];
};
#endif // EDITORTAB_H
