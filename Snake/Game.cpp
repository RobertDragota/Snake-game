//
// Created by robert12 on 7/5/23.
//

#include "Game.h"
#include "QDebug"
#include <QMessageBox>

void Login::initLogin() {

    setLayout(mainLayout);
    mainLayout->addWidget(username);
    mainLayout->addWidget(play);

}

void Login::connectLogin() {
    QObject::connect(play, &QPushButton::clicked, [this] {

        if (!username->text().isEmpty()) {
            emit Status(true);
            emit UserName(username->text().toStdString());
            this->close();
        } else
            QMessageBox::warning(nullptr, "Warning", "Your username should have at least 1 character!");
    });
}

void Game::initGame() {

    log->show();
    setLayout(mainLayout);

    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    tableWidget->setRowCount(23);
    tableWidget->setColumnCount(2);

    table_header << "Name" << "Score";
    tableWidget->setHorizontalHeaderLabels(table_header);
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->addWidget(sn);
    auto form_layout = new QFormLayout;
    form_layout->addRow("Scor:", score);

    infoLayout->addLayout(form_layout);
    infoLayout->addWidget(tableWidget);
    infoLayout->addWidget(pause_label);
    infoLayout->addWidget(resume_label);
    infoLayout->addWidget(replay);
    mainLayout->addLayout(infoLayout);

}

void Game::connect() {
    QObject::connect(sn, &Snake::Score, this, &Game::handleSignal);
    QObject::connect(sn, &Snake::GameStatus, this, &Game::handleTimeSignal);
    QObject::connect(log, &Login::Status, this, &Game::handleLoginSignal);
    QObject::connect(log, &Login::UserName, this, &Game::handleUSRSignal);

    QObject::connect(replay, &QPushButton::clicked, [this] {
        sn->reinit();
        save_to_file();
        score->setText("0");

        //load_from_file();

    });

}

void Game::handleSignal(int scor) {
    score->setText(QString::number(scor));
}

void Game::keyPressEvent(QKeyEvent *e) {
    int key = e->key();
    switch (key) {
        case Qt::Key_P: {
            //qDebug() << "AM APASAT TASTA P\n";
            if (sn->get_down())
                res_val = "down";
            if (sn->get_up())
                res_val = "up";
            if (sn->get_right())
                res_val = "right";
            if (sn->get_left())
                res_val = "left";
            sn->set_down(false);
            sn->set_up(false);
            sn->set_right(false);
            sn->set_left(false);
            sn->set_pause(true);
        }
            break;
        case Qt::Key_S: {
            // qDebug() << "AM APASAT TASTA S\n";
            if (res_val == "down")
                sn->set_down(true);
            if (res_val == "up")
                sn->set_up(true);
            if (res_val == "left")
                sn->set_left(true);
            if (res_val == "right")
                sn->set_right(true);
            sn->set_pause(false);
            sn->setFocusPolicy(Qt::StrongFocus);
        }
            break;
        default:
            QWidget::keyPressEvent(e);
    }

}


void Game::save_to_file() {

    int score_ = score->text().toInt();
    auto find = find_if(score_list.begin(), score_list.end(), [&](const pair<string, int> &p1) -> bool {
        return p1.first == username;
    });
    //auto found = std::find(score_list.begin(), score_list.end(),find_rule);
    if (find == score_list.end())
        score_list.emplace_back(username, score_);
    else {
        if (find->second < score_)
        {
            score_list.erase(find);
            pair<string,int> pr{username,score_};
            score_list.emplace_back(pr);
        }

    }
    auto sort_rule = [&](const pair<string, int> &p1, const pair<string, int> &p2) -> bool {
        return p1.second > p2.second;
    };
    sort(score_list.begin(), score_list.end(), sort_rule);
    ofstream out("score_file.txt");
    for (const auto &el: score_list)
        out << el.first << " " << el.second << "\n";

}

void Game::load_from_file() {
    ifstream in("score_file.txt");
    score_list.clear();
    int score_;
    string name;
    while (in >> name >> score_) {
        score_list.emplace_back(name, score_);
    }

    tableWidget->clear();
    table_header << "Name" << "Score";
    tableWidget->setHorizontalHeaderLabels(table_header);
    int rows = tableWidget->rowCount();
    if (score_list.size() > rows)
        tableWidget->insertRow(rows);
    int i = 0;
    for (const auto &el: score_list) {
        auto field1 = new QTableWidgetItem(QString::fromStdString(el.first));
        auto field2 = new QTableWidgetItem(QString::fromStdString(std::to_string(el.second)));
        field1->setFlags(field1->flags() ^ Qt::ItemIsEditable);
        field2->setFlags(field2->flags() ^ Qt::ItemIsEditable);
        tableWidget->setItem(i, 0, field1);
        tableWidget->setItem(i, 1, field2);
        i++;
    }
}

void Game::handleTimeSignal(bool status) {
    if (!status) {
        save_to_file();
        load_from_file();
    }
}

void Game::handleLoginSignal(bool status) {
    if (status) {
        sn->set_pause(false);
        sn->set_right(true);
    }
}

void Game::handleUSRSignal(string usr) {
    username = usr;
}

