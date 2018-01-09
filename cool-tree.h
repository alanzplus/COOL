#ifndef __COOL_TREE_H__
#define __COOL_TREE_H__
#include <iostream>
#include <string>
#include <vector>
#include "symboltab.h"

typedef std::string Type;

class TreeNode {
 protected:
  int line_number_;
  Type type_; 

 public:
  TreeNode() { type_ = ""; }
  virtual ~TreeNode() {}
  virtual void Dump(std::ostream& stream, int n) = 0;
  virtual void DumpWithTypes(std::ostream& stream, int n) = 0;
  void SetType(const Type& type) { type_ = type; }
  const Type& GetType() const { return type_; }
  int GetLine() const { return line_number_; }
  void SetLine(int line) { line_number_ = line; }
  TreeNode(const TreeNode& rhs) = delete;
  TreeNode& operator=(const TreeNode& rhs)  = delete;
};

typedef class Program* ProgramP;
typedef class Class* ClassP;
typedef class Feature* FeatureP;
typedef class Method* MethodP;
typedef class Attr* AttrP;
typedef class Formal* FormalP;
typedef class Expression* ExpressionP;
typedef class Case* CaseP;
typedef class Assign* AssingP;

typedef std::vector<ClassP> Classes;
typedef std::vector<FeatureP> Features;
typedef std::vector<FormalP> Formals;
typedef std::vector<ExpressionP> Expressions;
typedef std::vector<CaseP> Cases;

typedef Classes* ClassesP;
typedef Features* FeaturesP;
typedef Formals* FormalsP;
typedef Expressions* ExpressionsP;
typedef Cases* CasesP;

class Program : public TreeNode {
 public:
  ClassesP classes;
  Program(ClassesP cl, int lineno = 0) : classes(cl) { line_number_ = lineno; }
  void Dump(std::ostream& stream, int n);
  void DumpWithTypes(std::ostream& stream, int n);
};

class Class : public TreeNode {
 public:
  SymbolP name;
  SymbolP parent;
  SymbolP filename;
  FeaturesP features;
  
  Class(SymbolP v_name, SymbolP v_parent, SymbolP v_filename,
        FeaturesP v_features, int lineno = 0)
    : name(v_name), parent(v_parent),
      filename(v_filename), features(v_features) { line_number_ = lineno; }

  void Dump(std::ostream& stream, int n);
  void DumpWithTypes(std::ostream& stream, int n);
};

class Feature : public TreeNode {
 public:
  virtual void Dump(std::ostream& stream, int n) = 0;
  virtual void DumpWithTypes(std::ostream& stream, int n) = 0;
};

class Method : public Feature {
 public:
   SymbolP name;
   SymbolP return_type;
   FormalsP formals;
   ExpressionP expression;

   Method(SymbolP v_name,
          SymbolP v_return_type,
          FormalsP v_formals,
          ExpressionP v_expression,
          int lineno = 0)
     : name(v_name), return_type(v_return_type), formals(v_formals),
       expression(v_expression) { line_number_ = lineno; }

   void Dump(std::ostream& stream, int n);
   void DumpWithTypes(std::ostream& stream, int n);
};

class Attr : public Feature {
 public:
  SymbolP name;
  SymbolP type_decl;
  ExpressionP init;

  Attr(SymbolP v_name,
       SymbolP v_type_decl,
       ExpressionP v_init,
       int lineno = 0)
    : name(v_name), type_decl(v_type_decl), init(v_init) { line_number_ = lineno; }

  void Dump(std::ostream& stream, int n);
   void DumpWithTypes(std::ostream& stream, int n);
};

class Formal : public TreeNode {
 public:
  SymbolP name;
  SymbolP type_decl;
  Formal(SymbolP v_name, SymbolP v_type_decl, int lineno = 0)
    : name(v_name), type_decl(v_type_decl) { line_number_ = lineno; }
  void Dump(std::ostream& stream, int n);
  void DumpWithTypes(std::ostream& stream, int n);
};

class Case : public TreeNode {
 public:
   SymbolP name;
   SymbolP type_decl;
   ExpressionP expression;

   Case(SymbolP v_name,
        SymbolP v_type_decl,
        ExpressionP v_expression,
        int lineno = 0)
     : name(v_name), type_decl(v_type_decl), expression(v_expression) {
       line_number_ = lineno;
     }
  
   void Dump(std::ostream& stream, int n );
   void DumpWithTypes(std::ostream& stream, int n);
};

class Expression : public TreeNode {
 public:
   virtual void Dump(std::ostream& stream, int n) = 0;
   virtual void DumpWithTypes(std::ostream& stream, int n) = 0;
};

class Assign : public Expression {
 public:
  SymbolP name;
  ExpressionP expression;
  Assign(SymbolP v_name, ExpressionP v_expression, int lineno = 0)
    : name(v_name), expression(v_expression) { line_number_ = lineno; }
  void Dump(std::ostream& stream, int n);
  void DumpWithTypes(std::ostream& stream, int n);
};

// expression@type_name.name(actual_exprs)
class StaticDispatch : public Expression {
 public:
  SymbolP name;
  SymbolP type_name;
  ExpressionP expression;
  ExpressionsP actual_exprs;

  StaticDispatch(SymbolP v_name,
                 SymbolP v_type_name,
                 ExpressionP v_expression,
                 ExpressionsP v_actual_exprs,
                 int lineno = 0)
    : name(v_name),
      type_name(v_type_name),
      expression(v_expression),
      actual_exprs(v_actual_exprs) { line_number_ = lineno; }

  void Dump(std::ostream& stream, int n);
  void DumpWithTypes(std::ostream& stream, int n);
};

class Dispatch : public Expression {
 public:
  SymbolP name;
  ExpressionP expression;
  ExpressionsP actual_exprs;
  Dispatch(SymbolP v_name,
           ExpressionP v_expression,
           ExpressionsP v_actual_exprs,
           int lineno = 0)
    : name(v_name), expression(v_expression), actual_exprs(v_actual_exprs) {
      line_number_ = lineno;
    }
  void Dump(std::ostream& stream, int n);
  void DumpWithTypes(std::ostream& stream, int n);
};

class Cond : public Expression {
 public:
   ExpressionP pred;
   ExpressionP then_exp;
   ExpressionP else_exp;

   Cond(ExpressionP v_pred,
        ExpressionP v_then_exp,
        ExpressionP v_else_exp,
        int lineno = 0)
     : pred(v_pred), then_exp(v_then_exp), else_exp(v_else_exp) { 
       line_number_ = lineno; 
     }
   void Dump(std::ostream& stream, int n);
   void DumpWithTypes(std::ostream& stream, int n);
};

class Loop : public Expression {
 public:
  ExpressionP pred;
  ExpressionP body;
  
  Loop(ExpressionP v_pred,
       ExpressionP v_body,
       int lineno = 0)
    : pred(v_pred), body(v_body) { line_number_ = lineno; }

  void Dump(std::ostream& stream, int n);
  void DumpWithTypes(std::ostream& stream, int n);
};

class Typcase : public Expression {
 public:
  ExpressionP expression;
  CasesP cases;

  Typcase(ExpressionP v_expression,
          CasesP v_cases,
          int lineno = 0)
    : expression(v_expression),
      cases(v_cases) { line_number_ = lineno; }

  void Dump(std::ostream& stream, int n);
  void DumpWithTypes(std::ostream& stream, int n);
};

class Block : public Expression {
 public:
  ExpressionsP body;
  Block(ExpressionsP v_body,
        int lineno) : body(v_body) { line_number_ = lineno; }
  void Dump(std::ostream& stream, int n);
  void DumpWithTypes(std::ostream& stream, int n);
};

class Let : public Expression {
 public:
  SymbolP identifier;
  SymbolP type_decl;
  ExpressionP init;
  ExpressionP body;

  Let(SymbolP v_identifier,
      SymbolP v_type_decl,
      ExpressionP v_init,
      ExpressionP v_body,
      int lineno = 0)
    : identifier(v_identifier),
      type_decl(v_type_decl),
      init(v_init),
      body(v_body) { line_number_ = lineno; }

  void Dump(std::ostream& stream, int n);
  void DumpWithTypes(std::ostream& stream, int n);
};

class Plus : public Expression {
 public:
   ExpressionP e1;
   ExpressionP e2;
   
   Plus(ExpressionP v_e1, ExpressionP v_e2, int lineno = 0)
     : e1(v_e1),
       e2(v_e2) { line_number_ = lineno; }

  void Dump(std::ostream& stream, int n);
  void DumpWithTypes(std::ostream& stream, int n);
};

class Sub : public Expression {
 public:
  ExpressionP e1;
  ExpressionP e2;

  Sub(ExpressionP v_e1,
      ExpressionP v_e2,
      int lineno = 0)
    : e1(v_e1), e2(v_e2) { line_number_ = lineno; }

  void Dump(std::ostream& stream, int n);
  void DumpWithTypes(std::ostream& stream, int n);
};

class Mul : public Expression {
 public:
   ExpressionP e1;
   ExpressionP e2;

   Mul(ExpressionP v_e1,
       ExpressionP v_e2,
       int lineno = 0)
     : e1(v_e1),
       e2(v_e2) { line_number_ = lineno; }

  void Dump(std::ostream& stream, int n);
  void DumpWithTypes(std::ostream& stream, int n);
};

class Divide : public Expression {
 public:
   ExpressionP e1;
   ExpressionP e2;

   Divide(ExpressionP v_e1,
          ExpressionP v_e2,
          int lineno = 0)
     : e1(v_e1),
       e2(v_e2) { line_number_ = lineno; }

  void Dump(std::ostream& stream, int n);
  void DumpWithTypes(std::ostream& stream, int n);
};

class Neg : public Expression {
 public:
   ExpressionP e;

   Neg(ExpressionP v_e, int lineno) : e(v_e) { line_number_ = lineno; }

  void Dump(std::ostream& stream, int n);
  void DumpWithTypes(std::ostream& stream, int n);
};

class Lt : public Expression {
 public:
   ExpressionP e1;
   ExpressionP e2;

   Lt(ExpressionP v_e1,
      ExpressionP v_e2,
      int lineno = 0)
     : e1(v_e1),
       e2(v_e2) { line_number_ = lineno; }

  void Dump(std::ostream& stream, int n);
  void DumpWithTypes(std::ostream& stream, int n);
};

class Eq : public Expression {
 public:
   ExpressionP e1;
   ExpressionP e2;

   Eq(ExpressionP v_e1,
      ExpressionP v_e2,
      int lineno = 0)
     : e1(v_e1),
       e2(v_e2) { line_number_ = lineno; }

  void Dump(std::ostream& stream, int n);
  void DumpWithTypes(std::ostream& stream, int n);
};

class Leq : public Expression {
 public:
   ExpressionP e1;
   ExpressionP e2;

   Leq(ExpressionP v_e1,
       ExpressionP v_e2,
       int lineno = 0)
     : e1(v_e1),
       e2(v_e2) { line_number_ = lineno; }

  void Dump(std::ostream& stream, int n);
  void DumpWithTypes(std::ostream& stream, int n);
};

class Comp : public Expression {
 public:
   ExpressionP e;

   Comp(ExpressionP v_e, int lineno = 0) : e(v_e) { line_number_ = lineno; }

  void Dump(std::ostream& stream, int n);
  void DumpWithTypes(std::ostream& stream, int n);
};

class IntConst : public Expression {
 public:
  SymbolP token;

  IntConst(SymbolP v_token, int lineno = 0) : token(v_token) {
    line_number_ = lineno;
  }

  void Dump(std::ostream& stream, int n);
  void DumpWithTypes(std::ostream& stream, int n);
};

class BoolConst : public Expression {
 public:
   bool val;

   BoolConst(bool v_val, int lineno = 0) : val(v_val) { line_number_ = lineno; }

  void Dump(std::ostream& stream, int n);
  void DumpWithTypes(std::ostream& stream, int n);
};

class StringConst : public Expression {
 public:
   SymbolP token;
   StringConst(SymbolP v_token, int lineno = 0) : token(v_token) {
     line_number_ = lineno; 
   }

  void Dump(std::ostream& stream, int n);
  void DumpWithTypes(std::ostream& stream, int n);
};

class New : public Expression {
 public:
   SymbolP type_name;

   New(SymbolP v_type_name, int lineno = 0) : type_name(v_type_name) {
     line_number_ = lineno;
   }

  void Dump(std::ostream& stream, int n);
  void DumpWithTypes(std::ostream& stream, int n);
};

class IsVoid : public Expression {
 public:
   ExpressionP e;
   IsVoid(ExpressionP v_e, int lineno) : e(v_e) { line_number_ = lineno; }
   void Dump(std::ostream& stream, int n);
   void DumpWithTypes(std::ostream& stream, int n);
};

class NoExpr : public Expression {
 public:
   NoExpr(int lineno = 0) { line_number_ = lineno; }
   void Dump(std::ostream& stream, int n);
   void DumpWithTypes(std::ostream& stream, int n);
};

class Object : public Expression {
 public:
  SymbolP name;
  Object(SymbolP v_name, int lineno = 0) : name(v_name) { 
    line_number_ = lineno;
  }
  void Dump(std::ostream& stream, int n);
  void DumpWithTypes(std::ostream& stream, int n);
};

ClassesP CreateNilClasses();
ClassesP CreateSingleClasses(ClassP c);
ClassesP AppendClass(ClassesP cs, ClassP c);

FeaturesP CreateNilFeatures();
FeaturesP CreateSingleFeatures(FeatureP f);
FeaturesP AppendFeature(FeaturesP fs, FeatureP f);

FormalsP CreateNilFormals();
FormalsP CreateSingleFormals(FormalP f);
FormalsP AppendFormal(FormalsP fs, FormalP f);

ExpressionsP CreateNilExpressions();
ExpressionsP CreateSingleExpressions(ExpressionP e);
ExpressionsP AppendExpression(ExpressionsP es, ExpressionP e);

CasesP CreateNilCases();
CasesP CreateSingleCases(CaseP c);
CasesP AppendCase(CasesP cs, CaseP c);

ProgramP CreateProgram(ClassesP cs, int lineno = 0);

ClassP CreateClass(SymbolP name,
                   SymbolP parent,
                   SymbolP filename,
                   FeaturesP features,
                   int lineno = 0);

FeatureP CreateMethod(SymbolP name,
                      SymbolP return_type,
                      FormalsP formals,
                      ExpressionP expression,
                      int lineno = 0);

FeatureP CreateAttr(SymbolP name,
                    SymbolP type_decl,
                    ExpressionP init,
                    int lineno = 0);

FormalP CreateFormal(SymbolP name,
                     SymbolP type_decl,
                     int lineno = 0);

CaseP CreateCase(SymbolP name,
                 SymbolP type_decl,
                 ExpressionP expression,
                 int lineno = 0);

ExpressionP CreateAssign(SymbolP name,
                         ExpressionP expression,
                         int lineno = 0);

ExpressionP CreateStaticDispatch(SymbolP name,
                                 SymbolP type_name,
                                 ExpressionP expression,
                                 ExpressionsP actual_exprs,
                                 int lineno = 0);

ExpressionP CreateDispatch(SymbolP name,
                           ExpressionP expression,
                           ExpressionsP actual_exprs,
                           int lineno = 0);

ExpressionP CreateCond(ExpressionP pred,
                       ExpressionP then_exp,
                       ExpressionP else_exp,
                       int lineno = 0);

ExpressionP CreateLoop(ExpressionP pred,
                       ExpressionP body,
                       int lineno = 0);

ExpressionP CreateTypecase(ExpressionP expression,
                           CasesP cases,
                           int lineno = 0);

ExpressionP CreateBlock(ExpressionsP body,
                        int lineno = 0);

ExpressionP CreateLet(SymbolP identifier,
                       SymbolP type_decl,
                       ExpressionP init,
                       ExpressionP body,
                       int lineno = 0);

ExpressionP CreatePlus(ExpressionP e1,
                       ExpressionP e2,
                       int lineno = 0);

ExpressionP CreateSub(ExpressionP e1,
                      ExpressionP e2,
                      int lineno = 0);

ExpressionP CreateMul(ExpressionP e1,
                      ExpressionP e2,
                      int lineno = 0);

ExpressionP CreateDivide(ExpressionP e1,
                         ExpressionP e2,
                         int lineno = 0);

ExpressionP CreateNeg(ExpressionP e, int lineno = 0);

ExpressionP CreateLt(ExpressionP e1,
                     ExpressionP e2,
                     int lineno = 0);

ExpressionP CreateEq(ExpressionP e1,
                     ExpressionP e2,
                     int lineno = 0);

ExpressionP CreateLeq(ExpressionP e1,
                      ExpressionP e2,
                      int lineno = 0);

ExpressionP CreateComp(ExpressionP e, int lineno = 0);

ExpressionP CreateIntConst(SymbolP token, int lineno = 0);

ExpressionP CreateBoolConst(bool val, int lineno = 0);

ExpressionP CreateStringConst(SymbolP token, int lineno = 0);

ExpressionP CreateNew(SymbolP type_name, int lineno = 0);

ExpressionP CreateIsVoid(ExpressionP e, int lineno = 0);

ExpressionP CreateNoExpr(int lineno = 0);

ExpressionP CreateObject(SymbolP name, int lineno = 0);

#endif
