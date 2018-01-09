#include "inheritance-tree.h"
#include "symboltab.h"
#include <memory>

using namespace std;

InheritanceTree::InheritanceTree(ProgramP ast_root)
  : user_classes_(ast_root->classes) {
  InitBasicClasses();
  CreateTree();
  CreateMethodAndAttrTypeInfoTab(root_);
  CreateAncestorTable(root_);
  CheckRedefinedInheritedAttr(root_);
  CheckRedefinedInheritedMethod(root_);
}

void
InheritanceTree::CreateTree() {
  // create node for basic classes
  for (auto p : *basic_classes_) {
    const auto& class_name = p->name->GetString();
    nodes_tab_[class_name] = new Node(class_name, p);
    basic_classes_str_set_.insert(class_name);
    classes_str_set_.insert(class_name);
  }

  // create link in basic classes node
  for (auto p : *basic_classes_) {
    const auto& class_name = p->name->GetString();
    const auto& parent_name = p->parent->GetString();
    if (class_name == "Object") {
      nodes_tab_[class_name]->parent = nullptr;
      continue;
    }

    if (!nodes_tab_.count(class_name)) {
      cerr << "create link in basic classes node" << endl;
      cerr << "nodes_tab_ cannot find class_name " << class_name << endl;
      exit(1);
    }
    if (!nodes_tab_.count(parent_name)) {
      cerr << "nodes_tab_ cannot find parent_name " << parent_name << endl;
      exit(1);
    }

    auto parent_node = nodes_tab_[parent_name];
    auto curr_node = nodes_tab_[class_name];

    curr_node->parent = parent_node;
    parent_node->children.push_back(curr_node);
  }

  if (!nodes_tab_.count("Object")) {
    cerr << "Set Root" << endl;
    cerr << "nodes_tab_ cannot find Object" << endl;
    exit(1);
  }

  root_ = nodes_tab_["Object"];
  root_->parent = nullptr;

  // add user defined classes into tree and check whether there is a
  // redefinition
  auto semant_error = SemantError::GetInstance(cerr);
  for (auto p : *user_classes_) {
    const auto& class_name = p->name->GetString();
    if (nodes_tab_.count(class_name) || class_name == "SELF_TYPE") {
      if (basic_classes_str_set_.count(class_name) ||
          class_name == "SELF_TYPE") {
        semant_error->Dump(p->filename, p)
          << "Redefinition of basic class " << class_name << "." << endl;
      } else {
        semant_error->Dump(p->filename, p)
          << "Class " << class_name << " was previously defined." << endl;
      }
      semant_error->Abort();
    }

    nodes_tab_[class_name] = new Node(class_name, p);
    IdTable.AddString(class_name);
    user_classes_str_set_.insert(class_name);
    classes_str_set_.insert(class_name);
    StrTable.AddString(class_name);
  }

  // Check whether Main class is defined
  if (!user_classes_str_set_.count("Main")) {
    semant_error->Dump() << "Class Main is not defined." << endl;
    semant_error->Abort();
  }

  // Check whether there is a class inherits from basic classes or
  // undefined classes
  for (auto p : *user_classes_) {
    const auto& curr_name = p->name->GetString();
    const auto& parent_name = p->parent->GetString();

    // inherits from basic classes except Object or IO
    if ((parent_name != "Object" &&
        parent_name != "IO" &&
        basic_classes_str_set_.count(parent_name)) ||
        parent_name == "SELF_TYPE") {
      semant_error->Dump(p->filename, p)
        << "Class " << curr_name
        << " cannot inherit class " << parent_name << "." << endl;
      semant_error->Abort();
    }

    // inherits from undefined classes
    if (!user_classes_str_set_.count(parent_name) &&
        !basic_classes_str_set_.count(parent_name)) {
      semant_error->Dump(p->filename, p)
        << "Class " << curr_name
        << " inherits from an undefined class "
        << parent_name << "." << endl;
      semant_error->Abort();
    }
   
    // create link
    if (!nodes_tab_.count(parent_name)) {
      cerr << "Create Link in user_classes" << endl;
      cerr << "nodes_tab_ cannot find parent_name " << parent_name << endl;
      exit(1);
    }

    if (!nodes_tab_.count(curr_name)) {
      cerr << "Create Link in user_classes" << endl;
      cerr << "nodes_tab_ cannot find curr_name" << curr_name << endl;
      exit(1);
    }
    
    Node* parent_node = nodes_tab_[parent_name];
    Node* curr_node = nodes_tab_[curr_name];
    curr_node->parent = parent_node;
    parent_node->children.push_back(curr_node);
  }

  LoopDetector loop_detector;  
  if (loop_detector(nodes_tab_)) {
    for (auto s : loop_detector.GetLoopNodes()) {
      if (!nodes_tab_.count(s)) {
        cerr << "Found Loop:" << endl;
        cerr << "nodes_tab_ cannot find " << s << endl;
        exit(1);
      }
      Node* node = nodes_tab_[s];
      semant_error->Dump(node->ast_node_->filename, node->ast_node_)
        << "Class " << s << ", or an ancestor of " << s
        << ", is involved in an inheritance cycle." << endl;
    }
    semant_error->Abort();
  }
}

void
InheritanceTree::InitBasicClasses() {
  auto constants = ConstantSymbol::Get();
  auto arg = constants->arg;
  auto arg2 = constants->arg2;
  auto Bool = constants->Bool;
  auto concat = constants->concat;
  auto cool_abort = constants->cool_abort;
  auto copy = constants->copy;
  auto Int = constants->Int;
  auto in_int = constants->in_int;
  auto in_string = constants->in_string;
  auto IO = constants->IO;
  auto length = constants->length;
  auto Main = constants->Main;
  auto main_meth = constants->main_meth;
  auto No_class = constants->No_class;
  auto No_type = constants->No_type;
  auto Object = constants->Object;
  auto out_int = constants->out_int;
  auto out_string = constants->out_string;
  auto prim_slot = constants->prim_slot;
  auto self = constants->self;
  auto SELF_TYPE = constants->SELF_TYPE;
  auto Str = constants->Str;
  auto str_field = constants->str_field;
  auto substr = constants->substr;
  auto type_name = constants->type_name;
  auto val = constants->val;
  auto basic_fn = constants->basic_fn;

  ClassP Object_class =
    CreateClass(Object,
                No_class,
                basic_fn,
                AppendFeature(
                  AppendFeature(
                    CreateSingleFeatures(
                      CreateMethod(cool_abort, Object,
                                   CreateNilFormals(), CreateNoExpr())),
                    CreateMethod(type_name, Str,
                                 CreateNilFormals(), CreateNoExpr())
                    ),
                  CreateMethod(copy, SELF_TYPE,
                               CreateNilFormals(), CreateNoExpr())
                  )
                );


  ClassP IO_class =
    CreateClass(IO,
                Object,
                basic_fn,
                AppendFeature(
                  AppendFeature(
                    AppendFeature(
                      CreateSingleFeatures(
                        CreateMethod(out_string, SELF_TYPE,
                                     CreateSingleFormals(CreateFormal(arg, Str)),
                                     CreateNoExpr())
                      ),
                      CreateMethod(out_int, SELF_TYPE,
                                   CreateSingleFormals(CreateFormal(arg, Int)),
                                   CreateNoExpr())

                   ),
                   CreateMethod(in_string, Str, CreateNilFormals(),
                                CreateNoExpr())
                  ),
                  CreateMethod(in_int, Int, CreateNilFormals(), CreateNoExpr()) 
                )
               );

  ClassP Int_class =
    CreateClass(Int,
                Object,
                basic_fn,
                CreateSingleFeatures(CreateAttr(val, prim_slot, CreateNoExpr()))
               );

  ClassP Bool_class =
    CreateClass(Bool,
                Object,
                basic_fn,
                CreateSingleFeatures(
                  CreateAttr(val, prim_slot, CreateNoExpr())
                )
               );

  ClassP Str_class =
    CreateClass(
        Str,
        Object,
        basic_fn,
        AppendFeature(
          AppendFeature(
            AppendFeature(
              AppendFeature(
                CreateSingleFeatures(CreateAttr(val, Int, CreateNoExpr())),
                CreateAttr(str_field, prim_slot, CreateNoExpr())),
              CreateMethod(length, Int, CreateNilFormals(), CreateNoExpr())
            ),
           CreateMethod(concat,
                        Str,
                        CreateSingleFormals(CreateFormal(arg, Str)),
                        CreateNoExpr())
          ),
          CreateMethod(
                substr,
                Str,
                AppendFormal(CreateSingleFormals(CreateFormal(arg, Int)),
                             CreateFormal(arg2, Int)),
                CreateNoExpr())
        )
      );

  basic_classes_ = CreateSingleClasses(Object_class);
  basic_classes_ = AppendClass(basic_classes_, IO_class);
  basic_classes_ = AppendClass(basic_classes_, Int_class);
  basic_classes_ = AppendClass(basic_classes_, Bool_class);
  basic_classes_ = AppendClass(basic_classes_, Str_class);

  StrTable.AddString(constants->Object->GetString());
  StrTable.AddString(constants->IO->GetString());
  StrTable.AddString(constants->Int->GetString());
  StrTable.AddString(constants->Bool->GetString());
  StrTable.AddString(constants->Str->GetString());
}

bool LoopDetector::
RecursiveHelper(typename InheritanceTree::Node* node,
                StrSet& loop_nodes) {
  bool ret = false;  
  visited_[node->name] = true;
  instack_[node->name] = true;
  for (auto ch : node->children) {
    if (visited_.count(ch->name) && !visited_[ch->name]) {
      ret |= RecursiveHelper(ch, loop_nodes);
    }
    // found loop
    if (instack_.count(ch->name) && instack_[ch->name]) {
      for (auto it : instack_) {
        if (it.second) {
          loop_nodes.insert(it.first);
        }
      }
      ret |= true;
    }
  }
  instack_[node->name] = false;
  return ret;
}

bool LoopDetector::
operator()(InheritanceTree::NodeTable& nodes) {
  bool ret = false;
  loop_nodes_.clear();
  instack_.clear();
  visited_.clear();
  for (auto p : nodes) {
    if (visited_.count(p.first) && visited_[p.first]) {
      continue;
    }
    ret |= RecursiveHelper(p.second, loop_nodes_);
  }
  return ret;
}

void 
InheritanceTree::CreateMethodAndAttrTypeInfoTab(Node* node) {
  if (node == nullptr) {
    return;
  }
  auto semant_error = SemantError::GetInstance(cerr);
  ClassP curr_class = node->ast_node_;
  for (auto feature : *(curr_class->features)) {
    if (IsSubClass<Feature, Method>(feature)) {
      auto method = (MethodP)feature;
      const auto& method_name = method->name->GetString();
      Signature m_sig;
      TypeSignature sig;
      // add method args type
      for (auto formal : *(method->formals)) {
        if (formal->name->GetString() == "self") {
          semant_error->Dump(curr_class->filename, curr_class)
            << "\'self\' cannot be the name of a formal parameter." << endl;
          continue;
        }
        if (formal->type_decl->GetString() == "SELF_TYPE") {
          semant_error->Dump(curr_class->filename, curr_class)
            << "Formal parameter " << formal->name->GetString()
            << " cannot have type SELF_TYPE." << endl;
        }
        m_sig.push_back(make_pair(formal->name->GetString(),
                                  formal->type_decl->GetString()));
        sig.push_back(formal->type_decl->GetString());

        if (formal->type_decl->GetString() != "SELF_TYPE" &&
            !basic_classes_str_set_.count(formal->type_decl->GetString()) &&
            !user_classes_str_set_.count(formal->type_decl->GetString())) {
            cerr << curr_class->filename->GetString()
            << ":" << curr_class->GetLine() << ": "
            << "Undefined parameter type " << formal->type_decl->GetString()
            << " in method " << method_name << "."
            << endl;
        }
      }
      if (method->return_type->GetString() != "SELF_TYPE" &&
          !basic_classes_str_set_.count(method->return_type->GetString()) &&
          !user_classes_str_set_.count(method->return_type->GetString())) {
          cerr << curr_class->filename->GetString()
          << ":" << curr_class->GetLine() << ": "
          << "Undefined return type " << method->return_type->GetString()
          << " in method " << method_name << "."
          << endl;
      }
      m_sig.push_back(make_pair(method_name, method->return_type->GetString()));
      // add method return type info
      sig.push_back(method->return_type->GetString());
      if (node->method_type_tab.count(method_name)) {
        semant_error->Dump(curr_class->filename, curr_class)
            << "Method " << method_name << " is multiple defined." << endl;
          // only store the first defined method
          continue;
      }
      node->method_sig_tab[method_name].swap(m_sig);
      node->method_type_tab[method_name].swap(sig);
    } else if (IsSubClass<Feature, Attr>(feature)) {
      auto attr = (AttrP)feature;
      const auto& attr_name = attr->name->GetString();
      if (attr_name == "self") {
        semant_error->Dump(curr_class->filename, curr_class)
            << "\'self\' cannot be the name of an attribute." << endl;
          continue;
      }
      if (node->attr_type_tab.count(attr_name)) {
        semant_error->Dump(curr_class->filename, curr_class)
          << "Attribute " << attr_name << " is multiple defined." << endl;
        // only store the first defined attribute
        continue;
      }
      Signature a_sig;
      TypeSignature sig;
      a_sig.push_back(make_pair(attr->name->GetString(),
                                attr->type_decl->GetString()));
      sig.push_back(attr->type_decl->GetString());
      node->attr_sig_tab[attr_name].swap(a_sig);
      node->attr_type_tab[attr_name].swap(sig);
    } else {
      cerr << "CreateMethodAndAttrTypeInfoTab: Unkonw Subclass." << endl;
      exit(1);
    }
  }

  for (auto ch : node->children) {
    CreateMethodAndAttrTypeInfoTab(ch);
  }
}

void InheritanceTree::Node::
DumpMethodTypeTab(ostream& stream) {
  for (const auto it : method_type_tab) {
    stream << " " << it.first << "(";
    const auto& sig = it.second;
    int i = 0;
    for (i = 0; i < sig.size() - 1; ++i) {
      stream << sig[i];
      if (i == sig.size() - 2) {
        continue;
      }
      cout << ",";
    }
    cout << ")" << ":" << sig[i] << endl;
  }
}

void InheritanceTree::Node::
DumpAttrTypeTab(ostream& stream) {
  for (const auto it : attr_type_tab) {
    const auto& sig = it.second;
    cout << "   " << it.first << ":" << sig[0] << endl;
  }
}

void InheritanceTree::
DumpNodeTypeInfo(ostream& stream) {
  for (auto it : nodes_tab_) {
    stream << "Class "<< it.first << " {" << endl;
    it.second->DumpMethodTypeTab(stream);
    it.second->DumpAttrTypeTab(stream);
    stream << "}" << endl;
  }
}

void InheritanceTree::
CreateAncestorTable(Node* node) {
  static vector<string> st;
  vector<string> ancestors(st.rbegin(), st.rend());
  ancestor_tab_[node->name].swap(ancestors);
  st.push_back(node->name);
  for (auto ch : node->children) {
    CreateAncestorTable(ch);
  }
  st.pop_back();
}

// check whether current class defined an attribute already defined in its
// super class
void InheritanceTree::
CheckRedefinedInheritedAttr(Node* node) {
  if (node == nullptr) {
    return;
  }
  if (!ancestor_tab_.count(node->name)) {
    CoolDumpError(cerr)
      << "ancestor_tab_ cannot find " << node->name << endl;
    exit(1);
  }
  // get current class's ancestors
  const auto& ancestors = ancestor_tab_[node->name];
  const auto& attr_type_tab = node->attr_type_tab;
  StrSet redefined_attrs;
  auto semant_error = SemantError::GetInstance(cerr);
  // for each attr defined in current class
  for (const auto& it : attr_type_tab) {
    const auto& attr_name = it.first;
    // check current class's super classes
    for (const auto& ancestor_name : ancestors) {
      if (!nodes_tab_.count(ancestor_name)) {
        CoolDumpError(cerr) << "nodes_tab_ cannot find "
                            << ancestor_name << endl;
        exit(1);
      }
      Node* an = nodes_tab_[ancestor_name];

      if (!an->attr_type_tab.count(attr_name)) {
        continue;
      }

      redefined_attrs.insert(attr_name);
      semant_error->Dump(node->ast_node_->filename, node->ast_node_)
        << "Attribute " << attr_name
        << " is an attribute of an inherited class."
        << endl;
      break;
    }
  }

  // if current class has a redefined attribute, erase it
  for (const auto& it : redefined_attrs) {
    node->attr_type_tab.erase(it);
  }

  // recursively check
  for (auto ch : node->children) {
    CheckRedefinedInheritedAttr(ch);
  }
}

void InheritanceTree::
CheckRedefinedInheritedMethod(Node* node) {
  if (node == nullptr) {
    return;
  }

  if (!ancestor_tab_.count(node->name)) {
    CoolDumpError(cerr)
      << "ancestor_tab_ cannot find " << node->name << endl;
    exit(1);
  }

  // get current class's ancestors
  const auto& ancestors = ancestor_tab_[node->name];
  const auto& method_type_tab = node->method_type_tab;
  StrSet redefined_methods;
  auto semant_error = SemantError::GetInstance(cerr);
  // for each method in current class
  for (const auto& it : method_type_tab) {
    const auto& method_name = it.first;
    // check it in the super class
    for (const auto& ancestor_name : ancestors) {
      if (!nodes_tab_.count(ancestor_name)) {
        CoolDumpError(cerr) << "nodes_tab_ cannot find "
                            << ancestor_name << endl;
        exit(1);
      }
      Node* an = nodes_tab_[ancestor_name];

      if (!an->method_type_tab.count(method_name)) {
        continue;
      }

      // signature of method in current class
      const auto& curr_sig = it.second;
      // signature of method in super class
      const auto& sup_sig = an->method_type_tab[method_name];

      bool redefined_error = false;
      
      // first check return type
      if (curr_sig.back() != sup_sig.back()) {
        redefined_error = true;
        semant_error->Dump(node->ast_node_->filename, node->ast_node_)
          << "In redefined method " << it.first
          << ", return type " << curr_sig.back()
          << " is different from original return type "
          << sup_sig.back() << endl;
      } else if (curr_sig.size() != sup_sig.size()) {
        redefined_error = true;
        semant_error->Dump(node->ast_node_->filename, node->ast_node_)
          << "Incompatible number of formal parameters in redefined method "
          << it.first << "." << endl;
      } else {
        for (int i = 0; i < curr_sig.size(); ++i) {
          if (curr_sig[i] == sup_sig[i]) continue;
          redefined_error = true;
          semant_error->Dump(node->ast_node_->filename, node->ast_node_)
            << "In redefined method " << it.first
            << ", parameter type " << curr_sig[i]
            << " is different from original type "
            << sup_sig[i] << endl;
          break;
        }
      }

      if (redefined_error) {
        redefined_methods.insert(it.first);
      }
    }
  }

  for (const auto& name : redefined_methods) {
    node->method_type_tab.erase(name);
  }

  for (auto& ch : node->children) {
    CheckRedefinedInheritedMethod(ch);
  }
}

void InheritanceTree::DumpAncestorTable(std::ostream& stream) {
  stream << "--------- Ancestor List ---------" << endl;
  for (const auto& it : ancestor_tab_) {
    stream << "Class " << it.first << ": " << it.first;
    for (const auto& name : it.second) {
      stream << "->" << name;
    }
    stream << endl;
  }
  stream << endl;
}

const TypeSignature* InheritanceTree::
LookupAttrTypeInfo(const std::string& class_name,
                   const std::string& attr_name) {
  if (!nodes_tab_.count(class_name)) {
    return nullptr;
  }

  TypeSignature* ret = nullptr;

  auto* anode = nodes_tab_[class_name];

  if (anode->attr_type_tab.count(attr_name)) {
    ret = &(anode->attr_type_tab[attr_name]);
  }

  // search upward inheritance tree
  if (!ret) {
    if (!ancestor_tab_.count(class_name)) {
      return nullptr;
    }
    const auto& ancestors = ancestor_tab_[class_name];
    for (const auto& name : ancestors) {
      if (!nodes_tab_.count(name)) {
        CoolDumpError(cerr)
          << "nodes_tab_ cannot find ancestor " << name << endl;
        exit(1);
      }
      auto* an = nodes_tab_[name];
      if (!an->attr_type_tab.count(attr_name)) {
        continue;
      }
      ret = &(an->attr_type_tab[attr_name]);
    }
  }
  return ret;
}

const Signature* InheritanceTree::
LookupMethodInfo(const std::string& class_name,
                 const std::string& method_name) {
  if (!nodes_tab_.count(class_name)) {
    return nullptr;
  }

  Signature* ret = nullptr;

  auto* anode = nodes_tab_[class_name];

  if (anode->method_sig_tab.count(method_name)) {
    ret = &(anode->method_sig_tab[method_name]);
  }

  if (!ret) {
    if (!ancestor_tab_.count(class_name)) {
      return nullptr;
    }

    const auto& ancestors = ancestor_tab_[class_name];
    for (const auto& name : ancestors) {
      if (!nodes_tab_.count(name)) {
        CoolDumpError(cerr)
          << "nodes_tab_ cannot find ancestor " << name << endl;
        exit(1);
      }
      auto* an = nodes_tab_[name];
      if (!an->method_sig_tab.count(method_name)) {
        continue;
      }
      ret = &(an->method_sig_tab[method_name]);
    }
  }
  return ret;
}

const TypeSignature* InheritanceTree::
LookupMethodTypeInfo(const std::string& class_name,
                     const std::string& method_name) {
  if (!nodes_tab_.count(class_name)) {
    return nullptr;
  }

  TypeSignature* ret = nullptr;

  auto* anode = nodes_tab_[class_name];

  if (anode->method_type_tab.count(method_name)) {
    ret = &(anode->method_type_tab[method_name]);
  }

  if (!ret) {
    if (!ancestor_tab_.count(class_name)) {
      return nullptr;
    }
    const auto& ancestors = ancestor_tab_[class_name];
    for (const auto& name : ancestors) {
      if (!nodes_tab_.count(name)) {
        CoolDumpError(cerr)
          << "nodes_tab_ cannot find ancestor " << name << endl;
        exit(1);
      }
      auto* an = nodes_tab_[name];
      if (!an->method_type_tab.count(method_name)) {
        continue;
      }
      ret = &(an->method_type_tab[method_name]);
    }
  }

  return ret;
}

InheritanceTree::Node* InheritanceTree::
LookupNode(const std::string& name) {
  if (!nodes_tab_.count(name)) {
    return nullptr;
  } else {
    return nodes_tab_[name];
  }
}

bool InheritanceTree::
IsConformed(const std::string& type1, const std::string& type2) {
  if (type1 == type2) {
    return true;
  }

  bool ret = false;
  if (!ancestor_tab_.count(type1)) {
    CoolDumpError(cerr)
      << "ancestor_tab_ cannot find type " << type1 << endl;
    exit(1);
  }
  const auto& ancestors = ancestor_tab_[type1];
  for (const auto& name : ancestors) {
    if (name != type2) {
      continue;
    }
    ret = true;
    break;
  }
  return ret;
}

bool InheritanceTree::
IsChildOf(const Node* node1, const Node* node2) {
  if (node1 == node2) {
    return true;
  }
  bool ret = false;
  for (const auto* ch : node2->children) {
    ret |= IsChildOf(node1, ch);
    if (ret) {
      break;
    }
  }
  return ret;
}

std::string
InheritanceTree::LCA(const std::string& type1, const std::string& type2) {
  if (!nodes_tab_.count(type1) || !nodes_tab_.count(type2)) {
    CoolDumpError(cerr)
      << "nodes_tab_ cannot find " << type1 << " or " << type2 << endl;
    exit(1);
  }

  const auto* node1 = nodes_tab_[type1];
  const auto* node2 = nodes_tab_[type2];

  if (IsChildOf(node2, node1)) {
    return type1;
  }

  while (node2 != nullptr) {
    if (IsChildOf(node1, node2)) {
      return node2->name;
    }
    node2 = node2->parent;
  }

  return "Object";
}
