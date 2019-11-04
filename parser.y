%{
  #include <cstdio>
  #include <iostream>
  #include "PostFixVisitor.h"
  // #include "ast.h"
  using namespace std;

  // stuff from flex that bison needs to know about:
  extern int yylex();
  extern "C" int yyparse();
  extern FILE *yyin;
  extern int linenum;
  void yyerror(const char *s);
  class NumConstASTnode* start = NULL;
%}

%union {
  int ival;
  float fval;
  char *sval;
  ASTnode* ast;
  ProgramASTnode* program;
  DeclarationListASTnode* dec_list;
  DeclarationASTnode* dec;
  VarDecStatementASTnode* var_dec_stmnt;
  TypeSpecifierASTnode* type;
  VarDecListASTnode* var_dec;
  VarInitializeASTnode* var_initialize;
  VarInitializeSimpleASTnode* var_initialize_simple;
  VarInitializeComplexASTnode* var_initialize_complex;
  VarDecIDASTnode* var_dec_id;
  VarDecIDSimpleASTnode* var_dec_id_simple;
  VarDecID1dASTnode* var_dec_id_1d;
  VarDecID2dASTnode* var_dec_id_2d;
  FuncDecASTnode* func_dec;
  FunctionArgsASTnode* func_args;
  StatementASTnode* stmnt;
  AssignmentStatementASTnode* assignment_stmnt;
  VarAccessIdASTnode* var_access_id;
  SimpleStatementASTnode* simple_stmnt;
  BlockStatementASTnode* block_stmnt;
  IterationStatementASTnode* iteration_stmnt;
  ForStatementASTnode* for_stmnt;
  WhileStatementASTnode* while_stmnt;
  ControlStatementASTnode* control_stmnt;
  FuncCallASTnode* func_call;
  ReturnStatementASTnode* return_stmnt;
  BreakStatementASTnode* break_stmnt;
  ContinueStatementASTnode* continue_stmnt;
  StdinStatementASTnode* stdin_stmnt;
  StdoutStatementASTnode* stdout_stmnt;
  ParamsListASTnode* params_list_stmnt;
  StatementListASTnode* stmnt_list;
  ExprASTnode* expr;
  TernaryASTnode* ternary_expr;
  ConstASTnode* const_val;
  BinaryASTnode* binary_expr;
  UnaryASTnode* unary_expr;
  NumConstASTnode* num_const;
  CharConstASTnode* char_const;
  BoolConstASTnode* bool_const;
}
%define parse.error verbose

// define the constant-string tokens:
%token BREAK FOR IF RETURN TRUE FALSE VOID WHILE CONTINUE ELSE COUT CIN ENDL
%token INT CHAR BOOL UINT SINT
%token MULTI_COMMENT SINGLE_COMMENT LEFT_SHIFT RIGHT_SHIFT

// define the "terminal symbol" token types I'm going to use (in CAPS
// by convention), and associate each with a field of the union:
%token <num_const> NUM_CONST
%type <const_val> CONST
%type <ast> ast_node
%type <ternary_expr> TERNARY_EXPR
%type <program> PROGRAM
%type <DeclarationListASTnode> DECLARATION_LIST
%type <expr> EXPR

%token <sval> ID
%token <char_const> CHAR_CONST
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
TERNARY_EXPR: EXPR '?' EXPR ':' EXPR {$$ = new TernaryASTnode($1, $3, $5);}
            ;
CONST:      NUM_CONST {$$ = $1;}
            | CHAR_CONST {$$ = $1;}
            | TRUE {$$ = new BoolConstASTnode("TRUE");}
            | FALSE {$$ = new BoolConstASTnode("FALSE");}
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
	PostFixVisitor* dfs;
	dfs=new PostFixVisitor();
	start->accept(*dfs);
	printf("\nParsing Over\n");
}

void yyerror(const char *s) {
  cout << "EEK, parse error on line " << linenum << "!  Message: " << s << endl;
  // might as well halt now:
  exit(-1);
}