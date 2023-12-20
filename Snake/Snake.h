//
// Created by robert12 on 7/5/23.
//

#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H

#include <QWidget>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QTimerEvent>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

class Snake : public QWidget {
Q_OBJECT

private:
    QImage head, apple, body;

    static const int Width_ = 600;
    static const int Height_ = 600;
    static const int Body_size = 30;
    static const int all_bodys = 3600;
    static const int rand_pos = 19;
    static const int delay = 140;
    int score;
    int timerID, bodys, apple_x, apple_y;
    int x[all_bodys], y[all_bodys];
    bool right, left, up, down, inGame;
    bool pause_ = false;

    void loadImage();

    void initGame();

    void locateApple();

    void checkApple();

    void checkCollision();

    void move_();

    void doDrawing();

    void gameOver(QPainter &);

protected:
    void paintEvent(QPaintEvent *) override;

    void timerEvent(QTimerEvent *) override;

    void keyPressEvent(QKeyEvent *) override;

public:

    Snake(QWidget *parent = nullptr);

    bool get_right() const;

    bool get_left() const;

    bool get_up() const;

    bool get_down() const;

    // bool get_inGame()const;
    void set_right(bool new_right);

    void set_up(bool new_up);

    void set_down(bool new_down);

    void set_left(bool new_left);

    void set_pause(bool new_pause);

    void reinit();

signals:

    void Score(int scor);

    void GameStatus(bool status);
};


#endif //SNAKE_SNAKE_H
