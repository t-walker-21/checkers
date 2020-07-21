#include "board.h"
#include<QDebug>

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
    return false;
}

void board::get_available_moves(bool player, std::set<std::pair<int, int>>& move_set, std::list<std::vector<int>>& move_list)
{
    // Populate a list of possible moves for the player

    if (player)
    {
        //qDebug() << "player one turn";

        // Iterate through all regular red pieces and calculate moves
        for (auto i: pieces_red)
        {
            //qDebug() << i.first << " " << i.second;
            std::vector<int> move;

            // Regular moves (up and left/right)
            if (state[i.first - 1][i.second - 1] == 0 and i.second != 0) // Can move up and to the left
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

            if (state[i.first - 1][i.second + 1] == 0 and i.second != BOARD_SIZE - 1) // Can move up and to the right
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
            if (state[i.first - 1][i.second - 1] == -1 and state[i.first - 2][i.second - 2] == 0) // Can move up and to the left to capture
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

            if (state[i.first - 1][i.second + 1] == -1 and state[i.first - 2][i.second + 2] == 0) // Can move up and to the right to capture
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
        qDebug() << "player two turn";
    }

}

std::vector<std::vector<int>> board::get_state()
{
    return state;
}
