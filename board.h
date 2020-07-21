#ifndef BOARD_H
#define BOARD_H

#endif // BOARD_H

#include<set>
#include<vector>
#include<list>
#define BOARD_SIZE 8

class board
{
private:
    // Methods
    void init();

    // Members
    std::vector<std::vector<int>> state;
    std::set<std::pair<int, int>> pieces_black;
    std::set<std::pair<int, int>> pieces_red;
    std::set<std::pair<int, int>> kings_black;
    std::set<std::pair<int, int>> kings_red;
    int player_turn;

public:
    board();
    board copy();
    bool check_win();
    void get_available_moves(bool player, std::set<std::pair<int, int>>& move_set, std::list<std::vector<int>>& move_list);
    void print_board();
    std::vector<std::vector<int>> get_state();
};
