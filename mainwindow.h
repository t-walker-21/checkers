#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <playervplayer.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

private:
    Ui::MainWindow *ui;
    playerVplayer* multiplayer_window;
    //board game_board;

private slots:
    void launch_multiplayer_game();
    void clean_pointers();
};

#endif // MAINWINDOW_H
