#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(launch_multiplayer_game()));
    connect(ui->pushButton_2, SIGNAL(clicked(bool)), this, SLOT(launch_single_player_game()));

    /*
    std::vector<std::vector<int>> state = game_board.get_state();

    QString s;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            s.append(QString::number(state[i][j]) + " ");
        }
        s.append("\n");
    }

    ui->label->setText(s);

    std::list<std::vector<int>> red_moves;
    std::set<std::pair<int, int>> move_set;
    game_board.get_available_moves(true, move_set, red_moves);

    /*for (auto mov: red_moves)
    {
        qDebug() << QString::number(mov[0]) +  "," + QString::number(mov[1]) + " to: " + QString::number(mov[2]) << ", " + QString::number(mov[3]);
    }*/

    /*
    for (auto mov: move_set)
    {
        qDebug() << QString::number(mov.first) +  "," + QString::number(mov.second);
    }*/

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::launch_multiplayer_game()
{
    // Instantiate new game window
    multiplayer_window = new playerVplayer();
    //connect(multiplayer_window, SIGNAL(return_to_menu()), this, SLOT(show()));

    // Connect pointer handler
    connect(multiplayer_window, SIGNAL(destroyed(QObject*)), this, SLOT(clean_pointers()));

    // Show the game window
    multiplayer_window->show();

    //this->hide();
}

void MainWindow::launch_single_player_game()
{
    // Instantiate new game window
    player_window = new playervAI();
    //connect(multiplayer_window, SIGNAL(return_to_menu()), this, SLOT(show()));

    // Connect pointer handler
    connect(player_window, SIGNAL(destroyed(QObject*)), this, SLOT(clean_pointers()));

    // Show the game window
    player_window->show();

    //this->hide();
}

void MainWindow::clean_pointers()
{
    qDebug() << "here";
    delete multiplayer_window;
}
