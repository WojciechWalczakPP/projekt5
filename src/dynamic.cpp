#include <iostream>
#include <vector>
#include <list>

class BagProblem {
    friend class DynamicBagProblemSolver;
public:
    BagProblem(int capacity, std::vector<int> item_weights, std::vector<int> item_values)
        : max_capacity(capacity), item_count(item_weights.size()),
          weights(item_weights), values(item_values) {}

private:
    int max_capacity;
    int item_count;
    std::vector<int> weights;
    std::vector<int> values;
};

class DynamicBagProblemSolver {
public:
    static void solve(const BagProblem* problem) {
        int n = problem->item_count;
        int W = problem->max_capacity;

        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(W + 1, 0));

        for (int i = 1; i <= n; ++i) {
            for (int capacity = 1; capacity <= W; ++capacity) {
                if (problem->weights[i - 1] <= capacity) {
                    int include = problem->values[i - 1] + dp[i - 1][capacity - problem->weights[i - 1]];
                    int exclude = dp[i - 1][capacity];
                    dp[i][capacity] = std::max(include, exclude);
                } else {
                    dp[i][capacity] = dp[i - 1][capacity];
                }
            }
        }

        std::list<int> selected_items;
        int capacity = W;
        for (int i = n; i > 0 && capacity > 0; --i) {
            if (dp[i][capacity] != dp[i - 1][capacity]) {
                selected_items.push_front(i);
                capacity -= problem->weights[i - 1];
            }
        }

        std::cout << "\nSelected items (1-based): { ";
        for (int item_index : selected_items)
            std::cout << item_index << " ";
        std::cout << "}\n";

        std::cout << "Maximum value: " << dp[n][W] << "\n";
    }
};
