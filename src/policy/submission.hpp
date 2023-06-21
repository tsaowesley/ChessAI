#pragma once
#include "../state/state.hpp"


class ubmission {
public:
  static Move get_move(State *state, int depth);
  static int submission(State* state, int depth, int alpha, int beta, int maximizingPlayer);
};
