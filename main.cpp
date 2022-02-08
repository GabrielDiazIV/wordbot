#include <iostream>

#include "wordle.h"

using namespace std;

// std::string random(Options ops) { return ops.front(); }

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
    int score = 0;
    // int width = 70;
    int tests = 5000;
    // float progress = 0;

    Wordle w;
    for (int i = 0; i < tests; ++i) {
        score += w.simulate(&freq_best);
        w.new_game();
    }

    std::cout << "Final: " << score << std::endl;
}