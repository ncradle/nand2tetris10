#ifndef _JACK_TOKENIZER_H_
#define _JACK_TOKENIZER_H_

#include <fstream>
#include <string>

#include "KeyWordType.h"
#include "TokenType.h"

class JackTokenizer {
  std::ifstream &ifs;
  char initial_token, buff_initial_token;
  std::string token, buff_token;
  std::ifstream::pos_type pos;

 public:
  JackTokenizer(std::ifstream &jackfile);
  bool hasMoreTokens();
  void advance();
  void savePos();
  void resetPos();
  TokenType tokenType();
  std::string keyWord();
  std::string symbol();
  std::string identifier();
  int intVal();
  std::string stringVal();
};

#endif
