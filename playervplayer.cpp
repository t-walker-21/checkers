#include "playervplayer.h"
#include "ui_playervplayer.h"

playerVplayer::playerVplayer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::playerVplayer)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(close()));
}

playerVplayer::~playerVplayer()
{
    emit return_to_menu();
    delete ui;
}
