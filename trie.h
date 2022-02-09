#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

#define CHILDREN_SIZE 26
#define WORD_SIZE 5
typedef std::vector<std::string> Options;

class Trie {
    struct Node {
        Node* children[CHILDREN_SIZE] = {};
        bool allowed;
        bool isWord;
        std::string word;

        Node() : allowed(true), isWord(false), word(""){};
    };

   private:
    Node* root;
    // int index(const char& c) { return c - 'a'; }
    // int index(const int& i) {return i}

    bool validate(const Node*);
    void _add(Node*, const std::string&, size_t);
    Node* _at(Node*, const std::string&, size_t);
    Options _options(Node*, const std::string&, Options&);
    void _wild(Node*&, const std::string&, size_t, Options&);
    void _reset(Node*);

    void _count(Node* curr, int& num) {
        if (curr == nullptr) return;
        if (!curr->allowed) return;

        if (curr->isWord) num++;
        for (int i = 0; i < CHILDREN_SIZE; i++) {
            _count(curr->children[i], num);
        }
    }

   public:
    std::unordered_set<char> invalid_letters;
    std::unordered_set<char> must_contain;
    std::unordered_set<Node*> invalid_nodes;

    Trie() {
        root = new Node();
        std::unordered_set<char> invalid_letters;
        std::unordered_set<char> must_contain;
        std::unordered_set<Node*> invalid_nodes;
    }
    void add_word(std::string key) {
        assert(key.length() == 5);
        _add(root, key, 0);
    };
    Node* node_at(std::string key) { return _at(root, key, 0); };

    void count_words(int& n) { _count(root, n); }

    Options options(std::string key) {
        Options ops;

        Node* start = node_at(key);
        if (start == nullptr) return ops;
        return _options(start, key, ops);
    };

    Options find_wild(std::string key) {
        // std::cout << "\t" << key << std::endl;
        // assert(key.length() == 5);
        Options ops;
        _wild(root, key, 0, ops);
        return ops;
    }

    void add_invalid_char(const char);

    std::unordered_set<char> invalid() { return invalid_letters; };
    void reset() {
        invalid_letters.clear();
        must_contain.clear();
        // _reset(root);

        for (auto& node : invalid_nodes) {
            node->allowed = true;
        }
    }
    int index(const char& c) { return c - 'a'; }
};
