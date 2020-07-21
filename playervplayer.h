#ifndef PLAYERVPLAYER_H
#define PLAYERVPLAYER_H

#include <QDialog>
#include "board.h"
#include <QGraphicsScene>
#include <QMouseEvent>

namespace Ui {
class playerVplayer;
}

class playerVplayer : public QDialog
{
    Q_OBJECT

signals:
    void return_to_menu();

public:
    explicit playerVplayer(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent* e);
    ~playerVplayer();

private:
    Ui::playerVplayer *ui;
    board game_board;
    QGraphicsScene* scene;
    void update_board();
    void clearBoard();
    int game_state;
    int cache_move_val;
    std::pair<int, int> chosen_move;
    void game_over();

};

#endif // PLAYERVPLAYER_H
