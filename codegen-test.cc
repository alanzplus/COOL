#include <iostream>
#include <fstream>
#include "cool-tree.h"
#include "inheritance-tree.h"
#include "semant.h"
#include "cgen.h"
using namespace std;
int curr_lineno = 1;
char* curr_filename;
extern int yyparse();
extern ProgramP ast_root;
extern FILE* yyin;
extern int err_cnt;
int main(int argc, char* argv[]) {
  using namespace cool_helper;
  Init(&argc, argv);
  for (int i = 1; i < argc; ++i) {
    curr_filename = argv[i];
    FILE* fin = fopen(curr_filename, "r");
    if (fin == nullptr) {
      cerr << "Could not open input file " << argv[argc-1] << ", skip." << endl;
      continue;
    }
    yyin = fin;
    yyparse();
    if (err_cnt > 0) {
	    cerr << "Compilation halted due to lex and parse errors" << endl;
      exit(1);
    }
  }
  
  auto tree = new InheritanceTree(ast_root);
  if (SemantError::GetInstance(cerr)->NumErrors()) {
	  cerr << "Compilation halted due to static semantic errors." << endl;
    exit(1);
  }
  auto semant = new SemanticChecker(tree);
  semant->TypeChecking();
  if (SemantError::GetInstance(cerr)->NumErrors()) {
	  cerr << "Compilation halted due to static semantic errors." << endl;
    exit(1);
  }

  StrTable.AddString("Main");
  ofstream fos;
  fos.open(g_codegen_out_fn == "" ? "codegenout.s" : g_codegen_out_fn,
           ofstream::out);
  if (!fos.is_open()) {
    CoolDumpError(cerr)
      << "cannot open output file "
      << (g_codegen_out_fn == "" ? "codegenout.s" : g_codegen_out_fn)
      << endl;
    exit(-1);
  }
  unique_ptr<CodeGen> cgen(new CodeGen(ast_root, tree, fos));
  cgen->Generate();
  return 0;
}
