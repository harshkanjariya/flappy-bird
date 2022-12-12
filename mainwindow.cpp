#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QColor>
#include <QGraphicsEllipseItem>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->startButton, SIGNAL(clicked()), this, SLOT(onStartClick()));
    connect(ui->closeButton, SIGNAL(clicked()), this, SLOT(onCloseClick()));
    ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidget->widget(1)->setContentsMargins(0,0,0,0);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::onCloseClick() {
    QCoreApplication::quit();
}

void MainWindow::onStartClick()
{
    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);

    timerId = startTimer(30);

    ui->stackedWidget->setCurrentIndex(1);
    scene->setBackgroundBrush(QColor(0, 204, 255));
    view = new GameView();
    scene->addItem(view);
}

void MainWindow::timerEvent(QTimerEvent *) {
    if (!gameOverScreen) {
        view->update();
        if (view->isGameOver) {
            killTimer(timerId);
            timerId = startTimer(4000);
            gameOverScreen = true;
        }
    } else {
        gameOverScreen = false;
        killTimer(timerId);
        scene->removeItem(view);
        ui->stackedWidget->setCurrentIndex(0);
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event -> key()) {
        case Qt::Key_Space:
            view->jump();
            break;
    }
}
