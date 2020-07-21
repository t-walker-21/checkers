#ifndef PLAYERVAI_H
#define PLAYERVAI_H

#include <QDialog>
#include "board.h"
#include <QGraphicsScene>
#include <QMouseEvent>
#include "minimax.h"
#include <QDebug>
#include <QTimer>

namespace Ui {
class playervAI;
}

class playervAI : public QDialog
{
    Q_OBJECT

public:
    explicit playervAI(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent* e);
    ~playervAI();

private:
    Ui::playervAI *ui;
    board game_board;
    QGraphicsScene* scene;
    void update_board();
    void clearBoard();
    int game_state;
    int cache_move_val;
    std::pair<int, int> chosen_move;
    void game_over();
    minimax agent;
    QTimer* agentTimer;

private slots:
    void make_a_move();
};

#endif // PLAYERVAI_H
