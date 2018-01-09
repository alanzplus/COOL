%{
#include "symboltab.h"
#include "cool-tree.h"
#include "cool.tab.h"
#include <iostream>

#define MAX_STR_CONST 1025
#define YY_NO_UNPUT   /* keep g++ happy */

char string_buf[MAX_STR_CONST]; /* to assemble string constants */
char *string_buf_ptr;

// extern int curr_lineno;

#define STR_TOO_LONG "String constant too long"
#define STR_NULL_CHAR "String contains null character."
#define STR_ES_NULL_CHAR "String contains escaped null character."
#define STR_UNTER "Unterminated string constant"
#define STR_EOF "EOF in string constant"

static int const NULL_CHAR_ERROR = -1;
static int const UNTER_ERROR = -2;

static int too_long = 0;
static int null_char = 0;
static int escape_null_char = 0;
static int comment_level = 0;

%}

/* let flex maintains line number for us */
%option yylineno

/*
 * Define names for regular expressions here.
 */

DARROW          =>
ASSIGN          "<-"
LESS_EQ         "<="
STRING          \"[^"]*
WHITESPACE      [ \n\r\t\f\v]
TRUE            t[rR][uU][eE]
FALSE           f[aA][lL][sS][eE]
TYPE_ID         [A-Z][a-zA-Z0-9_]*
OBJECT_ID       [a-z][a-zA-Z0-9_]*
INTEGER         [0-9]+
SINGLE_CHAR     [+/\-*=<.~,;:(){}@]
/*
 *  Start condition
 */

%x STR
%x COMMENT

%%

 /*
  *  Nested comments
  */


 /*
  *  The multiple-character operators.
  */
{DARROW}		{ return (DARROW); }
{ASSIGN}    { return (ASSIGN); }
{LESS_EQ}   { return (LE); }

 /*
  * Keywords are case-insensitive except for the values true and false,
  * which must begin with a lower-case letter.
  */

[cC][lL][aA][sS][sS] {
  return CLASS;
}

[iI][fF] {
  return IF;
}

[fF][iI] {
  return FI;
}

[eE][lL][sS][eE] {
  return ELSE;
}

[iI][nN] {
  return IN;
}

[iI][nN][hH][eE][rR][iI][tT][sS] {
  return INHERITS;
}

[iI][sS][vV][oO][iI][dD] {
  return ISVOID;
}

[lL][eE][tT] {
  return LET;
}

[lL][oO][oO][pP] {
  return LOOP;
}

[pP][oO][oO][lL] {
  return POOL;
}

[tT][hH][eE][nN] {
  return THEN;
}

[wW][hH][iI][lL][eE] {
  return WHILE;
}

[cC][aA][sS][eE] {
  return CASE;
}

[eE][sS][aA][cC] {
  return ESAC;
}

[nN][eE][wW] {
  return NEW;
}

[oO][fF] {
  return OF;
}

[nN][oO][tT] {
  return NOT;
}

{TRUE} {
  yylval.boolean = true;
  return BOOL_CONST;
}

{FALSE} {
  yylval.boolean = false;
  return BOOL_CONST;
}


self {
  yylval.symbol = IdTable.AddString(yytext);
  return OBJECTID;
}

SELF_TYPE {
  yylval.symbol = IdTable.AddString(yytext);
  return TYPEID;
}

Object {
  yylval.symbol = IdTable.AddString(yytext);
  return TYPEID;
}

Int {
  yylval.symbol = IdTable.AddString(yytext);
  return TYPEID;
}

Bool {
  yylval.symbol = IdTable.AddString(yytext);
  return TYPEID;
}

String {
  yylval.symbol = IdTable.AddString(yytext);
  return TYPEID;
}

{SINGLE_CHAR} {
  return yytext[0];
}

{TYPE_ID} {
  yylval.symbol = IdTable.AddString(yytext);
  return TYPEID;
}

{OBJECT_ID} {
  yylval.symbol = IdTable.AddString(yytext);
  return OBJECTID;
}

{INTEGER} {
  yylval.symbol = IntTable.AddString(yytext);
  return INT_CONST;
}

"--".* {
  ;
}

 /*
  *  String constants (C syntax)
  *  Escape sequence \c is accepted for all characters c. Except for 
  *  \n \t \b \f, the result is c.
  *
  */

 /*
  *     new implementation of matching string reference to Lex Doc
  */

\" {
  too_long = 0;
  null_char = 0;
  string_buf_ptr = string_buf;
  BEGIN(STR);
}

<STR>\" {
  BEGIN(INITIAL);
  if (too_long) {
    too_long = 0;
    yylval.error_msg = STR_TOO_LONG;
    return ERROR;
  }

  if (null_char) {
    null_char = 0;
    yylval.error_msg = STR_NULL_CHAR;
    return ERROR;
  }

  if (escape_null_char) {
    escape_null_char = 0;
    yylval.error_msg = STR_ES_NULL_CHAR;
    return ERROR;
  }

  *string_buf_ptr = '\0';
  yylval.symbol = StrTable.AddString(string_buf);
  return STR_CONST;
}

<STR>\n {
  BEGIN(INITIAL);

  if (too_long) {
    unput('\n');
    too_long = 0;
    yylval.error_msg = STR_TOO_LONG;
    return ERROR;
  }

  if (null_char) {
    unput('\n');
    null_char = 0;
    yylval.error_msg = STR_NULL_CHAR;
    return ERROR;
  }

  // ++curr_lineno;
  yylval.error_msg = STR_UNTER;
  return ERROR;
}

<STR>\\n {
  if (string_buf_ptr - string_buf >= MAX_STR_CONST - 1) {
    too_long = 1;
  } else {
    *string_buf_ptr++ = '\n';
  }
}

<STR>\\t {
  if (string_buf_ptr - string_buf >= MAX_STR_CONST - 1) {
    too_long = 1;
  } else {
    *string_buf_ptr++ = '\t';
  }
}

<STR>\\b {
  if (string_buf_ptr - string_buf >= MAX_STR_CONST - 1) {
    too_long = 1;
  } else {
    *string_buf_ptr++ = '\b';
  }
}

<STR>\\f {
  if (string_buf_ptr - string_buf >= MAX_STR_CONST - 1) {
    too_long = 1;
  } else {
    *string_buf_ptr++ = '\f';
  }
}

<STR>\0 {
  null_char = 1;
}

<STR>\\(.|\n) {
  if (string_buf_ptr - string_buf >= MAX_STR_CONST - 1) {
    too_long = 1;
  } else {
    if (yytext[1] == '\0') {
      escape_null_char = 1;
    } else {
      *string_buf_ptr++ = yytext[1];
    }
  }
}

<STR>[^\"\\\n\0] {
  if (string_buf_ptr - string_buf >= MAX_STR_CONST - 1) {
    too_long = 1;
  } else {
    *string_buf_ptr++ = yytext[0];
  }
}

{WHITESPACE} {
  if (yytext[yyleng-1] == '\n') {
    // ++curr_lineno;
  }
}

. {
  yylval.error_msg = yytext;
  return ERROR;
}

"(*" {
  BEGIN(COMMENT);
  comment_level = 1;
}

<COMMENT>"(*" {
  ++comment_level;
}

<COMMENT>"*)" {
  --comment_level;
  if (comment_level == 0) {
    BEGIN(INITIAL);
  }
}


<COMMENT>[^\n] {
  ;
}

<COMMENT>\n {
  // ++curr_lineno;
}

"*)" {
  yylval.error_msg = "Unmatched *)";
  return ERROR;
}

<STR><<EOF>> {
  BEGIN(INITIAL);
  yylval.error_msg = STR_EOF;
  return ERROR;  
}

<COMMENT><<EOF>> {
  BEGIN(INITIAL);
  yylval.error_msg = "EOF in comment";
  return ERROR;
}


%%
