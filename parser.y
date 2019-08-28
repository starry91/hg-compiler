%{
  #include <cstdio>
  #include <iostream>
  using namespace std;

  // stuff from flex that bison needs to know about:
  extern int yylex();
  extern int yyparse();
  extern FILE *yyin;
 
  void yyerror(const char *s);
%}

%union {
  int ival;
  float fval;
  char *sval;
}

// define the constant-string tokens:
%token BREAK FOR IF RETURN TRUE FALSE VOID WHILE CONTINUE ELSE COUT CIN ENDL COMMA SEMICOLON
%token INT CHAR BOOL UINT SINT
%token BRACE_OPEN BRACE_CURLY_CLOSE BRACE_PARANTHESIS_OPEN BRACE_PARANTHESIS_CLOSE BRACE_SQUARE_OPEN BRACE_SQUARE_CLOSE
%token MULTI_COMMENT SINGLE_COMMENT LEFT_SHIFT RIGHT_SHIFT NUM_CONST ID CHAR_CONST
%token BIN_OP UNARY_OP EQUAL_OP

// define the "terminal symbol" token types I'm going to use (in CAPS
// by convention), and associate each with a field of the union:
%token <ival> INT_VAL
%token <fval> FLOAT_VAL
%token <sval> STRING_VAL
%%
// the first rule defined is the highest-level rule, which in our
// case is just the concept of a whole "snazzle file":
PROGRAM: DECLARATION_LIST
        ;
DECLARATION_LIST: DECLARATION_LIST  DECLARATION
                    | DECLARATION
                ;
DECLARATION: FUNC_DEC
            | VAR_DEC
            ;
VAR_DEC:    TYPE_SPECIFIER VAR_DEC_LIST ';'
            | TYPE_SPECIFIER VAR_DEC_LIST VAR_DEC ';'
            ;
TYPE_SPECIFIER: INT
            | BOOL
            | CHAR
            | SINT
            | UINT
            ;
VAR_DEC_LIST: VAR_DEC_LIST ',' VAR_INITIALIZE
            | VAR_INITIALIZE
            ;
VAR_INITIALIZE: VAR_DEC_ID
            | VAR_DEC_ID '=' EXPR
            ;
VAR_DEC_ID: ID '[' NUM_CONST ']'
            | ID
            | ID '[' NUM_CONST ']' '[' NUM_CONST ']'
            ;
FUNC_DEC:   TYPE_SPECIFIER ID '(' FUNC_ARGS ')' BLOCK_STATEMENT
            ;
FUNC_ARGS: TYPE_SPECIFIER ID ',' FUNC_ARGS
            | TYPE_SPECIFIER ID
            ;
STATEMENT: VAR_DEC ';'
            | BLOCK_STATEMENT ';'
            | ITERATION_STATEMENT ';'
            | CONTROL_STATEMENT ';'
            | ';'
            | RETURN_STATEMENT ';'
            | ASSIGNMENT_STATEMENT ';'
            | SIMPLE_STATEMENT ';'
            | BREAK_STATEMENT ';'
            | CONTINUE_STATEMENT ';'
            ;
ASSIGNMENT_STATEMENT: VAR_ACCESS_ID '=' SIMPLE_STATEMENT
            | VAR_ACCESS_ID '=' SIMPLE_STATEMENT ',' ASSIGNMENT_STATEMENT
            ;
VAR_ACCESS_ID: ID
            | ID '[' EXPR ']'
            | ID '[' EXPR ']' '[' EXPR ']'
            ;
SIMPLE_STATEMENT: EXPR
            | FUNC_CALL
            ;
BLOCK_STATEMENT: '{' VAR_DEC STMNT_LIST '}'
            | '{' STMNT_LIST '}'
            ;  
ITERATION_STATEMENT: FOR '(' EXPR ';' EXPR ';' EXPR ')' BLOCK_STATEMENT 
            | WHILE '(' EXPR ')' BLOCK_STATEMENT
            ;
CONTROL_STATEMENT: IF '(' EXPR ')' BLOCK_STATEMENT
            | IF '(' EXPR ')' BLOCK_STATEMENT ELSE BLOCK_STATEMENT
            | IF '(' EXPR ')' ELSE CONTROL_STATEMENT
            ;
FUNC_CALL: ID '(' PARAMS_LIST ')'
            ;
RETURN_STATEMENT: RETURN ID
            | RETURN CONST
            | RETURN
            ;
BREAK_STATEMENT: BREAK
            ;
CONTINUE_STATEMENT: CONTINUE
            ;
PARAMS_LIST: SIMPLE_STATEMENT ',' PARAMS_LIST
            | SIMPLE_STATEMENT
            ;
STMNT_LIST: STATEMENT STMNT_LIST
            | %empty
            ;
EXPR:       VAR_ACCESS_ID
            | CONST 
            | CONST BIN_OP EXPR
            | VAR_ACCESS_ID BIN_OP EXPR
            | '(' EXPR ')' 
            | UNARY_OP EXPR 
            | EXPR UNARY_OP 
            | TERNARY_EXPR
            ;
TERNARY_EXPR: EXPR '?' EXPR ':' EXPR
            ;
CONST:      NUM_CONST
            | CHAR_CONST
            ;
%%

int main(int, char**) {
  // open a file handle to a particular file:
  FILE *myfile = fopen("a.snazzle.file", "r");
  // make sure it's valid:
  if (!myfile) {
    cout << "I can't open a.snazzle.file!" << endl;
    return -1;
  }
  // Set lex to read from it instead of defaulting to STDIN:
  yyin = myfile;

  // Parse through the input:
  yyparse();
}

void yyerror(const char *s) {
  cout << "EEK, parse error!  Message: " << s << endl;
  // might as well halt now:
  exit(-1);
}