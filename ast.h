#ifndef _AST_H_
#define _AST_H_

#include "llvm/IR/Value.h"
#include <bits/stdc++.h>
using namespace std;
using namespace llvm;
class ProgramASTnode;
class DeclarationListASTnode;
class DeclarationASTnode;
class VarDecStatementASTnode;
class TypeSpecifierASTnode;
class VarDecListASTnode;
class VarInitializeASTnode;

class VarDecIDASTnode;

class FuncDecASTnode;
class FunctionArgsASTnode;
class StatementASTnode;
class AssignmentStatementASTnode;
class VarAccessIdASTnode;
class SimpleStatementASTnode;
class BlockStatementASTnode;
class IterationStatementASTnode;
class ForStatementASTnode;
class WhileStatementASTnode;
class ControlStatementASTnode;
class FuncCallASTnode;
class ReturnStatementASTnode;
class BreakStatementASTnode;
class ContinueStatementASTnode;
class StdinStatementASTnode;
class StdoutStatementASTnode;
class ParamsListASTnode;
class StatementListASTnode;

class ExprASTnode;
class EnclosedExprASTnode;
class TernaryASTnode;
class ConstASTnode;
class BinaryASTnode;
class UnaryASTnode;

class NumConstASTnode;
class CharConstASTnode;
class BoolConstASTnode;
class EmptyStatementASTnode;

class ASTvisitor
{
public:
	virtual void visit(BinaryASTnode &node) = 0;
	virtual void visit(TernaryASTnode &node) = 0;
	virtual void visit(ControlStatementASTnode &node) = 0;
	virtual void visit(BoolConstASTnode &node) = 0;
	virtual void visit(CharConstASTnode &node) = 0;
	virtual void visit(NumConstASTnode &node) = 0;
	virtual void visit(UnaryASTnode &node) = 0;
	virtual void visit(ConstASTnode &node) = 0;
	virtual void visit(ExprASTnode &node) = 0;
	virtual void visit(EnclosedExprASTnode &node) = 0;
	virtual void visit(StatementListASTnode &node) = 0;
	virtual void visit(ParamsListASTnode &node) = 0;
	virtual void visit(StdoutStatementASTnode &node) = 0;
	virtual void visit(StdinStatementASTnode &node) = 0;
	virtual void visit(ContinueStatementASTnode &node) = 0;
	virtual void visit(BreakStatementASTnode &node) = 0;
	virtual void visit(ReturnStatementASTnode &node) = 0;
	virtual void visit(FuncCallASTnode &node) = 0;
	virtual void visit(WhileStatementASTnode &node) = 0;
	virtual void visit(ForStatementASTnode &node) = 0;
	virtual void visit(IterationStatementASTnode &node) = 0;
	virtual void visit(BlockStatementASTnode &node) = 0;
	virtual void visit(SimpleStatementASTnode &node) = 0;
	virtual void visit(VarAccessIdASTnode &node) = 0;
	virtual void visit(AssignmentStatementASTnode &node) = 0;
	virtual void visit(StatementASTnode &node) = 0;
	virtual void visit(FunctionArgsASTnode &node) = 0;
	virtual void visit(FuncDecASTnode &node) = 0;
	virtual void visit(VarDecIDASTnode &node) = 0;
	virtual void visit(VarInitializeASTnode &node) = 0;
	virtual void visit(VarDecListASTnode &node) = 0;

	virtual void visit(TypeSpecifierASTnode &node) = 0;
	virtual void visit(VarDecStatementASTnode &node) = 0;
	virtual void visit(DeclarationASTnode &node) = 0;
	virtual void visit(DeclarationListASTnode &node) = 0;
	virtual void visit(ProgramASTnode &node) = 0;
	virtual void visit(EmptyStatementASTnode &node) = 0;
};

class CodeGenVisitor
{
public:
	virtual Value *codeGen(BinaryASTnode &node) = 0;
	virtual Value *codeGen(TernaryASTnode &node) = 0;
	virtual Value *codeGen(ControlStatementASTnode &node) = 0;
	virtual Value *codeGen(BoolConstASTnode &node) = 0;
	virtual Value *codeGen(CharConstASTnode &node) = 0;
	virtual Value *codeGen(NumConstASTnode &node) = 0;
	virtual Value *codeGen(UnaryASTnode &node) = 0;
	virtual Value *codeGen(ConstASTnode &node) = 0;
	virtual Value *codeGen(ExprASTnode &node) = 0;
	virtual Value *codeGen(EnclosedExprASTnode &node) = 0;
	virtual Value *codeGen(StatementListASTnode &node) = 0;
	virtual Value *codeGen(ParamsListASTnode &node) = 0;
	virtual Value *codeGen(StdoutStatementASTnode &node) = 0;
	virtual Value *codeGen(StdinStatementASTnode &node) = 0;
	virtual Value *codeGen(ContinueStatementASTnode &node) = 0;
	virtual Value *codeGen(BreakStatementASTnode &node) = 0;
	virtual Value *codeGen(ReturnStatementASTnode &node) = 0;
	virtual Value *codeGen(FuncCallASTnode &node) = 0;
	virtual Value *codeGen(WhileStatementASTnode &node) = 0;
	virtual Value *codeGen(ForStatementASTnode &node) = 0;
	virtual Value *codeGen(IterationStatementASTnode &node) = 0;
	virtual Value *codeGen(BlockStatementASTnode &node) = 0;
	virtual Value *codeGen(SimpleStatementASTnode &node) = 0;
	virtual Value *codeGen(VarAccessIdASTnode &node) = 0;
	virtual Value *codeGen(AssignmentStatementASTnode &node) = 0;
	virtual Value *codeGen(StatementASTnode &node) = 0;
	virtual Value *codeGen(FunctionArgsASTnode &node) = 0;
	virtual Value *codeGen(FuncDecASTnode &node) = 0;
	virtual Value *codeGen(VarDecIDASTnode &node) = 0;
	virtual Value *codeGen(VarInitializeASTnode &node) = 0;
	virtual Value *codeGen(VarDecListASTnode &node) = 0;

	virtual Value *codeGen(TypeSpecifierASTnode &node) = 0;
	virtual Value *codeGen(VarDecStatementASTnode &node) = 0;
	virtual Value *codeGen(DeclarationASTnode &node) = 0;
	virtual Value *codeGen(DeclarationListASTnode &node) = 0;
	virtual Value *codeGen(ProgramASTnode &node) = 0;
	virtual Value *codeGen(EmptyStatementASTnode &node) = 0;
};

class ASTnode
{
public:
	virtual ~ASTnode() {}

	//  virtual void printPostFix() const = 0;

	virtual void accept(ASTvisitor &V) = 0;
	virtual Value *codeGen(CodeGenVisitor &v) = 0;
};

// Program Start
class ProgramASTnode : public ASTnode
{
public:
	ASTnode *dec_list_item;
	virtual void accept(ASTvisitor &v) { v.visit(*this); }
	virtual Value *codeGen(CodeGenVisitor &v) { return v.codeGen(*this); }
	ASTnode *getDecListItem() { return dec_list_item; }
};

class DeclarationListASTnode : public ProgramASTnode
{
public:
	vector<ASTnode *> dec_list;
	void insert(ASTnode *dec_item) { dec_list.push_back(dec_item); }
	virtual void accept(ASTvisitor &v) { v.visit(*this); }
	virtual Value *codeGen(CodeGenVisitor &v) { return v.codeGen(*this); }
	vector<ASTnode *> &getDecList() { return dec_list; }
};

class DeclarationASTnode : public ASTnode
{
public:
	ASTnode *decl_item;
	string type;
	DeclarationASTnode(ASTnode *decl_item) : decl_item(decl_item) {}
	DeclarationASTnode(ASTnode *decl_item, string type_) : decl_item(decl_item), type(type_) {}
	virtual void accept(ASTvisitor &v) { v.visit(*this); }
	virtual Value *codeGen(CodeGenVisitor &v) { return v.codeGen(*this); }
	ASTnode *getDecItem() { return decl_item; }
	string getType() { return type; }
};

class TypeSpecifierASTnode : public ASTnode
{
public:
	string type;
	TypeSpecifierASTnode(string type) : type(type) {}
	virtual void accept(ASTvisitor &v) { v.visit(*this); }
	virtual Value *codeGen(CodeGenVisitor &v) { return v.codeGen(*this); }
	string getType() { return type; }
};

class VarDecListASTnode : public ASTnode
{
public:
	vector<ASTnode *> var_initialize_list;
	void insert(ASTnode *var_initialize)
	{
		var_initialize_list.push_back(var_initialize);
	}
	virtual void accept(ASTvisitor &v) { v.visit(*this); }
	virtual Value *codeGen(CodeGenVisitor &v) { return v.codeGen(*this); }
	vector<ASTnode *> &getVarInitList() { return var_initialize_list; }
};

enum INITIALIZE_TYPE
{
	INITIALIZE_SIMPLE = 0,
	INITIALIZE_COMPLEX = 1
};
class VarInitializeASTnode : public ASTnode
{
public:
	INITIALIZE_TYPE initialize_type;
	ASTnode *var_dec_id_item;
	ASTnode *simple_stmnt_item;
	VarInitializeASTnode(ASTnode *var_dec_id, ASTnode *simple_stmnt = nullptr)
		: var_dec_id_item(var_dec_id), simple_stmnt_item(simple_stmnt)
	{
		if (simple_stmnt)
			initialize_type = ::INITIALIZE_COMPLEX;
		else
			initialize_type = ::INITIALIZE_SIMPLE;
	}
	virtual void accept(ASTvisitor &v) { v.visit(*this); }
	virtual Value *codeGen(CodeGenVisitor &v) { return v.codeGen(*this); }
	INITIALIZE_TYPE getInitializeType() { return initialize_type; }
	ASTnode *getVarDecID() { return var_dec_id_item; }
	ASTnode *getSimpleStmnt() { return simple_stmnt_item; }
};

class VarDecIDASTnode : public ASTnode
{
public:
	string id;
	vector<ASTnode *> dims_size_list;
	VarDecIDASTnode(string var_id) : id(var_id) {}
	void insert(ASTnode *dim) { dims_size_list.push_back(dim); }
	virtual void accept(ASTvisitor &v) { v.visit(*this); }
	virtual Value *codeGen(CodeGenVisitor &v) { return v.codeGen(*this); }
	string getID() { return id; }
	vector<ASTnode *> &getDimsSizeList() { return dims_size_list; }
};

class FuncDecASTnode : public ASTnode
{
public:
	ASTnode *type_specifier_item;
	string id;
	ASTnode *func_args_item;
	ASTnode *block_stmnt_item;
	FuncDecASTnode(ASTnode *type_specifier_item, string id,
				   ASTnode *func_args_item, ASTnode *block_stmnt_item)
		: type_specifier_item(type_specifier_item), id(id),
		  func_args_item(func_args_item), block_stmnt_item(block_stmnt_item) {}
	virtual void accept(ASTvisitor &v) { v.visit(*this); }
	virtual Value *codeGen(CodeGenVisitor &v) { return v.codeGen(*this); }
	ASTnode *getTypeSpecifier() { return type_specifier_item; }
	string getID() { return id; }
	ASTnode *getFuncArgs() { return func_args_item; }
	ASTnode *getBlockStmnt() { return block_stmnt_item; }
};

class FunctionArgsASTnode : public ASTnode
{
public:
	vector<pair<ASTnode *, string>> func_arg_list;
	void insert(ASTnode *type_, string var_id)
	{
		func_arg_list.push_back(make_pair(type_, var_id));
	}
	virtual void accept(ASTvisitor &v) { v.visit(*this); }
	virtual Value *codeGen(CodeGenVisitor &v) { return v.codeGen(*this); }
	vector<pair<ASTnode *, string>> &getFuncArgsList() { return func_arg_list; }
};

enum STATEMENT_TYPE
{
	EMPTY_STATEMENT,
	BLOCK_STATEMENT,
	ITERATION_STATEMENT,
	CONTROL_STATEMENT,
	RETURN_STATEMENT,
	ASSIGNMENT_STATEMENT,
	VAR_DEC_STATEMENT,
	SIMPLE_STATEMENT,
	BREAK_STATEMENT,
	CONTINUE_STATEMENT,
	STDIN_STATEMENT,
	STDOUT_STATEMENT,
};
class StatementASTnode : public ASTnode
{
};

class EmptyStatementASTnode : public StatementASTnode
{
public:
	virtual void accept(ASTvisitor &v) { v.visit(*this); }
	virtual Value *codeGen(CodeGenVisitor &v) { return v.codeGen(*this); }
};

class BlockStatementASTnode : public StatementASTnode
{
public:
	ASTnode *stmnt_list_item;
	BlockStatementASTnode(ASTnode *stmnt_list_item_)
		: stmnt_list_item(stmnt_list_item_) {}
	virtual void accept(ASTvisitor &v) { v.visit(*this); }
	virtual Value *codeGen(CodeGenVisitor &v) { return v.codeGen(*this); }
	ASTnode *getStmntListItem() { return stmnt_list_item; }
};

// enum ITERATION_STATEMENT_TYPE
// {
//     FOR,
//     WHILE
// };
class IterationStatementASTnode : public StatementASTnode
{
};

class ForStatementASTnode : public IterationStatementASTnode
{
public:
	ASTnode *start_stmnt;
	ASTnode *loop_condition;
	ASTnode *end_stmnt;
	ASTnode *loop_body;
	ForStatementASTnode(ASTnode *start_stmnt, ASTnode *loop_cond,
						ASTnode *end_stmnt, ASTnode *loop_body)
		: start_stmnt(start_stmnt), loop_condition(loop_cond),
		  end_stmnt(end_stmnt), loop_body(loop_body) {}
	virtual void accept(ASTvisitor &v) { v.visit(*this); }
	virtual Value *codeGen(CodeGenVisitor &v) { return v.codeGen(*this); }
	ASTnode *getStartStmnt() { return start_stmnt; }
	ASTnode *getloopCond() { return loop_condition; }
	ASTnode *getEndStmnt() { return end_stmnt; }
	ASTnode *getloopBody() { return loop_body; }
};

class WhileStatementASTnode : public IterationStatementASTnode
{
public:
	ASTnode *loop_condition;
	ASTnode *loop_body;
	WhileStatementASTnode(ASTnode *loop_cond, ASTnode *loop_body)
		: loop_condition(loop_cond), loop_body(loop_body) {}
	virtual void accept(ASTvisitor &v) { v.visit(*this); }
	virtual Value *codeGen(CodeGenVisitor &v) { return v.codeGen(*this); }
	ASTnode *getloopCond() { return loop_condition; }
	ASTnode *getloopBody() { return loop_body; }
};

enum CONTROL_STATEMENT_TYPE
{
	IF_ONLY,
	IF_ELSE
};
class ControlStatementASTnode : public StatementASTnode
{
public:
	CONTROL_STATEMENT_TYPE stmnt_type;
	ASTnode *if_expr;
	ASTnode *if_body;
	ASTnode *else_body;
	ControlStatementASTnode(ASTnode *if_expr_, ASTnode *if_body_,
							ASTnode *else_body_ = NULL)
		: if_expr(if_expr_), if_body(if_body_), else_body(else_body_)
	{
		if (else_body_)
			stmnt_type = ::IF_ELSE;
		else
			stmnt_type = ::IF_ONLY;
	}
	ASTnode *getIfExpr() { return if_expr; }
	ASTnode *getIfBody() { return if_body; }
	ASTnode *getElseBody() { return else_body; }
	virtual void accept(ASTvisitor &v) { v.visit(*this); }
	virtual Value *codeGen(CodeGenVisitor &v) { return v.codeGen(*this); }
};

class ReturnStatementASTnode : public StatementASTnode
{
public:
	bool is_empty;
	ASTnode *return_item;
	ReturnStatementASTnode()
	{
		is_empty = true;
	}
	ReturnStatementASTnode(ASTnode *const_item) : return_item(const_item)
	{
		is_empty = false;
	}
	virtual void accept(ASTvisitor &v) { v.visit(*this); }
	virtual Value *codeGen(CodeGenVisitor &v) { return v.codeGen(*this); }
	bool checkIsEmpty() { return is_empty; }
	ASTnode *getReturnItem() { return return_item; }
};

class AssignmentStatementASTnode : public StatementASTnode
{
public:
	vector<pair<ASTnode *, ASTnode *>> assign_stmnt_list;
	void insert(ASTnode *access_id, ASTnode *simple_stmnt)
	{
		assign_stmnt_list.push_back(make_pair(access_id, simple_stmnt));
	}
	virtual void accept(ASTvisitor &v) { v.visit(*this); }
	virtual Value *codeGen(CodeGenVisitor &v) { return v.codeGen(*this); }
	vector<pair<ASTnode *, ASTnode *>> &getAssignmentStmntList()
	{
		return assign_stmnt_list;
	}
};

class VarDecStatementASTnode : public StatementASTnode
{
public:
	ASTnode *type_specifier_item;
	ASTnode *var_dec_list_item;
	VarDecStatementASTnode(ASTnode *type_, ASTnode *var_dec_list)
		: type_specifier_item(type_), var_dec_list_item(var_dec_list) {}
	virtual void accept(ASTvisitor &v) { v.visit(*this); }
	virtual Value *codeGen(CodeGenVisitor &v) { return v.codeGen(*this); }
	ASTnode *getTypeSpecifier() { return type_specifier_item; }
	ASTnode *getVarDecListItem() { return var_dec_list_item; }
};

enum SIMPLE_STATEMENT_TYPE
{
	EXPR,
	FUNC_CALL
};
class SimpleStatementASTnode : public StatementASTnode
{
	// public:
	// SIMPLE_STATEMENT_TYPE stmnt_type;
	// ASTnode* stmnt_item;
};

class FuncCallASTnode : public SimpleStatementASTnode
{
public:
	string func_id;
	ASTnode
		*params_list_item; // do we need this or can we replace this with a list?
	FuncCallASTnode(string id, ASTnode *params_list_item)
		: func_id(id), params_list_item(params_list_item) {}
	virtual void accept(ASTvisitor &v) { v.visit(*this); }
	virtual Value *codeGen(CodeGenVisitor &v) { return v.codeGen(*this); }
	string getFuncID() { return func_id; }
	ASTnode *getParamsListItem() { return params_list_item; }
};

class BreakStatementASTnode : public StatementASTnode
{
public:
	virtual void accept(ASTvisitor &v) { v.visit(*this); }
	virtual Value *codeGen(CodeGenVisitor &v) { return v.codeGen(*this); }
};

class ContinueStatementASTnode : public StatementASTnode
{
public:
	virtual void accept(ASTvisitor &v) { v.visit(*this); }
	virtual Value *codeGen(CodeGenVisitor &v) { return v.codeGen(*this); }
};

class StdinStatementASTnode : public StatementASTnode
{
public:
	ASTnode *expr_item;
	StdinStatementASTnode(ASTnode *expr_item_) : expr_item(expr_item_) {}
	virtual void accept(ASTvisitor &v) { v.visit(*this); }
	virtual Value *codeGen(CodeGenVisitor &v) { return v.codeGen(*this); }
	ASTnode *getExprItem() { return expr_item; }
};

class StdoutStatementASTnode : public StatementASTnode
{
public:
	ASTnode *expr_item;
	StdoutStatementASTnode(ASTnode *expr_item_) : expr_item(expr_item_) {}
	virtual void accept(ASTvisitor &v) { v.visit(*this); }
	virtual Value *codeGen(CodeGenVisitor &v) { return v.codeGen(*this); }
	ASTnode *getExprItem() { return expr_item; }
};

class ParamsListASTnode : public ASTnode
{
public:
	vector<ASTnode *> simple_stmnt_list;
	void insert(ASTnode *simple_stmnt)
	{
		simple_stmnt_list.push_back(simple_stmnt);
	}
	virtual void accept(ASTvisitor &v) { v.visit(*this); }
	virtual Value *codeGen(CodeGenVisitor &v) { return v.codeGen(*this); }
	vector<ASTnode *> &getSimpleStmntList() { return simple_stmnt_list; }
};

class StatementListASTnode : public ASTnode
{
public:
	vector<ASTnode *> stmnt_list;
	void insert(ASTnode *stmnt) { this->stmnt_list.push_back(stmnt); }
	virtual void accept(ASTvisitor &v) { v.visit(*this); }
	virtual Value *codeGen(CodeGenVisitor &v) { return v.codeGen(*this); }
	vector<ASTnode *> &getStmntList() { return stmnt_list; }
};

class ExprASTnode : public SimpleStatementASTnode
{
	// public:
	// enum EXPR_TYPE{
	//     ID,
	//     CONST,
	//     BIN_OP,
	//     UNI_OP,
	//     TERNARY_OP,
	// };
	// enum EXPR_TYPE expr_type_item;
	// ASTnode* expr_item;
};

class EnclosedExprASTnode : public ExprASTnode
{
public:
	ExprASTnode *expr_item;
	EnclosedExprASTnode(ExprASTnode *expr) : expr_item(expr){};
	virtual void accept(ASTvisitor &v) { v.visit(*this); }
	virtual Value *codeGen(CodeGenVisitor &v) { return v.codeGen(*this); }
	ExprASTnode *getExprItem() { return expr_item; }
};

// enum BIN_OP_TYPE
// {
// 	PLUS,
// 	MINUS,
// 	MULT,
// 	DIV,
// 	AND,
// 	OR,
// 	XOR,
// 	COMP,
// 	NE,
// 	LT_E,
// 	GT_E,
// 	LT,
// 	GT,
// 	MOD
// };
class VarAccessIdASTnode : public ExprASTnode
{
public:
	string id;
	vector<ASTnode *> dims_val_list;
	VarAccessIdASTnode(string id) : id(id){};
	virtual void accept(ASTvisitor &v) { v.visit(*this); }
	virtual Value *codeGen(CodeGenVisitor &v) { return v.codeGen(*this); }
	string getID() { return id; }
	vector<ASTnode *> &getDimsValList() { return dims_val_list; }
};

class BinaryASTnode : public ExprASTnode
{
	string bin_operator;

	// lhs and rhs can be of any type.
	// So we need to use BaseAST

public:
	// BIN_OP_TYPE op_type_item;
	ASTnode *left;
	ASTnode *right;
	// Constructor to initialize binary operator,
	// lhs and rhs of the binary expression.
	BinaryASTnode(std::string op, ASTnode *_left, ASTnode *_right)
		: bin_operator(op), left(_left), right(_right) {}

	/*  virtual void printPostFix() const
{
  lhs->printPostFix();
  rhs->printPostFix();
  std::cout << bin_operator << " ";
} */

	ASTnode *getLeft() { return left; }

	ASTnode *getRight() { return right; }

	std::string getBin_operator() { return bin_operator; }
	virtual void accept(ASTvisitor &v) { v.visit(*this); }
	virtual Value *codeGen(CodeGenVisitor &v) { return v.codeGen(*this); }
};

// enum UNI_OP_TYPE
// {
// 	NOT,
// 	MINUS_UNI,
// };
class UnaryASTnode : public ExprASTnode
{

public:
	// enum OP_TYPE op_type_item;
	string op_type;
	ASTnode *expr_item;
	UnaryASTnode(string op_type, ASTnode *expr_item_)
		: op_type(op_type), expr_item(expr_item_) {}
	virtual void accept(ASTvisitor &v) { v.visit(*this); }
	virtual Value *codeGen(CodeGenVisitor &v) { return v.codeGen(*this); }
	string getOpType() { return op_type; }
	ASTnode *getExprItem() { return expr_item; }
};

class TernaryASTnode : public ExprASTnode
{

	ASTnode *first;
	ASTnode *second;
	ASTnode *third;

public:
	TernaryASTnode(ASTnode *first, ASTnode *second, ASTnode *third)
		: first(first), second(second), third(third) {}

	/*   virtual void printPostFix() const
{
  first->printPostFix();
  second->printPostFix();
  third->printPostFix();
  std::cout << "? " << std::endl;
}  */

	ASTnode *getFirst() { return first; }

	ASTnode *getSecond() { return second; }

	ASTnode *getThird() { return third; }

	virtual void accept(ASTvisitor &v) { v.visit(*this); }
	virtual Value *codeGen(CodeGenVisitor &v) { return v.codeGen(*this); }
};

enum CONST_TYPE
{
	BOOL_CONST,
	INT_CONST,
	STRING_CONST
};
class ConstASTnode : public ExprASTnode
{
public:
	CONST_TYPE type;
	ConstASTnode(CONST_TYPE type) : type(type){};

	virtual int getValue() { return -1; };

	int getLitType() { return type; };

	virtual void accept(ASTvisitor &v) { v.visit(*this); }
	virtual Value *codeGen(CodeGenVisitor &v) { return v.codeGen(*this); }
};

class NumConstASTnode : public ConstASTnode
{
	int intlit;

public:
	NumConstASTnode(int intlit_) : intlit(intlit_), ConstASTnode(::INT_CONST) {}

	int getIntLit() { return intlit; }

	virtual void accept(ASTvisitor &v) { v.visit(*this); }
	virtual Value *codeGen(CodeGenVisitor &v) { return v.codeGen(*this); }

	// virtual void printPostFix() const
	// {
	// 	std::cout << intlit << " ";
	// }
};

class CharConstASTnode : public ConstASTnode
{
public:
	string charlit;
	CharConstASTnode(string charlit)
		: charlit(charlit), ConstASTnode(::STRING_CONST)
	{
		this->charlit = charlit.substr(1, charlit.size() - 2);
		while (this->charlit.find("\\n") != string::npos)
		{
			this->charlit = this->charlit.replace(this->charlit.find("\\n"), 2, "\n");
		}
	}

	string getCharConst() { return charlit; }

	virtual void accept(ASTvisitor &v) { v.visit(*this); }
	virtual Value *codeGen(CodeGenVisitor &v) { return v.codeGen(*this); }

	/* virtual void printPostFix() const
  {
          std::cout << intlit << " " ;
  } */
};

class BoolConstASTnode : public ConstASTnode
{
public:
	string bool_type;
	BoolConstASTnode(string type_)
		: bool_type(type_), ConstASTnode(::BOOL_CONST) {}
	virtual void accept(ASTvisitor &v) { v.visit(*this); }
	virtual Value *codeGen(CodeGenVisitor &v) { return v.codeGen(*this); }
	string getBoolConst() { return bool_type; }
};

class ASTContext
{
public:
	ASTnode *root;

	~ASTContext() { clearAST(); }

	/// free all saved expression trees
	void clearAST() { delete root; }
};
#endif