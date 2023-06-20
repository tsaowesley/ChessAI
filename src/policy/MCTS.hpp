#pragma once
#include "../state/state.hpp"

namespace MCTS {
    Move get_move(State* state, int simulations_per_move, double exploration_param);
    void simulate(State* state);
    double uct_value(int total_visits, double node_wins, int node_visits, double exploration_param);
}
