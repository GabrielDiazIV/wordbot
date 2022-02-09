
#include <iostream>
#include <string>
#include <unordered_set>

#include "wordle.h"

std::string random(Options ops) { return ops.front(); }

// std::string freq_best(Options ops) {
//     double max_val = 0;
//     std::string max = ops.at(0);

//     double curr = 0;

//     for (auto s : ops) {
//         curr = Constants::FREQ[LET(s[0])] + Constants::FREQ[LET(s[1])] +
//                Constants::FREQ[LET(s[2])] + Constants::FREQ[LET(s[3])] +
//                Constants::FREQ[LET(s[4])];
//         if (curr > max_val) {
//             max_val = curr;
//             max = s;
//         }
//     }
//     return max;
// }

std::string risk(Options ops) {
    // int z = ops.size();
    std::string best = ops.front();
    int reward = 0;
    int highest_reward = 0;

    for (auto op : ops) {
        std::unordered_set<int> s(op.begin(), op.end());
        reward = 0;
        for (auto cmp : ops) {
            int res = count_if(cmp.begin(), cmp.end(),
                               [&](int k) { return s.find(k) != s.end(); });
            reward += res;
        }
        if (reward > highest_reward) {
            highest_reward = reward;
            best = op;
        }
    }

    return best;
}

int main() {
    Wordle w;
    std::string y;
    for (;;) {
        w.add_invalid_letters();
        w.display_options(&random);

        std::cout << "New game (y/n)? ";
        std::cin >> y;
        if (y == "y") w.new_game();
    }
}