#include "semant.h"
using namespace std;

SemanticChecker::SemanticChecker(InheritanceTree* tree)
  : inherit_tree_(tree),
    name_scope_(new Scope),
    curr_class_node_(nullptr) {
  serr_ = SemantError::GetInstance(cerr);
  c_syms_ = ConstantSymbol::Get();
}

SemanticChecker::~SemanticChecker() {
  ;
}

void SemanticChecker::TypeChecking() {
  auto* user_classes = inherit_tree_->GetUserClasses();
  auto* semant_error = SemantError::GetInstance(cerr);
  for (auto* curr_class : (*user_classes)) {
    const auto& class_name = curr_class->name->GetString();
    curr_class_node_ = inherit_tree_->LookupNode(class_name);
    if (!curr_class_node_) {
      CoolDumpError(cerr)
        << "cannot find InheritanceTree Node " << class_name << endl;
      exit(1);
    }
    // create a scope for current class
    name_scope_->EnterScope();
    name_scope_->AddMapping("self", "SELF_TYPE");
    for (auto* feature : *(curr_class->features)) {
      if (IsSubClass<Feature, Attr>(feature)) {
        auto* attr = static_cast<Attr*>(feature);
        if (IsSubClass<Expression,NoExpr>(attr->init)) {
          continue;
        }
        const auto& attr_name = attr->name->GetString();
        TypeCheckingHelper(attr->init);
        string attr_decl_type = attr->type_decl->GetString();
        string attr_init_type = attr->init->GetType();

        if (attr_init_type == "_no_type") {
          CoolDumpError(cerr)
            << "NO TYPE" << endl;
          exit(1);
        }
        
        bool res = false;
        
        if (attr_decl_type == "SELF_TYPE" &&
            attr_init_type != "SELF_TYPE") {
          res = false;
        } else {
          attr_decl_type =
            attr_decl_type == "SELF_TYPE" ? class_name : attr_decl_type;
          attr_init_type =
            attr_init_type == "SELF_TYPE" ? class_name : attr_init_type;
          res = inherit_tree_->IsConformed(attr_init_type, attr_decl_type);
        }

        if (!res) {
          semant_error->Dump(curr_class->filename, curr_class)
            << "Inferred type " << attr_init_type << " of initialization of "
            << "attribute " << attr_name
            << " does not conform to declared type "
            << attr_decl_type << "." << endl;
        }

      } else if (IsSubClass<Feature, Method>(feature)) {
        auto* method = static_cast<Method*>(feature);
        // create a new scope for formals
        name_scope_->EnterScope();
        StrSet id_names_set;
        for (auto* formal : *(method->formals)) {
          const auto& id_name = formal->name->GetString();
          const auto& id_type = formal->type_decl->GetString();
          if (id_names_set.count(id_name)) {
            semant_error->Dump(curr_class->filename, curr_class)
              << "Formal parameter " << id_name << " is multiply defined."
              << endl;
          }
          id_names_set.insert(id_name);
          name_scope_->AddMapping(id_name, id_type);
        }
        TypeCheckingHelper(method->expression);
        name_scope_->ExitScope();
        
        string ret_type = method->return_type->GetString();
        string expr_type = method->expression->GetType();

        bool res = false;

        if (ret_type == "SELF_TYPE" && expr_type != "SELF_TYPE") {
          res = false;
        } else {
          ret_type =
            ret_type == "SELF_TYPE" ? class_name : ret_type;
          expr_type =
            expr_type == "SELF_TYPE" ? class_name : expr_type;
          res = inherit_tree_->IsConformed(expr_type, ret_type);
        }

        if (!res) {
          semant_error->Dump(curr_class->filename, curr_class)
            << "Inferred return type " << expr_type
            << " of method " << method->name->GetString()
            << " does not conform to declared return type "
            << ret_type << "." << endl;
        }
      }
    }
    name_scope_->ExitScope();
  }
}

void SemanticChecker::
TypeCheckingHelper(ExpressionP expr) {
  name_scope_->EnterScope();
  if (IsSubClass<Expression, IntConst>(expr)) {
    expr->SetType(c_syms_->Int->GetString());
  } else if (IsSubClass<Expression, BoolConst>(expr)) {
    expr->SetType(c_syms_->Bool->GetString());
  } else if (IsSubClass<Expression, StringConst>(expr)) {
    expr->SetType(c_syms_->Str->GetString());
  } else if (IsSubClass<Expression, Object>(expr)) {
    HandleObject(expr);
  } else if (IsSubClass<Expression, Assign>(expr)) {
    HandleAssign(expr);
  } else if (IsSubClass<Expression, New>(expr)) {
    HandleNew(expr);
  } else if (IsSubClass<Expression, Cond>(expr)) {
    HandleCond(expr);
  } else if (IsSubClass<Expression, Block>(expr)) {
    HandleBlock(expr);
  } else if (IsSubClass<Expression, Typcase>(expr)) {
    HandleCase(expr);
  } else if (IsSubClass<Expression, Loop>(expr)) {
    HandleLoop(expr);
  } else if (IsSubClass<Expression, IsVoid>(expr)) {
    HandleIsVoid(expr);
  } else if (IsSubClass<Expression, Comp>(expr)) {
    HandleComp(expr);
  } else if (IsSubClass<Expression, Lt>(expr)) {
    HandleLt(expr);
  } else if (IsSubClass<Expression, Leq>(expr)) {
    HandleLeq(expr);
  } else if (IsSubClass<Expression, Neg>(expr)) {
    HandleNeg(expr);
  } else if (IsSubClass<Expression, Plus>(expr)) {
    HandlePlus(expr);
  } else if (IsSubClass<Expression, Mul>(expr)) {
    HandleMul(expr);
  } else if (IsSubClass<Expression, Divide>(expr)) {
    HandleDivide(expr);
  } else if (IsSubClass<Expression, Sub>(expr)) {
    HandleSub(expr);
  } else if (IsSubClass<Expression, Eq>(expr)) {
    HandleEq(expr);
  } else if (IsSubClass<Expression, Let>(expr)) {
    HandleLet(expr);
  } else if (IsSubClass<Expression, Dispatch>(expr)) {
    HandleDispatch(expr);
  } else if (IsSubClass<Expression, StaticDispatch>(expr)) {
    HandleStaticDispatch(expr);
  } else {
    CoolDumpError(cerr)
      << "No match expression" << endl;
    exit(-1);
  }
  name_scope_->ExitScope();
}

void SemanticChecker::
HandleStaticDispatch(ExpressionP expr) {
  auto* dis = static_cast<StaticDispatch*>(expr);
  string method_name = dis->name->GetString();
  TypeCheckingHelper(dis->expression);
  string eval_type = dis->expression->GetType();
  string type_name = dis->type_name->GetString();

  if (!inherit_tree_->IsConformed(
        eval_type == "SELF_TYPE" ? curr_class_node_->name : eval_type,
        type_name)) {
    serr_->Dump(curr_class_node_->ast_node_->filename,
                curr_class_node_->ast_node_)
      << "Expression type " << eval_type << " does not "
      << "conform to declared static dispatch type "
      << type_name << "." << endl;
    expr->SetType(c_syms_->Object->GetString());
    return;
  }

  auto* sig = inherit_tree_->LookupMethodTypeInfo(type_name, method_name);

  if (!sig) {
    serr_->Dump(curr_class_node_->ast_node_->filename,
                curr_class_node_->ast_node_)
      << "Static dispatch to undefined method " << method_name << endl;
    expr->SetType(c_syms_->Object->GetString());
    return;
  }

  auto* arg_exprs = dis->actual_exprs;
  string ret_type = (*sig).back();
  string expr_type =
    ret_type == "SELF_TYPE" ? dis->expression->GetType() : ret_type;
  expr->SetType(expr_type);
  if (arg_exprs->size() != sig->size() - 1) {
    serr_->Dump(curr_class_node_->ast_node_->filename,
                curr_class_node_->ast_node_)
      << "Method " << method_name << " called with wrong number of arguments."
      << endl;
    return;
  }

  if (arg_exprs->size() == 0) {
    return;
  }

  auto* m_sig =
    inherit_tree_->LookupMethodInfo(type_name, method_name);
  if (!m_sig) {
    CoolDumpError(cerr)
      << "inherit_tree_->LookupMethodInfo(" << type_name 
      << "," << method_name << ")"
      << endl;
    exit(1);
  }

  for (int i = 0; i < arg_exprs->size(); ++i) {
    auto* arg_exp = (*arg_exprs)[i];
    TypeCheckingHelper(arg_exp);
    string decl_arg_type = (*sig)[i];
    string eval_arg_type = arg_exp->GetType();
    eval_arg_type =
      eval_arg_type == "SELF_TYPE" ? curr_class_node_->name : eval_arg_type;
    if (!inherit_tree_->IsConformed(eval_arg_type, decl_arg_type)) {
      serr_->Dump(curr_class_node_->ast_node_->filename,
                  curr_class_node_->ast_node_)
        << "In call of method " << method_name << ","
        << " type " << arg_exp->GetType()
        << " of parameter " << (*m_sig)[i].first
        << " does not conform to declared"
        << " type " << decl_arg_type
        << "."
        << endl;
    }
  }
}

void SemanticChecker::
HandleDispatch(ExpressionP expr) {
  auto* dis = static_cast<Dispatch*>(expr);
  string method_name = dis->name->GetString();
  TypeCheckingHelper(dis->expression);
  string class_name = dis->expression->GetType();
  class_name =
    class_name == "SELF_TYPE" ? curr_class_node_->name : class_name;
  auto* sig = inherit_tree_->LookupMethodTypeInfo(class_name, method_name);

  if (!sig) {
    serr_->Dump(curr_class_node_->ast_node_->filename,
                curr_class_node_->ast_node_)
      << "Dispatch to undefined method " << method_name << "." << endl;
    expr->SetType(c_syms_->Object->GetString());
    return;
  }

  auto* arg_exprs = dis->actual_exprs;
  string ret_type = (*sig).back();
  string expr_type = 
    ret_type == "SELF_TYPE" ? dis->expression->GetType() : ret_type;
  expr->SetType(expr_type);
  if (arg_exprs->size() != sig->size() - 1) {
    serr_->Dump(curr_class_node_->ast_node_->filename,
                curr_class_node_->ast_node_)
      << "Method " << method_name << " called with wrong number of arguments."
      << endl;
    return;
  }

  if (arg_exprs->size() == 0) {
    return;
  }

  auto* m_sig =
    inherit_tree_->LookupMethodInfo(class_name, method_name);
  if (!m_sig) {
    CoolDumpError(cerr)
      << "inherit_tree_->LookupMethodInfo(" << class_name
      << "," << method_name << ")"
      << endl;
    exit(1);
  }

  for (int i = 0; i < arg_exprs->size(); ++i) {
    auto* arg_exp = (*arg_exprs)[i];
    TypeCheckingHelper(arg_exp);
    string decl_arg_type = (*sig)[i];
    string eval_arg_type = arg_exp->GetType();
    eval_arg_type =
      eval_arg_type == "SELF_TYPE" ? curr_class_node_->name : eval_arg_type;
    if (!inherit_tree_->IsConformed(eval_arg_type, decl_arg_type)) {
      serr_->Dump(curr_class_node_->ast_node_->filename,
                  curr_class_node_->ast_node_)
        << "In call of method " << method_name << ","
        << " type " << arg_exp->GetType()
        << " of parameter " << (*m_sig)[i].first
        << " does not conform to declared"
        << " type " << decl_arg_type
        << "."
        << endl;
    }
  }
}

void SemanticChecker::
HandleLet(ExpressionP expr) {
  auto* let = static_cast<Let*>(expr);
  string id_name = let->identifier->GetString();
  string id_type = let->type_decl->GetString();
  if (!IsSubClass<Expression, NoExpr>(let->init)) {
    TypeCheckingHelper(let->init);
    string id_type_tmp = let->type_decl->GetString();
    string init_type = let->init->GetType();
    bool res = false;
    if (id_type_tmp == "SELF_TYPE" && id_type_tmp != init_type) {
      res = false;
    } else {
      id_type_tmp =
        id_type_tmp == "SELF_TYPE" ? curr_class_node_->name : id_type_tmp;
      init_type = 
        init_type == "SELF_TYPE" ? curr_class_node_->name : init_type;
      res = inherit_tree_->IsConformed(init_type, id_type_tmp);
    }

    if (!res) {
      serr_->Dump(curr_class_node_->ast_node_->filename,
                  curr_class_node_->ast_node_)
        << "Inferred type " << init_type
        << " of initialization of " << id_name
        << " does not conform to identifier's declared type "
        << id_type_tmp << "." << endl;
    }
  }

  name_scope_->EnterScope();
  if (id_name == "self") {
    serr_->Dump(curr_class_node_->ast_node_->filename,
                curr_class_node_->ast_node_)
    << "\'self\' cannot be bound in a \'let\' expression." << endl;
  } else {
    name_scope_->AddMapping(id_name, id_type);
  }
  TypeCheckingHelper(let->body);
  name_scope_->ExitScope();
  expr->SetType(let->body->GetType());
}

void SemanticChecker::
HandleEq(ExpressionP expr) {
  auto* eq = static_cast<Eq*>(expr);
  TypeCheckingHelper(eq->e1);
  TypeCheckingHelper(eq->e2);
  string type1 = eq->e1->GetType();
  string type2 = eq->e2->GetType();
  const auto& bset = inherit_tree_->GetBasicClassStrSet();
  if (bset.count(type1) || bset.count(type2)) {
    if (type1 != type2) {
      serr_->Dump(curr_class_node_->ast_node_->filename,
                curr_class_node_->ast_node_)
          << "Illegal comparison with a basic type." << endl;
    }
  }
  expr->SetType(c_syms_->Bool->GetString());
}

void SemanticChecker::
HandleSub(ExpressionP expr) {
  auto* sub = static_cast<Sub*>(expr);
  TypeCheckingHelper(sub->e1);
  TypeCheckingHelper(sub->e2);
  string type1 = sub->e1->GetType();
  string type2 = sub->e2->GetType();
  if (type1 != "Int" || type2 != "Int") {
    serr_->Dump(curr_class_node_->ast_node_->filename,
                curr_class_node_->ast_node_)
      << "non-Int arguments: " << type1 << " - " << type2 << endl;
  }
  expr->SetType(c_syms_->Int->GetString());
}

void SemanticChecker::
HandleDivide(ExpressionP expr) {
  auto* div = static_cast<Divide*>(expr);
  TypeCheckingHelper(div->e1);
  TypeCheckingHelper(div->e2);
  string type1 = div->e1->GetType();
  string type2 = div->e2->GetType();
  if (type1 != "Int" || type2 != "Int") {
    serr_->Dump(curr_class_node_->ast_node_->filename,
                curr_class_node_->ast_node_)
      << "non-Int arguments: " << type1 << " / " << type2 << endl;
  }
  expr->SetType(c_syms_->Int->GetString());
}

void SemanticChecker::
HandleMul(ExpressionP expr) {
  auto* mul = static_cast<Mul*>(expr);
  TypeCheckingHelper(mul->e1);
  TypeCheckingHelper(mul->e2);
  string type1 = mul->e1->GetType();
  string type2 = mul->e2->GetType();
  if (type1 != "Int" || type2 != "Int") {
    serr_->Dump(curr_class_node_->ast_node_->filename,
                curr_class_node_->ast_node_)
      << "non-Int arguments: " << type1 << " * " << type2 << endl;
  }
  expr->SetType(c_syms_->Int->GetString());
}

void SemanticChecker::
HandlePlus(ExpressionP expr) {
  auto* plus = static_cast<Plus*>(expr);
  TypeCheckingHelper(plus->e1);
  TypeCheckingHelper(plus->e2);
  string type1 = plus->e1->GetType();
  string type2 = plus->e2->GetType();
  if (type1 != "Int" || type2 != "Int") {
    serr_->Dump(curr_class_node_->ast_node_->filename,
                curr_class_node_->ast_node_)
      << "non-Int arguments: " << type1 << " + " << type2 << endl;
  }
  expr->SetType(c_syms_->Int->GetString());
}

void SemanticChecker::
HandleObject(ExpressionP expr) {
  const auto* c_sym = ConstantSymbol::Get();
  auto* obj = static_cast<Object*>(expr);
  const auto& id_name = obj->name->GetString();
  if (id_name == "self") {
    expr->SetType("SELF_TYPE");
    return;
  }
  const auto* ret = IDTypeInfoLookup(id_name);
  if (ret) {
    expr->SetType(*ret);
  } else {
    expr->SetType(c_sym->Object->GetString());
    auto* se = SemantError::GetInstance(cerr);
    se->Dump(curr_class_node_->ast_node_->filename, curr_class_node_->ast_node_)
      << "Undeclared identifier " << id_name << "." << endl;
  }
}

void SemanticChecker::
HandleAssign(ExpressionP expr) {
  const auto* c_sym = ConstantSymbol::Get();
  auto* assign = static_cast<Assign*>(expr);
  const auto& id_name = assign->name->GetString();
  auto* serr = SemantError::GetInstance(cerr);
  if (id_name == "self") {
    serr->Dump(curr_class_node_->ast_node_->filename, curr_class_node_->ast_node_)
      << "Cannot assign to \'self\'." << endl;
  }
  const auto* ret = IDTypeInfoLookup(id_name);
  if (!ret) {
    serr->Dump(curr_class_node_->ast_node_->filename, curr_class_node_->ast_node_)
      << "Assignment to undeclared variable " << id_name << "." << endl;
  }
  TypeCheckingHelper(assign->expression);
  if (ret) {
    auto id_type(*ret);
    auto expr_type(assign->expression->GetType());
    bool res = false;
    if (id_type == "SELF_TYPE" && id_type != expr_type) {
      res = false;
    } else {
      id_type =
        id_type == "SELF_TYPE" ? curr_class_node_->name : id_type;
      expr_type =
        expr_type == "SELF_TYPE" ? curr_class_node_->name : expr_type;
      res = inherit_tree_->IsConformed(expr_type, id_type);
    }

    if (!res) {
      expr->SetType(c_sym->Object->GetString());
      serr->Dump(curr_class_node_->ast_node_->filename,
                 curr_class_node_->ast_node_)
        << "Type " << expr_type << " of assigned expression "
        << "does not conform to declared type " << id_type
        << " of identifier " << id_name << "." << endl;
    }
  }
  expr->SetType(assign->expression->GetType());
}

void SemanticChecker::
HandleNew(ExpressionP expr) {
  auto* new_expr = static_cast<New*>(expr);
  const auto& type_name = new_expr->type_name->GetString();
  const auto* anode = inherit_tree_->LookupNode(type_name);
  auto* serr = SemantError::GetInstance(cerr);
  const auto* c_sym = ConstantSymbol::Get();
  if (type_name != "SELF_TYPE" && !anode) {
    serr->Dump(curr_class_node_->ast_node_->filename,
               curr_class_node_->ast_node_)
      << "\'new\' used with undefined class " << type_name << "." << endl;
    cerr << "Compilation halted due to static semantic errors." << endl;
    exit(1);
  } else {
    expr-> SetType(type_name);
  }
}

void SemanticChecker::
HandleCond(ExpressionP expr) {
  const auto* c_sym = ConstantSymbol::Get();
  auto* serr = SemantError::GetInstance(cerr);
  auto* cond_expr = static_cast<Cond*>(expr);
  TypeCheckingHelper(cond_expr->pred);
  TypeCheckingHelper(cond_expr->then_exp);
  TypeCheckingHelper(cond_expr->else_exp);

  if (cond_expr->pred->GetType() != c_sym->Bool->GetString()) {
    serr->Dump(curr_class_node_->ast_node_->filename,
               curr_class_node_->ast_node_)
      << "Predicate of \'if\' does not have type Bool" << endl;
  }

  string then_type(cond_expr->then_exp->GetType());
  string else_type(cond_expr->else_exp->GetType());

  if (then_type == "SELF_TYPE" && else_type == "SELF_TYPE") {
    expr->SetType("SELF_TYPE");
    return;
  }

  then_type =
    then_type == "SELF_TYPE" ? curr_class_node_->name : then_type;

  else_type =
    else_type == "SELF_TYPE" ? curr_class_node_->name : else_type;

  expr->SetType(inherit_tree_->LCA(then_type, else_type));
}

void SemanticChecker::
HandleBlock(ExpressionP expr) {
  auto* expressions = static_cast<Block*>(expr)->body;
  string tp;
  for (auto* e : (*expressions)) {
    TypeCheckingHelper(e);
    tp = e->GetType();
  }
  expr->SetType(tp);
}

void SemanticChecker::
HandleCase(ExpressionP expr) {
  const auto* c_sym = ConstantSymbol::Get();
  auto* serr = SemantError::GetInstance(cerr);
  Typcase* typ = static_cast<Typcase*>(expr);
  TypeCheckingHelper(typ->expression);
  StrSet branch_type_set;
  bool first = true;
  string lca;
  for (auto* ca : *(typ->cases)) {
    string id_name = ca->name->GetString();
    string branch_type_name = ca->type_decl->GetString();
    if (branch_type_set.count(branch_type_name)) {
      serr->Dump(curr_class_node_->ast_node_->filename,
                 curr_class_node_->ast_node_)
        << "Duplicate branch " << branch_type_name
        << " in case statement." << endl;
    }

    branch_type_set.insert(branch_type_name);
    name_scope_->EnterScope();
    name_scope_->AddMapping(id_name, branch_type_name);
    TypeCheckingHelper(ca->expression);
    name_scope_->ExitScope();

    string sub_expr_type = ca->expression->GetType();
    if (first) {
      lca = sub_expr_type;
      first = false;
    } else {
      string temp_type1 =
        lca == "SELF_TYPE" ? curr_class_node_->name : lca;
      string temp_type2 =
        sub_expr_type == "SELF_TYPE" ? curr_class_node_->name : sub_expr_type;
      lca = inherit_tree_->LCA(temp_type1, temp_type2);
    }
  }

  expr->SetType(lca);
}

void SemanticChecker::
HandleLoop(ExpressionP expr) {
  const auto* c_sym = ConstantSymbol::Get();
  auto* serr = SemantError::GetInstance(cerr);
  auto* loop = static_cast<Loop*>(expr);
  TypeCheckingHelper(loop->pred);
  if (loop->pred->GetType() != c_sym->Bool->GetString()) {
    serr->Dump(curr_class_node_->ast_node_->filename,
               curr_class_node_->ast_node_)
      << "Loop condition does not have type Bool." << endl;
  }
  TypeCheckingHelper(loop->body);
  expr->SetType(c_sym->Object->GetString());
}

void SemanticChecker::
HandleIsVoid(ExpressionP expr) {
  const auto* c_sym = ConstantSymbol::Get();
  TypeCheckingHelper(static_cast<IsVoid*>(expr)->e);
  expr->SetType(c_sym->Bool->GetString());
}

void SemanticChecker::
HandleComp(ExpressionP expr) {
  const auto* c_sym = ConstantSymbol::Get();
  auto* serr = SemantError::GetInstance(cerr);
  auto* comp = static_cast<Comp*>(expr);
  TypeCheckingHelper(comp->e);
  if (comp->e->GetType() != c_sym->Bool->GetString()) {
    serr->Dump(curr_class_node_->ast_node_->filename,
               curr_class_node_->ast_node_)
      << "Argument of \'not\' has type "
      << comp->e->GetType() << " instead of Bool" << endl;
  }
  expr->SetType(c_sym->Bool->GetString());
}

void SemanticChecker::
HandleLt(ExpressionP expr) {
  const auto* c_sym = ConstantSymbol::Get();
  auto* serr = SemantError::GetInstance(cerr);
  auto* lt = static_cast<Lt*>(expr);
  TypeCheckingHelper(lt->e1);
  TypeCheckingHelper(lt->e2);
  string type1 = lt->e1->GetType();
  string type2 = lt->e2->GetType();
  if (type1 != "Int" || type2 != "Int") {
    serr->Dump(curr_class_node_->ast_node_->filename,
               curr_class_node_->ast_node_)
      << "not-int arguments: " << type1 << " < " << type2 << endl;
  }
  expr->SetType(c_sym->Bool->GetString());
}

void SemanticChecker::
HandleLeq(ExpressionP expr) {
  auto* leq = static_cast<Leq*>(expr);
  TypeCheckingHelper(leq->e1);
  TypeCheckingHelper(leq->e2);
  string type1 = leq->e1->GetType();
  string type2 = leq->e2->GetType();
  if (type1 != "Int" || type2 != "Int") {
    serr_->Dump(curr_class_node_->ast_node_->filename,
               curr_class_node_->ast_node_)
      << "not-int arguments: " << type1 << " < " << type2 << endl;
  }
  expr->SetType(c_syms_->Bool->GetString());
}

void SemanticChecker::
HandleNeg(ExpressionP expr) {
  auto* neg = static_cast<Neg*>(expr);
  TypeCheckingHelper(neg->e);
  string type = neg->e->GetType();
  if (type != "Int") {
    serr_->Dump(curr_class_node_->ast_node_->filename,
               curr_class_node_->ast_node_)
      << "Argument of \'~\' has type " << type << " instead of Int" << endl;
  }
  expr->SetType(c_syms_->Int->GetString());
}

const std::string*
SemanticChecker::IDTypeInfoLookup(const std::string& name) {
  const std::string* ret = nullptr;
  if ((ret = name_scope_->Lookup(name))) {
    return ret;
  }
  const auto* sig =
    inherit_tree_->LookupAttrTypeInfo(curr_class_node_->name,
                                      name);
  return sig == nullptr ? nullptr : &(*sig)[0];
}

