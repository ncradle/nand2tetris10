#include <filesystem>
#include <fstream>
#include <iostream>

#include "CompilationEngine.h"
#include "JackTokenizer.h"
#include "KeyWordType.h"
#include "TokenType.h"

int main(int argc, char *argv[]) {
  using namespace std;
  namespace fs = filesystem;
  vector<fs::path> jackfiles;

  if (argc == 1) {
    cout << "usage: JackAnalyzer [source]\n\n";
    cout << "source :.jack or directory with.jack\n";
    return 1;
  }

  if (argc > 2) {
    cout << "error : too much argument" << endl;
    return 1;
  }

  const string source = argv[1];
  fs::path path(source);
  if (fs::is_directory(path)) {
    for (const fs::directory_entry &dir_entry : fs::directory_iterator(path)) {
      jackfiles.push_back(dir_entry.path());
    }
  } else {
    jackfiles.push_back(path.replace_extension("vm"));
  }

  for (const auto &jackfile : jackfiles) {
    if (jackfile.extension() != ".jack") continue;

    cout << "open filename : " << jackfile.filename() << endl;
    ifstream ifs(jackfile);
    if (!ifs) {
      cout << "Can't open " << jackfile.filename() << endl;
      continue;
    }

    fs::path Txml_file = jackfile;
    Txml_file.replace_filename(jackfile.stem().string() + "TT");
    ofstream ofs(Txml_file.replace_extension("xml"));

    JackTokenizer jt(ifs);
    /*
    ofs << "<tokens>" << endl;
    while (jt.hasMoreTokens()) {
      jt.advance();
      TokenType token_type = jt.tokenType();
      switch (token_type) {
        case KEYWORD:
          ofs << "  <keyword> " << jt.keyWord() << " </keyword>" << endl;
          break;
        case SYMBOL:
          ofs << "  <symbol> " << jt.symbol() << " </symbol>" << endl;
          break;
        case IDENTIFIER:
          ofs << "  <identifier> " << jt.identifier() << " </identifier>"
              << endl;
          break;
        case INT_CONST:
          ofs << "  <integerConstant> " << jt.intVal() << " </integerConstant>"
              << endl;
          break;
        case STRING_CONST:
          ofs << "  <stringConstant> " << jt.stringVal() << " </stringConstant>"
              << endl;
          break;
        default:
          break;
      }
    }
    ofs << "</tokens>" << endl;
*/
    Txml_file.replace_filename(jackfile.stem().string() + "TTT");
    ofstream ofsp(Txml_file.replace_extension("xml"));
    CompilationEngine ce{jt, ofsp};
    ce.compileClass();
  }
  return 0;
}
