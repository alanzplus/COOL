#ifndef __SEMANT_H__
#define __SEMANT_H__
#include <memory>
#include "helper.h"
#include "cool-tree.h"
#include "symboltab.h"
#include "inheritance-tree.h"

class SemanticChecker {
 public:
   SemanticChecker(InheritanceTree* tree);
   ~SemanticChecker();
  void TypeChecking();

 private:
  void TypeCheckingHelper(ExpressionP expr);
  void HandleObject(ExpressionP expr);
  void HandleAssign(ExpressionP expr);
  void HandleNew(ExpressionP expr);
  void HandleCond(ExpressionP expr);
  void HandleBlock(ExpressionP expr);
  void HandleCase(ExpressionP expr);
  void HandleLoop(ExpressionP expr);
  void HandleIsVoid(ExpressionP expr);
  void HandleComp(ExpressionP expr);
  void HandleLt(ExpressionP expr);
  void HandleLeq(ExpressionP expr);
  void HandleNeg(ExpressionP expr);
  void HandlePlus(ExpressionP expr);
  void HandleSub(ExpressionP expr);
  void HandleMul(ExpressionP expr);
  void HandleDivide(ExpressionP expr);
  void HandleEq(ExpressionP expr);
  void HandleLet(ExpressionP expr);
  void HandleDispatch(ExpressionP expr);
  void HandleStaticDispatch(ExpressionP expr);
  const std::string* IDTypeInfoLookup(const std::string& name);

 private:
  InheritanceTree* inherit_tree_;
  std::unique_ptr<Scope> name_scope_;
  InheritanceTree::Node* curr_class_node_;
  SemantError* serr_;
  const ConstantSymbol* c_syms_;
};
#endif
