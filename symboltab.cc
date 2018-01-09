#include "symboltab.h"
#include "helper.h"
using namespace std;
using namespace cool_helper;

SymbolTable IdTable;
SymbolTable IntTable;
SymbolTable StrTable;

ConstantSymbol* ConstantSymbol::constants_ = nullptr;

static std::string SymbolRefGenerator() {
  static int cnt = 0;
  return to_string(cnt++);
}

Symbol::Symbol(const std::string& str, int index)
  : str_(str), index_(index) {
  ref_ = "_" + SymbolRefGenerator() + "_symref";
}

void Symbol::Dump(ostream& stream, int n) {
  stream << PadSpace(n) << str_ << endl;
}

SymbolTable::~SymbolTable() {
  for (auto& p : table_) {
    if (p.second) {
      delete p.second;
    }
  }
}

SymbolP
SymbolTable::AddString(const string& str) {
  if (!table_.count(str)) {
    table_[str] = new Symbol(str, idx_cnt_++);
  }
  return table_[str];
}

SymbolP
SymbolTable::Lookup(const string& str) {
  return table_.count(str) ? table_[str] : nullptr;
}

string*
Scope::LookupCurrentScope(const std::string& key) {
  if (scope_.empty()) {
    return nullptr;
  }
  auto* table = scope_.back();
  return table->count(key) ? &(*table)[key] : nullptr;
}

string*
Scope::Lookup(const std::string& key) {
  if (scope_.empty()) {
    return nullptr;
  }
  for (auto it = scope_.rbegin(); it != scope_.rend(); ++it) {
    auto* table = *it;
    if (table->count(key)) {
      return &(*table)[key];
    }
  }
  return nullptr;
}

Scope::~Scope() {
  for (auto e : scope_) {
    delete e;
  }
}

void Scope::
EnterScope() {
 scope_.push_back(new Table);
}

void Scope::
ExitScope() {
  if (scope_.empty()) {
    CoolDumpError(cerr)
      << "scope is empty";
    exit(1);
  }
  delete scope_.back();
  scope_.pop_back();
}

void Scope::
AddMapping(const std::string& key, const std::string& value) {
  if (scope_.empty()) {
    CoolDumpError(cerr)
      << "scope is empty, cannot add mapping" << endl;
    exit(1);
  }
  (*(scope_.back()))[key] = value;
}

ConstantSymbol::ConstantSymbol() {
  arg = IdTable.AddString("arg");
  arg2 = IdTable.AddString("arg2");
  Bool = IdTable.AddString("Bool");
  concat = IdTable.AddString("concat");
  cool_abort = IdTable.AddString("abort");
  copy = IdTable.AddString("copy");
  Int = IdTable.AddString("Int");
  in_int = IdTable.AddString("in_int");
  in_string = IdTable.AddString("in_string");
  IO = IdTable.AddString("IO");
  length = IdTable.AddString("length");
  Main = IdTable.AddString("Main");
  main_meth = IdTable.AddString("main");
  No_class = IdTable.AddString("_no_class");
  No_type = IdTable.AddString("_no_type");
  Object = IdTable.AddString("Object");
  out_int = IdTable.AddString("out_int");
  out_string = IdTable.AddString("out_string");
  prim_slot = IdTable.AddString("_prim_slot");
  self = IdTable.AddString("self");
  SELF_TYPE = IdTable.AddString("SELF_TYPE");
  Str = IdTable.AddString("String");
  str_field = IdTable.AddString("_str_field");
  substr = IdTable.AddString("substr");
  type_name = IdTable.AddString("type_name");
  val = IdTable.AddString("_val");
  basic_fn = StrTable.AddString("basic_class");
}

ConstantSymbol::~ConstantSymbol() {
  ;
}

