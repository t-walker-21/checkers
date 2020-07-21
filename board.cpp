#include "board.h"
#include<QDebug>

board::board(const board &b2)
{
    state = b2.state;
    player_turn = b2.player_turn;
    pieces_black = b2.pieces_black;
    pieces_red = b2.pieces_red;
    kings_black = b2.kings_black;
    kings_red = b2.kings_red;
}

board::board()
{
    // Initialize board

    // First put zeros on board
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        std::vector<int> vec;
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            vec.push_back(0);
        }
        state.push_back(vec);
    }

    // Now, place players 1 will be red, -1 will be black. Also, populate piece sets
    for (int i = 1; i < BOARD_SIZE; i += 2)
    {
        // Black player
        state[0][i] = -1;
        state[2][i] = -1;

        pieces_black.insert(std::make_pair(0, i));
        pieces_black.insert(std::make_pair(2, i));

        // Red Player
        state[6][i] = 1;
        pieces_red.insert(std::make_pair(6, i));
    }

    for (int i = 0; i < BOARD_SIZE; i += 2)
    {
        // Black player
        state[1][i] = -1;
        pieces_black.insert(std::make_pair(1, i));

        // Red Player
        state[5][i] = 1;
        state[7][i] = 1;

        pieces_red.insert(std::make_pair(5, i));
        pieces_red.insert(std::make_pair(7, i));
    }

    //print_board();

    // Player one goes first (RED)
    player_turn = 1;
}

void board::print_board()
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            qDebug() << state[i][j];
        }
        qDebug() << "\n";
    }
}

bool board::check_win()
{
    // Check if game is over
    return false;
}

void board::get_available_moves(int player, std::set<std::pair<int, int>>& move_set, std::list<std::vector<int>>& move_list)
{
    // Populate a list of possible moves for the player

    if (player == 1)
    {
        //qDebug() << "player one turn";

        // Iterate through all regular red pieces and calculate moves
        for (auto i: pieces_red)
        {
            //qDebug() << i.first << " " << i.second;
            std::vector<int> move;

            // Regular moves (up and left/right)
            if (i.first != 0 and i.second != 0 and state[i.first - 1][i.second - 1] == 0) // Can move up and to the left
            {
                // Hash the fact that this piece has a possible move
                move_set.insert(std::make_pair(i.first, i.second));

                // Add this move
                move.push_back(i.first);
                move.push_back(i.second);
                move.push_back(i.first - 1);
                move.push_back(i.second - 1);

                move_list.push_back(move);
                move.clear();
            }

            if (i.first != 0 and i.second != BOARD_SIZE - 1 and state[i.first - 1][i.second + 1] == 0) // Can move up and to the right
            {
                // Hash the fact that this piece has a possible move
                move_set.insert(std::make_pair(i.first, i.second));

                // Add this move
                move.push_back(i.first);
                move.push_back(i.second);
                move.push_back(i.first - 1);
                move.push_back(i.second + 1);

                move_list.push_back(move);
                move.clear();
            }

            // Capture moves (up two and left/right)
            if (i.first > 1 and i.second > 1 and state[i.first - 1][i.second - 1] == -1 and state[i.first - 2][i.second - 2] == 0) // Can move up and to the left to capture
            {
                // Hash the fact that this piece has a possible move
                move_set.insert(std::make_pair(i.first, i.second));

                // Add this move
                move.push_back(i.first);
                move.push_back(i.second);
                move.push_back(i.first - 2);
                move.push_back(i.second - 2);
                move_list.push_back(move);
                move.clear();
            }

            if (i.first > 1 and i.second < BOARD_SIZE - 2 and state[i.first - 1][i.second + 1] == -1 and state[i.first - 2][i.second + 2] == 0) // Can move up and to the right to capture
            {
                // Hash the fact that this piece has a possible move
                move_set.insert(std::make_pair(i.first, i.second));

                // Add this move
                move.push_back(i.first);
                move.push_back(i.second);
                move.push_back(i.first - 2);
                move.push_back(i.second + 2);
                move_list.push_back(move);
                move.clear();
            }
        }

    }

    else
    {
        //qDebug() << "calcing black";

        // Iterate through all regular black pieces and calculate moves
        for (auto i: pieces_black)
        {
            //qDebug() << i.first << " " << i.second;
            std::vector<int> move;

            // Regular moves (down and left/right)
            if (i.first != BOARD_SIZE - 1 and i.second != 0 and state[i.first + 1][i.second - 1] == 0) // Can move down and to the left
            {
                // Hash the fact that this piece has a possible move
                move_set.insert(std::make_pair(i.first, i.second));

                // Add this move
                move.push_back(i.first);
                move.push_back(i.second);
                move.push_back(i.first + 1);
                move.push_back(i.second - 1);

                move_list.push_back(move);
                move.clear();
            }

            if (i.first != BOARD_SIZE - 1 and i.second < BOARD_SIZE - 1 and state[i.first + 1][i.second + 1] == 0) // Can move down and to the right
            {
                // Hash the fact that this piece has a possible move
                move_set.insert(std::make_pair(i.first, i.second));

                // Add this move
                move.push_back(i.first);
                move.push_back(i.second);
                move.push_back(i.first + 1);
                move.push_back(i.second + 1);

                move_list.push_back(move);
                move.clear();
            }

            // Capture moves (down two and left/right)
            if (i.first != BOARD_SIZE - 2 and i.second < BOARD_SIZE - 2 and state[i.first + 1][i.second + 1] == 1 and state[i.first + 2][i.second + 2] == 0) // Can move down and to the right to capture
            {
                // Hash the fact that this piece has a possible move
                move_set.insert(std::make_pair(i.first, i.second));

                // Add this move
                move.push_back(i.first);
                move.push_back(i.second);
                move.push_back(i.first + 2);
                move.push_back(i.second + 2);
                move_list.push_back(move);
                move.clear();
            }

            if (i.first != BOARD_SIZE - 2 and i.second > 1 and state[i.first + 1][i.second - 1] == 1 and state[i.first + 2][i.second - 2] == 0) // Can move down and to the left to capture
            {
                // Hash the fact that this piece has a possible move
                move_set.insert(std::make_pair(i.first, i.second));

                // Add this move
                move.push_back(i.first);
                move.push_back(i.second);
                move.push_back(i.first + 2);
                move.push_back(i.second - 2);
                move_list.push_back(move);
                move.clear();
            }
        }


    }

}

std::vector<std::vector<int>> board::get_state()
{
    // Return current board state
    return state;
}

int board::get_player_turn()
{
    // Return the turn of the current player
    return player_turn;
}

void board::set_state(int i, int j, int v)
{
    // Set board state to value
    state[i][j] = v;
}

bool board::process_move(int a, int b, int c, int d)
{
    // Take in a move and process it

    // Move piece at location
    state[a][b] = 0;
    state[c][d] = player_turn;

    bool capture = false;
    int dx, dy;

    if (std::abs(a - c) == 2)
    {
       //qDebug() << "********CAPTURE*******";
        capture = true;

        dx = a - c;
        dy = b - d;
        //qDebug() << dx << ", " << dy;
    }

    // Now toggle the player turn and alter the piece sets
    if (player_turn == 1)
    {
        pieces_red.erase(std::make_pair(a, b));
        pieces_red.insert(std::make_pair(c, d));
        player_turn = -1;


        if (capture)
        {
            if (dx > 0)
                dx = -1;

            else
                dx = 1;

            if (dy > 0)
                dy = -1;

            else
                dy = 1;
            set_state(a + dx, b + dy, 0);
            pieces_black.erase(std::make_pair(a + dx, b + dy));
        }
    }

    else
    {
        pieces_black.erase(std::make_pair(a, b));
        pieces_black.insert(std::make_pair(c, d));
        player_turn = 1;

        if (capture)
        {
            if (dx > 0)
                dx = -1;

            else
                dx = 1;

            if (dy > 0)
                dy = -1;

            else
                dy = 1;

            //qDebug() << a + dx << ", " << b + dy;
            set_state(a + dx, b + dy, 0);
            pieces_red.erase(std::make_pair(a + dx, b + dy));
        }
    }

    if (c == 0 and player_turn == -1)
    {
        pieces_red.erase(std::make_pair(c, d));
        kings_red.insert(std::make_pair(c, d));
    }

    if (c == BOARD_SIZE - 1 and player_turn == 1)
    {
        pieces_black.erase(std::make_pair(c, d));
        kings_black.insert(std::make_pair(c, d));
    }

    if (pieces_black.size() + kings_black.size() == 0 or pieces_red.size() + kings_red.size() == 0)
        return true;

    else
        return false;
}

int board::get_remaining_pieces(int player)
{
    if (player == 1)
        return pieces_red.size() + kings_red.size();

    return pieces_black.size() + kings_black.size();
}

int board::get_num_kings(int player)
{
    if (player == 1)
        return kings_red.size();

     return kings_black.size();
}

int board::get_num_pawns(int player)
{
    if (player == 1)
        return pieces_red.size();

    return pieces_black.size();

}
