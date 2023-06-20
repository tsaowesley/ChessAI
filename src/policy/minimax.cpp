#include "./minimax.hpp"
#include <climits>
#include <cstdlib>
#include "../state/state.hpp"

int Minimax::minimax(State* state, int depth, bool maximizingPlayer) {
    if (depth == 0 || state->game_state != NONE) {
        return state->evaluate();
    }

    State* next_state;
    int evaluation;

    if (maximizingPlayer) {
        int highestEval = INT_MIN;
        for (auto& move : state->legal_actions) {
            next_state = state->next_state(move);
            evaluation = minimax(next_state, depth - 1, false);
            highestEval = (evaluation > highestEval) ? evaluation : highestEval;
            delete next_state;
        }
        return highestEval;
    } else {
        int lowestEval = INT_MAX;
        for (auto& move : state->legal_actions) {
            next_state = state->next_state(move);
            evaluation = minimax(next_state, depth - 1, true);
            lowestEval = (evaluation < lowestEval) ? evaluation : lowestEval;
            delete next_state;
        }
        return lowestEval;
    }
}

Move Minimax::get_move(State* state, int depth) {
    if (!state->legal_actions.size())
        state->get_legal_actions();

    Move bestMove;
    State* next_state;
    int highestEval = INT_MIN;
    int evaluation;

    for (auto& move : state->legal_actions) {
        next_state = state->next_state(move);
        evaluation = minimax(next_state, depth - 1, true);

        if (evaluation > highestEval) {
            highestEval = evaluation;
            bestMove = move;
        }

        delete next_state;
    }
    return bestMove;
}
