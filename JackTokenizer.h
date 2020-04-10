#ifndef _JACK_TOKENIZER_H_
#define _JACK_TOKENIZER_H_

#include <fstream>
#include <string>

#include "KeyWordType.h"
#include "TokenType.h"

class JackTokenizer {
 public:
  JackTokenizer(std::ifstream &ifs);
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
