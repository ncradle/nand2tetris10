#include "CompilationEngine.h"

#include "TokenType.h"

CompilationEngine::CompilationEngine(JackTokenizer &jt, std::ofstream &ofs)
    : jt{jt}, ofs{ofs}, tab{""}, tab_num(0) {
  advance();
}

void CompilationEngine::advance() {
  jt.hasMoreTokens();
  jt.advance();
}

void CompilationEngine::lookAhead() {
  jt.savePos();
  advance();
}

void CompilationEngine::keyword() {
  ofs << tab << "<keyword> " << jt.keyWord() << " </keyword>\n";
  advance();
}

void CompilationEngine::symbol() {
  ofs << tab << "<symbol> " << jt.symbol() << " </symbol>\n";
  advance();
}

void CompilationEngine::integerConstant() {
  ofs << tab << "<integerConstant> " << jt.intVal() << " </integerConstant\n";
  advance();
}

void CompilationEngine::stringConstant() {
  ofs << tab << "<stringConstant> " << jt.stringVal() << " </stringConstant>\n";
  advance();
}

void CompilationEngine::identifier() {
  ofs << tab << "<identifier> " << jt.identifier() << " </identifier>\n";
  advance();
}

void CompilationEngine::type() {
  if (jt.tokenType() == KEYWORD) {
    keyword();
  } else {
    identifier();
  }
}

bool CompilationEngine::isType() {
  if (jt.tokenType() == KEYWORD) {
    std::string word = jt.keyWord();
    if (word == "int" || word == "char" || word == "bookean") return true;
  }
  if (jt.tokenType() == IDENTIFIER) return true;
  return false;
}

bool CompilationEngine::isOp() {
  if (jt.tokenType() != SYMBOL) return false;
  std::string op = jt.symbol();
  if (op == "+") return true;
  if (op == "-") return true;
  if (op == "*") return true;
  if (op == "/") return true;
  if (op == "&") return true;
  if (op == "|") return true;
  if (op == "<") return true;
  if (op == ">") return true;
  if (op == "=") return true;
  return false;
}

void CompilationEngine::indentLabel(std::string label) {
  ofs << tab << "<" << label << ">\n";
  tab_num++;
  tab.clear();
  for (int i = 0; i < tab_num; i++) tab += "  ";
}

void CompilationEngine::deindentLabel(std::string label) {
  tab_num--;
  tab.clear();
  for (int i = 0; i < tab_num; i++) tab += "  ";
  ofs << tab << "</" << label << ">\n";
}

void CompilationEngine::compileClass() {
  if (jt.tokenType() != KEYWORD) return;
  if (jt.keyWord() != "class") return;
  indentLabel("class");
  keyword();
  identifier();
  symbol();
  while (1) {
    if (jt.tokenType() != KEYWORD) break;
    if (!(jt.keyWord() == "static" || jt.keyWord() == "field")) break;
    compileVarDec();
  }
  while (1) {
    if (jt.tokenType() != KEYWORD) break;
    if (!(jt.keyWord() == "constructor" || jt.keyWord() == "function" ||
          jt.keyWord() == "method"))
      break;
    compileSubroutine();
  }
  symbol();
  deindentLabel("class");
}

void CompilationEngine::compileClassVarDec() {
  indentLabel("classVarDec");
  keyword();
  type();
  identifier();
  while (jt.symbol() == ",") {
    symbol();
    identifier();
  }
  symbol();
  deindentLabel("classVarDec");
}

void CompilationEngine::compileSubroutine() {
  indentLabel("subroutineDec");
  keyword();
  if (jt.tokenType() == KEYWORD && jt.keyWord() == "void") {
    keyword();
  } else {
    type();
  }
  identifier();
  symbol();
  compileParameterList();
  symbol();
  indentLabel("subroutineBody");
  symbol();
  while (jt.tokenType() == KEYWORD && jt.keyWord() == "var") {
    compileVarDec();
  }
  compileStatements();
  symbol();
  deindentLabel("subroutineBody");
  deindentLabel("subroutineDec");
}

void CompilationEngine::compileParameterList() {
  indentLabel("parameterList");
  if (isType()) {
    type();
    identifier();
    while (jt.symbol() == ",") {
      symbol();
      type();
      identifier();
    }
  }
  deindentLabel("parameterList");
}

void CompilationEngine::compileVarDec() {
  indentLabel("varDec");
  keyword();
  type();
  identifier();
  while (jt.symbol() == ",") {
    symbol();
    identifier();
  }
  symbol();
  deindentLabel("varDec");
}

void CompilationEngine::compileStatements() {
  indentLabel("statements");
  while (1) {
    std::string statement = jt.keyWord();
    if (statement == "let") {
      compileLet();
    } else if (statement == "if") {
      compileIf();
    } else if (statement == "while") {
      compileWhile();
    } else if (statement == "do") {
      compileDo();
    } else if (statement == "return") {
      compileReturn();
    } else {
      break;
    }
  }
  deindentLabel("statements");
}

void CompilationEngine::compileLet() {
  indentLabel("letStatement");
  keyword();
  identifier();
  if (jt.symbol() == "[") {
    symbol();
    compileExpression();
    symbol();
  }
  symbol();
  compileExpression();
  symbol();
  deindentLabel("letStatement");
}

void CompilationEngine::compileIf() {
  indentLabel("ifStatement");
  keyword();
  symbol();
  compileExpression();
  symbol();
  symbol();
  compileStatements();
  symbol();
  if (jt.tokenType() == KEYWORD && jt.keyWord() == "else") {
    keyword();
    symbol();
    compileStatements();
    symbol();
  }
  deindentLabel("ifStatement");
}

void CompilationEngine::compileWhile() {
  indentLabel("whileStatement");
  keyword();
  symbol();
  compileExpression();
  symbol();
  symbol();
  compileStatements();
  symbol();
  deindentLabel("whileStatement");
}

void CompilationEngine::compileDo() {
  indentLabel("doStatement");
  keyword();
  compileSubroutineCall();
  symbol();
  deindentLabel("doStatement");
}

void CompilationEngine::compileReturn() {
  keyword();
  if (!(jt.tokenType() == SYMBOL && jt.symbol() == ";")) {
    compileExpression();
  }
  symbol();
}

void CompilationEngine::compileExpression() {
  indentLabel("expression");
  compileTerm();
  while (isOp()) {
    indentLabel("op");
    symbol();
    deindentLabel("op");
    compileTerm();
  }
  deindentLabel("expression");
}

void CompilationEngine::compileExpressionList() {
  indentLabel("expressionList");
  if (!(jt.tokenType() == SYMBOL && jt.symbol() == ")")) {
    compileExpression();
    while (jt.symbol() == ",") {
      symbol();
      compileExpression();
    }
  }
  deindentLabel("expressionList");
}

void CompilationEngine::compileTerm() {
  indentLabel("term");
  TokenType tt = jt.tokenType();
  switch (tt) {
    case INT_CONST:
      integerConstant();
      break;

    case STRING_CONST:
      stringConstant();
      break;

    case KEYWORD:
      keyword();
      break;

    case IDENTIFIER:
      lookAhead();
      if (jt.tokenType() == SYMBOL) {
        std::string symbl = jt.symbol();
        jt.resetPos();
        if (symbl == "[") {
          symbol();
          compileExpression();
          symbol();
          break;
        }
        if (symbl == "(") {
          compileSubroutineCall();
          break;
        }
        if (symbl == ".") {
          compileSubroutineCall();
          break;
        }
      }
      break;

    case SYMBOL:
      if (jt.symbol() == "(") {
        symbol();
        compileExpression();
        symbol();
        break;
      }
      indentLabel("unaryOp");
      symbol();
      deindentLabel("unaryOp");
      compileTerm();
      break;
  }
  deindentLabel("term");
}

void CompilationEngine::compileSubroutineCall() {
  identifier();
  if (jt.symbol() == ".") {
    symbol();
    identifier();
  }
  symbol();
  compileExpressionList();
  symbol();
}
