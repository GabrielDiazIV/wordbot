
#include <iostream>
#include <string>

#include "trie.h"

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

int main() {
    // Wordle w;
    // std::string y;
    // for (;;) {
    //     w.add_invalid_letters();
    //     w.display_options(&random);

    //     std::cout << "New game (y/n)? ";
    //     std::cin >> y;
    //     if (y == "y") w.new_game();
    // }

    Trie t;
    t.add_word("picle");
    t.add_word("pikes");
    t.add_word("pifff");
    t.add_word("aifff");
    int a = 0;
    t.count_words(a);

    std::cout << "SIZE: " << a << std::endl;
    auto ss = t.find_wild("pi***");
    for (auto s : ss) {
        std::cout << s << std::endl;
    }
}