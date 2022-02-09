#include "wordle.h"

#include <iostream>

bool Wordle::validate_key(const std::string &key) const {
    int ex = 0;
    for (int i = 0; i < key.length(); ++i) {
        if (i == key.length() - 1 && key[i] == '!') return false;
        if (key[i] == '!' && !(isalpha(key[i + 1]) || key[i + 1] == '*'))
            return false;
        ex += (key[i] == '!');
    }
    return key.length() - ex == 5;
}

std::string Wordle::display_options(std::string (*func)(Options),
                                    std::string in) {
    Options ops;
    std::string key = in;
    if (in == "-") {
        std::cout << "Enter key (-h for help): ";
        std::cin >> key;

        if (key == "-h") {
            display_help();
            return display_options(func);
        }

        if (!validate_key(key)) {
            std::cout << "Key is not valid\n" << std::endl;
            display_help();
            return display_options(func);
        }
        std::cout << "Seaching ..." << std::endl;
    }

    ops = t.find_wild(key);
    if (in == "-") std::cout << *ops.begin() << std::endl;
    return func(ops);
};

void Wordle::add_invalid_letters(std::string key) {
    if (key != "-") {
        for (auto c : key) {
            t.add_invalid_char(c);
        }
        return;
    }

    std::cout << "Add Current invalid characters (!=none): ";
    std::cin >> key;

    if (key == "!") return;
    for (auto c : key) {
        t.add_invalid_char(c);
    }

    std::cout << "Invalid characters: ";
    for (auto c : t.invalid()) {
        std::cout << c << ", ";
    }
    std::cout << "\n" << std::endl;
};

void Wordle::new_game() { t.reset(); };

void Wordle::display_help() const {
    std::cout << "*  ---> wildcard" << std::endl;
    std::cout << "!n ---> character is not 'n'" << std::endl;
    std::cout << "n  ---> character is 'n'" << std::endl;
}

int Wordle::simulate(std::string wordle, std::string start,
                     std::string (*func)(Options)) {
    int n = 0;
    t.count_words(n);
    std::cout << "wordle: " << wordle << std::endl;

    // std::string key = display_options(func, "*****");
    std::string key = start;
    std::string next_key = "";

    for (int turn = 0; turn < 6; turn++) {
        if (key == wordle) return turn + 1;
        for (int i = 0; i < wordle.length(); ++i) {
            if (key[i] == wordle[i]) {
                next_key += key[i];
            } else if (wordle.find(key[i]) != std::string::npos) {
                next_key += "!";
                next_key += key[i];
                // i++;
            } else {
                next_key += "*";
                t.add_invalid_char(key[i]);
            }
        }
        int words_left = 0;
        t.count_words(words_left);
        std::cout << "\tturn " << turn << " --> " << key << " --> " << next_key
                  << " left: " << words_left << std::endl;
        // std::cout << "\tnew_key: " << next_key << std::endl;

        key = display_options(func, next_key);
        next_key = "";
    }
    return 6;
}
