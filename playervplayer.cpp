#include "playervplayer.h"
#include "ui_playervplayer.h"
#include "QDebug"

playerVplayer::playerVplayer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::playerVplayer)
{
    ui->setupUi(this);

    // Initialize board
    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    ui->graphicsView->scene()->setBackgroundBrush(QBrush(Qt::blue, Qt::SolidPattern));
    ui->graphicsView->setFixedHeight((BOARD_SIZE + 1) * 50);
    ui->graphicsView->setFixedWidth((BOARD_SIZE + 1) * 50);

    //qDebug() << QString::number(ui->graphicsView->height());
    //qDebug() << QString::number(ui->graphicsView->width());

    //ui->graphicsView->scene()->addLine(-190, 0, -140, 100, Qt::DashLine);

    // Add the vertical lines first, paint them red
    for (int x = 50; x < BOARD_SIZE * 50; x += 50)
        scene->addLine(x, 0, x, BOARD_SIZE * 50, QPen(Qt::white));

    // Now add the horizontal lines, paint them green
    for (int y=50; y < BOARD_SIZE * 50; y+=50)
        scene->addLine(0, y , BOARD_SIZE * 50, y, QPen(Qt::white));

    // Fit the view in the scene's bounding rect
    //ui->graphicsView->fitInView(scene->itemsBoundingRect());

    // Initialize board
    update_board();

    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(close()));
}

playerVplayer::~playerVplayer()
{
    //emit return_to_menu();
    delete ui;
}

void playerVplayer::mousePressEvent(QMouseEvent* event)
{
    // 430 is max(x)
    // 30 is min(x)

    // 40 is min(y)
    // 440 is max(y)

     int click_x = event->x();
     int click_y = event->y();

     if (click_x > 430 or click_x < 30 or click_y > 440 or click_y < 40)
     {
         return;
     }

     int board_x = ((event->y() - 30) / 50);
     int board_y = ((event->x() - 30) / 50);

     qDebug() << QString::number(board_x) << ", " << QString::number(board_y);
}

void playerVplayer::update_board()
{
    // Paint in game pieces according to their board state

    std::vector<std::vector<int>> state = game_board.get_state();

    for (int x = 20, i = 0; x < BOARD_SIZE * 50; x += 50, i++)
    {
        for (int y = 10, j = 0; y < BOARD_SIZE * 50; y += 50, j++)
        {
            if (state[j][i] == -1)
                scene->addRect(x, y, 20, 20, QPen(Qt::black), QBrush(Qt::black));

            else if(state[j][i] == 1)
                scene->addRect(x, y, 20, 20, QPen(Qt::black), QBrush(Qt::red));
        }
    }

    /*
    // Now add the horizontal lines, paint them green
    for (int y=50; y < BOARD_SIZE * 50; y+=50)
        scene->addLine(0, y , BOARD_SIZE * 50, y, QPen(Qt::white));
    */

}
