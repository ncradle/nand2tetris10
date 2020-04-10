#include <filesystem>
#include <fstream>
#include <iostream>

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
    if (jackfile.extension() != ".vm") continue;

    cout << "open filename : " << jackfile.filename() << endl;
  }
}
