#include <iostream>
#include <vector>
#include <string>
#include <fstream> 

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

public:
    Trie() {
        root = new TrieNode();
    }

    
    void insert(const string& word) {
        TrieNode* node = root;
        for (char c : word) {
            int index = c - 'a';
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
            int index = c - 'a';
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
        while (getline(file, word)) {
            insert(word);
        }

        file.close();
        cout << "Dictionary loaded from file: " << filename << endl;
    }
};

int main() {
    Trie trie;

  
    string dictionaryFile = "dicionary.txt"; 
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
