#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gameview.h"

#include <QGraphicsScene>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void timerEvent(QTimerEvent */* unused */);
    void keyPressEvent(QKeyEvent *event);

private slots:
    void onStartClick();
    void onCloseClick();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    int timerId;
    bool gameOverScreen = false;
    GameView *view;
};
#endif // MAINWINDOW_H
