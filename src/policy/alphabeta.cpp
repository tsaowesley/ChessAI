#include <cstdlib>
#include <climits>
#include <iostream>
#include "../state/state.hpp"
#include "./alphabeta.hpp"


Move Alphabeta::get_move(State *state, int depth){
  state->get_legal_actions();
  int bestScore;

  if (state->player)
      bestScore = INT_MAX;
  else
      bestScore = INT_MIN;

  auto legalActions = state->legal_actions;
  Move selectedMove = legalActions[0];

  auto updateBestScore = [&](int currentScore, const Move& action) {
      if (state->player && currentScore < bestScore) {
          bestScore = currentScore;
          selectedMove = action;
      } else if (!state->player && currentScore > bestScore) {
          bestScore = currentScore;
          selectedMove = action;
      }
  };

  for (const auto& action : legalActions) {
      auto nextState = state->next_state(action);
      int currentScore = Alphabeta::alphabeta(nextState, depth - 1, INT_MIN, INT_MAX, 1 - state->player);
      updateBestScore(currentScore, action);
  }

  return selectedMove;
}


int Alphabeta::alphabeta(State* state, int depth, int alpha, int beta, int maximizingPlayer){

  int currentPlayer = state->player;
  int evalScore;

  if (depth == 0 || state->legal_actions.empty()) {
      evalScore = state->evaluate();
      return evalScore;
  }

  state->get_legal_actions();
  if (maximizingPlayer == 0) {
      for (auto currentMove : state->legal_actions) {
          auto futureState = state->next_state(currentMove);
          int moveScore = alphabeta(futureState, depth - 1, alpha, beta, 1);
          alpha = std::max(alpha, moveScore);
          if(beta <= alpha)
              break;
      }
      return alpha;
  } else {
      for (auto currentMove : state->legal_actions) {
          auto futureState = state->next_state(currentMove);
          int moveScore = alphabeta(futureState, depth - 1, alpha, beta, 0);
          beta = std::min(beta, moveScore);
          if(beta <= alpha)
              break;
      }
      return beta;
  }
}
