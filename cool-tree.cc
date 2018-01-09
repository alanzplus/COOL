#include "cool-tree.h"
#include "helper.h"
using namespace std;
using namespace cool_helper;

void Program::
Dump(ostream& stream, int n) {
  stream << PadSpace(n) << "_program\n";
  for (const auto& p : *classes) {
    p->Dump(stream, n+2);
  }
}

void Class::
Dump(ostream& stream, int n) {
  stream << PadSpace(n) << "class_\n";
  name->Dump(stream, n + 2);
  parent->Dump(stream, n + 2);
  for (auto& p : *features) {
    p->Dump(stream, n + 2);
  }
  filename->Dump(stream, n + 2);
}

void Method::
Dump(ostream& stream, int n) {
  stream << PadSpace(n) << "method\n";

  name->Dump(stream, n + 2);

  for (auto& p : *formals) {
    p->Dump(stream, n + 2);
  }
  return_type->Dump(stream, n + 2);
  expression->Dump(stream, n + 2);
}

void Attr::
Dump(ostream& stream, int n) {
  stream << PadSpace(n) << "attr\n";
  name->Dump(stream, n + 2);
  type_decl->Dump(stream, n + 2);
}

void Formal::
Dump(ostream& stream, int n) {
  stream << PadSpace(n) << "formal\n";
  name->Dump(stream, n + 2);
  type_decl->Dump(stream, n + 2);
}

void Case::
Dump(ostream& stream, int n) {
  stream << PadSpace(n) << "branch\n";
  name->Dump(stream, n + 2);
  type_decl->Dump(stream, n + 2);
}

void Assign::
Dump(ostream& stream, int n) {
  stream << PadSpace(n) << "assign\n";
  name->Dump(stream, n + 2);
  expression->Dump(stream, n + 2);
}

void StaticDispatch::
Dump(ostream& stream, int n) {
  stream << PadSpace(n) << "static_dispatch\n";
  expression->Dump(stream, n + 2);
  type_name->Dump(stream, n + 2);
  name->Dump(stream, n + 2);
  for (auto& p : *actual_exprs) {
    p->Dump(stream, n + 2);
  }
}

void Dispatch::
Dump(ostream& stream, int n) {
  stream << PadSpace(n) << "dispatch\n";
  expression->Dump(stream, n + 2);
  name->Dump(stream, n + 2);
  for (auto& p : *actual_exprs) {
    p->Dump(stream, n + 2);
  }
}

void Cond::
Dump(ostream& stream, int n) {
  stream << PadSpace(n) << "cond\n";
  pred->Dump(stream, n + 2);
  then_exp->Dump(stream, n + 2);
  else_exp->Dump(stream, n + 2);
}

void Loop::
Dump(ostream& stream, int n) {
  stream << PadSpace(n) << "loop\n";
  pred->Dump(stream, n + 2);
  body->Dump(stream, n + 2);
}

void Typcase::
Dump(ostream& stream, int n) {
  stream << PadSpace(n) << "typcase\n";
  expression->Dump(stream, n + 2);
  for (auto& p : *cases) {
    p->Dump(stream, n + 2);
  }
}

void Block::
Dump(ostream& stream, int n) {
  stream << PadSpace(n) << "block\n";
  for (auto& p : *body) {
    p->Dump(stream, n + 2);
  }
}

void Let::
Dump(ostream& stream, int n) {
  stream << PadSpace(n) << "let\n";
  identifier->Dump(stream, n + 2);
  type_decl->Dump(stream, n + 2);
  init->Dump(stream, n + 2);
  body->Dump(stream, n + 2);
}

void Plus::
Dump(ostream& stream, int n) {
  stream << PadSpace(n) << "plus\n";
  e1->Dump(stream, n + 2);
  e2->Dump(stream, n + 2);
}

void Sub::
Dump(ostream& stream, int n) {
  stream << PadSpace(n) << "sub\n";
  e1->Dump(stream, n + 2);
  e2->Dump(stream, n + 2);
}

void Mul::
Dump(ostream& stream, int n) {
  stream << PadSpace(n) << "mul\n";
  e1->Dump(stream, n + 2);
  e2->Dump(stream, n + 2);
}

void Divide::
Dump(ostream& stream, int n) {
  stream << PadSpace(n) << "divide\n";
  e1->Dump(stream, n + 2);
  e2->Dump(stream, n + 2);
}

void Neg::
Dump(ostream& stream, int n) {
  stream << PadSpace(n) << "neg\n";
  e->Dump(stream, n + 2);
}

void Lt::
Dump(ostream& stream, int n) {
  stream << PadSpace(n) << "lt\n";
  e1->Dump(stream, n + 2);
  e2->Dump(stream, n + 2);
}

void Eq::
Dump(ostream& stream, int n) {
  stream << PadSpace(n) << "eq\n";
  e1->Dump(stream, n + 2);
  e2->Dump(stream, n + 2);
}

void Leq::
Dump(ostream& stream, int n) {
  stream << PadSpace(n) << "leq\n";
  e1->Dump(stream, n + 2);
  e2->Dump(stream, n + 2);
}

void Comp::
Dump(ostream& stream, int n) {
  stream << PadSpace(n) << "comp\n";
  e->Dump(stream, n + 2);
}

void IntConst::
Dump(ostream& stream, int n) {
  stream << PadSpace(n) << "int_const\n";
  token->Dump(stream, n + 2);
}

void BoolConst::
Dump(ostream& stream, int n) {
  stream << PadSpace(n) << "bool_const\n";
  stream << PadSpace(n + 2) << (val ? "true" : "false") << endl;
}

void StringConst::
Dump(ostream& stream, int n) {
  stream << PadSpace(n) << "string_const\n";
  token->Dump(stream, n + 2);
}

void New::
Dump(ostream& stream, int n) {
  stream << PadSpace(n) << "new_\n";
  type_name->Dump(stream, n + 2);
}

void IsVoid::
Dump(ostream& stream, int n) {
  stream << PadSpace(n) << "isvoid\n";
  e->Dump(stream, n + 2);
}

void NoExpr::
Dump(ostream& stream, int n) {
  stream << PadSpace(n) << "no_expr\n";
}

void Object::
Dump(ostream& stream, int n) {
  stream << PadSpace(n) << "object\n";
  name->Dump(stream, n + 2);
}

ClassesP CreateNilClasses() {
  return new Classes();
}

ClassesP CreateSingleClasses(ClassP c) {
  return AppendClass(new Classes(), c);
}

ClassesP AppendClass(ClassesP cs, ClassP c) {
  if (!cs) {
    if (g_log_cerr) cerr << "AppendClass:NULL" << endl;
    return NULL;
  }
  cs->push_back(c);
  return cs;
}

FeaturesP CreateNilFeatures() {
  return new Features();
}

FeaturesP CreateSingleFeatures(FeatureP f) {
  return AppendFeature(new Features(), f);
}

FeaturesP AppendFeature(FeaturesP fs, FeatureP f) {
  if (!fs) {
    if (g_log_cerr) cerr << "AppendFeature:NULL" << endl;
    return NULL;
  }
  fs->push_back(f);
  return fs;
}

FormalsP CreateNilFormals() {
  return new Formals();
}

FormalsP CreateSingleFormals(FormalP f) {
  return AppendFormal(new Formals(), f);
}

FormalsP AppendFormal(FormalsP fs, FormalP f) {
  if (!fs) {
    if (g_log_cerr) cerr << "AppendFormal:NULL" << endl;
    return NULL;
  }
  fs->push_back(f);
  return fs;
}

ExpressionsP CreateNilExpressions() {
  return new Expressions();
}

ExpressionsP CreateSingleExpressions(ExpressionP e) {
  return AppendExpression(new Expressions(), e);
}

ExpressionsP AppendExpression(ExpressionsP es, ExpressionP e) {
  if (!es) {
    if (g_log_cerr) cerr << "AppendExpression:NULL" << endl;
    return NULL;
  }
  es->push_back(e);
  return es;
}

CasesP CreateNilCases() {
  return new Cases();
}

CasesP CreateSingleCases(CaseP c) {
  return AppendCase(new Cases(), c);
}

CasesP AppendCase(CasesP cs, CaseP c) {
  if (!cs) {
    if (g_log_cerr) cerr << "AppendCase:NULL" << endl;
    return NULL;
  }
  cs->push_back(c);
  return cs;
}

ProgramP CreateProgram(ClassesP cs, int lineno) {
  return new Program(cs, lineno);
}

ClassP CreateClass(SymbolP name,
                   SymbolP parent,
                   SymbolP filename,
                   FeaturesP features,
                   int lineno) {
  return new Class(name, parent, filename, features, lineno);
}

FeatureP CreateMethod(SymbolP name,
                      SymbolP return_type,
                      FormalsP formals,
                      ExpressionP expression,
                      int lineno) {
  return new Method(name, return_type, formals, expression, lineno);
}

FeatureP CreateAttr(SymbolP name,
                    SymbolP type_decl,
                    ExpressionP init,
                    int lineno) {
  return new Attr(name, type_decl, init, lineno);
}

FormalP CreateFormal(SymbolP name,
                     SymbolP type_decl,
                     int lineno) {
  return new Formal(name, type_decl, lineno);
}

CaseP CreateCase(SymbolP name,
                 SymbolP type_decl,
                 ExpressionP expression,
                 int lineno) {
  return new Case(name, type_decl, expression, lineno);
}

ExpressionP CreateAssign(SymbolP name,
                         ExpressionP expression,
                         int lineno) {
  return new Assign(name, expression, lineno);
}

ExpressionP CreateStaticDispatch(SymbolP name,
                                 SymbolP type_name,
                                 ExpressionP expression,
                                 ExpressionsP actual_exprs,
                                 int lineno) {
  return new StaticDispatch(name, type_name, expression, actual_exprs, lineno);
}

ExpressionP CreateDispatch(SymbolP name,
                           ExpressionP expression,
                           ExpressionsP actual_exprs,
                           int lineno) {
  return new Dispatch(name, expression, actual_exprs, lineno);
}

ExpressionP CreateCond(ExpressionP pred,
                       ExpressionP then_exp,
                       ExpressionP else_exp,
                       int lineno) {
  return new Cond(pred, then_exp, else_exp, lineno);
}

ExpressionP CreateLoop(ExpressionP pred,
                       ExpressionP body,
                       int lineno) {
  return new Loop(pred, body);
}

ExpressionP CreateTypecase(ExpressionP expression,
                           CasesP cases,
                           int lineno) {
  return new Typcase(expression, cases);
}

ExpressionP CreateBlock(ExpressionsP body, int lineno) {
  return new Block(body, lineno);
}

ExpressionP CreateLet(SymbolP identifier,
                       SymbolP type_decl,
                       ExpressionP init,
                       ExpressionP body,
                       int lineno) {
  return new Let(identifier, type_decl, init, body, lineno);
}

ExpressionP CreatePlus(ExpressionP e1,
                       ExpressionP e2,
                       int lineno) {
  return new Plus(e1, e2, lineno);
}

ExpressionP CreateSub(ExpressionP e1,
                      ExpressionP e2,
                      int lineno) {
  return new Sub(e1, e2, lineno);
}

ExpressionP CreateMul(ExpressionP e1,
                      ExpressionP e2,
                      int lineno) {
  return new Mul(e1, e2, lineno);
}

ExpressionP CreateDivide(ExpressionP e1,
                         ExpressionP e2,
                         int lineno) {
  return new Divide(e1, e2);
}

ExpressionP CreateNeg(ExpressionP e, int lineno) {
  return new Neg(e, lineno);
}

ExpressionP CreateLt(ExpressionP e1,
                     ExpressionP e2,
                     int lineno) {
  return new Lt(e1, e2, lineno);
}

ExpressionP CreateEq(ExpressionP e1,
                     ExpressionP e2,
                     int lineno) {
  return new Eq(e1, e2);
}

ExpressionP CreateLeq(ExpressionP e1,
                      ExpressionP e2,
                      int lineno) {
  return new Leq(e1, e2);
}

ExpressionP CreateComp(ExpressionP e, int lineno) {
  return new Comp(e, lineno);
}

ExpressionP CreateIntConst(SymbolP token, int lineno) {
  return new IntConst(token, lineno);
}

ExpressionP CreateBoolConst(bool val, int lineno) {
  return new BoolConst(val, lineno);
}

ExpressionP CreateStringConst(SymbolP token, int lineno) {
  return new StringConst(token, lineno);
}

ExpressionP CreateNew(SymbolP type_name, int lineno) {
  return new New(type_name, lineno);
}

ExpressionP CreateIsVoid(ExpressionP e, int lineno) {
  return new IsVoid(e, lineno);
}

ExpressionP CreateNoExpr(int lineno) {
  return new NoExpr(lineno);
}

ExpressionP CreateObject(SymbolP name, int lineno) {
  return new Object(name, lineno);
}

void
Program::DumpWithTypes(ostream& stream, int n) {
  DumpLine(stream, n, line_number_);
  stream << PadSpace(n) << "_program" << endl;
  for (auto& p : *classes) {
    p->DumpWithTypes(stream, n + 2);
  }
}

void
Class::
DumpWithTypes(ostream& stream, int n) {
  DumpLine(stream, n, line_number_);
  stream << PadSpace(n) << "_class" << endl;
  name->Dump(stream, n + 2);
  parent->Dump(stream, n + 2);
  stream << PadSpace(n + 2) << "\""
         << ToEscapedString(filename->GetString())
         << "\"\n" << PadSpace(n + 2) << "(\n";
  for (auto& feature : *features) {
    feature->DumpWithTypes(stream, n + 2);
  }
  stream << PadSpace(n + 2) << ")\n";
}

void Method::
DumpWithTypes(ostream& stream, int n) {
  DumpLine(stream, n, line_number_);
  stream << PadSpace(n) << "_method" << endl;
  name->Dump(stream, n + 2);
  for (auto& formal : *formals) {
    formal->DumpWithTypes(stream, n + 2);
  }
  return_type->Dump(stream, n + 2);
  expression->DumpWithTypes(stream, n + 2);
}

void Attr::
DumpWithTypes(ostream& stream, int n) {
  DumpLine(stream, n, line_number_);
  stream << PadSpace(n) << "_attr" << endl;
  name->Dump(stream, n + 2);
  type_decl->Dump(stream, n + 2);
  init->DumpWithTypes(stream, n + 2);
}

void Formal::
DumpWithTypes(ostream& stream, int n) {
  DumpLine(stream, n, line_number_);
  stream << PadSpace(n) << "_formal" << endl;
  name->Dump(stream, n + 2);
  type_decl->Dump(stream, n + 2);
}

void Case::
DumpWithTypes(ostream& stream, int n) {
  DumpLine(stream, n, line_number_);
  stream << PadSpace(n) << "_branch" << endl;
  name->Dump(stream, n + 2);
  type_decl->Dump(stream, n + 2);
  expression->DumpWithTypes(stream, n + 2);
}

void Assign::
DumpWithTypes(ostream& stream, int n) {
  DumpLine(stream, n, line_number_);
  stream << PadSpace(n) << "_assign" << endl;
  name->Dump(stream, n + 2);
  expression->DumpWithTypes(stream, n + 2);
  DumpType(stream, n, type_);
}

void StaticDispatch::
DumpWithTypes(ostream& stream, int n) {
  DumpLine(stream, n, line_number_);
  stream << PadSpace(n) << "_static_dispatch" << endl;
  expression->DumpWithTypes(stream, n + 2);
  type_name->Dump(stream, n + 2);
  name->Dump(stream, n + 2);
  stream << PadSpace(n + 2) << "(" << endl;
  for (auto& p : *actual_exprs) {
    p->DumpWithTypes(stream, n + 2);
  }
  stream << PadSpace(n + 2) << ")\n";
  DumpType(stream, n, type_);
}

void Dispatch::
DumpWithTypes(ostream& stream, int n) {
  DumpLine(stream, n, line_number_);
  stream << PadSpace(n) << "_dispatch\n";
  expression->DumpWithTypes(stream, n + 2);
  name->Dump(stream, n + 2);
  stream << PadSpace(n + 2) << "(\n";
  for (auto& p : *actual_exprs) {
    p->DumpWithTypes(stream, n + 2);
  }
  stream << PadSpace(n + 2) << ")" << endl;
  DumpType(stream, n, type_);
}

void Cond::
DumpWithTypes(ostream& stream, int n) {
  DumpLine(stream, n, line_number_);
  stream << PadSpace(n) << "_cond" << endl;
  pred->DumpWithTypes(stream, n + 2);
  then_exp->DumpWithTypes(stream, n + 2);
  else_exp->DumpWithTypes(stream, n + 2);
  DumpType(stream, n, type_);
}

void Loop::
DumpWithTypes(ostream& stream, int n) {
  DumpLine(stream, n, line_number_);
  stream << PadSpace(n) << "_loop" << endl;
  pred->DumpWithTypes(stream, n + 2);
  body->DumpWithTypes(stream, n + 2);
  DumpType(stream, n, type_);
}

void Typcase::
DumpWithTypes(ostream& stream, int n) {
  DumpLine(stream, n, line_number_);
  stream << PadSpace(n) << "_typcase" << endl;
  expression->DumpWithTypes(stream, n + 2);
  for (auto& p : *cases) {
    p->DumpWithTypes(stream, n + 2);
  }
  DumpType(stream, n, type_);
}

void Block::
DumpWithTypes(ostream& stream, int n) {
  DumpLine(stream, n, line_number_);
  stream << PadSpace(n) << "_block" << endl;
  for (auto& p : *body) {
    p->DumpWithTypes(stream, n + 2);
  }
  DumpType(stream, n, type_);
}

void Let::
DumpWithTypes(ostream& stream, int n) {
  DumpLine(stream, n, line_number_);
  stream << PadSpace(n) << "_let" << endl;
  identifier->Dump(stream, n + 2);
  type_decl->Dump(stream, n + 2);
  init->DumpWithTypes(stream, n + 2);
  body->DumpWithTypes(stream, n + 2);
  DumpType(stream, n, type_);
}

void Plus::
DumpWithTypes(ostream& stream, int n) {
  DumpLine(stream, n, line_number_);
  stream << PadSpace(n) << "_plus" << endl;
  e1->DumpWithTypes(stream, n + 2);
  e2->DumpWithTypes(stream, n + 2);
  DumpType(stream, n, type_);
}

void Sub::
DumpWithTypes(ostream& stream, int n) {
  DumpLine(stream, n, line_number_);
  stream << PadSpace(n) << "_sub" << endl;
  e1->DumpWithTypes(stream, n + 2);
  e2->DumpWithTypes(stream, n + 2);
  DumpType(stream, n, type_);
}

void Mul::
DumpWithTypes(ostream& stream, int n) {
  DumpLine(stream, n, line_number_);
  stream << PadSpace(n) << "_mul" << endl;
  e1->DumpWithTypes(stream, n + 2);
  e2->DumpWithTypes(stream, n + 2);
  DumpType(stream, n, type_);
}

void Divide::
DumpWithTypes(ostream& stream, int n) {
  DumpLine(stream, n, line_number_);
  stream << PadSpace(n) << "_divide" << endl;
  e1->DumpWithTypes(stream, n + 2);
  e2->DumpWithTypes(stream, n + 2);
  DumpType(stream, n, type_);
}

void Neg::
DumpWithTypes(ostream& stream, int n) {
  DumpLine(stream, n, line_number_);
  stream << PadSpace(n) << "_neg" << endl;
  e->DumpWithTypes(stream, n + 2);
  DumpType(stream, n, type_);
}

void Lt::
DumpWithTypes(ostream& stream, int n) {
  DumpLine(stream, n, line_number_);
  stream << PadSpace(n) << "_lt" << endl;
  e1->DumpWithTypes(stream, n + 2);
  e2->DumpWithTypes(stream, n + 2);
  DumpType(stream, n, type_);
}

void Eq::
DumpWithTypes(ostream& stream, int n) {
  DumpLine(stream, n, line_number_);
  stream << PadSpace(n) << "_eq" << endl;
  e1->DumpWithTypes(stream, n + 2);
  e2->DumpWithTypes(stream, n + 2);
  DumpType(stream, n, type_);
}

void Leq::
DumpWithTypes(ostream& stream, int n) {
  DumpLine(stream, n, line_number_);
  stream << PadSpace(n) << "_leq" << endl;
  e1->DumpWithTypes(stream, n + 2);
  e2->DumpWithTypes(stream, n + 2);
  DumpType(stream, n, type_);
}

void Comp::
DumpWithTypes(ostream& stream, int n) {
  DumpLine(stream, n, line_number_);
  stream << PadSpace(n) << "_comp" << endl;
  e->DumpWithTypes(stream, n + 2);
  DumpType(stream, n, type_);
}

void IntConst::
DumpWithTypes(ostream& stream, int n) {
  DumpLine(stream, n, line_number_);
  stream << PadSpace(n) << "_int" << endl;
  token->Dump(stream, n + 2);
  DumpType(stream, n, type_);
}

void BoolConst::
DumpWithTypes(ostream& stream, int n) {
  DumpLine(stream, n, line_number_);
  stream << PadSpace(n) << "_bool" << endl;
  stream << PadSpace(n+2) << (val ? "1" : "0") << endl;
  DumpType(stream, n, type_);
}

void StringConst::
DumpWithTypes(ostream& stream, int n) {
  DumpLine(stream, n, line_number_);
  stream << PadSpace(n) << "_string" << endl;
  stream << PadSpace(n + 2) << "\""
         << ToEscapedString(token->GetString()) << "\"" << endl;
  DumpType(stream, n, type_);
}

void New::
DumpWithTypes(ostream& stream, int n) {
  DumpLine(stream, n, line_number_);
  stream << PadSpace(n) << "_new" << endl;
  type_name->Dump(stream, n + 2);
  DumpType(stream, n, type_);
}

void IsVoid::
DumpWithTypes(ostream& stream, int n) {
  DumpLine(stream, n, line_number_);
  stream << PadSpace(n) << "_isvoid" << endl;
  e->DumpWithTypes(stream, n + 2);
  DumpType(stream, n, type_);
}

void NoExpr::
DumpWithTypes(ostream& stream, int n) {
  DumpLine(stream, n, line_number_);
  stream << PadSpace(n) << "_no_expr" << endl;
  DumpType(stream, n, type_);
}

void Object::
DumpWithTypes(ostream& stream, int n) {
  DumpLine(stream, n, line_number_);
  stream << PadSpace(n) << "_object" << endl;
  name->Dump(stream, n + 2);
  DumpType(stream, n, type_);
}
