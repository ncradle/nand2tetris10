#ifndef _COMPILATION_ENGINE_H_
#define _COMPILATION_ENGINE_H_

#include <fstream>

#include "JackTokenizer.h"

class CompilationEngine {
  JackTokenizer& jt;
  std::ofstream& ofs;
  std::string tab;
  int tab_num;

  void advance();
  void lookAhead();
  void indent();
  void deIndent();
  void keyword();
  void symbol();
  void integerConstant();
  void stringConstant();
  void identifier();
  void type();
  bool isType();
  bool isOp();
  void indentLabel(std::string label);
  void deindentLabel(std::string label);

 public:
  CompilationEngine(JackTokenizer& jt, std::ofstream& ofs);
  void compileClass();
  void compileClassVarDec();
  void compileSubroutine();
  void compileParameterList();
  void compileVarDec();
  void compileStatements();
  void compileDo();
  void compileLet();
  void compileWhile();
  void compileReturn();
  void compileIf();
  void compileExpression();
  void compileTerm();
  void compileExpressionList();
  void compileSubroutineCall();
};

#endif
