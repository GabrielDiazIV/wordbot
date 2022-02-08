#include "trie.h"

#include <assert.h>
#include <stdio.h>

// inline int index(char a) { return a - 'a'; }

void Trie::_add(Node* curr, const std::string& word, size_t i) {
    if (word.length() == i) return;
    if (curr->children[index(word[i])] == nullptr)
        curr->children[index(word[i])] = new Node;

    if (word.length() - 1 == i) {
        curr->children[index(word[i])]->isWord = true;
        curr->children[index(word[i])]->word = word;
    }

    _add(curr->children[index(word[i])], word, i + 1);
}

Trie::Node* Trie::_at(Node* curr, const std::string& key, size_t i) {
    if (key.length() == i) return curr;

    if (curr->children[(int)key[i]] != nullptr) {
        return _at(curr->children[index(key[i])], key, i + 1);
    }
    return nullptr;
}

Options Trie::_options(Node* curr, const std::string& key, Options& ops) {
    for (int i = 0; i < CHILDREN_SIZE; ++i) {
        Trie::Node* child = curr->children[i];
        if (child != nullptr) {
            if (child->isWord) ops.push_back(child->word);
            _options(child, key, ops);
        }
    }
    return ops;
};

bool Trie::validate(const Node* node) {
    for (auto c : must_contain) {
        if (node->word.find(c) == std::string::npos) return false;
    }
    return true;
};
void Trie::_wild(Node* curr, const std::string& key, size_t pos, Options& ops) {
    if (curr->isWord && validate(curr))
        ops.push_back(curr->word);
    else {
        Node* child;
        int inc = 1;
        if (key[pos] == '!') {
            must_contain.insert(key[pos + 1]);
            child = curr->children[index(key[pos + 1])];
            if (child != nullptr) child->allowed = false;
            inc++;
        }

        if (isalpha(key[pos])) {
            child = curr->children[index(key[pos])];
            if (child != nullptr && child->allowed)
                _wild(child, key, pos + 1, ops);
        } else {
            for (int i = 0; i < CHILDREN_SIZE; ++i) {
                child = curr->children[i];
                if (child != nullptr &&
                    child->allowed &
                        !invalid_letters.contains((char)(i + 'a'))) {
                    _wild(child, key, pos + inc, ops);
                }
            }
        }
    }
    // if (key[index] == '*' || key[index] == '!') {

    //     if (key[index] == '!') {
    //         must_contain.insert(key[index + 1]);
    //         curr->children[(int)key[index + 1]] = nullptr;
    //     }

    //     for (int i = 0; i < CHILDREN_SIZE; i++) {
    //         Trie::Node* child = curr->children[i];
    //         if (child != nullptr && !invalid_letters.contains((char)i)) {
    //             // if (key[index] == '!' && key[index + 1] == (char)i)
    //             continue; auto inc = key[index] == '!' ? 2 : 1; _wild(child,
    //             key, index + inc, ops);
    //         }
    //     }
    // } else {
    //     Trie::Node* child = curr->children[(int)key[index]];
    //     if (child != nullptr) _wild(child, key, index + 1, ops);
    // }
}

void Trie::add_invalid_char(const char invalid) {
    invalid_letters.insert(invalid);
}

void Trie::_reset(Node* curr) {
    if (curr != nullptr) return;
    curr->allowed = true;

    for (int i = 0; i < CHILDREN_SIZE; i++) {
        _reset(curr->children[i]);
    }
}
