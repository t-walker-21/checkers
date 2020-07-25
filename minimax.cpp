#include "minimax.h"

minimax::minimax()
{
    srand(time(0));
    searchDepth = 7;
}

std::vector<int> minimax::get_move(std::list<std::vector<int>> possible_moves, board game_board) // This function will always be given a NON-EMPTY list of moves
{
    int min_score = INT_MAX;
    std::vector<int> best_move = possible_moves.front(); // Initialize to avoid returning a garbage value
    int alpha = INT_MIN;
    int beta = INT_MAX;

    for (auto move: possible_moves) // Evaluate each possible move
    {
        board board_temp = game_board;
        board_temp.process_move(move[0], move[1], move[2], move[3]);
        int score = minmax(board_temp, 0, alpha, beta);

        if (score < min_score)
        {
            min_score = score;
            best_move = move;
        }

        qDebug() << "score was: " + QString::number((score));

    }

    //qDebug() << "best score was: " << QString::number(min_score);
    qDebug() << "best move --> was: " << QString::number(best_move[0]);

    return best_move;

}

std::vector<int> minimax::get_random_move(std::list<std::vector<int>> possible_moves)
{
    int move_ind = rand() % possible_moves.size();
    auto front = possible_moves.begin();

    std::advance(front, move_ind);

    return *front;
}

int minimax::minmax(board game_board, int depth, int alpha, int beta)
{
    if (depth == searchDepth) // We've bottomed-out with our search depth, apply huerestic eval of current board
    {
        int score;

        score = game_board.get_num_kings(1) * 5 + game_board.get_num_pawns(1);
        score -= (game_board.get_num_kings(-1) * 5 + game_board.get_num_pawns(-1));

        //qDebug() << "Apply eval at depth level: " << depth;

        return score;
    }

    else // Keep searching
    {

        if (depth % 2 == 0) // Maximizing player
        {
            std::list<std::vector<int>> possible_moves;
            std::set<std::pair<int, int>> move_set;

            game_board.get_available_moves(1, move_set, possible_moves);

            int max_score = INT_MIN;

            for (auto move: possible_moves) // Evaluate each possible move
            {
                board board_temp = game_board;
                board_temp.process_move(move[0], move[1], move[2], move[3]);
                int score = minmax(board_temp, depth + 1, alpha, beta);
                if (score > max_score)
                {
                    max_score = score;
                }

                alpha = std::max(alpha, max_score);

                if (beta <= alpha)
                    break;

            }

            return max_score;
        }

        else // Minimizing player
        {
            std::list<std::vector<int>> possible_moves;
            std::set<std::pair<int, int>> move_set;

            game_board.get_available_moves(-1, move_set, possible_moves);
            int min_score = INT_MAX;

            for (auto move: possible_moves) // Evaluate each possible move
            {
                board board_temp = game_board;
                board_temp.process_move(move[0], move[1], move[2], move[3]);
                int score = minmax(board_temp, depth + 1, alpha, beta);
                if (score < min_score)
                {
                    min_score = score;
                }

                beta = std::min(beta, min_score);

                if (beta <= alpha)
                    break;
            }

            return min_score;

        }
    }

}
