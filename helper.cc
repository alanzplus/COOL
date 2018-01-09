#include "helper.h"
#include "symboltab.h"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cctype>
#include <unistd.h>
#include <algorithm>
using namespace std;

extern int yydebug;
extern int yy_flex_debug;     // flex : prints recognized rules

SemantError* SemantError::serror_ = nullptr;

namespace cool_helper {
int g_log_cerr = 0;
string g_codegen_out_fn = "";

void Init(int* argc, char *argv[]) {
  const std::string help_msg = R"(
  usage:
    [-hlpg] input-files [-o outputfile]

  options:
    -h    print this messages
    -l    set yy_flex_debug = 1, prints recognized rules
    -p    set yydebug = 1, prints parser state
    -g    set g_log_cerr = 1
    -o    specify code-gen output file
)";

  auto print_help_msg = [&]() {
    cout << help_msg << endl;
    exit(0);
  };

  // init all flags
  yy_flex_debug = 0;
  yydebug = 0;
  g_log_cerr = 0;
  
  // get flag 
  char c;
  while ((c = getopt(*argc, argv, "hlpg")) != -1) {
    switch (c) {
      case 'h':
        print_help_msg();

      case 'l':
        yy_flex_debug = 1;
        break;

      case 'g':
        g_log_cerr = 1;
        break;

      case 'p':
        yydebug = 1;
        break;

      default:
        print_help_msg();
    }
  }

  int idx = 1;
  for (int i = 1; i < *argc; ++i) {
    if (argv[i][0] == '-') {
      if (argv[i][1] == 'o') {
        // no output file
        if ((i + 1) >= *argc) {
          print_help_msg();
        } else {
          g_codegen_out_fn = argv[++i];
        }
      }
      continue;
    }
    argv[idx++]  = argv[i];
  }
  
  *argc = idx;

  if (*argc < 2) {
    print_help_msg();
    exit(1);
  }
}

std::string TokenToString(int tok) {
  switch (tok) {
  case 0:            return("EOF");        break;
  case (CLASS):      return("CLASS");      break;
  case (ELSE):       return("ELSE");       break;
  case (FI):         return("FI");         break;
  case (IF):         return("IF");         break;
  case (IN):         return("IN");         break;
  case (INHERITS):   return("INHERITS");   break;
  case (LET):        return("LET");        break;
  case (LOOP):       return("LOOP");       break;
  case (POOL):       return("POOL");       break;
  case (THEN):       return("THEN");       break;
  case (WHILE):      return("WHILE");      break;
  case (ASSIGN):     return("ASSIGN");     break;
  case (CASE):       return("CASE");       break;
  case (ESAC):       return("ESAC");       break;
  case (OF):         return("OF");         break;
  case (DARROW):     return("DARROW");     break;
  case (NEW):        return("NEW");        break;
  case (STR_CONST):  return("STR_CONST");  break;
  case (INT_CONST):  return("INT_CONST");  break;
  case (BOOL_CONST): return("BOOL_CONST"); break;
  case (TYPEID):     return("TYPEID");     break;
  case (OBJECTID):   return("OBJECTID");   break;
  case (ERROR):      return("ERROR");      break;
  case (LE):         return("LE");         break;
  case (NOT):        return("NOT");        break;
  case (ISVOID):     return("ISVOID");     break;
  case '+': return("'+'"); break;
  case '/': return("'/'"); break;
  case '-': return("'-'"); break;
  case '*': return("'*'"); break;
  case '=': return("'='"); break;
  case '<': return("'<'"); break;
  case '.': return("'.'"); break;
  case '~': return("'~'"); break;
  case ',': return("','"); break;
  case ';': return("';'"); break;
  case ':': return("':'"); break;
  case '(': return("'('"); break;
  case ')': return("')'"); break;
  case '@': return("'@'"); break;
  case '{': return("'{'"); break;
  case '}': return("'}'"); break;
  default:  return("<Invalid Token>");
  }
}

void
DumpCoolToken(std::ostream& out, int lineno, int token, YYSTYPE yylval) {
  out << "#" << lineno << " " << TokenToString(token);
  switch (token) {
    case (STR_CONST):
      out << " \"" << ToEscapedString(yylval.symbol->GetString())
          << "\"" << endl;
      break;

    case (INT_CONST):
      out << " " << yylval.symbol->GetString() << endl;
      break;
    
    case (BOOL_CONST):
      out << " " << (yylval.boolean ? "true" : "false") << endl;
      break;

    case (TYPEID):
    case (OBJECTID):
      out << " " << yylval.symbol->GetString() << endl;
      break;

    case (ERROR):
      if (yylval.error_msg[0] == 0) {
        out << " \"\\000\"" << endl;
      } else {
        out << " \""
            << ToEscapedString(yylval.error_msg)
            << "\"" << endl;
      }
      break;
      
    default:
      out << endl;
  }
}

std::string ToEscapedString(const std::string& str) {
  ostringstream oss;
  for (const auto& c : str) {
    switch (c) {
      case '\\' : oss << "\\\\"; break;
      case '\"' : oss << "\\\""; break;
      case '\n' : oss << "\\n"; break;
      case '\t' : oss << "\\t"; break;
      case '\b' : oss << "\\b"; break;
      case '\f' : oss << "\\f"; break;
      default:
        if (isprint(c)) oss << c;
        else {
          oss << '\\' << oct << setfill('0') << setw(3)
              << static_cast<int>(static_cast<unsigned int>(c))
              << dec << setfill(' ');
          break;
        }
    }
  }
  return oss.str();
}


// 80 spaces for padding
static const char *padding = "                                                                                ";

const char* PadSpace(int n) {
  if (n > 80) return padding;
  if (n <= 0) return "";
  return padding + (80 - n);
}

void DumpLine(ostream& out, int n, int line) {
  out << PadSpace(n) << "#" << line << endl;
}

void DumpType(ostream& stream, int n, const std::string& type) {
  stream << PadSpace(n) << ": " << (type == "" ? "_no_type" : type) << endl;
}

std::string GetClassLabelName(const std::string& class_name) {
  return class_name + "_" + "protObj";
}

std::string GetClassDispatchTabName(const std::string& class_name) {
  return class_name + "_" + "dispatch_tab";
}

std::string GetClassTagName(const std::string& class_name) {
  std::string tag = "_" + class_name + "_" + "tag";
  const auto* c_syms = ConstantSymbol::Get();
  if (class_name == c_syms->Bool->GetString() ||
      class_name == c_syms->Int->GetString() ||
      class_name == c_syms->Str->GetString()) {
    std::transform(tag.begin(), tag.end(), tag.begin(), ::tolower);
  }
  return tag;
}

std::string GetClassInitMethod(const std::string& class_name) {
  return class_name + "_init";
}

} // namespace cool_helper
