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
  class ProgramASTnode* start = NULL;
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
  VarDecListASTnode* var_dec_list;
  VarInitializeASTnode* var_initialize;
  VarDecIDASTnode* var_dec_id;
  FuncDecASTnode* func_dec;
  FunctionArgsASTnode* func_args;
  StatementASTnode* stmnt;
  AssignmentStatementASTnode* assignment_stmnt;
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
  ParamsListASTnode* params_list;
  StatementListASTnode* stmnt_list;
  ExprASTnode* expr;
  EnclosedExprASTnode* enclosed_expr;
  VarAccessIdASTnode* var_access_id;
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
%type <ast> ast_node
%type <ternary_expr> TERNARY_EXPR
// %type <binary_expr> TERNARY_EXPR
// %type <unary_expr> TERNARY_EXPR
%type <const_val> CONST
%type <var_access_id> VAR_ACCESS_ID
%type <stmnt_list> STMNT_LIST
%type <expr> EXPR
%type <stdin_stmnt> STDIN_STATEMENT
%type <stdout_stmnt> STDOUT_STATEMENT
%type <continue_stmnt> CONTINUE_STATEMENT
%type <break_stmnt> BREAK_STATEMENT
%type <return_stmnt>  RETURN_STATEMENT
%type <control_stmnt> CONTROL_STATEMENT
%type <block_stmnt> BLOCK_STATEMENT
%type <for_stmnt> FOR_STATEMENT
%type <while_stmnt> WHILE_STATEMENT
%type <assignment_stmnt> ASSIGNMENT_STATEMENT
%type <iteration_stmnt> ITERATION_STATEMENT
%type <params_list> PARAMS_LIST
%type <simple_stmnt> SIMPLE_STATEMENT
%type <func_call> FUNC_CALL
%type <stmnt> STATEMENT
%type <var_dec_stmnt> VAR_DEC_STATEMENT
%type <func_args> FUNC_ARGS
%type <type> TYPE_SPECIFIER
%type <func_dec> FUNC_DEC
%type <var_dec_id> VAR_DEC_ID
%type <var_initialize> VAR_INITIALIZE
%type <var_dec_list> VAR_DEC_LIST
%type <dec> DECLARATION
%type <dec_list> DECLARATION_LIST
%type <program> PROGRAM

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
PROGRAM: DECLARATION_LIST {$$ = $1; start=$$;}
        ;
DECLARATION_LIST: DECLARATION_LIST  DECLARATION {$$->insert($2);}
                    | DECLARATION {$$ = new DeclarationListASTnode();
                      $$->insert($1);
                    }
                ;
DECLARATION: FUNC_DEC {$$ = $1}
            | VAR_DEC_STATEMENT ';' {$$ = $1}
            ;
VAR_DEC_STATEMENT:  TYPE_SPECIFIER VAR_DEC_LIST {$$ = new VarDecStatementASTnode($1, $2);}
            ;
TYPE_SPECIFIER: INT {$$ = new TypeSpecifierASTnode("INT");}
            | BOOL {$$ = new TypeSpecifierASTnode("BOOL");}
            | CHAR {$$ = new TypeSpecifierASTnode("CHAR");}
            | SINT {$$ = new TypeSpecifierASTnode("SINT");}
            | UINT {$$ = new TypeSpecifierASTnode("UINT");}
            | VOID {$$ = new TypeSpecifierASTnode("VOID");}
            ;
VAR_DEC_LIST: VAR_DEC_LIST ',' VAR_INITIALIZE {$$->insert($3);}
            | VAR_INITIALIZE {$$ = new VarDecListASTnode();
                $$->insert($1);
              }
            ;
VAR_INITIALIZE: VAR_DEC_ID {$$ = new VarInitializeASTnode($1);}
            | VAR_DEC_ID '=' SIMPLE_STATEMENT {$$ = new VarInitializeASTnode($1, $3);}
            ;
VAR_DEC_ID: ID '[' NUM_CONST ']' {$$ = new VarDecIDASTnode($1);
                $$->insert($3);
              }
            | ID {$$ = new VarDecIDASTnode($1);
              }
            | ID '[' NUM_CONST ']' '[' NUM_CONST ']' {$$ = new VarDecIDASTnode($1);
                $$->insert($3);
                $$->insert($6);
              }
            ;
FUNC_DEC:   TYPE_SPECIFIER ID '(' FUNC_ARGS ')' BLOCK_STATEMENT {$$ = new FuncDecASTnode($1, $2, $4, $6);}
            ;
FUNC_ARGS: FUNC_ARGS ',' TYPE_SPECIFIER ID {$$->insert($3, $4);}
            | TYPE_SPECIFIER ID {
              $$ = new FunctionArgsASTnode();
              $$->insert($1, $2);
              }
            | %empty {$$ = new FunctionArgsASTnode();}
            ;
STATEMENT: BLOCK_STATEMENT ';' {$$ = $1;}
            | ITERATION_STATEMENT ';' {$$ = $1;}
            | CONTROL_STATEMENT ';' {$$ = $1;}
            | ';' {$$ = new EmptyStatementASTnode();}
            | RETURN_STATEMENT ';' {$$ = $1;}
            | ASSIGNMENT_STATEMENT ';' {$$ = $1;}
            | VAR_DEC_STATEMENT ';' {$$ = $1;}
            | SIMPLE_STATEMENT ';' {$$ = $1;}
            | BREAK_STATEMENT ';' {$$ = $1;}
            | CONTINUE_STATEMENT ';' {$$ = $1;}
            | STDIN_STATEMENT ';' {$$ = $1;}
            | STDOUT_STATEMENT ';' {$$ = $1;}
            ;
ASSIGNMENT_STATEMENT: VAR_ACCESS_ID '=' SIMPLE_STATEMENT {$$ = new AssignmentStatementASTnode();
                  $$->insert($1, $3);
              }
            | ASSIGNMENT_STATEMENT ',' VAR_ACCESS_ID '=' SIMPLE_STATEMENT {$$->insert($3, $5);}
            ;
SIMPLE_STATEMENT: EXPR {$$ = $1;}
            | FUNC_CALL {$$ = $1;}
            ;
FUNC_CALL: ID '(' PARAMS_LIST ')' {$$ = new FuncCallASTnode($1, $3);}
            ;
PARAMS_LIST: PARAMS_LIST ',' SIMPLE_STATEMENT {$$->insert($3);}
            | SIMPLE_STATEMENT  {$$ = new ParamsListASTnode(); $$->insert($1);}
BLOCK_STATEMENT:  '{' STMNT_LIST '}' {$$ = new BlockStatementASTnode($2);}
            ;  
ITERATION_STATEMENT: FOR_STATEMENT {$$ = $1;}
            | WHILE_STATEMENT {$$ = $1;}
            ;
FOR_STATEMENT: FOR '(' ASSIGNMENT_STATEMENT ';' EXPR ';' ASSIGNMENT_STATEMENT ')' BLOCK_STATEMENT {
                $$ = new ForStatementASTnode($3, $5, $7, $9);
              }
            ;
WHILE_STATEMENT: WHILE '(' EXPR ')' BLOCK_STATEMENT {$$ = new WhileStatementASTnode($3, $5);}
            ;
CONTROL_STATEMENT: IF '(' EXPR ')' BLOCK_STATEMENT {$$ = new ControlStatementASTnode($3, $5);}
            | IF '(' EXPR ')' BLOCK_STATEMENT ELSE BLOCK_STATEMENT {$$ = new ControlStatementASTnode($3, $5, $7);}
            ;
RETURN_STATEMENT: RETURN ID {$$ = new ReturnStatementASTnode($2);}
            | RETURN {$$ = new ReturnStatementASTnode();}
            | RETURN CONST{$$ = new ReturnStatementASTnode($2);}
            ;
BREAK_STATEMENT: BREAK {$$ = new BreakStatementASTnode();}
            ;
CONTINUE_STATEMENT: CONTINUE {$$ = new ContinueStatementASTnode();}
            ;
STDIN_STATEMENT: CIN RIGHT_SHIFT EXPR {$$ = new StdinStatementASTnode($3);}
            ;
STDOUT_STATEMENT: COUT LEFT_SHIFT EXPR {$$ = new StdoutStatementASTnode($3);}
            ;
            ;
STMNT_LIST: STMNT_LIST STATEMENT {$$->insert($2);}
            | %empty  {$$ = new StatementListASTnode();}
            ;
EXPR:       VAR_ACCESS_ID {$$ = $1;}
            | CONST {$$ = $1;}
            | EXPR BIN_OP EXPR {$$ = new BinaryASTnode($2, $1, $3);}
            | '(' EXPR ')' {$$ = new EnclosedExprASTnode($2);}
            | UNARY_OP EXPR {$$ = new UnaryASTnode($1, $2);}
            | TERNARY_EXPR {$$ = $1;}
            ;
VAR_ACCESS_ID: ID {$$ = new VarAccessIdASTnode($1);
            }
            | ID '[' EXPR ']' {$$ = new VarAccessIdASTnode($1);
                $$->dims_val_list.push_back($3);
            }
            | ID '[' EXPR ']' '[' EXPR ']' {$$ = new VarAccessIdASTnode($1);
                $$->dims_val_list.push_back($3);
                $$->dims_val_list.push_back($6);
            }
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