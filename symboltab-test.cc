#include <gtest/gtest.h>
#include "symboltab.h"
#include <string>
#include <algorithm>
#include <functional>

using namespace std;
TEST(SymbolTest, CreateTest) {
  const int idx = 1;
  const std::string name = "hello";
  SymbolP sym = new Symbol(name, idx);
  EXPECT_TRUE(idx == sym->GetIndex());
  EXPECT_TRUE(name == sym->GetString());
}

TEST(SymbolTabTest, LookupTest) {
  SymbolTable symtab;
  const std::string str1 = "Hello";
  symtab.AddString(str1);
  EXPECT_TRUE(str1 == symtab.Lookup(str1)->GetString());
  EXPECT_TRUE(0 == symtab.Lookup(str1)->GetIndex());
  
  const std::string str2 = "World";
  symtab.AddString(str2);
  EXPECT_TRUE(str2 == symtab.Lookup(str2)->GetString());
  EXPECT_TRUE(1 == symtab.Lookup(str2)->GetIndex());

  EXPECT_TRUE(nullptr == symtab.Lookup("abc"));
}

TEST(SymbolTabTest, IteratorTest) {
  SymbolTable symtab;
  std::vector<std::string> strvec = {
    "Hello", "World", "You"
  };

  std::sort(strvec.begin(), strvec.end());


  for (const auto& str : strvec) {
    symtab.AddString(str);
  }

  std::vector<std::string> res; 
  for (auto p : symtab) {
    res.push_back(p.first);
  }

  std::sort(res.begin(), res.end());

  bool ret = true;
  for (int i = 0; i < strvec.size(); ++i) {
    ret &= strvec[i] == res[i];
  }
  
  EXPECT_TRUE(ret);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
