#include <QApplication>
#include <QPainter>
#include <QVBoxLayout>
#include "Snake.h"
#include "Game.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    auto *sn = new Snake();
    auto *lg = new Login();

    Game g{sn, lg};
    g.show();

    return QApplication::exec();
}
