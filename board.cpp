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

    // Now, place players 1 will be red, -1 will be black
    for (int i = 1; i < BOARD_SIZE; i += 2)
    {
        // Black player
        state[0][i] = -1;
        state[2][i] = -1;

        // Red Player
        state[6][i] = 1;
    }

    for (int i = 0; i < BOARD_SIZE; i += 2)
    {
        // Black player
        state[1][i] = -1;

        // Red Player
        state[5][i] = 1;
        state[7][i] = 1;
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

int board::get_available_moves(int player)
{
    return 0;
}

std::vector<std::vector<int>> board::get_state()
{
    return state;
}
