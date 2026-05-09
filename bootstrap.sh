#!/usr/bin/env bash
# Fetch dictionary.txt if it isn't already on disk. The repo intentionally
# does not commit the 4 MB wordlist — it pulls from a stable upstream
# instead, or copies the local /usr/share/dict/words if available.
set -euo pipefail

DEST="dictionary.txt"
URL="https://raw.githubusercontent.com/dwyl/english-words/master/words_alpha.txt"

if [ -f "$DEST" ]; then
  echo "$DEST already exists ($(wc -l < "$DEST") lines) — skipping download."
  exit 0
fi

if [ -f /usr/share/dict/words ]; then
  echo "Copying /usr/share/dict/words -> $DEST"
  # macOS and Linux ship words with apostrophes/hyphens/accents; the trie
  # only stores [a-z] so we filter to pure alpha lines before saving.
  tr 'A-Z' 'a-z' < /usr/share/dict/words | grep -E '^[a-z]+$' | sort -u > "$DEST"
  echo "Saved $(wc -l < "$DEST") alpha-only words."
  exit 0
fi

if command -v curl >/dev/null 2>&1; then
  echo "Downloading dictionary from $URL"
  curl -fsSL "$URL" -o "$DEST"
elif command -v wget >/dev/null 2>&1; then
  echo "Downloading dictionary from $URL"
  wget -q "$URL" -O "$DEST"
else
  echo "Need curl or wget to fetch the dictionary." >&2
  exit 1
fi

echo "Saved $(wc -l < "$DEST") words to $DEST"
