
#include <string>

#include "wordle.h"

std::string random(Options ops) { return ops.front(); }

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
    Wordle w;
    std::string y;
    for (;;) {
        w.add_invalid_letters();
        w.display_options(&freq_best);

        std::cout << "New game (y/n)? ";
        std::cin >> y;
        if (y == "y") w.new_game();
    }
}