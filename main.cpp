#include <iostream>

#include "graph.h"
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

std::string dijkstra_best(Options ops) {
    graph g(ops);
    std::string guess = g.dijkstra();
    // std::cout << "GUESS: " << guess << std::endl;

    std::string max_val = ops.front();
    int max = 0;
    int curr = 0;

    auto score = [&](std::string& s, int x) {
        if (s.find(guess[x]) == x) return 2;
        if (s.find(guess[x]) != std::string::npos) return 1;
        return 0;
    };

    for (auto word : ops) {
        curr = score(word, 0) + score(word, 1) + score(word, 2) +
               score(word, 3) + score(word, 4);
        if (curr > max) {
            max = curr;
            max_val = word;
        }
    }

    return max_val;
}

int main() {
    Wordle w;
    int score = 0;
    int total = 0;

    for (int i = 0; i < Constants::WORD_COUNT; ++i) {
        score = w.simulate(Constants::WORDS[i], "ghost", &risk);

        total += score;
        w.new_game();
    }
    std::cout << "Farts: " << (double)total / Constants::WORD_COUNT
              << std::endl;
}
// total = 0;
// Options words;
// for (int i = 0; i < Constants::WORD_COUNT; ++i) {
//     words.push_back(Constants::WORDS[i]);
// }

// auto res = dijkstra_best(words);

// std::cout << res << std::endl;
// }