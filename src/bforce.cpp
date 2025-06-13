#include <iostream>
#include <vector>
#include <list>

class BagProblem {
    friend class BruteForceBagProblemSolver;
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

class BruteForceBagProblemSolver {
public:
    static void solve(const BagProblem* problem) {
        int n = problem->item_count;
        int W = problem->max_capacity;

        int best_value = 0;
        int best_combination = 0;

        int total_combinations = 1 << n;

        for (int mask = 0; mask < total_combinations; ++mask) {
            int current_weight = 0;
            int current_value = 0;

            for (int i = 0; i < n; ++i) {
                if (mask & (1 << i)) {
                    current_weight += problem->weights[i];
                    current_value += problem->values[i];
                }
            }

            if (current_weight <= W && current_value > best_value) {
                best_value = current_value;
                best_combination = mask;
            }
        }

        std::list<int> selected_items;
        for (int i = 0; i < n; ++i) {
            if (best_combination & (1 << i)) {
                selected_items.push_back(i + 1);
            }
        }

        std::cout << "\nSelected items (1-based): { ";
        for (int item_index : selected_items)
            std::cout << item_index << " ";
        std::cout << "}\n";

        std::cout << "Maximum value: " << best_value << "\n";
    }
};
