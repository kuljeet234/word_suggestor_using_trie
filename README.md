# Word Suggestor Using Trie Tree

This project implements a Word Suggestor using a **Trie Tree** data structure in C++. The suggestor provides auto-completion by suggesting words based on a given prefix. This type of data structure is highly efficient for prefix-based queries, making it useful for applications like search engines or text editors.

## Features

- **Efficient Word Lookup**: Given a prefix, the suggestor efficiently finds and returns all words in the Trie that begin with that prefix.
- **Insertion of Words**: Adds words to the Trie for future lookup and suggestion.
- **Case-Insensitive Search**: The implementation handles words in a case-insensitive manner.
- **Simple CLI Interface**: Users can interact with the suggestor via a command-line interface.

## How It Works

1. **Trie Tree Structure**: The Trie (prefix tree) is a specialized data structure used to store a set of strings, where each node represents a single character of a word. All the children of a node share the same prefix.
2. **Insert Operation**: When a word is inserted, it's broken down into characters, with each character being placed in a node. If the prefix already exists, only the remaining part of the word is added.
3. **Search Operation**: To suggest words, the Trie is traversed based on the given prefix, and all words branching out from that prefix are collected and returned as suggestions.

## Code Structure

- **TrieNode Class**: 
  - Represents a single node in the Trie. 
  - Contains an array of child nodes for each character (A-Z) and a boolean to mark the end of a word.
  
- **Trie Class**:
  - Contains the root node.
  - Functions include:
    - `insert(string word)`: Inserts a word into the Trie.
    - `suggest(string prefix)`: Suggests all words based on the provided prefix.
    - `search(string word)`: Searches for the complete existence of a word in the Trie.

## Functions

### `void insert(string word)`
Inserts the given word into the Trie.

```cpp
void Trie::insert(string word) {
    TrieNode* node = root;
    for (char c : word) {
        if (!node->children[c - 'a']) {
            node->children[c - 'a'] = new TrieNode();
        }
        node = node->children[c - 'a'];
    }
    node->isEndOfWord = true;
}
