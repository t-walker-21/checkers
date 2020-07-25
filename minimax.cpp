#include "minimax.h"

minimax::minimax()
{
    srand(time(0));
    searchDepth = 5;
}

std::vector<int> minimax::get_move(std::priority_queue<std::pair<int, std::vector<int>>>& possible_moves, board game_board) // This function will always be given a NON-EMPTY list of moves
{
    float min_score = INT_MAX;
    std::vector<int> best_move = possible_moves.top().second; // Initialize to avoid returning a garbage value
    float alpha = INT_MIN;
    float beta = INT_MAX;

    qDebug() << "first move: " << QString::number(best_move[0]) << QString::number(best_move[1]) << QString::number(best_move[2]) << QString::number(best_move[3]);

    while (!possible_moves.empty()) // Evaluate each possible move
    {
        auto move = possible_moves.top().second;
        possible_moves.pop();

        board board_temp = game_board;
        board_temp.process_move(move[0], move[1], move[2], move[3]);
        float score = minmax(board_temp, 0, alpha, beta, true);

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

float minimax::minmax(board game_board, int depth, float alpha, float beta, bool pruning)
{
    if (depth == searchDepth) // We've bottomed-out with our search depth, apply huerestic eval of current board
    {
        float score;

        score = game_board.get_num_kings(1) * 5 + game_board.get_num_pawns(1);
        score -= (game_board.get_num_kings(-1) * 5 + game_board.get_num_pawns(-1));

        //qDebug() << "Apply eval at depth level: " << depth;

        return score;
    }

    else // Keep searching
    {

        if (depth % 2 == 0) // Maximizing player
        {
            std::priority_queue<std::pair<int, std::vector<int>>> possible_moves;
            std::set<std::pair<int, int>> move_set;

            game_board.get_available_moves(1, move_set, possible_moves);

            float max_score = INT_MIN;

            while (!possible_moves.empty()) // Evaluate each possible move
            {
                auto move = possible_moves.top().second;
                possible_moves.pop();

                board board_temp = game_board;
                board_temp.process_move(move[0], move[1], move[2], move[3]);
                float score = minmax(board_temp, depth + 1, alpha, beta, pruning);
                if (score > max_score)
                {
                    max_score = score;
                }

                alpha = std::max(alpha, max_score);

                if (beta <= alpha and pruning)
                {
                    //qDebug() << "pruning";
                    break;
                }

            }

            return max_score * 0.9;
        }

        else // Minimizing player
        {
            std::priority_queue<std::pair<int, std::vector<int>>> possible_moves;
            std::set<std::pair<int, int>> move_set;

            game_board.get_available_moves(-1, move_set, possible_moves);
            float min_score = INT_MAX;

            while (!possible_moves.empty()) // Evaluate each possible move
            {
                auto move = possible_moves.top().second;
                possible_moves.pop();

                board board_temp = game_board;
                board_temp.process_move(move[0], move[1], move[2], move[3]);
                float score = minmax(board_temp, depth + 1, alpha, beta, pruning);
                if (score < min_score)
                {
                    min_score = score;
                }

                beta = std::min(beta, min_score);

                if (beta <= alpha and pruning)
                    break;
            }

            return min_score * 0.9;

        }
    }

}
