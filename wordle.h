#include <string>

#include "constants.h"
#include "trie.h"

#define LET(x) (x - 'a')

class Wordle {
   private:
    Trie t;

    bool validate_key(const std::string&) const;

   public:
    Wordle() {
        for (int i = 0; i < Constants::WORD_COUNT; ++i)
            t.add_word(Constants::WORDS[i]);
        // std::cout << "Trie built" << std::endl;
    };

    void add_invalid_letters(std::string = "-");
    std::string display_options(std::string (*func)(Options),
                                std::string = "-");
    void display_help() const;
    void new_game();

    int simulate(std::string, std::string, std::string (*func)(Options));
};