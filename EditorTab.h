#ifndef EDITORTAB_H
#define EDITORTAB_H

#include <QWidget>

class EditorTabPrivate;
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

signals:
    void titleChanged();
    void iconChanged();

private:
    EditorTabPrivate *d;
};
#endif // EDITORTAB_H
