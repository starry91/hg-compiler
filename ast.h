#include<bits/stdc++.h>

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
class TernaryExprASTnode;
class ConstASTnode;
class BinaryASTnode;
class UnaryASTnode;

class NumConstASTnode;
class CharConstASTnode;

class ASTvisitor {
  public:
    virtual void visit(BinaryASTnode& node) = 0;
    virtual void visit(TernaryASTnode& node) = 0;
    virtual void visit(NumConstASTnode& node) = 0;
};

class ASTnode {
     public :
     virtual ~ASTnode()
     {
     }

    //  virtual void printPostFix() const = 0;

     virtual void accept(ASTvisitor& V) = 0;

};

//Program Start
class ProgramASTnode : public ASTnode
{
    public:
    DeclarationListASTnode* dec_list_item;
};

class DeclarationListASTnode : public ASTnode
{
    public:
    vector<DeclarationASTnode*> dec_list;
};

enum DEC_TYPE{
    FUNC_DEC = 0,
    VAR_DEC_STATEMENT = 1
};
class DeclarationASTnode : public ASTnode
{
    public:
    DEC_TYPE dec_type;
    FuncDecASTnode* func_dec_item;
    VarDecStatementASTnode* var_dec_stmnt_item;
};

class TypeSpecifierASTnode: public ASTnode
{
    public:
    string type;
};

class VarDecListASTnode: public ASTnode
{
    public:
    vector<VarInitializeASTnode*> var_initialize_list;
};

class VarInitializeASTnode: public ASTnode
{
    public:
    enum INITIALIZE_TYPE{
        SIMPLE = 0,
        COMPLEX = 1
    };
    enum INITIALIZE_TYPE initialize_type;
    VarDecIDASTnode* var_dec_id_item;
    SimpleStatementASTnode* simple_stmnt_item;
};

class VarDecIDASTnode: public ASTnode
{
    public:
    string id;
    vector<NumConstASTnode*> dims_size_list;
};

class FuncDecASTnode: public ASTnode
{
    public:
    TypeSpecifierASTnode* type_specifier_item;
    string id;
    FunctionArgsASTnode* func_args_item;
    BlockStatementASTnode* block_stmnt_item;
};

class FunctionArgsASTnode: public ASTnode
{
    public:
    vector<pair<TypeSpecifierASTnode*, FunctionArgsASTnode*>> func_arg_list;
};

class StatementASTnode: public ASTnode
{
    public:
    enum STATEMENT_TYPE{
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
    enum STATEMENT_TYPE stmnt_type;
    StatementASTnode* stmnt_item;
};

class BlockStatementASTnode: public StatementASTnode
{
    public:
    StatementListASTnode* stmnt_list_item;
};

class IterationStatementASTnode: public StatementASTnode
{
    public:
    enum ITERATION_STATEMENT_TYPE{
        FOR,
        WHILE
    };
    enum ITERATION_STATEMENT_TYPE stmnt_type;
    IterationStatementASTnode* iteration_stmnt_item;
};

class ForStatementASTnode: public IterationStatementASTnode
{
    public:
    AssignmentStatementASTnode* start_stmnt;
    ExprASTnode* loop_condition;
    AssignmentStatementASTnode* end_stmnt;
    BlockStatementASTnode* loop_body;
};

class WhileStatementASTnode: public IterationStatementASTnode
{
    public:
    ExprASTnode* loop_condition;
    BlockStatementASTnode* loop_body;
};

class ControlStatementASTnode: public StatementASTnode
{
    public:
    enum CONTROL_STATEMENT_TYPE{
        IF,
        IF_ELSE
    };
    enum CONTROL_STATEMENT_TYPE stmnt_type;
    ExprASTnode* if_expr;
    BlockStatementASTnode* if_body;
    BlockStatementASTnode* else_body;
};

class ReturnStatementASTnode: public StatementASTnode
{
    public:
    string id;
};

class AssignmentStatementASTnode: public StatementASTnode
{
    public:
    vector<pair<VarAccessIdASTnode*, SimpleStatementASTnode*>> assign_stmnt_list;
};


class VarDecStatementASTnode: public StatementASTnode
{
    public:
    TypeSpecifierASTnode* type_specifier_item;
    VarDecListASTnode* var_dec_list_item;
};

class SimpleStatementASTnode: public StatementASTnode
{
    public:
    enum SIMPLE_STATEMENT_TYPE{
        EXPR,
        FUNC_CALL
    };
    enum SIMPLE_STATEMENT_TYPE stmnt_type;
    SimpleStatementASTnode* stmnt_item;
};

class BreakStatementASTnode: public StatementASTnode
{
};

class ContinueStatementASTnode: public StatementASTnode
{
};

class StdinStatementASTnode: public StatementASTnode
{
    public:
    ExprASTnode* expr_item;
};

class StdoutStatementASTnode: public StatementASTnode
{
    public:
    ExprASTnode* expr_item;  
};

class VarAccessIdASTnode: public ASTnode
{
    public:
    string id;
    vector<ExprASTnode*> dims_val_list;
};

class FuncCallASTnode: public ASTnode
{
    public:
    string id;
    ParamsListASTnode* params_list_item; //do we need this or can we replace this with a list?
};

class ParamsListASTnode: public ASTnode
{
    public:
    vector<SimpleStatementASTnode*> simple_stmnt_list;
};

class StatementListASTnode: public ASTnode
{
    public:
    vector<StatementASTnode*> stmnt_list;
};

class ExprASTnode: public ASTnode
{
    public:
    // enum EXPR_TYPE{
    //     ID,
    //     CONST,
    //     BIN_OP,
    //     UNI_OP,
    //     TERNARY_OP,
    // };
    // enum EXPR_TYPE expr_type_item;
    ASTnode* expr_item;
};

class BinaryASTnode : public ExprASTnode {
     std::string bin_operator;  

// lhs and rhs can be of any type. 
// So we need to use BaseAST
     ASTnode  *left;
     ASTnode *right;  

     public:
    enum OP_TYPE{
        PLUS,
        MINUS,
        MULT,
        DIV,
        AND,
        OR,
        XOR,
        COMP,
        NE,
        LT_E,
        GT_E,
        LT,
        GT,
        MOD
    };
    enum OP_TYPE op_type_item;
// Constructor to initialize binary operator, 
// lhs and rhs of the binary expression.
     BinaryASTnode (std::string op, ASTnode* _left, ASTnode* _right ) :
     bin_operator(op), left(_left), right(_right) {}  

    /*  virtual void printPostFix() const 
     {
     	lhs->printPostFix();
     	rhs->printPostFix();
     	std::cout << bin_operator << " "; 
     } */

    ASTnode* getLeft() {
        return left;
    }

    ASTnode* getRight() {
        return right;
    }

    std::string getBin_operator() {
        return bin_operator;
    }
     virtual void accept(ASTvisitor& v)
    {
      v.visit(*this);
    }

};

class UnaryASTnode: public ExprASTnode{

    public:
    enum OP_TYPE{
        NOT,
        MINUS,
    };
    enum OP_TYPE op_type_item;
    ASTnode* expr_item;
};

class TernaryASTnode : public ExprASTnode {

     ASTnode  *first;
     ASTnode *second;
     ASTnode *third;  

     public:
     TernaryASTnode (ASTnode *first, ASTnode *second, ASTnode *third ) :
     first(first), second(second), third(third) {}  

  /*   virtual void printPostFix() const
     {
     	first->printPostFix();
     	second->printPostFix();
     	third->printPostFix();
     	std::cout << "? " << std::endl; 
     }  */

    ASTnode* getFirst()
    {
        return first;
    }

    ASTnode* getSecond()
    {
        return second;
    }

    ASTnode* getThird()
    {
        return third;
    }

     virtual void accept(ASTvisitor& v) 
    {
      v.visit(*this);
    }
};

enum CONST_TYPE{
    NOT,
    MINUS,
};
class ConstASTnode: public ExprASTnode
{
    public:
    CONST_TYPE const_type_item;
    string char_const;
    int num_const;
};

class NumConstASTnode: public ExprASTnode {

	int intlit;

	public:

	IntLitASTnode(int intlit): 
	intlit(intlit){}

    int getIntLit()
    {
        return intlit;
    }

     virtual void accept(ASTvisitor& v) 
    {
      v.visit(*this);
    }
    
	/* virtual void printPostFix() const
	{
		std::cout << intlit << " " ;
	} */

};

class Char: public ASTnode {

	int intlit;

	public:

	IntLitASTnode(int intlit): 
	intlit(intlit){}

    int getIntLit()
    {
        return intlit;
    }

     virtual void accept(ASTvisitor& v) 
    {
      v.visit(*this);
    }
    
	/* virtual void printPostFix() const
	{
		std::cout << intlit << " " ;
	} */

};


class ProgramStart: public ASTnode {

	ASTnode* decl_list; 

	public:

	ProgramStart(ASTnode* intlit): 
	ProgramStart(intlit){}

    int getIntLit()
    {
        return intlit;
    }

     virtual void accept(ASTvisitor& v) 
    {
      v.visit(*this);
    }
    
	/* virtual void printPostFix() const
	{
		std::cout << intlit << " " ;
	} */

};

class ASTContext {
public:
    ASTnode *root;

    ~ASTContext()
    {
	    clearAST();
    }

    /// free all saved expression trees
    void	clearAST()
    {
        delete root;
    }
};
