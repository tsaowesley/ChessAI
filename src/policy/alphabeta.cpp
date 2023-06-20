#include "./alphabeta.hpp"
#include <climits>
#include <cstdlib>
#include "../state/state.hpp"

int Alphabeta::alphabeta(State* state, int depth, int alpha, int beta, bool maximizingPlayer) {
    if (depth == 0 || state->game_state != NONE) {
        return state->evaluate();
    }

    State* next_state;
    int evaluation;

    if (maximizingPlayer) {
        int highestEval = INT_MIN;
        for (auto& move : state->legal_actions) {
            next_state = state->next_state(move);
            evaluation = alphabeta(next_state, depth - 1, alpha, beta, false);
            highestEval = (evaluation > highestEval) ? evaluation : highestEval;
            alpha = (alpha > highestEval) ? alpha : highestEval;
            delete next_state;
            if (beta <= alpha)
                break;
        }
        return highestEval;
    } else {
        int lowestEval = INT_MAX;
        for (auto& move : state->legal_actions) {
            next_state = state->next_state(move);
            evaluation = alphabeta(next_state, depth - 1, alpha, beta, true);
            lowestEval = (evaluation < lowestEval) ? evaluation : lowestEval;
            beta = (beta < lowestEval) ? beta : lowestEval;
            delete next_state;
            if (beta <= alpha)
                break;
        }
        return lowestEval;
    }
}

Move Alphabeta::get_move(State* state, int depth) {
    if (!state->legal_actions.size())
        state->get_legal_actions();

    Move bestMove;
    State* next_state;
    int highestEval = INT_MIN;
    int evaluation;
    int alpha = INT_MIN;
    int beta = INT_MAX;

    for (auto& move : state->legal_actions) {
        next_state = state->next_state(move);
        evaluation = alphabeta(next_state, depth - 1, alpha, beta, true);

        if (evaluation > highestEval) {
            highestEval = evaluation;
            bestMove = move;
        }

        delete next_state;
    }
    return bestMove;
}
