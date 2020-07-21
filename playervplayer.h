#ifndef PLAYERVPLAYER_H
#define PLAYERVPLAYER_H

#include <QDialog>
//#include "board.h"

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
    ~playerVplayer();

private:
    Ui::playerVplayer *ui;
    //board game_board;

};

#endif // PLAYERVPLAYER_H
