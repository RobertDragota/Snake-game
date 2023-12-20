//
// Created by robert12 on 7/5/23.
//

#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include "Snake.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QObject>
#include <QTextEdit>
#include <QTableWidget>
#include <QTableView>
#include <QHeaderView>
#include <QSizePolicy>
#include <vector>
#include <algorithm>
#include <string>
#include <utility>
#include <fstream>


using std::vector;
using std::string;
using std::sort;
using std::find_if;
using std::pair;
using std::ifstream;
using std::ofstream;

class Login : public QWidget {
Q_OBJECT

private:
    QLineEdit *username = new QLineEdit("");
    QPushButton *play = new QPushButton("&Play");
    QHBoxLayout *mainLayout = new QHBoxLayout();
public:
    Login() {
        emit Status(false);
        initLogin();
        connectLogin();
    }

    void initLogin();

    void connectLogin();

signals:

    void Status(bool stat);

    void UserName(string urs);
};

class Game : public QWidget {
Q_OBJECT

private:
    Snake *sn;
    Login *log;
    string username;
    QStringList table_header;
    vector<pair<string, int>> score_list;
    QString res_val;
    QTableWidget *tableWidget = new QTableWidget();
    QLabel *pause_label = new QLabel("Press 'P' key for pause.", this);
    QLabel *resume_label = new QLabel("Press 'S' key for resume.", this);
    QPushButton *replay = new QPushButton("&Replay");
    QLineEdit *score = new QLineEdit("0");
    QHBoxLayout *mainLayout = new QHBoxLayout();
    QVBoxLayout *infoLayout = new QVBoxLayout();
protected:
    void keyPressEvent(QKeyEvent *) override;


public:
    Game(Snake *s, Login *lg) : sn{s}, log{lg} {

        initGame();
        connect();
        load_from_file();

    }

    void connect();

    void initGame();

    void save_to_file();

    void load_from_file();

public slots:

    void handleSignal(int scor);

    void handleTimeSignal(bool status);

    void handleLoginSignal(bool status);

    void handleUSRSignal(string usr);

};


#endif //SNAKE_GAME_H
