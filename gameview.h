#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsItem>

class GameView: public QGraphicsItem
{
public:
    GameView(QGraphicsItem *parent = NULL);
    void update();
    void jump();
    bool isGameOver = false;

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

private:
    struct Pipe {
        int x;
        int start;
        int gap;
    };
    int score = 0;

    float position = 100;
    float velocity = 0;
    float acceleration = 0.4;
    int totalPipes = 5;
    struct Pipe pipes[5];
    int firstPipeIndex = 0;

    void drawPipes(QPainter *painter);
    void generateNewPipe();
    void checkGameOver();
};

#endif // GAMEVIEW_H
