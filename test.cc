#include "cool-tree.h"
#include "symboltab.h"
#include <iostream>
#include <gtest/gtest.h>
using namespace std;
int main() {
  SymbolTable symtab;
  symtab.AddString("hello");
  auto sym = symtab.Lookup("hello");
  cout << sym->GetIndex() << endl;
  cout << sym->GetString() << endl;
  return 0;
}
