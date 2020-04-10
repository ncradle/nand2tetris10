#include "JackTokenizer.h"

JackTokenizer::JackTokenizer(std::ifstream &jackfile)
    : ifs{jackfile}, token("") {}

bool JackTokenizer::hasMoreTokens() {
  token.clear();
  while (char word = ifs.get()) {
    if (word == ' ') continue;
    if (word == '/') {
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

      // 除算演算子
      token += word;
      return true;
    }

    token += word;
    return true;
  }

  // eof
  return false;
}
