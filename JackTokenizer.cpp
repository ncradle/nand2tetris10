#include "JackTokenizer.h"

#include "KeywordReservedWord.h"
#include "SymbolReservedWord.h"
#include "TokenType.h"

JackTokenizer::JackTokenizer(std::ifstream &jackfile)
    : ifs{jackfile},
      initial_token(0),
      buff_initial_token(0),
      token(""),
      buff_token(""),
      pos{0} {}

bool JackTokenizer::hasMoreTokens() {
  if (initial_token != 0) return true;
  while (1) {
    char word = ifs.get();
    // eof
    if (ifs.eof()) return false;
    if (word == ' ') continue;
    if (word == '\n') continue;
    if (word == '\t') continue;
    if (word == '/') {
      initial_token = word;
      word = ifs.get();

      // /**/パターン
      if (word == '*') {
        word = ifs.get();
        while (1) {
          while (word != '*') {
            word = ifs.get();
          }
          word = ifs.get();
          if (word == '/') break;
          continue;
        }
        continue;
      }

      // //パターン
      if (word == '/') {
        while (word != '\n') {
          word = ifs.get();
        }
        continue;
      }

      // 除算演算子パターン
      return true;
    }

    initial_token = word;
    return true;
  }
}

void JackTokenizer::advance() {
  token = initial_token;
  // symbolの場合
  if (SymbolReserverdWord.contains(initial_token)) {
    initial_token = 0;
    return;
  }

  // stringConstantの場合
  if (initial_token == '\"') {
    char word = ifs.get();
    while (word != '\"') {
      token += word;
      word = ifs.get();
    }
    token += word;
    initial_token = 0;
    return;
  }

  char word = ifs.get();
  while (isalnum(word) | (word == '_')) {
    token += word;
    word = ifs.get();
  }

  if (SymbolReserverdWord.contains(word)) {
    initial_token = word;
    return;
  }
  initial_token = 0;
}

TokenType JackTokenizer::tokenType() {
  const char token_initial = token[0];
  if (SymbolReserverdWord.contains(token_initial)) return SYMBOL;
  if (token_initial == '\"') return STRING_CONST;
  if (KeywordReservedWord.contains(token)) return KEYWORD;
  if (std::all_of(token.cbegin(), token.cend(), isdigit)) return INT_CONST;
  return IDENTIFIER;
}

std::string JackTokenizer::keyWord() { return token; }

std::string JackTokenizer::symbol() {
  if (token[0] == '<') return "&lt;";
  if (token[0] == '>') return "&gt;";
  if (token[0] == '&') return "&amp;";
  return token;
}

std::string JackTokenizer::identifier() { return token; }

int JackTokenizer::intVal() { return std::stoi(token); }

std::string JackTokenizer::stringVal() {
  std::string remove_doublequote;
  for (auto str : token) {
    if (str == '\"') continue;
    remove_doublequote += str;
  }
  return remove_doublequote;
}

void JackTokenizer::savePos() {
  if (pos != 0) return;
  pos = ifs.tellg();
  buff_initial_token = initial_token;
  buff_token = token;
}

void JackTokenizer::resetPos() {
  if (pos == 0) return;
  ifs.seekg(pos);
  pos = 0;
  token = buff_token;
  initial_token = buff_initial_token;
}
