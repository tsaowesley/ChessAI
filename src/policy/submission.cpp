#include <cstdlib>
#include <climits>
#include <iostream>
#include "../state/state.hpp"
#include "./submission.hpp"


/**
 * @brief Obtain a legal action based on the state and depth
 *
 * @param state Current state
 * @param depth Depth for the Submission search
 * @return Move Best move found by Submission algorithm
 */
Move Submission::get_move(State *state, int depth){
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
      int currentScore = Submission::minimax(nextState, depth - 1, 1 - state->player);
      updateBestScore(currentScore, action);
  }

  return selectedMove;
}


int Submission::minimax(State* state, int depth, int maximizingPlayer){

  int currentPlayer = state->player;
  int evalScore;

  if (depth == 0 || state->legal_actions.empty()) {
      evalScore = state->evaluate();
      return evalScore;
  }

  int topScore;
  if (maximizingPlayer == 0) {
      topScore = INT_MIN;
      state->get_legal_actions();
      if (!state->legal_actions.empty()) {
          for (auto currentMove : state->legal_actions) {
              auto futureState = state->next_state(currentMove);
              int moveScore = minimax(futureState, depth - 1, 1);
              topScore = std::max(topScore, moveScore);
          }
          return topScore;
      }
  } else {
      topScore = INT_MAX;
      state->get_legal_actions();
      if (!state->legal_actions.empty()) {
          for (auto currentMove : state->legal_actions) {
              auto futureState = state->next_state(currentMove);
              int moveScore = minimax(futureState, depth - 1, 0);
              topScore = std::min(topScore, moveScore);
          }
          return topScore;
      }
  }

}
