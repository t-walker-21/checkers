#ifndef MINIMAX_H
#define MINIMAX_H
#include<vector>
#include<list>
#include <stdlib.h>
#include <time.h>

class minimax
{
public:
    minimax();
    std::vector<int> get_move(std::list<std::vector<int>> possible_moves);
    std::vector<int> get_random_move(std::list<std::vector<int>> possible_moves);

private:

};

#endif // MINIMAX_H
