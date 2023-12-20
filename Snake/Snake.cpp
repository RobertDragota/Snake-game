//
// Created by robert12 on 7/5/23.
//

#include "Snake.h"
#include <QTimer>
#include <QPainter>
#include <ctime>
#include <cstdlib>
#include <QStyleOption>

Snake::Snake(QWidget *parent) : QWidget(parent) {
    setFixedSize(Width_, Height_);
    setStyleSheet("background-color:white");
    setFocusPolicy(Qt::StrongFocus);
    score = 0;
    left = false, right = false;
    up = false, down = false;
    inGame = true;
    loadImage();
    initGame();

}

void Snake::loadImage() {

    body.load("body.png");
    head.load("head.png");
    apple.load("apple.png");
    body = body.scaled(30, 30);
    head = head.scaled(30, 30);
    head = head.transformed(QTransform().rotate(-90));
    apple = apple.scaled(30, 30);
}

void Snake::initGame() {
    bodys = 3;
    for (int k = 0; k < bodys; k++) {
        x[k] = 60 - 30 * k;
        y[k] = 60;
    }
    locateApple();
    timerID = startTimer(delay);
}

void Snake::locateApple() {
    srand(time(NULL));
    int c = rand() % rand_pos;
    apple_x = c * Body_size;
    c = rand() % rand_pos;
    apple_y = c * Body_size;
}


void Snake::checkApple() {
    if (!pause_) {
        if (x[0] == apple_x && y[0] == apple_y) {
            bodys++, locateApple();
            score += 15;
            emit Score(score);
        }
    }
}

void Snake::checkCollision() {
    if (!pause_) {
        for (int k = bodys; k > 0; k--)
            if (k >= 4 && x[0] == x[k] && y[0] == y[k])
                inGame = false;
        if (x[0] >= Width_)
            x[0] = x[0] % Width_;
        if (x[0] < 0)
            x[0] = Width_;
        if (y[0] >= Height_)
            y[0] = y[0] % Height_;
        if (y[0] < 0)
            y[0] = Height_;
    }
}

void Snake::move_() {
    if (!pause_) {
        if (!inGame) {
            killTimer(timerID);
            emit GameStatus(inGame);

        }
        for (int k = bodys; k > 0; k--) {
            x[k] = x[k - 1];
            y[k] = y[k - 1];
        }
        if (right)
            x[0] += Body_size;
        if (left)
            x[0] -= Body_size;
        if (up)
            y[0] -= Body_size;
        if (down)
            y[0] += Body_size;

    }
}

void Snake::doDrawing() {
    QPainter p(this);
    if (inGame) {
        int width = this->width();
        int height = this->height();
        int grid_size = 30;
        int x_step = width / grid_size;
        int y_step = height / grid_size;
        p.setPen(Qt::gray);
        for (int i = 0; i <= x_step; i++) {
            int x_ = i * grid_size;
            p.drawLine(x_, 0, x_, height);
        }
        for (int j = 0; j <= y_step; j++) {
            int y_ = j * grid_size;
            p.drawLine(0, y_, width, y_);
        }
        p.drawImage(apple_x, apple_y, apple);
        for (int k = 0; k < bodys; k++)
            if (k == 0)
                p.drawImage(x[k], y[k], head);
            else
                p.drawImage(x[k], y[k], body);
    } else {
        gameOver(p);
    }
}

void Snake::gameOver(QPainter &e) {
    QString message = "Game over!";
    QFont font("Courier", 15, QFont::DemiBold);
    QFontMetrics fm(font);
    int textWidth = fm.horizontalAdvance(message);
    e.setFont(font);
    int h = height();
    int w = width();
    e.translate(QPoint(w / 2, h / 2));
    e.setPen(Qt::black);
    e.drawText(-textWidth / 2, 0, message);

}

void Snake::paintEvent(QPaintEvent *e) {
    Q_UNUSED(e);
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    doDrawing();
}

void Snake::timerEvent(QTimerEvent *e) {
    Q_UNUSED(e);

    if (inGame) {
        checkApple();
        checkCollision();
        move_();
    }
    if (!pause_)
        repaint();
}

void Snake::keyPressEvent(QKeyEvent *e) {


    int key = e->key();
    switch (key) {
        case Qt::Key_Left:
            if (!right && !pause_) {
                //qDebug() << "AM APASAT TASTA stanga\n";
                if (up)
                    head = head.transformed(QTransform().rotate(-90));
                if (down)
                    head = head.transformed(QTransform().rotate(90));
                left = true;
                up = false;
                down = false;
            }
            break;

        case Qt::Key_Right:
            if (!left && !pause_) {
                //qDebug() << "AM APASAT TASTA dreapta\n";
                if (up)
                    head = head.transformed(QTransform().rotate(90));
                if (down)
                    head = head.transformed(QTransform().rotate(-90));
                right = true;
                up = false;
                down = false;
            }
            break;

        case Qt::Key_Up:
            if (!down && !pause_) {
                //qDebug() << "AM APASAT TASTA sus\n";
                if (right)
                    head = head.transformed(QTransform().rotate(-90));
                if (left)
                    head = head.transformed(QTransform().rotate(90));
                left = false;
                right = false;
                up = true;
            }
            break;

        case Qt::Key_Down:
            if (!up && !pause_) {
                //qDebug() << "AM APASAT TASTA jos\n";
                if (right)
                    head = head.transformed(QTransform().rotate(90));
                if (left)
                    head = head.transformed(QTransform().rotate(-90));
                left = false;
                right = false;
                down = true;
            }
            break;
        default:
            QWidget::keyPressEvent(e);
            break;
    }


}

void Snake::set_right(bool new_right) {
    right = new_right;
}

void Snake::set_up(bool new_up) {
    up = new_up;
}

void Snake::set_down(bool new_down) {
    down = new_down;
}

void Snake::set_left(bool new_left) {
    left = new_left;
}

bool Snake::get_right() const {
    return right;
}

bool Snake::get_left() const {
    return left;
}

bool Snake::get_up() const {
    return up;
}

bool Snake::get_down() const {
    return down;
}

void Snake::set_pause(bool new_pause) {
    pause_ = new_pause;
}

void Snake::reinit() {
    if (inGame)
        killTimer(timerID);
    setFixedSize(Width_, Height_);
    setStyleSheet("background-color:white");
    setFocusPolicy(Qt::StrongFocus);
    score = 0;
    left = false, right = true;
    up = false, down = false;
    inGame = true;
    loadImage();
    initGame();
}


