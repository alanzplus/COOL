#ifndef __INHERITANCE_TREE_H__
#define __INHERITANCE_TREE_H__
#include "helper.h"
#include "cool-tree.h"
class InheritanceTree {
 public:
  struct Node {
   ClassP ast_node_; // pointes to the ast node of this class
   std::string name;
   MethodTypeSigTable method_type_tab;
   MethodSigTab method_sig_tab;
   AttrTypeSigTable attr_type_tab;
   AttrSigTab attr_sig_tab;

   Node* parent;
   std::vector<Node*> children;

   Node(const std::string& v_name, ClassP v_class)
     : ast_node_(v_class),
       name(v_name)
    {}

   void DumpMethodTypeTab(std::ostream& stream);
   void DumpAttrTypeTab(std::ostream& stream);
  };

  typedef std::unordered_map<std::string, Node*> NodeTable;

 private:
  NodeTable nodes_tab_;
  ClassesP user_classes_;
  ClassesP basic_classes_;
  Node* root_;
  
  StrSet basic_classes_str_set_;
  StrSet user_classes_str_set_;
  StrSet classes_str_set_;

  AncestorTable ancestor_tab_;

 public:
  StrSet& GetBasicClassStrSet() {
    return basic_classes_str_set_;
  }

  const StrSet& GetBasicClassStrSet() const {
    return basic_classes_str_set_;
  }


 public:
  InheritanceTree(ProgramP ast_root);
  ~InheritanceTree();
  Node* GetRoot() { return root_; }
  Node* LookupNode(const std::string& name);

  const TypeSignature* LookupAttrTypeInfo(const std::string& class_name,
                                          const std::string& attr_name);
  const TypeSignature* LookupMethodTypeInfo(const std::string& class_name,
                                            const std::string& method_name);
  const Signature* LookupMethodInfo(const std::string& class_name,
                                    const std::string& method_name);
  void CheckRedefinedInheritedAttr(Node* node);
  void CheckRedefinedInheritedMethod(Node* node);
  void DumpAncestorTable(std::ostream& stream);

  bool IsConformed(const std::string& type1, const std::string& type2);
  std::string LCA(const std::string& type1, const std::string& type2);

  void DumpNodeTypeInfo(std::ostream& stream);

  ClassesP GetUserClasses() {
    return user_classes_;
  }

  ClassesP GetBasicClasses() {
    return basic_classes_;
  }

 private:
  ClassesP CreateBasicClasses();
  void InitBasicClasses();
  void CreateTree();
  void CreateMethodAndAttrTypeInfoTab(Node* node);
  void CreateAncestorTable(Node* node);
  // node1 is a child of node2
  bool IsChildOf(const Node* node1, const Node* node2);
};

class LoopDetector {
 public:
  bool RecursiveHelper(typename InheritanceTree::Node* node,
                       StrSet& loop_nodes);

  bool operator()(typename InheritanceTree::NodeTable& nodes);

  const StrSet& GetLoopNodes() const {
    return loop_nodes_;
  }

 private:
  std::unordered_map<std::string, bool> instack_;
  std::unordered_map<std::string, bool> visited_;
  StrSet loop_nodes_;
};

#endif
