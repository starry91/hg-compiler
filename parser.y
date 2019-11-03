%{
  #include <cstdio>
  #include <iostream>
  using namespace std;

  // stuff from flex that bison needs to know about:
  extern int yylex();
  extern "C" int yyparse();
  extern FILE *yyin;
  extern int linenum;
 
  void yyerror(const char *s);
%}

%union {
  int ival;
  float fval;
  char *sval;
}
%define parse.error verbose

// define the constant-string tokens:
%token BREAK FOR IF RETURN TRUE FALSE VOID WHILE CONTINUE ELSE COUT CIN ENDL
%token INT CHAR BOOL UINT SINT
%token MULTI_COMMENT SINGLE_COMMENT LEFT_SHIFT RIGHT_SHIFT

// define the "terminal symbol" token types I'm going to use (in CAPS
// by convention), and associate each with a field of the union:
%token <ival> NUM_CONST
%token <sval> ID
%token <sval> CHAR_CONST
%token <sval> BIN_OP
%token <sval> UNARY_OP

%right '?' ':'
%left UNARY_OP
%left BIN_OP
%left ';'
%%
// the first rule defined is the highest-level rule, which in our
// case is just the concept of a whole "snazzle file":
PROGRAM: DECLARATION_LIST
        ;
DECLARATION_LIST: DECLARATION_LIST  DECLARATION
                    | DECLARATION
                ;
DECLARATION: FUNC_DEC
            | VAR_DEC_STATEMENT ';'
            ;
VAR_DEC_STATEMENT:  TYPE_SPECIFIER VAR_DEC_LIST
            ;
TYPE_SPECIFIER: INT
            | BOOL
            | CHAR
            | SINT
            | UINT
            | VOID
            ;
VAR_DEC_LIST: VAR_DEC_LIST ',' VAR_INITIALIZE
            | VAR_INITIALIZE
            ;
VAR_INITIALIZE: VAR_DEC_ID
            | VAR_DEC_ID '=' SIMPLE_STATEMENT
            ;
VAR_DEC_ID: ID '[' NUM_CONST ']'
            | ID
            | ID '[' NUM_CONST ']' '[' NUM_CONST ']'
            ;
FUNC_DEC:   TYPE_SPECIFIER ID '(' FUNC_ARGS ')' BLOCK_STATEMENT
            ;
FUNC_ARGS: TYPE_SPECIFIER ID ',' FUNC_ARGS
            | TYPE_SPECIFIER ID
            | %empty
            ;
STATEMENT: BLOCK_STATEMENT ';'
            | ITERATION_STATEMENT ';'
            | CONTROL_STATEMENT ';'
            | ';'
            | RETURN_STATEMENT ';'
            | ASSIGNMENT_STATEMENT ';'
            | VAR_DEC_STATEMENT ';'
            | SIMPLE_STATEMENT ';'
            | BREAK_STATEMENT ';'
            | CONTINUE_STATEMENT ';'
            | STDIN_STATEMENT ';'
            | STDOUT_STATEMENT ';'
            ;
ASSIGNMENT_STATEMENT: VAR_ACCESS_ID '=' SIMPLE_STATEMENT
            | VAR_ACCESS_ID '=' SIMPLE_STATEMENT ',' ASSIGNMENT_STATEMENT
            ;
SIMPLE_STATEMENT: EXPR
            | FUNC_CALL
            ;
BLOCK_STATEMENT:  '{' STMNT_LIST '}'
            ;  
ITERATION_STATEMENT: FOR_STATEMENT
            | WHILE_STATEMENT
            ;
FOR_STATEMENT: FOR '(' ASSIGNMENT_STATEMENT ';' EXPR ';' ASSIGNMENT_STATEMENT ')' BLOCK_STATEMENT
            ;
WHILE_STATEMENT: WHILE '(' EXPR ')' BLOCK_STATEMENT
            ;
CONTROL_STATEMENT: IF '(' EXPR ')' BLOCK_STATEMENT
            | IF '(' EXPR ')' BLOCK_STATEMENT ELSE BLOCK_STATEMENT
            ;
RETURN_STATEMENT: RETURN ID
            | RETURN
            ;
BREAK_STATEMENT: BREAK
            ;
CONTINUE_STATEMENT: CONTINUE
            ;
STDIN_STATEMENT: CIN RIGHT_SHIFT EXPR
            ;
STDOUT_STATEMENT: COUT LEFT_SHIFT EXPR
            ;
FUNC_CALL: ID '(' PARAMS_LIST ')'
            ;
VAR_ACCESS_ID: ID
            | ID '[' EXPR ']'
            | ID '[' EXPR ']' '[' EXPR ']'
            ;
PARAMS_LIST: SIMPLE_STATEMENT ',' PARAMS_LIST
            | SIMPLE_STATEMENT
            ;
STMNT_LIST: STATEMENT STMNT_LIST
            | %empty
            ;
EXPR:       VAR_ACCESS_ID
            | CONST
            | EXPR BIN_OP EXPR
            | '(' EXPR ')' 
            | UNARY_OP EXPR
            | TERNARY_EXPR
            ;
TERNARY_EXPR: EXPR '?' EXPR ':' EXPR
            ;
CONST:      NUM_CONST
            | CHAR_CONST
            | TRUE
            | FALSE
            ;
%%

int main(int argc,char** argv) {
#ifdef YYDEBUG
  yydebug = 0;
#endif
    // open a file handle to a particular file:
    FILE *myfile = fopen(argv[1], "r");
    // make sure it's valid:
    if (!myfile) {
        cout << "I can't open a.snazzle.file!" << endl;
        // return -1;
    }
    // set lex to read from it instead of defaulting to STDIN:
    yyin = myfile;

  // Parse through the input:
  yyparse();
}

void yyerror(const char *s) {
  cout << "EEK, parse error on line " << linenum << "!  Message: " << s << endl;
  // might as well halt now:
  exit(-1);
}