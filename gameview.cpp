#include "gameview.h"
#include <QPainter>
#include <QRandomGenerator>

GameView::GameView(QGraphicsItem *parent): QGraphicsItem(parent)
{
    for(int i=0; i<totalPipes;i++){
        pipes[i].x = i * 300 + 500;
        pipes[i].start = QRandomGenerator::global()->bounded(200) + 100;
        pipes[i].gap = 150;
    }
}
void GameView::generateNewPipe() {
    int previousIndex = firstPipeIndex == 0 ? totalPipes - 1 : firstPipeIndex - 1;
    pipes[firstPipeIndex].x = pipes[previousIndex].x + 300;
    pipes[firstPipeIndex].start = QRandomGenerator::global()->bounded(200) + 100;
    pipes[firstPipeIndex].gap = 150;
    firstPipeIndex = firstPipeIndex == totalPipes - 1 ? 0 : firstPipeIndex + 1;
}

QRectF GameView::boundingRect() const {
    return QRectF(0,0,750,520);
}

void GameView::drawPipes(QPainter *painter) {
    for(int i=0; i<totalPipes;i++){
        int y1 = pipes[i].start - 390;
        int h = 390;
        int y2 = pipes[i].start + pipes[i].gap;
        painter->drawImage(QRect(pipes[i].x, y1, 60, h), QImage(":/images/pipe-inverted.png"));
        painter->drawImage(QRect(pipes[i].x, y2, 60, h), QImage(":/images/pipe.png"));
    }
}
void GameView::checkGameOver() {
    if (position > 500 || position < -20) {
        isGameOver = true;
        return;
    }
    for(int i=0; i<totalPipes;i++){
        int x = pipes[i].x;
        if (128 > x && 100 < x + 60 && (position < pipes[i].start || position > pipes[i].start+pipes[i].gap)) {
            isGameOver = true;
        }
    }
}

void GameView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    if(!isGameOver) {
        drawPipes(painter);

        int x = 100;
        int y = position;
        int w = 30;
        int h = 20;
        int rotation = (velocity > 10 ? 10 : velocity) * 6;
        painter->save();
        painter->translate(x + w/2,y + h/2);
        painter->rotate(rotation);
        painter->drawImage(QRect(-w/2, -h/2, w, h), QImage(":/images/bird.png"));
        painter->restore();

        QString s = QString("Score: %1").arg(score);
        painter->drawText(QPoint(20,20), s);
    } else {
        QString scr = QString("Score: %1").arg(score);
        QFont font = painter->font();
        font.setPixelSize(40);
        painter->setFont(font);

        painter->setPen(QColor(255,0,0));
        painter->drawText(QPoint(280,200), "GAME OVER!");

        painter->setPen(QColor(0,0,255));
        painter->drawText(QPoint(320,300), scr);
    }
}

void GameView::update() {
    velocity += acceleration;
    position += velocity;
    for(int i=0; i<totalPipes;i++){
        pipes[i].x--;
        if (pipes[i].x + 60 == 99) {
            score++;
        }
        if (pipes[i].x < -100) {
            generateNewPipe();
        }
    }
    checkGameOver();

    QGraphicsItem::update();
}

void GameView::jump() {
    velocity = -7;
}
