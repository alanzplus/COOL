#ifndef __CGEN_H__
#define __CGEN_H__
#include "helper.h"
#include "cool-tree.h"
#include "inheritance-tree.h"
#include <memory>

class CodeGen {
 public:
   struct ObjectLayout {
     int gc_tag;
     int class_tag;
     int object_size; // when we use it we must multiply sizeof(WORD)
     std::string dispatch_tab_label;
     std::vector<std::string> attr_labels;
   };

   // TODO: combine this into inheritance tree
   struct ClassInfo {
     ClassInfo() : layout(new ObjectLayout()) {};
     std::string class_name;
     std::string parent_name;
     std::string label;
     std::string tag_name;
     ClassP ast_node;
     std::unique_ptr<ObjectLayout> layout;

     // Attributes Info
     Signature ordered_attrs;        // a vector of (attr_name, type) pair
     StrToIntTab attrs_offset_tab;   // map attr name to its offset

     // Methods Info
     
     // a vector of method_name that is in order.
     VecStr ordered_methods;      

     // a set of methods including current class defined methods and inherited methods
     StrSet method_set;           

     MethodSigTab method_sig_tab; // method_name -> a vector of (arg_name, arg_type)

     // method_name -> a vector of class_name.method_name,
     // the last element is the method should be called
     StrToVecStrTab method_tab;

     // method_name to offset in dispatch table.
     // The offset means the index in this table.
     // When use the offset value in code gen we should times the sizeof(WORD)
     StrToIntTab methods_offset_tab;


     // Dump
     void Dump();
   };

  typedef std::unordered_map<std::string, ClassInfo*> ClassInfoTab;

   struct Env {
     std::string class_name;
     std::string filename;
     const ClassInfoTab* class_info_tab;
     int allocated_temp_space; // in byte
     int next_free_temp_space; // in byte
     // id -> reg or addr
     std::unique_ptr<Scope> loc;

     Env(const std::string& name, const ClassInfoTab* info);
     ~Env();
   };
 

 CodeGen(ProgramP ast_root, InheritanceTree* inherit_tree,
         std::ostream& os = std::cout);
 ~CodeGen();

 void Generate();

 private:
  void CollectClassInfo();
  void CollectClassInfoHelper(const InheritanceTree::Node* node,
                              ClassInfo* info);

  void HandleExpression(const ExpressionP expr, Env* env);
  void HandleAssign(const Assign* assign, Env* env);
  void HandleStaticDispatch(const StaticDispatch* dispatch, Env* env);
  void HandleDispatch(const Dispatch* dispatch, Env* env);
  void HandleCond(const Cond* cond, Env* env);
  void HandleLoop(const Loop* loop, Env* env);
  void HandleCase(const Typcase* typcase, Env* env);
  void HandleBlock(const Block* block, Env* env);
  void HandleLet(const Let* let, Env* env);
  void HandlePlus(const Plus* plus, Env* env);
  void HandleSub(const Sub* sub, Env* env);
  void HandleMul(const Mul* mul, Env* env);
  void HandleDivide(const Divide* divide, Env* env);
  void HandleNeg(const Neg* neg, Env* env);
  void HandleLt(const Lt* lt, Env* env);
  void HandleEq(const Eq* eq, Env* env);
  void HandleLeq(const Leq* leq, Env* env);
  void HandleComp(const Comp* comp, Env* env);
  void HandleIntConst(const IntConst* i, Env* env);
  void HandleStrConst(const StringConst* str, Env* env);
  void HandleBoolConst(const BoolConst* b, Env* env);
  void HandleNew(const New* n, Env* env);
  void HandleIsVoid(const IsVoid* isvoid, Env* env);
  void HandleNoExpr(const NoExpr* noexpr, Env* env);
  void HandleObject(const Object* obj, Env* env);


  void EmitGlobalData();
  void EmitGCSelect();
  void EmitStringConstant(std::ostream& str, const std::string& s);
  void EmitIntTabEntry(const SymbolP sym, std::ostream& s, int tagno);
  void EmitStringTabEntry(const SymbolP sym, std::ostream& s, int tagno);
  void EmitSymbolTabConstants();
  void EmitStrSymbolTab();
  void EmitIntSymbolTab();
  void EmitBoolConstSymbol();
  void EmitClassTagDeclaration();
  void EmitClassTagDefinition();
  void EmitClassNameTab();
  void EmitClassDispatchTab();
  void EmitClassPrototype();
  void EmitGlobalText();
  void EmitClassInitMethod();
  void EmitClassProtObjTab();
  void EmitClassInitTab();
  void EmitClassMethods();

  std::string GetRegOffset(int offset, const std::string& reg);
  
  int CalculateTemporaries(const ExpressionP expr);
  std::string AllocateNewJumpLabel();
  std::string GetAttrOffset(const StrToIntTab& tab, const std::string& name);
  std::string GetProtoObjRef(const std::string& name);

  void EmitSetupStackFrame(std::ostream& str, int temp_space);
  void EmitFreeStackFrame(std::ostream& str, int temp_space);
  void EmitADDIU(std::ostream& str, const std::string& dst,
                 const std::string& op1Reg, const std::string& op2Imm);
  void EmitSW(std::ostream& str, const std::string& srcReg,
             const std::string& tarAddr);
  void EmitLW(std::ostream& str, const std::string& srcAddr,
              const std::string& tarReg);
  void EmitMOVE(std::ostream& str, const std::string& tarReg,
                const std::string& srcReg);
  void EmitPush(std::ostream& str, const std::string& srcReg);
  void EmitPop(std::ostream& str, const std::string& dstReg);
  void EmitPop(std::ostream& str);
  void EmitReturn(std::ostream& str);
  void EmitJAL(std::ostream& str, const std::string& tar);
  void EmitBNE(std::ostream& str, const std::string& r1, const std::string& r2,
               const std::string& label);
  void EmitBEQZ(std::ostream& str, const std::string& reg,
                const std::string& label);
  void EmitLI(std::ostream& str, const std::string& r, const std::string& imm);
  void EmitLA(std::ostream& str, const std::string& r, const std::string& addr);
  void EmitJALR(std::ostream& str, const std::string& reg);
  void EmitB(std::ostream& str, const std::string& label);
  void EmitADD(std::ostream& str,
               const std::string& tarReg,
               const std::string& srcReg1,
               const std::string& srcReg2);
  void EmitSUB(std::ostream& str,
               const std::string& tarReg,
               const std::string& srcReg1,
               const std::string& srcReg2);
  void EmitMUL(std::ostream& str,
               const std::string& tarReg,
               const std::string& srcReg1,
               const std::string& srcReg2);
  void EmitDIV(std::ostream& str,
               const std::string& tarReg,
               const std::string& srcReg1,
               const std::string& srcReg2);
  void EmitNEG(std::ostream& str,
               const std::string& srcReg,
               const std::string& tarReg);
  void EmitBLT(std::ostream& str, const std::string& reg1,
               const std::string& reg2,
               const std::string& label);
  void EmitBEQ(std::ostream& str, const std::string& reg1,
               const std::string& reg2,
               const std::string& label);
  void EmitBLE(std::ostream& str, const std::string& reg1,
               const std::string& reg2,
               const std::string& label);

  std::string GetNextTempSpace(Env* env);
  void FreeTempSpace(Env* env, int nWords);
  std::string GetArgumentOffset(int nth, int len);

  void EmitClassDirectParentTab();

 private:
  ClassInfoTab class_info_tab_;
  ProgramP ast_root_;
  InheritanceTree* inherit_tree_;
  int tag_cnt_;
  // tag number -> class name
  VecStr tag_to_class_name_;

  std::ostream& str_;
};
#endif

