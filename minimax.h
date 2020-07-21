#ifndef MINIMAX_H
#define MINIMAX_H
#include<vector>
#include<list>
#include <stdlib.h>
#include <time.h>
#include "board.h"
#include <queue>
#include <limits.h>
#include <QDebug>

class minimax
{
public:
    minimax();
    std::vector<int> get_move(std::list<std::vector<int>> possible_moves, board game_board);
    std::vector<int> get_random_move(std::list<std::vector<int>> possible_moves);

private:
    int minmax(board game_board, int depth);
    int searchDepth;


};

#endif // MINIMAX_H
