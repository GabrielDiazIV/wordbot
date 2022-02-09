#include <iostream>

#include "wordle.h"

using namespace std;

std::string random(Options ops) { return ops.front(); }

std::string risk(Options ops) {
    // int z = ops.size();
    std::string best = ops.front();
    int reward = 0;
    int highest_reward = 0;

    for (auto op : ops) {
        unordered_set<int> s(op.begin(), op.end());
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

    // for (ind)
}

std::string freq_best(Options ops) {
    double max_val = 0;
    std::string max = ops.at(0);

    double curr = 0;

    for (auto s : ops) {
        curr = Constants::FREQ[LET(s[0])] + Constants::FREQ[LET(s[1])] +
               Constants::FREQ[LET(s[2])] + Constants::FREQ[LET(s[3])] +
               Constants::FREQ[LET(s[4])];
        if (curr > max_val) {
            max_val = curr;
            max = s;
        }
    }
    return max;
}

int main() {
    // int width = 70;
    // float progress = 0;

    // auto funcs = {&random, &freq_best};
    Wordle w;

    int score = 0;
    int total = 0;
    // Trie h;

    // int tests = 2000;
    // for (int start = 0; start < 5; start++) {
    for (int i = 0; i < Constants::WORD_COUNT; ++i) {
        score = w.simulate(Constants::WORDS[i], "alert", &risk);
        total += score;
        w.new_game();
    }
    std::cout << "Farts: " << (double)total / Constants::WORD_COUNT
              << std::endl;
    // total = 0;
    // }
}