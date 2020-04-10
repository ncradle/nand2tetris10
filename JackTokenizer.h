#ifndef _JACK_TOKENIZER_H_
#define _JACK_TOKENIZER_H_

#include <fstream>
#include <string>

#include "KeyWordType.h"
#include "TokenType.h"

class JackTokenizer {
  std::ifstream &ifs;
  std::string token;

 public:
  JackTokenizer(std::ifstream &jackfile);
  bool hasMoreTokens();
  void advance();
  TokenType tokenType();
  KeyWordType keyWord();
  char symbol();
  std::string identifier();
  int intVal();
  std::string stringVal();
};

#endif
