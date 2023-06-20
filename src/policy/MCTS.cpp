#include <climits>
#include <cstdlib>
#include <cmath>
#include "./MCTS.hpp"

namespace MCTS {
    double uct_value(int total_visits, double node_wins, int node_visits, double exploration_param) {
        if (node_visits == 0)
            return INT_MAX;
        return (node_wins / node_visits) + exploration_param * sqrt(log(total_visits) / node_visits);
    }

    // 删除了minimax函数，因为MCTS算法并不需要这个。

    Move get_move(State* state, int simulations_per_move, double exploration_param) {
        size_t total_visits = 0; // 修改了变量的类型
        std::vector<int> move_visits(state->legal_actions.size(), 0);
        std::vector<double> move_wins(state->legal_actions.size(), 0.0);

        for (int i = 0; i < simulations_per_move; i++) {
            State* copy_state = new State(*state);
            simulate(copy_state);
            total_visits++;

            // 需要改变这里的逻辑，因为legal_actions[j].second的类型并不是bool
            // 假设second是一个pair，其first代表是否执行，second代表执行的评价值

            for (size_t j = 0; j < copy_state->legal_actions.size(); j++) { // 修改了变量的类型
                if (copy_state->legal_actions[j].second.first) { // 使用first作为bool判断
                    move_visits[j]++;
                    if (copy_state->legal_actions[j].second.second == state->legal_actions[j].second.second)
                        move_wins[j]++;
                }
            }

            delete copy_state;
        }

        size_t best_move = -1; // 修改了变量的类型
        double best_value = INT_MIN;

        for (size_t i = 0; i < move_visits.size(); i++) { // 修改了变量的类型
            double uct = uct_value(total_visits, move_wins[i], move_visits[i], exploration_param);
            if (uct > best_value) {
                best_value = uct;
                best_move = i;
            }
        }

        return state->legal_actions[best_move];
    }

    void simulate(State* state) {
        if (state->legal_actions.empty())
            state->get_legal_actions();

        int random_move = rand() % state->legal_actions.size();
        state->legal_actions[random_move].second.first = true; // 假设first代表是否执行，这里模拟执行动作
    }
}
