#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QStackedWidget>

class EditorWindow;
class SimWindow;
class PictureFlow;
class MainWindow : public QStackedWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    
signals:
    
public slots:

private slots:
    void showTabMode(int index = -1);
    void showSlideMode();

private:
    EditorWindow *editorWindow;
    SimWindow *simWindow;
    PictureFlow *pictureFlow;
};

#endif // MAINWINDOW_H
