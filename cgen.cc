#include <memory>
#include <sstream>
#include "cgen.h"
using namespace std;
static const int DEFAULT_OBJFIELDS = 3;
static const int INT_SLOTS = 1;
static const int STRING_SLOTS = 1;
static const int BOOL_SLOTS = 1;

static const std::string CLASSINIT_SUFFIX = "_init";
static const std::string CLASS_PROT_OBJ_TAB = "class_prot_obj_tab";
static const std::string CLASS_INIT_TAB = "class_init_tab";
static const std::string CLASS_DIRECT_PARENT_TAB = "class_direct_parent_tab";
static const std::string SPTop = "4($sp)";
static const std::string WORD = "\t.word\t";
static const std::string ASCII = "\t.ascii\t";
static const std::string ALIGN = "\t.align\t2\n";
static const std::string GLOBAL = "\t.globl\t";
static const std::string BOOLCONST_TRUE_REF = "bool_const_true";
static const std::string BOOLCONST_FALSE_REF = "bool_const_false";
static const std::string PROTOBJ_SUFFIX = "_protObj";
static const std::string CLASS_NAME_TAB = "class_nameTab";
static const std::string CLASS_OBJ_TAB = "class_objTab";
static const std::string HEAP_START = "heap_start";

// register names
static const std::string ZERO = "$zero";		// Zero register 
static const std::string ACC = "$a0";		// Accumulator 
static const std::string A1  = "$a1";		// For arguments to prim funcs 
static const std::string SELF = "$s0";		// Ptr to self (callee saves) 
static const std::string T1  = "$t1";		// Temporary 1 
static const std::string T2  = "$t2";		// Temporary 2 
static const std::string T3  = "$t3";		// Temporary 3 
static const std::string SP  = "$sp";		// Stack pointer 
static const std::string FP  = "$fp";		// Frame pointer 
static const std::string RA  = "$ra";		// Return address 

// Opcodes
static const std::string JALR = "\tjalr\t";
static const std::string JAL = "\tjal\t";
static const std::string RET = "\tjr\t" + RA + "\t";
static const std::string SW  = "\tsw\t";
static const std::string LW  = "\tlw\t";
static const std::string LI  = "\tli\t";
static const std::string LA  = "\tla\t";
static const std::string MOVE = "\tmove\t";
static const std::string NEG = "\tneg\t";
static const std::string ADD = "\tadd\t";
static const std::string ADDI = "\taddi\t";
static const std::string ADDU = "\taddu\t";
static const std::string ADDIU = "\taddiu\t";
static const std::string DIV = "\tdiv\t";
static const std::string MUL = "\tmul\t";
static const std::string SUB = "\tsub\t";
static const std::string SLL = "\tsll\t";
static const std::string BEQZ = "\tbeqz\t";
static const std::string BRANCH = "\tb\t";
static const std::string BEQ   = "\tbeq\t";
static const std::string BNE   = "\tbne\t";
static const std::string BLEQ  = "\tble\t";
static const std::string BLT   = "\tblt\t";
static const std::string BGT   = "\tbgt\t";


enum Memmgr { GC_NOGC, GC_GENGC, GC_SNCGC } cgen_Memmgr;
enum Memmgr_Test { GC_NORMAL, GC_TEST } cgen_Memmgr_Test;
enum Memmgr_Debug { GC_QUICK, GC_DEBUG } cgen_Memmgr_Debug;

static const string _gc_init_names[] = {
  "_NoGC_Init", "_GenGC_Init", "_ScnGC_Init"
};

static const string _gc_collect_names[] = {
  "_NoGC_Collect", "_GenGC_Collect", "_ScnGC_Collect"
};

static std::string _g_filename;

std::string CodeGen::
GetProtoObjRef(const std::string& name) {
  return name + PROTOBJ_SUFFIX;
}

void CodeGen::
EmitIntTabEntry(const SymbolP sym, ostream& s, int tagno) {
  s << WORD << "-1" << endl
    << sym->GetRef() << ":" << endl
    << WORD << tagno << endl
    << WORD << (DEFAULT_OBJFIELDS + INT_SLOTS) << endl
    << WORD << cool_helper::GetClassDispatchTabName(
        ConstantSymbol::Get()->Int->GetString()) << endl
    << WORD << sym->GetString() << endl;
}

void CodeGen::
EmitStringTabEntry(const SymbolP sym, ostream& s, int tagno) {
  int len = sym->GetLen();
  SymbolP len_sym = IntTable.AddString(to_string(len));

  s << WORD << "-1" << endl
    << sym->GetRef() << ":" << endl
    << WORD << tagno << endl
    << WORD << (DEFAULT_OBJFIELDS + STRING_SLOTS + (len + 4) / 4) << endl
    << WORD << cool_helper::GetClassDispatchTabName(
        ConstantSymbol::Get()->Str->GetString()) << endl
    << WORD << len_sym->GetRef() << endl;
  
  EmitStringConstant(s, sym->GetString());
  
  s << ALIGN;
}

// With reference to cgen_supp.cc
void 
CodeGen::EmitStringConstant(ostream& str, const std::string& s) {
  int ascii = 0;
  auto byte_mode = [&]() {
    if (ascii) {
      str << "\"\n";
      ascii = 0;
    }
  };

  auto ascii_mode = [&]() {
    if (!ascii) {
      str << "\t.ascii\t\"";
      ascii = 1;
    }
  };

  for (const auto& ch : s) {
    switch (ch) {
      case '\n':
        ascii_mode();
        str << "\\n";
        break;

      case '\t':
        ascii_mode();
        str << "\\t";
        break;

      case '\\':
        byte_mode();
        str << "\t.byte\t"
            << static_cast<int>(static_cast<unsigned char>('\\'))
            << endl;
        break;

      case '"':
        ascii_mode();
        str << "\\\"";
        break;

      default:
        if (ch >= ' ' && static_cast<unsigned char>(ch) < 128) {
          ascii_mode();
          str << ch;
        } else {
          byte_mode();
          str << "\t.byte\t"
              << static_cast<int>(static_cast<unsigned char>(ch))
              << endl;
        }
        break;
    }
  }
  byte_mode();
  str << "\t.byte\t0\t" << endl;
}

CodeGen::
CodeGen(ProgramP ast_root,
        InheritanceTree* inherit_tree,
        ostream& os)
  : ast_root_(ast_root),
    inherit_tree_(inherit_tree),
    str_(os) {
  auto& log_flag = cool_helper::g_log_cerr;
  CollectClassInfo();
  if (log_flag) {
    for (const auto& ele : class_info_tab_) {
      ele.second->Dump();
    }
  }

}


void CodeGen::
Generate() {
  auto& log_flag = cool_helper::g_log_cerr;

  IntTable.AddString("0");
  StrTable.AddString("");
  
  str_ << endl << " # global data" << endl;
  if (cool_helper::g_log_cerr) {
    cerr << " # global data " << endl;
  }
  EmitGlobalData();

  str_ << endl << " # choosing gc" << endl;
  if (cool_helper::g_log_cerr) {
    cerr << " # choosing gc" << endl;
  }
  EmitGCSelect();

  str_ << endl << " # constants" << endl;
  if (cool_helper::g_log_cerr) {
    cerr << " # constants" << endl;
  }
  EmitSymbolTabConstants();
  
  str_ << endl << " # declare class tag name" << endl;
  if (cool_helper::g_log_cerr) {
    cerr << " # declare class tag name" << endl;
  }
  EmitClassTagDeclaration();

  str_ << endl << " # class tag definition" << endl;
  if (cool_helper::g_log_cerr) {
    cerr << " # declare class tag definition" << endl;
  }
  EmitClassTagDefinition();

  str_ << endl << " # class name table" << endl;
  if (cool_helper::g_log_cerr) {
    cerr << " # class name table" << endl;
  }
  EmitClassNameTab();

  str_ << endl << " # class dispatch table" << endl;
  if (cool_helper::g_log_cerr) {
    cerr << " # class dispatch table" << endl;
  }
  EmitClassDispatchTab();

  str_ << endl << " # class prototype" << endl;
  if (cool_helper::g_log_cerr) {
    cerr << " # class prototype" << endl;
  }
  EmitClassPrototype();

  str_ << endl << " # class direct parent tab" << endl;
  if (cool_helper::g_log_cerr) {
    cerr << " # class direct parent tab" << endl;
  }
  EmitClassDirectParentTab();

  str_ << endl << " # class prototype obj tab" << endl;
  if (cool_helper::g_log_cerr) {
    cerr << " # class prototype obj tab" << endl;
  }
  EmitClassProtObjTab();

  str_ << endl << " # class init method tab" << endl;
  if (cool_helper::g_log_cerr) {
    cerr << " # class init method tab" << endl;
  }
  EmitClassInitTab();

  str_ << endl << " # global text" << endl;
  if (cool_helper::g_log_cerr) {
    cerr << " # global text" << endl;
  }
  EmitGlobalText();

  str_ << endl << " # class init" << endl;
  if (cool_helper::g_log_cerr) {
    cerr << " # class init" << endl;
  }
  EmitClassInitMethod();

  str_ << endl << " # class methods " << endl;
  if (cool_helper::g_log_cerr) {
    cerr << " # class methods" << endl;
  }
  EmitClassMethods();

  str_ << "main:" << endl;
}

CodeGen::~CodeGen() {
  ;
}

void CodeGen::
EmitClassMethods() {
  const auto* c_syms = ConstantSymbol::Get();
  for (const auto& ele : class_info_tab_) {
    const std::string& class_name = ele.first;
    const auto* cinfo = ele.second;
    const auto* node = cinfo->ast_node;
    unique_ptr<Env> env(new Env(class_name, &class_info_tab_));

    // skip generate method code for basic classes
    if (class_name == c_syms->IO->GetString() ||
        class_name == c_syms->Object->GetString() ||
        class_name == c_syms->Str->GetString() ||
        class_name == c_syms->Int->GetString() ||
        class_name == c_syms->Bool->GetString()) {
      continue;
    }
    
    // 1. enter class scope
    // add self and attrs location mapping
    env->loc->EnterScope();
    env->loc->AddMapping("self", "$s0");
    const auto& ordered_attrs = cinfo->ordered_attrs;
    for (const auto& ele: ordered_attrs) {
      const std::string& name = ele.first;
      std::string offset = GetAttrOffset(cinfo->attrs_offset_tab, name);
      env->loc->AddMapping(name, offset);
    }

    // 2. generate code for new methods or overrided methods
    for (const auto& feature : *(node->features)) {
      if (IsSubClass<Feature, Attr>(feature)) {
        continue;
      }
      const auto* method = static_cast<Method*>(feature);
      std::string method_name = method->name->GetString();

      // 2.1 precalculate temp space for method
      env->allocated_temp_space = CalculateTemporaries(method->expression) * 4;

      // 2.2 lookup method signature
      const auto& method_sig_tab = cinfo->method_sig_tab;
      auto mst_it = method_sig_tab.find(method_name);
      if (mst_it == method_sig_tab.end()) {
        CoolDumpError(cerr)
          << "method_sig_tab cannot find " << method_name << endl;
        exit(-1);
      }

      // 2.3 create method scope
      // add method argument mapping
      env->loc->EnterScope();
      const auto& method_sig = mst_it->second;
      for (int i = 0; i < method_sig.size(); ++i) {
        const std::string& arg_name = method_sig[i].first;
        env->loc->AddMapping(arg_name,
                             GetArgumentOffset(i, method_sig.size()));
      }

      // 2.4 method label
      str_ << endl
           << class_name << "." << method_name << ":" << endl;

      // 2.5 setup stack frame
      EmitSetupStackFrame(str_, env->allocated_temp_space);

      // 2.6 method code gen
      env->next_free_temp_space = 4;
      HandleExpression(method->expression, env.get());

      // 2.6 free stack frame
      EmitFreeStackFrame(str_, env->allocated_temp_space);

      // 2.6.1 free pushed arg
      EmitADDIU(str_, "$sp", "$sp", to_string(method_sig.size() * 4));

      // 2.8 return
      EmitReturn(str_);
       
      // 2.9 exit method scope
      env->loc->ExitScope();
    }

    // 3 exit class scope
    env->loc->ExitScope();
  }
}

void CodeGen::
EmitClassTagDefinition() {
  const auto* c_sym = ConstantSymbol::Get();
  for (const auto& ele : class_info_tab_) {
    const auto& name = ele.first;
    if (name == c_sym->Bool->GetString() ||
        name == c_sym->Int->GetString() ||
        name == c_sym->Str->GetString()) {
      continue;
    }
    const std::string& tag_name = ele.second->tag_name;
    int tag_no = ele.second->layout->class_tag;
    str_ << tag_name << ":" << endl
         << WORD << tag_no << endl;
  }
}

void CodeGen::
EmitClassTagDeclaration() {
  const auto* c_sym = ConstantSymbol::Get();
  for (const auto& ele : class_info_tab_) {
    const auto& name = ele.first;
    if (name == c_sym->Bool->GetString() ||
        name == c_sym->Int->GetString() ||
        name == c_sym->Str->GetString()) {
      continue;
    }
    const std::string& tag_name = ele.second->tag_name;
    str_ << GLOBAL << tag_name << endl;
  }
}

void CodeGen::CollectClassInfo() {
  // clear class_info_tab_
  for (auto& ele : class_info_tab_) {
    delete ele.second;
  }

  tag_cnt_ = 0;
  unique_ptr<ClassInfo> info(new ClassInfo());
  CollectClassInfoHelper(inherit_tree_->LookupNode("Object"), info.get());
}

void CodeGen::CollectClassInfoHelper(const InheritanceTree::Node* node,
                                     ClassInfo* info) {

  if (!node) {
    return;
  }

  // init per class info
  auto* ninfo = new ClassInfo();
  ninfo->class_name = node->name;
  // object node doesn't have parent node
  ninfo->parent_name = node->parent != nullptr ? node->parent->name : "";
  ninfo->label = cool_helper::GetClassLabelName(ninfo->class_name);
  ninfo->tag_name = cool_helper::GetClassTagName(ninfo->class_name);
  ninfo->ast_node = node->ast_node_;
  ninfo->layout->gc_tag = -1;
  ninfo->layout->class_tag = tag_cnt_++;
  ninfo->layout->dispatch_tab_label =
    cool_helper::GetClassDispatchTabName(ninfo->class_name);
  tag_to_class_name_.push_back(ninfo->class_name);
  
  // info
  auto& ordered_attrs = info->ordered_attrs;
  auto& attrs_offset_tab = info->attrs_offset_tab;
  auto& ordered_methods = info->ordered_methods;
  auto& method_set = info->method_set;
  auto& method_sig_tab = info->method_sig_tab;
  auto& method_tab = info->method_tab;
  auto& methods_offset_tab = info->methods_offset_tab;

  // count number new features added to class inheritance tree
  int added_method_cnt = 0;
  int added_attr_cnt = 0;

  const auto& features = node->ast_node_->features;

  VecStr current_class_defined_methods;
  for (const auto& feature : *(features)) {
    if (IsSubClass<Feature, Method>(feature)) {
      const auto* method = static_cast<Method*>(feature);
      std::string method_name = method->name->GetString();
      current_class_defined_methods.push_back(method_name);
      // if current class defined class is not appear in class inheritance tree
      if (!method_set.count(method_name)) {
        method_set.insert(method_name);
        ordered_methods.push_back(method_name);
        ++added_method_cnt;
      }
      const auto* formals = method->formals;
      Signature args;
      for (const auto& formal : *(formals)) {
        args.push_back(make_pair(formal->name->GetString(),
                                 formal->type_decl->GetString()));
      }
      method_sig_tab[method_name] = args;
      method_tab[method_name].push_back(ninfo->class_name + "." + method_name);
    } else if (IsSubClass<Feature, Attr>(feature)) {
      const auto* attr = static_cast<Attr*>(feature);
      ++added_attr_cnt;
      ordered_attrs.push_back(make_pair(attr->name->GetString(),
                                        attr->type_decl->GetString()));
    } else {
      CoolDumpError(cerr)
        << "Unknow Feature Class" << endl;
      exit(-1);
    }
  }

  // generate offset
  int offset = 0;
  for (const auto& ele : ordered_attrs) {
    attrs_offset_tab[ele.first] = offset++;
  }
  offset = 0;
  for (const auto& n : ordered_methods) {
    methods_offset_tab[n] = offset++;
  }

  // copy
  ninfo->ordered_attrs = ordered_attrs;
  ninfo->attrs_offset_tab = attrs_offset_tab;
  ninfo->method_set = method_set;
  ninfo->ordered_methods = ordered_methods;
  ninfo->method_sig_tab = method_sig_tab;
  ninfo->method_tab = method_tab;
  ninfo->methods_offset_tab = methods_offset_tab;
  ninfo->layout->object_size = ordered_attrs.size() + 3;
  class_info_tab_[ninfo->class_name] = ninfo;

  // recursively collect
  for (const auto* child : node->children) {
    CollectClassInfoHelper(child, info);
  }

  // Pop added attributes
  while (added_attr_cnt > 0) {
    --added_attr_cnt;
    ordered_attrs.pop_back();
  }

  // Pop added Methods
  while (added_method_cnt > 0) {
    --added_method_cnt;
    const auto& name = ordered_methods.back();
    method_set.erase(name);
    method_sig_tab.erase(name);
    ordered_methods.pop_back();
  }

  // Pop added & override method
  for (const auto& n : current_class_defined_methods) {
    method_tab[n].pop_back();
    if (method_tab[n].empty()) {
      method_tab.erase(n);
    }
  }
}

void CodeGen::ClassInfo::Dump() {
  cout << "class name:" << class_name << " inherits "<< parent_name << endl;
  cout << "--> tag_name:" << tag_name << endl;
  cout << "--> label:" << label << endl;
  cout << "--> tag number:" << layout->class_tag << endl;
  cout << "--> size:" << layout->object_size << endl;
  cout << "--> dispatch table:" << layout->dispatch_tab_label << endl;
  cout << "--> Attributes:" << endl;
  for (const auto& ele : ordered_attrs) {
    cout << "----> " << ele.first << ":" << ele.second
         << ":" << attrs_offset_tab[ele.first] << endl;
  }
  cout << "--> Methods:" << endl;
  for (const auto& ele : ordered_methods) {
    cout << "----> " << ele
         << "(";
    for (const auto& arg : method_sig_tab[ele]) {
      cout << arg.first << ":" << arg.second << ",";
    }
    cout << ")"
         << ":"
         << method_tab[ele].back()
         << ":"
         << methods_offset_tab[ele]
         << endl;
  }
  cout << endl;
}

void CodeGen::
EmitSymbolTabConstants() {
  EmitStrSymbolTab();
  EmitIntSymbolTab();
  EmitBoolConstSymbol();
}

void CodeGen::
EmitBoolConstSymbol() {
  const auto* c_sym = ConstantSymbol::Get();
  
  if (!class_info_tab_.count(c_sym->Bool->GetString())) {
    CoolDumpError(cerr)
      << "class_info_tab_ cannot find "
      << c_sym->Bool->GetString()
      << endl;
  }

  const auto* cinfo = class_info_tab_[c_sym->Bool->GetString()];
  if (!cinfo) {
    CoolDumpError(cerr)
      << "cinfo is nullptr" << endl;
  }

  auto tag_no = cinfo->layout->class_tag;

  // bool const true
  str_ << WORD << "-1" << endl
       << BOOLCONST_TRUE_REF << ":" << endl
       << WORD << tag_no << endl
       << WORD << (DEFAULT_OBJFIELDS + BOOL_SLOTS) << endl
       << WORD << cool_helper::GetClassDispatchTabName(
           ConstantSymbol::Get()->Bool->GetString()) << endl
       << WORD << 1 << endl;

  // bool const false
  str_ << WORD << "-1" << endl
       << BOOLCONST_FALSE_REF << ":" << endl
       << WORD << tag_no << endl
       << WORD << (DEFAULT_OBJFIELDS + BOOL_SLOTS) << endl
       << WORD << cool_helper::GetClassDispatchTabName(
           ConstantSymbol::Get()->Bool->GetString()) << endl
       << WORD << 0 << endl;
}

void CodeGen::
EmitStrSymbolTab() {
  const auto* c_sym = ConstantSymbol::Get();
  if (!class_info_tab_.count(c_sym->Str->GetString())) {
    CoolDumpError(cerr)
      << "class_info_tab_ cannot find "
      << c_sym->Str->GetString()
      << endl;
  }

  const auto* cinfo = class_info_tab_[c_sym->Str->GetString()];
  if (!cinfo) {
    CoolDumpError(cerr)
      << "cinfo is nullptr" << endl;
  }

  auto tag_no = cinfo->layout->class_tag;
  for (const auto& ele : StrTable) {
    EmitStringTabEntry(ele.second, str_, tag_no);
  }
}

void CodeGen::
EmitIntSymbolTab() {
  const auto* c_sym = ConstantSymbol::Get();
  if (!class_info_tab_.count(c_sym->Int->GetString())) {
    CoolDumpError(cerr)
      << "class_info_tab_ cannot find "
      << c_sym->Int->GetString()
      << endl;
  }

  const auto* cinfo = class_info_tab_[c_sym->Int->GetString()];
  if (!cinfo) {
    CoolDumpError(cerr)
      << "cinfo is nullptr" << endl;
  }
  auto tag_no = cinfo->layout->class_tag;
  for (const auto& ele : IntTable) {
    EmitIntTabEntry(ele.second, str_, tag_no);
  }
}

void CodeGen::
EmitGlobalData() {
  using namespace cool_helper;

  const auto* c_sym = ConstantSymbol::Get();

  // Get Int Tag Number
  if (!class_info_tab_.count(c_sym->Int->GetString())) {
    CoolDumpError(cerr)
      << "class_info_tab_ cannot find "
      << c_sym->Int->GetString()
      << endl;
  }
  const auto* cinfo = class_info_tab_[c_sym->Int->GetString()];
  if (!cinfo) {
    CoolDumpError(cerr)
      << "cinfo is nullptr" << endl;
  }
  auto int_tag_no = cinfo->layout->class_tag;

  // Get Bool Tag Number
  if (!class_info_tab_.count(c_sym->Bool->GetString())) {
    CoolDumpError(cerr)
      << "class_info_tab_ cannot find "
      << c_sym->Bool->GetString()
      << endl;
  }
  cinfo = class_info_tab_[c_sym->Bool->GetString()];
  auto bool_tag_no = cinfo->layout->class_tag;

  // Get Str Tag Number
  if (!class_info_tab_.count(c_sym->Str->GetString())) {
    CoolDumpError(cerr)
      << "class_info_tab_ cannot find "
      << c_sym->Str->GetString()
      << endl;
  }
  cinfo = class_info_tab_[c_sym->Str->GetString()];
  auto str_tag_no = cinfo->layout->class_tag;


  // Emit global names must be defined first
  str_ << "\t.data\n" << ALIGN;
  str_ << GLOBAL << CLASS_NAME_TAB << endl
       << GLOBAL << GetProtoObjRef(c_sym->Main->GetString()) << endl
       << GLOBAL << GetProtoObjRef(c_sym->Int->GetString()) << endl
       << GLOBAL << GetProtoObjRef(c_sym->Str->GetString()) << endl
       << GLOBAL << BOOLCONST_TRUE_REF << endl
       << GLOBAL << BOOLCONST_FALSE_REF << endl
       << GLOBAL << GetClassTagName(c_sym->Int->GetString()) << endl
       << GLOBAL << GetClassTagName(c_sym->Bool->GetString()) << endl
       << GLOBAL << GetClassTagName(c_sym->Str->GetString()) << endl
       // Int, Bool, Str Tag definiton
       << GetClassTagName(c_sym->Int->GetString()) << ":" << endl
       << WORD << int_tag_no << endl
       << GetClassTagName(c_sym->Bool->GetString()) << ":" << endl
       << WORD << bool_tag_no << endl
       << GetClassTagName(c_sym->Str->GetString()) << ":" << endl
       << WORD << str_tag_no << endl;
}

void CodeGen::
EmitGCSelect() {
  str_ << GLOBAL << "_MemMgr_INITIALIZER" << endl;
  str_ << "_MemMgr_INITIALIZER:" << endl;
  str_ << WORD << _gc_init_names[cgen_Memmgr] << endl;
  str_ << GLOBAL << "_MemMgr_COLLECTOR" << endl;
  str_ << "_MemMgr_COLLECTOR:" << endl;
  str_ << WORD << _gc_collect_names[cgen_Memmgr] << endl;
  str_ << GLOBAL << "_MemMgr_TEST" << endl;
  str_ << "_MemMgr_TEST:" << endl;
  str_ << WORD << (cgen_Memmgr_Test == GC_TEST) << endl;
}

void CodeGen::
EmitClassNameTab() {
  str_ << CLASS_NAME_TAB << ":" << endl;
  for (const auto& name : tag_to_class_name_) {
    const auto* sym = StrTable.Lookup(name);
    if (!sym) {
      exit(-1);
    }
    str_ << WORD << sym->GetRef() << endl;
  }
}

void CodeGen::
EmitClassDispatchTab() {
  for (const auto& ele : class_info_tab_) {
    const auto* cinfo = ele.second;
    str_ << cinfo->layout->dispatch_tab_label << ":" << endl;
    for (const auto& method_name : cinfo->ordered_methods) {
      str_ << WORD << (cinfo->method_tab.at(method_name)).back() << endl;
    }
    str_ << endl;
  }
}

void CodeGen::
EmitClassPrototype() {
  const auto* c_syms = ConstantSymbol::Get();
  for (const auto& ele : class_info_tab_) {
    const auto* cinfo = ele.second;
    if (!cinfo) {
      CoolDumpError(cerr)
        << "cinfo is null" << endl;
      exit(-1);
    }
    str_ << WORD << cinfo->layout->gc_tag << endl
         << cinfo->label << ":" << endl
         << WORD << cinfo->layout->class_tag << endl
         << WORD << cinfo->layout->object_size << endl
         << WORD << cinfo->layout->dispatch_tab_label <<  endl;
    const auto& ordered_attrs = cinfo->ordered_attrs;
    for (const auto& ele : ordered_attrs) {
      const auto& name = ele.first;
      const auto& type = ele.second;
      if (type == c_syms->Int->GetString()) {
        str_ << WORD << IntTable.Lookup("0")->GetRef() << endl;
      } else if (type == c_syms->Bool->GetString()) {
        str_ << WORD << BOOLCONST_FALSE_REF << endl;
      } else if (type == c_syms->Str->GetString()) {
        str_ << WORD << StrTable.Lookup("")->GetRef() << endl;
      } else {
        str_ << WORD << 0 << endl;
      }
    }
  }
}

void CodeGen::
EmitGlobalText() {
  using namespace cool_helper;
  const auto* c_syms = ConstantSymbol::Get();
  str_ << GLOBAL << HEAP_START << endl
       << HEAP_START << ":"  << endl
       << WORD << 0 << endl
       << endl
       << "\t.text" << endl
       << GLOBAL << GetClassInitMethod(c_syms->Main->GetString()) << endl
       << GLOBAL << GetClassInitMethod(c_syms->Int->GetString()) << endl
       << GLOBAL << GetClassInitMethod(c_syms->Str->GetString()) << endl
       << GLOBAL << GetClassInitMethod(c_syms->Bool->GetString()) << endl
       << GLOBAL << "Main.main" << endl;
}

void CodeGen::
EmitClassInitMethod() {
  const auto* c_syms = ConstantSymbol::Get();
  for (const auto& ele : class_info_tab_) {
    const auto& class_name = ele.first;
    const auto* cinfo = ele.second;
    const auto* node = cinfo->ast_node;
    unique_ptr<Env> env(new Env(class_name, &class_info_tab_));
    // 1. precaculate the temporaries space in class.init method
    int temp_space = 0;
    for (const auto feature : *(node->features)) {
      if (IsSubClass<Feature, Attr>(feature)) {
        Attr* attr = static_cast<Attr*>(feature);
        if (IsSubClass<Expression, NoExpr>(attr->init)) {
          continue;
        }
        temp_space = max(temp_space, CalculateTemporaries(attr->init));
      }
    }

    env->allocated_temp_space = temp_space << 2;
    env->next_free_temp_space = 4;

    if (cool_helper::g_log_cerr) {
      CoolDump(cerr) << "total temp space:"
                     << env->allocated_temp_space << endl;
    }

    // 2. add attributes' location mapping (create a scope)
    // attr_name -> offset from this pointer
    env->loc->EnterScope();
    env->loc->AddMapping("self", "$s0");
    const auto& ordered_attrs = cinfo->ordered_attrs;
    for (const auto& ele : ordered_attrs) {
      const auto& name = ele.first;
      env->loc->AddMapping(name, GetAttrOffset(cinfo->attrs_offset_tab, name));
    }

    // 3. class init method label
    str_ << cool_helper::GetClassInitMethod(class_name) << ":" << endl;

    // 4. setup stack frame
    EmitSetupStackFrame(str_, env->allocated_temp_space);

    // 5. call init method of direct parent
    if (class_name != c_syms->Object->GetString()) {
      EmitJAL(str_,
              cool_helper::GetClassInitMethod(node->parent->GetString()));
    }

    // 6. init attributes
    for (const auto& feature : *(node->features)) {
      if (IsSubClass<Feature, Method>(feature)) {
        continue;
      }
      const auto* attr = static_cast<const Attr*>(feature);
      std::string name = attr->name->GetString();
      std::string type = attr->type_decl->GetString();
      if (IsSubClass<Expression, NoExpr>(attr->init)) {
        continue;
      }
      env->next_free_temp_space = 4;
      HandleExpression(attr->init, env.get());

      // 6.1 store init result in attr location
      const auto* l = env->loc->Lookup(name);
      if (!l) {
        CoolDumpError(cerr)
          << "env->loc cannot find " << name << endl;
        exit(-1);
      }
      EmitSW(str_, ACC, *l);
    }

    // 6.5 set return value $a0 to self pointer
    EmitMOVE(str_, ACC, SELF);
  
    // 7. free stack frame
    EmitFreeStackFrame(str_, env->allocated_temp_space);

    // 8. return
    EmitReturn(str_);

    env->loc->ExitScope();
  }
}

void CodeGen::
EmitFreeStackFrame(std::ostream& str, int temp_space) {
  EmitLW(str, to_string(temp_space + 12) + "($sp)", "$fp");
  EmitLW(str, to_string(temp_space + 8) + "($sp)", "$s0");
  EmitLW(str, to_string(temp_space + 4) + "($sp)", "$ra");
  EmitADDIU(str, "$sp", "$sp", to_string(temp_space + 12));
}

int CodeGen::
CalculateTemporaries(const ExpressionP expr) {
  int ret = 0;
  if (IsSubClass<Expression, Assign>(expr)) {
    const auto* assign = static_cast<Assign*>(expr);
    ret = CalculateTemporaries(assign->expression);
  } else if (IsSubClass<Expression, StaticDispatch>(expr)) {
    const auto* dispatch = static_cast<StaticDispatch*>(expr);
    ret = CalculateTemporaries(dispatch->expression);
    for (const auto& e : *(dispatch->actual_exprs))  {
      ret = max(ret, CalculateTemporaries(e));
    }
  } else if (IsSubClass<Expression, Dispatch>(expr)) {
    const auto* dispatch = static_cast<Dispatch*>(expr);
    ret = CalculateTemporaries(dispatch->expression);
    for (const auto& e : *(dispatch->actual_exprs)) {
      ret = max(ret, CalculateTemporaries(e));
    }
  } else if (IsSubClass<Expression, Cond>(expr)) {
    const auto* cond = static_cast<Cond*>(expr);
    ret = CalculateTemporaries(cond->pred);
    ret = max(ret, CalculateTemporaries(cond->then_exp));
    ret = max(ret, CalculateTemporaries(cond->else_exp));
  } else if (IsSubClass<Expression, Loop>(expr)) {
    const auto* loop = static_cast<Loop*>(expr);
    ret = CalculateTemporaries(loop->pred);
    ret = max(ret, CalculateTemporaries(loop->body));
  } else if (IsSubClass<Expression, Typcase>(expr)) {
    const auto* typcase = static_cast<Typcase*>(expr);
    ret = CalculateTemporaries(typcase->expression);
    for (const auto& c : *(typcase->cases)) {
      ret = max(ret, 1 + CalculateTemporaries(c->expression));
    }
  } else if (IsSubClass<Expression, Block>(expr)) {
    const auto* block = static_cast<Block*>(expr);
    for (const auto& e : *(block->body)) {
      ret = max(ret, CalculateTemporaries(e));
    }
  } else if (IsSubClass<Expression, Let>(expr)) {
    const auto* let = static_cast<Let*>(expr);
    ret = max(CalculateTemporaries(let->init),
              1 + CalculateTemporaries(let->body));
  } else if (IsSubClass<Expression, Plus>(expr)) {
    const auto* plus = static_cast<Plus*>(expr);
    ret = max(CalculateTemporaries(plus->e1),
              2 + CalculateTemporaries(plus->e2));
  } else if (IsSubClass<Expression, Sub>(expr)) {
    const auto* sub = static_cast<Sub*>(expr);
    ret = max(CalculateTemporaries(sub->e1),
              2 + CalculateTemporaries(sub->e2));
  } else if (IsSubClass<Expression, Mul>(expr)) {
    const auto* mul = static_cast<Mul*>(expr);
    ret = max(CalculateTemporaries(mul->e1),
              2 + CalculateTemporaries(mul->e2));
  } else if (IsSubClass<Expression, Divide>(expr)) {
    const auto* divide = static_cast<Divide*>(expr);
    ret = max(CalculateTemporaries(divide->e1),
              2 + CalculateTemporaries(divide->e2));
  } else if (IsSubClass<Expression, Neg>(expr)) {
    const auto* neg = static_cast<Neg*>(expr);
    ret = max(1, CalculateTemporaries(neg->e));
  } else if (IsSubClass<Expression, Lt>(expr)) {
    const auto* lt = static_cast<Lt*>(expr);
    ret = max(CalculateTemporaries(lt->e1),
              2 + CalculateTemporaries(lt->e2));
  } else if (IsSubClass<Expression, Eq>(expr)) {
    const auto* eq = static_cast<Eq*>(expr);
    ret = max(CalculateTemporaries(eq->e1),
              2 + CalculateTemporaries(eq->e2));
  } else if (IsSubClass<Expression, Leq>(expr)) {
    const auto* leq = static_cast<Leq*>(expr);
    ret = max(CalculateTemporaries(leq->e1),
              2 + CalculateTemporaries(leq->e2));
  } else if (IsSubClass<Expression, Comp>(expr)) {
    const auto* comp = static_cast<Comp*>(expr);
    ret = CalculateTemporaries(comp->e);
  } else if (IsSubClass<Expression, IntConst>(expr) ||
             IsSubClass<Expression, BoolConst>(expr) ||
             IsSubClass<Expression, StringConst>(expr) ||
             IsSubClass<Expression, New>(expr) ||
             IsSubClass<Expression, IsVoid>(expr) ||
             IsSubClass<Expression, NoExpr>(expr) ||
             IsSubClass<Expression, Object>(expr)) {
    ret = 0;
  } else {
    CoolDumpError(cerr)
      << "unkonw expression class" << endl;
    exit(1);
  }
  return ret;
}

CodeGen::Env::
Env(const std::string& name,
    const ClassInfoTab* info) : 
  class_name(name),
  class_info_tab(info),
  allocated_temp_space(-1), 
  next_free_temp_space(-1), 
  loc(new Scope()) {
  const auto* cinfo = class_info_tab->at(class_name);
  if (!cinfo) {
    CoolDumpError(cerr)
      << "class_info_tab no " << class_name << endl;
    exit(1);
  }
  const auto* node = cinfo->ast_node;
  filename = node->filename->GetString();
  _g_filename = filename;
}

CodeGen::Env::~Env() {
}

std::string
CodeGen::GetAttrOffset(const StrToIntTab& tab, const std::string& name) {
  if (tab.count(name) == 0) {
    CoolDumpError(cerr)
      << "Cannot find " << name << " in attributes tab" << endl;
    exit(-1);
  }

  std::ostringstream oss;
  oss << ((tab.find(name))->second + 3) * 4 << "($s0)";
  return oss.str();
}

void CodeGen::
EmitSetupStackFrame(std::ostream& str, int temp_space) {
  EmitADDIU(str, "$sp", "$sp", to_string(-(temp_space + 12)));
  EmitSW(str, "$fp", to_string(temp_space + 12) + "($sp)");
  EmitSW(str, "$s0", to_string(temp_space + 8) + "($sp)");
  EmitSW(str, "$ra", to_string(temp_space + 4) + "($sp)");
  EmitADDIU(str, "$fp", "$sp", to_string(temp_space + 4));
  EmitMOVE(str, SELF, ACC);
}

void CodeGen::
EmitADDIU(std::ostream& str, const std::string& dst,
          const std::string& op1Reg, const std::string& op2Imm) {
  str << ADDIU << dst << "\t" << op1Reg << "\t" << op2Imm << endl;
}

void CodeGen::
EmitSW(ostream& str, const std::string& srcReg, const std::string& tarAddr) {
  str << SW << srcReg << "\t" << tarAddr << endl;
}

void CodeGen::
EmitLW(ostream& str, const std::string& srcAddr, const std::string& tarReg) {
  str << LW << tarReg << "\t" << srcAddr << endl;
}

void CodeGen::
EmitMOVE(ostream& str, const std::string& tarReg, const std::string& srcReg) {
  str << MOVE << tarReg << "\t" << srcReg << endl;
}

void CodeGen::
EmitPush(std::ostream& str, const std::string& srcReg) {
  EmitSW(str, srcReg, "0($sp)");
  EmitADDIU(str, "$sp", "$sp", "-4");
}

void CodeGen::
EmitPop(std::ostream& str, const std::string& dstReg) {
  EmitADDIU(str, "$sp", "$sp", "4");
  EmitLW(str, SPTop, dstReg);
}

void CodeGen::
EmitPop(std::ostream& str) {
  EmitADDIU(str, "$sp", "$sp", "4");
}

void CodeGen::
EmitReturn(std::ostream& str) {
  str << "\tjr\t$ra" << endl;
}

void CodeGen::
EmitJAL(std::ostream& str, const std::string& tar) {
  str << "\tjal\t" << tar << endl;
}

void CodeGen::
EmitBNE(std::ostream& str, const std::string& r1, const std::string& r2,
        const std::string& label) {
  str << "\tbne\t" << r1 << " " << r2 << " " << label << endl;
}

void CodeGen::
EmitBEQZ(std::ostream& str, const std::string& reg, const std::string& label) {
  str << "\tbeqz\t" << reg << " " << label << endl;
}

void CodeGen::
EmitLI(std::ostream& str, const std::string& r, const std::string& imm) {
  str << "\tli\t" << r << " " << imm << endl;
}

void CodeGen::
EmitLA(std::ostream& str, const std::string& r, const std::string& addr) {
  str << "\tla\t" << r << " " << addr << endl;
}

void CodeGen::
EmitJALR(std::ostream& str, const std::string& reg) {
  str << "\tjalr\t" << reg << endl;
}

void CodeGen::
EmitB(std::ostream& str, const std::string& label) {
  str << "\tb\t" << label << endl;
}

void CodeGen::
EmitADD(std::ostream& str,
        const std::string& tarReg,
        const std::string& srcReg1,
        const std::string& srcReg2) {
  str << "\tadd\t" << tarReg << "\t" << srcReg1 << "\t" << srcReg2 << endl;
}

void CodeGen::
EmitSUB(std::ostream& str,
        const std::string& tarReg,
        const std::string& srcReg1,
        const std::string& srcReg2) {
  str << "\tsub\t" << tarReg << "\t" << srcReg1 << "\t" << srcReg2 << endl;
}

void CodeGen::
EmitMUL(std::ostream& str,
        const std::string& tarReg,
        const std::string& srcReg1,
        const std::string& srcReg2) {
  str << "\tmul\t" << tarReg << "\t" << srcReg1 << "\t" << srcReg2 << endl;
}

void CodeGen::
EmitDIV(std::ostream& str,
        const std::string& tarReg,
        const std::string& srcReg1,
        const std::string& srcReg2) {
  str << "\tdiv\t" << tarReg << "\t" << srcReg1 << "\t" << srcReg2 << endl;
}

void CodeGen::
EmitNEG(std::ostream& str,
        const std::string& srcReg,
        const std::string& tarReg) {
  str << "\tneg\t" << tarReg << "\t" << srcReg << endl;
}

void CodeGen::
EmitBLT(std::ostream& str, const std::string& reg1, const std::string& reg2,
        const std::string& label) {
  str << "\tblt\t" << reg1 << " " << reg2 << " " << label << endl;
}

void CodeGen::
EmitBEQ(std::ostream& str, const std::string& reg1, const std::string& reg2,
        const std::string& label) {
  str << "\tbeq\t" << reg1 << " " << reg2 << " " << label << endl;
}

void CodeGen::
EmitBLE(std::ostream& str, const std::string& reg1, const std::string& reg2,
        const std::string& label) {
  str << "\tble\t" << reg1 << " " << reg2 << " " << label << endl;
}

void CodeGen::
HandleAssign(const Assign* assign, Env* env) {
  HandleExpression(assign->expression, env);
  const auto* l = env->loc->Lookup(assign->name->GetString());
  if (!l) {
    CoolDumpError(cerr)
      << "cannot find " << assign->name->GetString() << endl;
    exit(-1);
  }
  EmitSW(str_, ACC, *l);
}

// e0@T.f(e1,e2,..,en)
void CodeGen::
HandleStaticDispatch(const StaticDispatch* dispatch, Env* env) {
  // 1. evaluate each argument expression from left to right
  //    and push result onto the stack
  for (const auto& e : *(dispatch->actual_exprs)) {
    HandleExpression(e, env);
    EmitPush(str_, ACC);
  }

  // 2. evaluate dispatch expression
  // 2.1 evaluate
  HandleExpression(dispatch->expression, env);
  std::string static_type = dispatch->type_name->GetString();
  const std::string& class_name =
    static_type == "SELF_TYPE" ? env->class_name : static_type;

  // 2.2 check whether result is void
  const std::string label(AllocateNewJumpLabel());
  EmitBNE(str_, ACC, ZERO, label);

  // 2.3 abort
  str_ << "\tla\t" << ACC << " ";
  const auto* p = StrTable.Lookup(env->filename);
  if (!p) {
    CoolDumpError(cerr)
      << "StrTable cannot find " << env->filename << endl;
    exit(-1);
  }
  str_ << p->GetRef() << endl;
  str_ << endl;
  str_ << "\tli\t" << "$t1" << " 1" << endl;
  str_ << "\tjal\t" << "_dispatch_abort" << endl;
  str_ << label << ":" << endl;

  // 3. lookup correct method
  // 3.1 find class info
  auto it = env->class_info_tab->find(class_name);
  if (it == env->class_info_tab->end()) {
    CoolDumpError(cerr)
      << "env->class_info_tab cannot find " << class_name << endl;
    exit(-1);
  }

  // 3.2 find method
  // NOTE: ACC keeps the a pointer to the object of expr
  const auto* cinfo = it->second;
  string method_name = dispatch->name->GetString();
  auto it2 = cinfo->method_tab.find(method_name);
  if (it2 == cinfo->method_tab.end()) {
    CoolDumpError(cerr)
      << "cinfo->method_tab cannot find " << method_name << endl;
    exit(-1);
  }

  method_name = it2->second.back();

  // 4. invoke method
  EmitJAL(str_, method_name);
}

void CodeGen::
HandleDispatch(const Dispatch* dispatch, Env* env) {
  // 1. evaluate each argument expression from left to right
  //     and push result onto the stack
  for (const auto& e : *(dispatch->actual_exprs)) {
    HandleExpression(e, env);
    EmitPush(str_, ACC);
  }

  // 2. evaluate dispatch expression
  // 2.1 evaluate
  HandleExpression(dispatch->expression, env);
  string expr_type = dispatch->expression->GetType();
  const std::string& class_name =
    expr_type == "SELF_TYPE" ? env->class_name : expr_type;

  // 2.2 check whether result is void
  const std::string label(AllocateNewJumpLabel());
  EmitBNE(str_, ACC, ZERO, label);

  // 2.3 abort
  str_ << "\tla\t" << ACC << " ";
  const auto* p = StrTable.Lookup(env->filename);
  if (!p) {
    CoolDumpError(cerr)
      << "StrTable cannot find " << env->filename << endl;
    exit(-1);
  }
  str_ << p->GetRef() << endl;
  str_ << endl;
  str_ << "\tli\t" << "$t1" << " 1" << endl;
  str_ << "\tjal\t" << "_dispatch_abort" << endl;
  str_ << label << ":" << endl;

  // 3. lookup correct method
  // 3.1 find class info
  auto it = env->class_info_tab->find(class_name);
  if (it == env->class_info_tab->end()) {
    CoolDumpError(cerr)
      << "env->class_info_tab cannot find " << class_name << endl;
    exit(-1);
  }

  // 3.2 lookup method offset
  const string method_name = dispatch->name->GetString();
  const auto* cinfo = it->second;
  auto it2 = cinfo->methods_offset_tab.find(method_name);
  if (it2 == cinfo->methods_offset_tab.end()) {
    CoolDumpError(cerr)
      << "methods_offset_tab cannot find " << method_name << " in"
      << " class " << class_name
      << endl;
    exit(-1);
  }
  int offset = it2->second * 4;

  // 4. method dispatch
  // 4.1 load dispatch pointer
  EmitLW(str_, GetRegOffset(8, ACC), T1);
  // 4.2 lookup method
  EmitLW(str_, GetRegOffset(offset, T1), T1);
  // 4.3 invoke method
  EmitJALR(str_, T1);

}

std::string CodeGen::
GetRegOffset(int offset, const std::string& reg) {
  std::ostringstream oss;
  oss << offset << "(" << reg << ")";
  return oss.str();
}

void CodeGen::
HandleCond(const Cond* cond, Env* env) {
  HandleExpression(cond->pred, env);
  // 1. load the value of Bool object into T1
  EmitLW(str_, GetRegOffset(12, ACC), T1);
  // 2. test pred if false jump to else expr
  std::string else_label(AllocateNewJumpLabel());
  std::string end_label(AllocateNewJumpLabel());
  EmitBEQZ(str_, T1, else_label);
  // 3. then expr
  HandleExpression(cond->then_exp, env);
  EmitB(str_, end_label);
  // 4. els expr
  str_ << else_label << ":" << endl;
  HandleExpression(cond->else_exp, env);
  // 5. end label
  str_ << end_label << ":" << endl;
}

void CodeGen::
HandleLoop(const Loop* loop, Env* env) {
  std::string pred_label = AllocateNewJumpLabel();
  std::string end_label = AllocateNewJumpLabel();
  
  // 1. evaluate pred expression
  str_ << pred_label << ":" << endl;
  HandleExpression(loop->pred, env);
  
  // 2. if pred false then jump to end
  EmitLW(str_, GetRegOffset(12, ACC), T1);
  EmitBEQZ(str_, T1, end_label);
  
  // 3. evaluate body expression and jump back to pred
  HandleExpression(loop->body, env);
  EmitB(str_, pred_label);

  str_ << end_label << ":" << endl;
  
  // 4. return value of loop is void
  EmitLI(str_, ACC, "0");
}

void CodeGen::
HandleCase(const Typcase* typcase, Env* env) {
  // 1. evalute expression and abort on void
  HandleExpression(typcase->expression, env);

  // 1.1 abort on void
  std::string label = AllocateNewJumpLabel();
  EmitBNE(str_, ACC, ZERO, label);
  str_ << "\tla\t" << ACC << " ";
  const auto* p = StrTable.Lookup(env->filename);
  if (!p) {
    CoolDumpError(cerr)
      << "StrTable cannot find " << env->filename << endl;
    exit(-1);
  }
  str_ << p->GetRef() << endl;
  str_ << endl;
  str_ << "\tli\t" << "$t1" << " 1" << endl;
  str_ << "\tjal\t" << "_case_abort2" << endl;
  str_ << label << ":" << endl;
  // 2. collect branch info
  VecStr branch_labels;
  std::vector<CaseP> branch_vec;
  vector<int> tags;
  for (auto& branch : *(typcase->cases)) {
    // 2.1 get branch type tag no
    branch_vec.push_back(branch);
    std::string type_name = branch->type_decl->GetString();
    const auto* class_info_tab = env->class_info_tab;
    auto it = class_info_tab->find(type_name);
    if (it == class_info_tab->end()) {
      CoolDumpError(cerr)
        << "class_info_tab cannot find " << type_name << endl;
      exit(-1);
    }
    const auto* cinfo = it->second;
    tags.push_back(cinfo->layout->class_tag);
    // 2.2 allocate branch label
    branch_labels.push_back(AllocateNewJumpLabel());
  }

  // 3. load expr type tag no into T1
  EmitLW(str_, GetRegOffset(0, ACC), T1);
  
  // 3. find ancestor
  std::string find_ancestor_label = AllocateNewJumpLabel();
  std::string no_match_label = AllocateNewJumpLabel();

  str_ << find_ancestor_label << ":" << endl;
  
  for (int i = 0; i < tags.size(); ++i) {
    // 3.1 load branch type tag no into T2
    EmitLI(str_, T2, to_string(tags[i]));
    // 3.2 if tag no equals then jump to its branch
    EmitBEQ(str_, T1, T2, branch_labels[i]);
  }

  // 3.3 check whether there is no match case
  EmitLI(str_, T2, "0");
  EmitBEQ(str_, T1, T2, no_match_label);
  
  // 3.4 get parent
  EmitLA(str_, T2, CLASS_DIRECT_PARENT_TAB);
  EmitLI(str_, T3, "4");
  EmitMUL(str_, T1, T1, T3);
  EmitADD(str_, T1, T1, T2);   // T1 contains the addr of parent tag
  EmitLW(str_, GetRegOffset(0, T1), T1); // load parent tag no
  EmitB(str_, find_ancestor_label);

  // 3.5 no match case abort
  str_ << no_match_label << ":" << endl;
  str_ << "\tjal\t" << "_case_abort" << endl;

  // 4. code gen for case branch
  std::string end_label = AllocateNewJumpLabel();
  for (int i = 0; i < tags.size(); ++i) {
    str_ << branch_labels[i] << ":" << endl;
    const CaseP branch = branch_vec[i];
    std::string id_name = branch->name->GetString();
    std::string type_decl = branch->type_decl->GetString();
    std::string temp_space = GetNextTempSpace(env);
    // 4.1 store expr value into temp_space
    EmitSW(str_, ACC, temp_space);
    // 4.2 create branch scope
    env->loc->EnterScope();
    // 4.3 add mapping: id -> temp_space
    env->loc->AddMapping(
        id_name, temp_space);
    // 4.4 evalute expr
    HandleExpression(branch->expression, env);
    // 4.5 exit branch scope
    env->loc->ExitScope();

    // 4.6 free tempspace
    FreeTempSpace(env, 1);
    EmitB(str_, end_label);
  }

  str_ << end_label << ":" << endl;
}

void CodeGen::
HandleExpression(const ExpressionP expr, Env* env) {
  if (IsSubClass<Expression, Assign>(expr)) {
    HandleAssign(static_cast<const Assign*>(expr), env);
  } else if (IsSubClass<Expression, StaticDispatch>(expr)) {
    HandleStaticDispatch(static_cast<const StaticDispatch*>(expr), env);
  } else if (IsSubClass<Expression, Dispatch>(expr)) {
    HandleDispatch(static_cast<const Dispatch*>(expr), env);
  } else if (IsSubClass<Expression, Cond>(expr)) {
    HandleCond(static_cast<const Cond*>(expr), env);
  } else if (IsSubClass<Expression, Loop>(expr)) {
    HandleLoop(static_cast<const Loop*>(expr), env);
  } else if (IsSubClass<Expression, Typcase>(expr)) {
    HandleCase(static_cast<const Typcase*>(expr), env);
  } else if (IsSubClass<Expression, Block>(expr)) {
    HandleBlock(static_cast<const Block*>(expr), env);
  } else if (IsSubClass<Expression, Let>(expr)) {
    HandleLet(static_cast<const Let*>(expr), env);
  } else if (IsSubClass<Expression, Plus>(expr)) {
    HandlePlus(static_cast<const Plus*>(expr), env);
  } else if (IsSubClass<Expression, Sub>(expr)) {
    HandleSub(static_cast<const Sub*>(expr), env);
  } else if (IsSubClass<Expression, Mul>(expr)) {
    HandleMul(static_cast<const Mul*>(expr), env);
  } else if (IsSubClass<Expression, Divide>(expr)) {
    HandleDivide(static_cast<const Divide*>(expr), env);
  } else if (IsSubClass<Expression, Neg>(expr)) {
    HandleNeg(static_cast<const Neg*>(expr), env);
  } else if (IsSubClass<Expression, Lt>(expr)) {
    HandleLt(static_cast<const Lt*>(expr), env);
  } else if (IsSubClass<Expression, Eq>(expr)) {
    HandleEq(static_cast<const Eq*>(expr), env);
  } else if (IsSubClass<Expression, Leq>(expr)) {
    HandleLeq(static_cast<const Leq*>(expr), env);
  } else if (IsSubClass<Expression, Comp>(expr)) {
    HandleComp(static_cast<const Comp*>(expr), env);
  } else if (IsSubClass<Expression, IntConst>(expr)) {
    HandleIntConst(static_cast<const IntConst*>(expr), env);
  } else if (IsSubClass<Expression, StringConst>(expr)) {
    HandleStrConst(static_cast<const StringConst*>(expr), env);
  } else if (IsSubClass<Expression, BoolConst>(expr)) {
    HandleBoolConst(static_cast<const BoolConst*>(expr), env);
  } else if (IsSubClass<Expression, New>(expr)) {
    HandleNew(static_cast<const New*>(expr), env);
  } else if (IsSubClass<Expression, IsVoid>(expr)) {
    HandleIsVoid(static_cast<const IsVoid*>(expr), env);
  } else if (IsSubClass<Expression, NoExpr>(expr)) {
    HandleNoExpr(static_cast<const NoExpr*>(expr), env);
  } else if (IsSubClass<Expression, Object>(expr)) {
    HandleObject(static_cast<const Object*>(expr), env);
  } else {
    CoolDumpError(cerr)
      << "Uknow expression class" << endl;
    exit(-1);
  }
}

void CodeGen::
HandleNew(const New* n, Env* env) {
  std::string type = n->type_name->GetString();
  if (type == "SELF_TYPE") {
    // load prototype object label
    EmitLW(str_, GetRegOffset(0, SELF), T1); // T1 = current class tag no
    EmitLA(str_, T3, "4");     // T3 = 4
    EmitMUL(str_, T1, T1, T3); // offset = T1 * T3 = tag_no * 4
    EmitLA(str_, T2, CLASS_PROT_OBJ_TAB); // T2 = TAB
    EmitADD(str_, T1, T1, T2); // T1 = TAB + OFFSET
    EmitLW(str_, GetRegOffset(0, T1), ACC); // ACC = *(0($T1))
    EmitJAL(str_, "Object.copy");

    // load class init label
    EmitLW(str_, GetRegOffset(0, SELF), T1); // T1 = current class tag no
    EmitLA(str_, T3, "4");     // T3 = 4
    EmitMUL(str_, T1, T1, T3); // offset = T1 * T3 = tag_no * 4
    EmitLA(str_, T2, CLASS_INIT_TAB); // T2 = TAB
    EmitADD(str_, T1, T1, T2); // T1 = TAB + OFFSET
    EmitLW(str_, GetRegOffset(0, T1), T1); // T1 = * (0($T1))
    EmitJALR(str_, T1);
  } else {
    std::string class_prot = type + PROTOBJ_SUFFIX;
    std::string class_init = type + CLASSINIT_SUFFIX;
    EmitLA(str_, ACC, class_prot);
    EmitJAL(str_, "Object.copy");
    EmitJAL(str_, class_init);
  }
}

void CodeGen::
HandleIsVoid(const IsVoid* isvoid, Env* env) {
  // 1. evaluate e1
  HandleExpression(isvoid->e, env);

  // 2. move ACC to T1
  EmitMOVE(str_, T1, ACC);

  // 3. load true
  str_ << "\tla\t" << ACC << "\t" << BOOLCONST_TRUE_REF << endl;

  // 4. if e1 is false then branch true else branch to else
  std::string label(AllocateNewJumpLabel());
  EmitBEQZ(str_, T1, label);

  // 5. load false
  str_ << "\tla\t" << ACC << "\t" << BOOLCONST_FALSE_REF << endl;

  // 6. true label
  str_ << label << ":" << endl;
}

void CodeGen::
HandleNoExpr(const NoExpr* noexpr, Env* env) {
  return;
}

void CodeGen::
HandleObject(const Object* obj, Env* env) {
  std::string* l = env->loc->Lookup(obj->name->GetString());
  if (l == NULL) {
    CoolDumpError(cerr)
      << "cannot find " << obj->name->GetString() << endl;
    exit(-1);
  }

  // if expr is self, move $a0, $s0
  // $s0 always contains the self pointer of current object
  if (*l == "$s0") {
    EmitMOVE(str_, ACC, *l);
  } else {
    EmitLW(str_, *l, ACC);
  }
}

void CodeGen::
HandleNeg(const Neg* neg, Env* env) {
  // 1. evaluate e1
  HandleExpression(neg->e, env);

  // 1.1 allocate temp space
  std::string temp_space = GetNextTempSpace(env);
  EmitSW(str_, ACC, temp_space);

  // 1.2 creat new int
  EmitLA(str_, ACC, "Int_protObj");
  EmitJAL(str_, "Int_init");
  
  // 2. load e1.val into t1
  EmitLW(str_, temp_space , T1);
  EmitLW(str_, GetRegOffset(12, T1), T1);

  // 3. neg
  EmitNEG(str_, T1, T1);

  // 4. store result into ACC field
  EmitSW(str_, T1, GetRegOffset(12, ACC));

  // 5. free temp space
  FreeTempSpace(env, 1);
}

void CodeGen::
HandleLt(const Lt* lt, Env* env) {
  // 1. evaluate e1
  HandleExpression(lt->e1, env);

  // 2. allocate temp space for e1 result
  std::string e1_t = GetNextTempSpace(env);

  // 3. store e1 value into e1_t
  EmitSW(str_, ACC, e1_t);

  // 4. evaluate e2
  HandleExpression(lt->e2, env);

  // 5. allocate temp space for e2 result
  std::string e2_t = GetNextTempSpace(env);

  // 6. store e2 value into e2_t
  EmitSW(str_, ACC, e2_t);
  
  // 7. load true
  str_ << "\tla\t" << ACC << "\t" << BOOLCONST_TRUE_REF << endl;
  
  // 8. load e1 into t1
  EmitLW(str_, e1_t, T1);

  // 9. load e1.val into t1
  EmitLW(str_, GetRegOffset(12, T1), T1);

  // 10. load e2 into t2
  EmitLW(str_, e2_t, T2);

  // 11. load e2.val into t2
  EmitLW(str_, GetRegOffset(12, T2), T2);

  // 12. if t1 < t2 then branch to true else branch to false
  std::string label(AllocateNewJumpLabel());
  EmitBLT(str_, T1, T2, label);

  // 13. load false
  str_ << "\tla\t" << ACC << "\t" << BOOLCONST_FALSE_REF << endl;

  // 14. true label
  str_ << label << ":" << endl;

  // 15. free temp space
  FreeTempSpace(env, 2);
}

void CodeGen::
HandleEq(const Eq* eq, Env* env) {
  // 1. evaluate e1
  HandleExpression(eq->e1, env);

  // 2. allocate temp space for e1 result
  std::string e1_t = GetNextTempSpace(env);

  // 3. store e1 value into e1_t
  EmitSW(str_, ACC, e1_t);

  // 4. evaluate e2
  HandleExpression(eq->e2, env);

  // 5. allocate temp space for e2 result
  std::string e2_t = GetNextTempSpace(env);

  // 6. store e2 value into e2_t
  EmitSW(str_, ACC, e2_t);
  
  // 7. A0 = true
  str_ << "\tla\t" << ACC << "\t" << BOOLCONST_TRUE_REF << endl;
  
  // 8. load e1 into t1
  EmitLW(str_, e1_t, T1);
  // 9. load e2 into t2
  EmitLW(str_, e2_t, T2);
  
  std::string label = AllocateNewJumpLabel();

  // 10. use equality_test given in trap.handler
  EmitBEQ(str_, T1, T2, label);

  // 11. if two pointers point to different objects, use equality_test
  // given in trap.handler
  // A1 = false
  str_ << "\tla\t" << A1 << "\t" << BOOLCONST_FALSE_REF << endl;
  EmitJAL(str_, "equality_test");
 
  // 12. label
  str_ << label << ":" << endl;

  // 13. free temp space
  FreeTempSpace(env, 2);
}

void CodeGen::
HandleLeq(const Leq* leq, Env* env) {
  // 1. evaluate e1
  HandleExpression(leq->e1, env);

  // 2. allocate temp space for e1 result
  std::string e1_t = GetNextTempSpace(env);

  // 3. store e1 value into e1_t
  EmitSW(str_, ACC, e1_t);

  // 4. evaluate e2
  HandleExpression(leq->e2, env);

  // 5. allocate temp space for e2 result
  std::string e2_t = GetNextTempSpace(env);

  // 6. store e2 value into e2_t
  EmitSW(str_, ACC, e2_t);
  
  // 7. load true
  str_ << "\tla\t" << ACC << "\t" << BOOLCONST_TRUE_REF << endl;
  
  // 8. load e1 into t1
  EmitLW(str_, e1_t, T1);

  // 9. load e1.val into t1
  EmitLW(str_, GetRegOffset(12, T1), T1);

  // 10. load e2 into t2
  EmitLW(str_, e2_t, T2);

  // 11. load e2.val into t2
  EmitLW(str_, GetRegOffset(12, T2), T2);

  // 12. if t1 < t2 then branch to true else branch to false
  std::string label(AllocateNewJumpLabel());
  EmitBLE(str_, T1, T2, label);

  // 13. load false
  str_ << "\tla\t" << ACC << "\t" << BOOLCONST_FALSE_REF << endl;

  // 14. true label
  str_ << label << ":" << endl;

  // 15. free temp space
  FreeTempSpace(env, 2);
}

void CodeGen::
HandleComp(const Comp* comp, Env* env) {
  // 1. evaluate e1
  HandleExpression(comp->e, env);
  
  // 2. load e1.val into t1
  EmitLW(str_, GetRegOffset(12, ACC), T1);

  // 3. load true
  str_ << "\tla\t" << ACC << "\t" << BOOLCONST_TRUE_REF << endl;

  // 4. if e1 is false then branch true else branch to else
  std::string label(AllocateNewJumpLabel());
  EmitBEQZ(str_, T1, label);

  // 5. load false
  str_ << "\tla\t" << ACC << "\t" << BOOLCONST_FALSE_REF << endl;

  // 6. true label
  str_ << label << ":" << endl;
}

void CodeGen::
HandleSub(const Sub* sub, Env* env) {
  // 1. evaluate e1
  HandleExpression(sub->e1, env);

  // 2. allocate temp space for e1 result
  std::string e1_t = GetNextTempSpace(env);

  // 3. store e1 value into e1_t
  EmitSW(str_, ACC, e1_t);

  // 4. evaluate e2
  HandleExpression(sub->e2, env);

  // 5. allocate temp space for e2 result
  std::string e2_t = GetNextTempSpace(env);

  // 6. store e2 value into e2_t
  EmitSW(str_, ACC, e2_t);
  
  // 7. load Int_protObj into ACC
  EmitLA(str_, ACC, "Int_protObj");

  // 8. call Object.copy and Int_init
  EmitJAL(str_, "Object.copy");
  EmitJAL(str_, "Int_init");

  // 9. load e1 into t1
  EmitLW(str_, e1_t, T1);

  // 10. load e1.val into t1
  EmitLW(str_, GetRegOffset(12, T1), T1);

  // 11. load e2 into t2
  EmitLW(str_, e2_t, T2);

  // 12. load e2.val into t2
  EmitLW(str_, GetRegOffset(12, T2), T2);

  // 13. sub
  EmitSUB(str_, T1, T1, T2);

  // 14. store add result into ACC filed
  EmitSW(str_, T1, GetRegOffset(12, ACC));

  // 15. free temp space
  FreeTempSpace(env, 2);
}

void CodeGen::
HandleMul(const Mul* mul, Env* env) {
  // 1. evaluate e1
  HandleExpression(mul->e1, env);

  // 2. allocate temp space for e1 result
  std::string e1_t = GetNextTempSpace(env);

  // 3. store e1 value into e1_t
  EmitSW(str_, ACC, e1_t);

  // 4. evaluate e2
  HandleExpression(mul->e2, env);

  // 5. allocate temp space for e2 result
  std::string e2_t = GetNextTempSpace(env);

  // 6. store e2 value into e2_t
  EmitSW(str_, ACC, e2_t);
  
  // 7. load Int_protObj into ACC
  EmitLA(str_, ACC, "Int_protObj");

  // 8. call Object.copy and Int_init
  EmitJAL(str_, "Object.copy");
  EmitJAL(str_, "Int_init");

  // 9. load e1 into t1
  EmitLW(str_, e1_t, T1);

  // 10. load e1.val into t1
  EmitLW(str_, GetRegOffset(12, T1), T1);

  // 11. load e2 into t2
  EmitLW(str_, e2_t, T2);

  // 12. load e2.val into t2
  EmitLW(str_, GetRegOffset(12, T2), T2);

  // 13. mul
  EmitMUL(str_, T1, T1, T2);

  // 14. store add result into ACC filed
  EmitSW(str_, T1, GetRegOffset(12, ACC));

  // 15. free temp space
  FreeTempSpace(env, 2);
}

void CodeGen::
HandleDivide(const Divide* divide, Env* env) {
  // 1. evaluate e1
  HandleExpression(divide->e1, env);

  // 2. allocate temp space for e1 result
  std::string e1_t = GetNextTempSpace(env);

  // 3. store e1 value into e1_t
  EmitSW(str_, ACC, e1_t);

  // 4. evaluate e2
  HandleExpression(divide->e2, env);

  // 5. allocate temp space for e2 result
  std::string e2_t = GetNextTempSpace(env);

  // 6. store e2 value into e2_t
  EmitSW(str_, ACC, e2_t);
  
  // 7. load Int_protObj into ACC
  EmitLA(str_, ACC, "Int_protObj");

  // 8. call Object.copy and Int_init
  EmitJAL(str_, "Object.copy");
  EmitJAL(str_, "Int_init");

  // 9. load e1 into t1
  EmitLW(str_, e1_t, T1);

  // 10. load e1.val into t1
  EmitLW(str_, GetRegOffset(12, T1), T1);

  // 11. load e2 into t2
  EmitLW(str_, e2_t, T2);

  // 12. load e2.val into t2
  EmitLW(str_, GetRegOffset(12, T2), T2);

  // 13. divide
  EmitDIV(str_, T1, T1, T2);

  // 14. store add result into ACC filed
  EmitSW(str_, T1, GetRegOffset(12, ACC));

  // 15. free temp space
  FreeTempSpace(env, 2);
}

void CodeGen::
HandlePlus(const Plus* plus, Env* env) {
  // 1. evaluate e1
  HandleExpression(plus->e1, env);

  // 2. allocate temp space for e1 result
  std::string e1_t = GetNextTempSpace(env);

  // 3. store e1 value into e1_t
  EmitSW(str_, ACC, e1_t);

  // 4. evaluate e2
  HandleExpression(plus->e2, env);


  // 5. allocate temp space for e2 result
  std::string e2_t = GetNextTempSpace(env);

  // 6. store e2 value into e2_t
  EmitSW(str_, ACC, e2_t);
  
  // 7. load Int_protObj into ACC
  EmitLA(str_, ACC, "Int_protObj");

  // 8. call Object.copy and Int_init
  EmitJAL(str_, "Object.copy");
  EmitJAL(str_, "Int_init");

  // 9. load e1 into t1
  EmitLW(str_, e1_t, T1);

  // 10. load e1.val into t1
  EmitLW(str_, GetRegOffset(12, T1), T1);

  // 11. load e2 into t2
  EmitLW(str_, e2_t, T2);

  // 12. load e2.val into t2
  EmitLW(str_, GetRegOffset(12, T2), T2);

  // 13. add
  EmitADD(str_, T1, T1, T2);

  // 14. store add result into ACC filed
  EmitSW(str_, T1, GetRegOffset(12, ACC));

  // 15. free temp space
  FreeTempSpace(env, 2);
}

void CodeGen::
HandleLet(const Let* let, Env* env) {
  const auto* c_syms = ConstantSymbol::Get();
  string id_name = let->identifier->GetString();
  string type = let->type_decl->GetString();
  // 0. evalute init or set default value
  if (!IsSubClass<Expression, NoExpr>(let->init)) {
    HandleExpression(let->init, env);
  } else {
    if (type == c_syms->Int->GetString()) {
      str_ << LA << ACC << "\t"
           << IntTable.Lookup("0")->GetRef() << endl;
    } else if (type == c_syms->Bool->GetString()) {
      str_ << LA << ACC << "\t" << BOOLCONST_FALSE_REF << endl;
    } else if (type == c_syms->Str->GetString()) {
      str_ << LA << ACC << "\t" << StrTable.Lookup("")->GetRef() << endl;
    } else {
      str_ << LI << ACC << "\t" << 0 << endl;
    }
  }

  // 1. allocate temp space
  std::string temp_space = GetNextTempSpace(env);

  // 2. create a new scope for let
  env->loc->EnterScope();
  env->loc->AddMapping(id_name, temp_space);

  // 3. store init value into temp_space
  EmitSW(str_, ACC, temp_space);

  // 4. evalute body
  HandleExpression(let->body, env);
  
  // 5. free temp space
  FreeTempSpace(env, 1);

  // 6. exit let scope
  env->loc->ExitScope();
}

void CodeGen::
HandleBlock(const Block* block, Env* env) {
  for (const auto& e : *(block->body)) {
    HandleExpression(e, env);
  }
}

std::string CodeGen::
AllocateNewJumpLabel() {
  static int cnt = 0;
  std::ostringstream oss;
  oss << "label" << cnt++;
  return oss.str();
}

std::string CodeGen::
GetNextTempSpace(Env* env) {
  int offset = -env->next_free_temp_space;
  std::string temp_space = GetRegOffset(offset, FP);
  env->next_free_temp_space += 4;
  return temp_space;
}

void CodeGen::
FreeTempSpace(Env* env, int nWords) {
  env->next_free_temp_space -= nWords * 4;
}

void CodeGen::EmitClassDirectParentTab() {
  const auto* c_syms = ConstantSymbol::Get();
  str_ << CLASS_DIRECT_PARENT_TAB << ":" << endl;
  for (int i = 0; i < tag_to_class_name_.size(); ++i) {
    const std::string& class_name = tag_to_class_name_[i];
    auto it = class_info_tab_.find(class_name);

    if (it == class_info_tab_.end()) {
      CoolDumpError(cerr)
        << "class_info_tab cannot find " << class_name << endl;
      exit(-1);
    }

    int parent_tag_no = -1;
    std::string parent_name = "";
    if (class_name != c_syms->Object->GetString()) {
      const ClassInfo* cinfo = it->second;
      parent_name = cinfo->parent_name;
      it = class_info_tab_.find(parent_name);
      if (it == class_info_tab_.end()) {
        CoolDumpError(cerr)
          << "class_info_tab cannot find " << parent_name << endl;
        exit(-1);
      }
      cinfo = it->second;
      parent_tag_no = cinfo->layout->class_tag;
    }
    str_ << WORD << parent_tag_no
         << " #" << class_name << ", tag_no:" << i
         << ", " << parent_name << ", tag_no:" << parent_tag_no << endl;
  }
}

void CodeGen::
HandleIntConst(const IntConst* i, Env* env) {
  str_ << LA << ACC << " "
       << IntTable.Lookup(i->token->GetString())->GetRef()
       << endl;
}

void CodeGen::
HandleStrConst(const StringConst* str, Env* env) {
  str_ << LA << ACC << " "
       << StrTable.Lookup(str->token->GetString())->GetRef()
       << endl;
}

void CodeGen::
HandleBoolConst(const BoolConst* b, Env* env) {
  str_ << LA << ACC << " "
       << (b->val ? BOOLCONST_TRUE_REF : BOOLCONST_FALSE_REF)
       << endl;
}

void CodeGen::
EmitClassProtObjTab() {
  str_ << CLASS_PROT_OBJ_TAB << ":" << endl;
  for (int i = 0; i < tag_to_class_name_.size(); ++i) {
    const std::string& class_name = tag_to_class_name_[i];
    str_ << WORD << class_name + PROTOBJ_SUFFIX << endl;
  }
}

void CodeGen::
EmitClassInitTab() {
  str_ << CLASS_INIT_TAB << ":" << endl;
  for (int i = 0; i < tag_to_class_name_.size(); ++i) {
    const std::string& class_name = tag_to_class_name_[i];
    str_ << WORD << class_name + CLASSINIT_SUFFIX << endl;
  }
}

std::string CodeGen::
GetArgumentOffset(int nth, int len) {
  std::ostringstream oss;
  oss << 4 * (len - 1 - nth + 3) << "($fp)";
  return oss.str();
}
