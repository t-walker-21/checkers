#include "minimax.h"

minimax::minimax()
{
    srand(time(0));

}

std::vector<int> minimax::get_move(std::list<std::vector<int>> possible_moves)
{

}

std::vector<int> minimax::get_random_move(std::list<std::vector<int>> possible_moves)
{
    int move_ind = rand() % possible_moves.size();
    auto front = possible_moves.begin();

    std::advance(front, move_ind);

    return *front;
}
