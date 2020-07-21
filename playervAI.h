#ifndef PLAYERVAI_H
#define PLAYERVAI_H

#include <QDialog>
#include "board.h"
#include <QGraphicsScene>
#include <QMouseEvent>

namespace Ui {
class playerVAI;
}

class playerVAI : public QDialog
{
    Q_OBJECT

signals:
    void return_to_menu();

public:
    explicit playerVAI(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent* e);
    ~playerVAI();

private:
    Ui::playerVAI *ui;
    board game_board;
    QGraphicsScene* scene;
    void update_board();
    void clearBoard();
    int game_state;
    int cache_move_val;
    std::pair<int, int> chosen_move;
    void game_over();

};

#endif // PLAYERVAI_H
