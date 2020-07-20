#ifndef BOARD_H
#define BOARD_H

#endif // BOARD_H

#include<set>
#include<vector>
#define BOARD_SIZE 8

class board
{
private:
    // Methods
    void init();

    // Members
    std::vector<std::vector<int>> state;
    std::set<std::pair<int, int>> pieces_1;
    std::set<std::pair<int, int>> pieces_2;
    std::set<std::pair<int, int>> kings_1;
    std::set<std::pair<int, int>> kings_2;
    int player_turn;

public:
    board();
    board copy();
    bool check_win();
    int get_available_moves(int player);
    void print_board();
    std::vector<std::vector<int>> get_state();
};
