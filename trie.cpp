#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cctype>

using namespace std;

class TrieNode {
public:
    TrieNode* children[26];
    bool isEndOfWord;

    TrieNode() {
        for (int i = 0; i < 26; i++)
            children[i] = nullptr;
        isEndOfWord = false;
    }
};

class Trie {
private:
    TrieNode* root;

    // Lowercase a-z map to 0-25; anything else returns -1 to signal
    // "not part of our alphabet" so callers can drop the word safely.
    static int charToIndex(char c) {
        unsigned char uc = static_cast<unsigned char>(c);
        if (uc >= 'a' && uc <= 'z') return uc - 'a';
        if (uc >= 'A' && uc <= 'Z') return uc - 'A';
        return -1;
    }

public:
    Trie() {
        root = new TrieNode();
    }

    // Insert a word; skip the entire word if it contains non-alpha
    // characters (apostrophes, hyphens, accents) — both /usr/share/dict/words
    // and many community wordlists include those, and the fixed-26 child
    // array would otherwise be indexed out of bounds.
    void insert(const string& word) {
        if (word.empty()) return;

        TrieNode* node = root;
        for (char c : word) {
            int index = charToIndex(c);
            if (index < 0) return;
            if (!node->children[index])
                node->children[index] = new TrieNode();
            node = node->children[index];
        }
        node->isEndOfWord = true;
    }

    void suggestHelper(TrieNode* node, const string& prefix, vector<string>& suggestions) {
        if (node->isEndOfWord)
            suggestions.push_back(prefix);

        for (char c = 'a'; c <= 'z'; c++) {
            int index = c - 'a';
            if (node->children[index]) {
                suggestHelper(node->children[index], prefix + c, suggestions);
            }
        }
    }

    vector<string> getSuggestions(const string& prefix) {
        TrieNode* node = root;
        vector<string> suggestions;
        for (char c : prefix) {
            int index = charToIndex(c);
            if (index < 0)
                return suggestions;
            if (!node->children[index])
                return suggestions;
            node = node->children[index];
        }
        suggestHelper(node, prefix, suggestions);
        return suggestions;
    }

    void loadDictionaryFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        string word;
        size_t loaded = 0, skipped = 0;
        while (getline(file, word)) {
            if (word.empty()) { skipped++; continue; }
            // Strip trailing \r (CRLF files) before validation.
            if (word.back() == '\r') word.pop_back();
            bool valid = !word.empty();
            for (char c : word) {
                if (charToIndex(c) < 0) { valid = false; break; }
            }
            if (valid) { insert(word); loaded++; }
            else { skipped++; }
        }

        file.close();
        cout << "Dictionary loaded from " << filename
             << " (" << loaded << " words, " << skipped << " skipped)" << endl;
    }
};

int main() {
    Trie trie;

  
    string dictionaryFile = "dictionary.txt";
    trie.loadDictionaryFromFile(dictionaryFile);

 
    string prefix;
    cout << "Enter a prefix: ";
    cin >> prefix;


    vector<string> suggestions = trie.getSuggestions(prefix);

    if (suggestions.empty()) {
        cout << "No suggestions found for the prefix: " << prefix << endl;
    } else {
        cout << "Suggestions for the prefix \"" << prefix << "\":" << endl;
        for (const string& suggestion : suggestions) {
            cout << suggestion << endl;
        }
    }

    return 0;
}
