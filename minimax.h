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
    std::vector<int> get_move(std::priority_queue<std::pair<int, std::vector<int>>>& possible_moves, board game_board);
    std::vector<int> get_random_move(std::list<std::vector<int>> possible_moves);

private:
    float minmax(board game_board, int depth, float alpha, float beta, bool pruning);
    int searchDepth;


};

#endif // MINIMAX_H
