#ifndef __SYMBOL_TAB__
#define __SYMBOL_TAB__
#include <string>
#include <unordered_map>
#include <vector>
typedef class Symbol* SymbolP;

class Symbol {
 private:
  std::string str_;
  int index_;
  std::string ref_;
 public:
  Symbol(const std::string& str, int index);
  Symbol(const Symbol& rhs) = delete;
  Symbol& operator=(const Symbol& rhs) = delete;
  int GetIndex() const { return index_; }
  int GetLen() const { return str_.size(); }
  const std::string& GetString() const { return str_; }
  const std::string& GetRef() const {
    return ref_;
  }
  void Dump(std::ostream& stream, int n);
};

class SymbolTable {
 private:
   typedef std::unordered_map<std::string, SymbolP> Table;
 public:
  SymbolTable() : idx_cnt_(0) {}
  ~SymbolTable();
  SymbolP AddString(const std::string& str);
  SymbolP Lookup(const std::string& str);
  Table::const_iterator begin() { return table_.begin(); }
  Table::const_iterator end() { return table_.end(); }
 private:
  Table table_;
  int idx_cnt_;
};

extern SymbolTable IdTable;
extern SymbolTable IntTable;
extern SymbolTable StrTable;

class ConstantSymbol {
 public:
  static const ConstantSymbol* Get() {
    if (constants_ == nullptr) {
      constants_ = new ConstantSymbol();
    }
    return constants_;
  }

  SymbolP arg;
  SymbolP arg2;
  SymbolP Bool;
  SymbolP concat;
  SymbolP cool_abort;
  SymbolP copy;
  SymbolP Int;
  SymbolP in_int;
  SymbolP in_string;
  SymbolP IO;
  SymbolP length;
  SymbolP Main;
  SymbolP main_meth;
  SymbolP No_class;
  SymbolP No_type;
  SymbolP Object;
  SymbolP out_int;
  SymbolP out_string;
  SymbolP prim_slot;
  SymbolP self;
  SymbolP SELF_TYPE;
  SymbolP Str;
  SymbolP str_field;
  SymbolP substr;
  SymbolP type_name;
  SymbolP val;
  SymbolP basic_fn;

 private:
  ConstantSymbol();
  ~ConstantSymbol();
  static ConstantSymbol* constants_;
};

class Scope {
 private:
  typedef std::unordered_map<std::string, std::string> Table;

 public:
  Scope() {}
  ~Scope();

  void EnterScope();
  void ExitScope();
  void AddMapping(const std::string& key, const std::string& value);

  // lookup current scope
  std::string* LookupCurrentScope(const std::string& key);
  // lookup from current scope to topest scope, and return the first found
  // mapping
  std::string* Lookup(const std::string& key);

 private:
  std::vector<Table*> scope_;
};
#endif
