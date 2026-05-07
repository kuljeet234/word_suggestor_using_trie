CXX      ?= g++
CXXFLAGS ?= -std=c++17 -O2 -Wall -Wextra
BIN      := trie

$(BIN): trie.cpp dictionary.txt
	$(CXX) $(CXXFLAGS) -o $@ trie.cpp

dictionary.txt:
	./bootstrap.sh

clean:
	rm -f $(BIN) a.out

distclean: clean
	rm -f dictionary.txt

.PHONY: clean distclean
