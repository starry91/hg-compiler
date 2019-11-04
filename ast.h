#include <bits/stdc++.h>

using namespace std;

class ProgramASTnode;
class DeclarationListASTnode;
class DeclarationASTnode;
class VarDecStatementASTnode;
class TypeSpecifierASTnode;
class VarDecListASTnode;
class VarInitializeASTnode;
class VarInitializeSimpleASTnode;
class VarInitializeComplexASTnode;

class VarDecIDASTnode;
class VarDecIDSimpleASTnode;
class VarDecID1dASTnode;
class VarDecID2dASTnode;

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
class TernaryASTnode;
class ConstASTnode;
class BinaryASTnode;
class UnaryASTnode;

class NumConstASTnode;
class CharConstASTnode;
class BoolConstASTnode;

class ASTvisitor
{
public:
	virtual void visit(BinaryASTnode &node) = 0;
	virtual void visit(TernaryASTnode &node) = 0;
	virtual void visit(BoolConstASTnode &node) = 0;
	virtual void visit(CharConstASTnode &node) = 0;
	virtual void visit(NumConstASTnode &node) = 0;
	virtual void visit(UnaryASTnode &node) = 0;
	virtual void visit(ConstASTnode &node) = 0;
	virtual void visit(ExprASTnode &node) = 0;
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
	virtual void visit(VarDecID2dASTnode &node) = 0;
	virtual void visit(VarDecID1dASTnode &node) = 0;
	virtual void visit(VarDecIDSimpleASTnode &node) = 0;
	virtual void visit(VarDecIDASTnode &node) = 0;
	virtual void visit(VarInitializeComplexASTnode &node) = 0;
	virtual void visit(VarInitializeSimpleASTnode &node) = 0;
	virtual void visit(VarInitializeASTnode &node) = 0;
	virtual void visit(VarDecListASTnode &node) = 0;

	virtual void visit(TypeSpecifierASTnode &node) = 0;
	virtual void visit(VarDecStatementASTnode &node) = 0;
	virtual void visit(DeclarationASTnode &node) = 0;
	virtual void visit(DeclarationListASTnode &node) = 0;
	virtual void visit(ProgramASTnode &node) = 0;
};

class ASTnode
{
public:
	virtual ~ASTnode()
	{
	}

	//  virtual void printPostFix() const = 0;

	virtual void accept(ASTvisitor &V) = 0;
};

//Program Start
class ProgramASTnode : public ASTnode
{
public:
	ASTnode *dec_list_item;
};

class DeclarationListASTnode : public ASTnode
{
public:
	vector<ASTnode *> dec_list;
};

class DeclarationASTnode : public ASTnode
{
};

class TypeSpecifierASTnode : public ASTnode
{
public:
	string type;
};

class VarDecListASTnode : public ASTnode
{
public:
	vector<ASTnode *> var_initialize_list;
};

enum INITIALIZE_TYPE
{
	SIMPLE = 0,
	COMPLEX = 1
};
class VarInitializeASTnode : public ASTnode
{
public:
	INITIALIZE_TYPE initialize_type;
	ASTnode *var_dec_id_item;
	ASTnode *simple_stmnt_item;
};

class VarDecIDASTnode : public ASTnode
{
public:
	string id;
	vector<NumConstASTnode *> dims_size_list;
};

class FuncDecASTnode : public ASTnode
{
public:
	ASTnode *type_specifier_item;
	string id;
	ASTnode *func_args_item;
	ASTnode *block_stmnt_item;
};

class FunctionArgsASTnode : public ASTnode
{
public:
	vector<pair<ASTnode *, ASTnode *>> func_arg_list;
};

enum STATEMENT_TYPE
{
	EMPTY,
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
public:
	// STATEMENT_TYPE stmnt_type;
	// ASTnode* stmnt_item;
};

class BlockStatementASTnode : public ASTnode
{
public:
	ASTnode *stmnt_list_item;
};

// enum ITERATION_STATEMENT_TYPE
// {
//     FOR,
//     WHILE
// };
class IterationStatementASTnode : public ASTnode
{
public:
	// ITERATION_STATEMENT_TYPE stmnt_type;
	// IterationStatementASTnode* iteration_stmnt_item;
};

class ForStatementASTnode : public ASTnode
{
public:
	ASTnode *start_stmnt;
	ASTnode *loop_condition;
	ASTnode *end_stmnt;
	ASTnode *loop_body;
};

class WhileStatementASTnode : public ASTnode
{
public:
	ASTnode *loop_condition;
	ASTnode *loop_body;
};

enum CONTROL_STATEMENT_TYPE
{
	IF_ONLY,
	IF_ELSE
};
class ControlStatementASTnode : public ASTnode
{
public:
	CONTROL_STATEMENT_TYPE stmnt_type;
	ASTnode *if_expr;
	ASTnode *if_body;
	ASTnode *else_body;
};

class ReturnStatementASTnode : public ASTnode
{
public:
	bool is_empty;
	string id;
};

class AssignmentStatementASTnode : public ASTnode
{
public:
	vector<pair<ASTnode *, ASTnode *>> assign_stmnt_list;
};

class VarDecStatementASTnode : public ASTnode
{
public:
	ASTnode *type_specifier_item;
	ASTnode *var_dec_list_item;
};

enum SIMPLE_STATEMENT_TYPE
{
	EXPR,
	FUNC_CALL
};
class SimpleStatementASTnode : public ASTnode
{
	// public:
	// SIMPLE_STATEMENT_TYPE stmnt_type;
	// ASTnode* stmnt_item;
};

class BreakStatementASTnode : public ASTnode
{
};

class ContinueStatementASTnode : public ASTnode
{
};

class StdinStatementASTnode : public ASTnode
{
public:
	ASTnode *expr_item;
};

class StdoutStatementASTnode : public ASTnode
{
public:
	ASTnode *expr_item;
};

class VarAccessIdASTnode : public ASTnode
{
public:
	string id;
	vector<ASTnode *> dims_val_list;
};

class FuncCallASTnode : public ASTnode
{
public:
	string id;
	ASTnode *params_list_item; //do we need this or can we replace this with a list?
};

class ParamsListASTnode : public ASTnode
{
public:
	vector<ASTnode *> simple_stmnt_list;
};

class StatementListASTnode : public ASTnode
{
public:
	vector<ASTnode *> stmnt_list;
};

class ExprASTnode : public ASTnode
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
	BinaryASTnode(std::string op, ASTnode *_left, ASTnode *_right) : bin_operator(op), left(_left), right(_right) {}

	/*  virtual void printPostFix() const 
     {
     	lhs->printPostFix();
     	rhs->printPostFix();
     	std::cout << bin_operator << " "; 
     } */

	ASTnode *getLeft()
	{
		return left;
	}

	ASTnode *getRight()
	{
		return right;
	}

	std::string getBin_operator()
	{
		return bin_operator;
	}
	virtual void accept(ASTvisitor &v)
	{
	    v.visit(*this);
	}
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
	UnaryASTnode(ASTnode * expr_item_) : expr_item(expr_item_) {}
	virtual void accept(ASTvisitor &v)
	{
	    v.visit(*this);
	}
};

class TernaryASTnode : public ExprASTnode
{

	ASTnode *first;
	ASTnode *second;
	ASTnode *third;

public:
	TernaryASTnode(ASTnode *first, ASTnode *second, ASTnode *third) : first(first), second(second), third(third) {}

	/*   virtual void printPostFix() const
     {
     	first->printPostFix();
     	second->printPostFix();
     	third->printPostFix();
     	std::cout << "? " << std::endl; 
     }  */

	ASTnode *getFirst()
	{
		return first;
	}

	ASTnode *getSecond()
	{
		return second;
	}

	ASTnode *getThird()
	{
		return third;
	}

	virtual void accept(ASTvisitor &v)
	{
	    v.visit(*this);
	}
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
    ConstASTnode(CONST_TYPE type) : type(type) {};

    virtual int getValue() {return -1;};
    
    int getLitType() {return type;};

    virtual void accept(ASTvisitor& v)
    {
      v.visit(*this);
    }
};

class NumConstASTnode : public ConstASTnode
{
	int intlit;

public:
	NumConstASTnode(int intlit_) : intlit(intlit_), ConstASTnode(::INT_CONST) {}

	int getIntLit()
	{
		return intlit;
	}

	virtual void accept(ASTvisitor &v)
	{
		v.visit(*this);
	}

	// virtual void printPostFix() const
	// {
	// 	std::cout << intlit << " ";
	// }
};

class CharConstASTnode : public ConstASTnode
{
public:
	string charlit;
	CharConstASTnode(string charlit) : charlit(charlit), ConstASTnode(::STRING_CONST) {}

	string getCharConst()
	{
		return charlit;
	}

	virtual void accept(ASTvisitor &v)
	{
	    v.visit(*this);
	}

	/* virtual void printPostFix() const
	{
		std::cout << intlit << " " ;
	} */
};

class BoolConstASTnode : public ConstASTnode
{
public:
	string bool_type;
	BoolConstASTnode(string type_) : bool_type(type_), ConstASTnode(::BOOL_CONST) {}
	virtual void accept(ASTvisitor &v)
	{
		v.visit(*this);
	}
};

// class ProgramStart : public ASTnode
// {

//     ASTnode *decl_list;

// public:
//     ProgramStart(ASTnode *intlit) : ProgramStart(intlit) {}

//     int getIntLit()
//     {
//         return intlit;
//     }

//     virtual void accept(ASTvisitor &v)
//     {
//         v.visit(*this);
//     }

//     /* virtual void printPostFix() const
// 	{
// 		std::cout << intlit << " " ;
// 	} */
// };

class ASTContext
{
public:
	ASTnode *root;

	~ASTContext()
	{
		clearAST();
	}

	/// free all saved expression trees
	void clearAST()
	{
		delete root;
	}
};
