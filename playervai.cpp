#include "playervai.h"
#include "ui_playervai.h"

playervAI::playervAI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::playervAI)
{
    ui->setupUi(this);
    // Initialize board
    scene = new QGraphicsScene();
    agentTimer = new QTimer();
    agentTimer->setInterval(1000);
    agentTimer->start();

    connect(agentTimer, SIGNAL(timeout()), this, SLOT(make_a_move()));
    clearBoard();
    // Fit the view in the scene's bounding rect
    //ui->graphicsView->fitInView(scene->itemsBoundingRect());

    // Initialize board
    update_board();
    game_state = 0;
}

playervAI::~playervAI()
{
    delete ui;
}

void playervAI::mousePressEvent(QMouseEvent *event)
{
    // 430 is max(x)
    // 30 is min(x)

    // 40 is min(y)
    // 440 is max(y)

    if (game_board.get_player_turn() != 1)
        return;


    // Process click event
     int click_x = event->x();
     int click_y = event->y();

     // Ignore inputs off the screen
     if (click_x > 430 or click_x < 30 or click_y > 440 or click_y < 40)
     {
         return;
     }

     // Convert click position to board position
     int board_x = ((event->y() - 30) / 50);
     int board_y = ((event->x() - 30) / 50);

     //qDebug() << QString::number(board_x) << ", " << QString::number(board_y);

     // Make sure choosen position is a piece that can be moved
     std::set<std::pair<int, int>> move_set;
     std::list<std::vector<int>> move_list;

     qDebug() << "look right here: " << QString::number(game_board.get_player_turn());

     game_board.get_available_moves(game_board.get_player_turn(), move_set, move_list);

     if (game_state == 0) // Player is choosing game piece to move
     {
         chosen_move = std::make_pair(board_x, board_y);
         if (move_set.find(chosen_move) == move_set.end()) // player clicked invalid start piece
         {
             qDebug() << "invalid move selected!!";
             return;
         }

         // Player choose a valid first move

         cache_move_val = game_board.get_state()[board_x][board_y];
         game_board.set_state(board_x, board_y, 10); // Highlight player piece
         clearBoard();
         update_board();
         game_state++;
         return;
     }

     if (game_state == 1) // A piece is already chosen, process the second click
     {
         move_set.clear();
         move_list.clear();

         game_board.get_available_moves(game_board.get_player_turn(), move_set, move_list);

         // Iterate through list of moves availble and confirm that a valid choice was made

        for (auto move: move_list)
        {
            if (move[0] == chosen_move.first and move[1] == chosen_move.second and move[2] == board_x and move[3] == board_y)
            {
                // Player has selected a valid move, submit this move to the board object and reset game state
                game_state = 0;
                if (game_board.process_move(move[0], move[1], move[2], move[3]))
                {
                    game_over();
                }
                clearBoard();
                update_board();
                return;
                //qDebug() << "you've chosen a valid move";
            }
        }

        // If this point is reached, no valid move was chosen, so reset back to non-selected
        game_board.set_state(chosen_move.first, chosen_move.second, cache_move_val); // Highlight player piece
        clearBoard();
        update_board();
        game_state = 0;

     }
}

void playervAI::update_board()
{
    // Paint in game pieces according to their board state

    // Update turn label
    if (game_board.get_player_turn() == 1)
        ui->label->setText(QString("Player turn: RED"));

    else
        ui->label->setText(QString("Player turn: BLACK"));

    // Update remaining pieces label
    ui->label_2->setText("RED REMAINING PIECES: " + QString::number(game_board.get_remaining_pieces(1)));
    ui->label_3->setText("BLACK REMAINING PIECES: " + QString::number(game_board.get_remaining_pieces(-1)));

    std::vector<std::vector<int>> state = game_board.get_state();

    for (int x = 20, i = 0; x < BOARD_SIZE * 50; x += 50, i++)
    {
        for (int y = 10, j = 0; y < BOARD_SIZE * 50; y += 50, j++)
        {
            if (state[j][i] == -1)
                scene->addRect(x, y, 20, 20, QPen(Qt::black), QBrush(Qt::black));

            else if(state[j][i] == 1)
                scene->addRect(x, y, 20, 20, QPen(Qt::black), QBrush(Qt::red));

            else if(state[j][i] == 10)
                scene->addRect(x, y, 20, 20, QPen(Qt::black), QBrush(Qt::green));
        }
    }

    /*
    // Now add the horizontal lines, paint them green
    for (int y=50; y < BOARD_SIZE * 50; y+=50)
        scene->addLine(0, y , BOARD_SIZE * 50, y, QPen(Qt::white));
    */
}

void playervAI::game_over()
{
    ui->label_4->setText("Game Over!!!");
}



void playervAI::clearBoard()
{
    // Clean the game board
    scene->clear();
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
}

void playervAI::make_a_move()
{

    //qDebug() << "hello there";
    if (game_board.get_player_turn() == 1) // Not the AI's turn
        return;

    agentTimer->stop();

    std::set<std::pair<int, int>> move_set;
    std::list<std::vector<int>> move_list;
    game_board.get_available_moves(game_board.get_player_turn(), move_set, move_list);

    std::vector<int> move = agent.get_random_move(move_list);

    if (game_board.process_move(move[0], move[1], move[2], move[3]))
    {
        game_over();
        clearBoard();
        update_board();
    }

    clearBoard();
    update_board();

    agentTimer->start();
}



