#ifndef BOARD_H
#define BOARD_H



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
    board(const board &b2);
    int check_win();
    void get_available_moves(int player, std::set<std::pair<int, int>>& move_set, std::list<std::vector<int>>& move_list);
    void print_board();
    std::vector<std::vector<int>> get_state();
    int get_player_turn();
    void set_state(int i, int j, int v);
    bool process_move(int a, int b, int c, int d);
    int get_remaining_pieces(int player);
    int get_num_pawns(int player);
    int get_num_kings(int player);
};

#endif // BOARD_H
