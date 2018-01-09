#include <iostream>
#include "cool-tree.h"
#include "cool.tab.h"
#include "helper.h"
using namespace std;

char* curr_filename = "<stdin>";
FILE *fin;
extern int yylex();
extern FILE* yyin;
extern int yylineno;
extern YYSTYPE yylval;
int curr_lineno = 1;

int main(int argc, char **argv) {
  cool_helper::Init(&argc, argv);

  for (int i = 1; i < argc; ++i) {
    FILE* fin = fopen(argv[i], "r");
    if (fin == nullptr) {
      cerr << "Could not open input file " << argv[argc-1] << ", skip." << endl;
      continue;
    }
    yyin = fin;
    cout << "#name " << argv[argc-1] << endl;
    int token = 0;
    while ((token = yylex()) != 0) {
      cool_helper::DumpCoolToken(cout, yylineno, token, yylval);
    }
    fclose(yyin);
    exit(0);
  }
}
