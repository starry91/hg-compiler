#include "ast.h"

class PostFixVisitor: public ASTvisitor {
    public:

    virtual void visit(BinaryASTnode& node)
    {
        node.getLeft()->accept(*this);
        node.getRight()->accept(*this);
        std::cout << node.getBin_operator() << " ";
    }

    virtual void visit(TernaryASTnode& node)
    {
        node.getFirst()->accept(*this);
        node.getSecond()->accept(*this);
        node.getThird()->accept(*this);
        std::cout << "? ";
    }

    virtual void visit(NumConstASTnode& node) 
    {
        std::cout << node.getIntLit() << " ";
    }

	virtual void visit(CharConstASTnode &node){};
	virtual void visit(BoolConstASTnode &node){};
	virtual void visit(UnaryASTnode &node){};
	virtual void visit(ConstASTnode &node){};
	virtual void visit(ExprASTnode &node){};
	virtual void visit(StatementListASTnode &node){};
	virtual void visit(ParamsListASTnode &node){};
	virtual void visit(StdoutStatementASTnode &node){};
	virtual void visit(StdinStatementASTnode &node){};
	virtual void visit(ContinueStatementASTnode &node){};
	virtual void visit(BreakStatementASTnode &node){};
	virtual void visit(ReturnStatementASTnode &node){};
	virtual void visit(FuncCallASTnode &node){};
	virtual void visit(WhileStatementASTnode &node){};
	virtual void visit(ForStatementASTnode &node){};
	virtual void visit(IterationStatementASTnode &node){};
	virtual void visit(BlockStatementASTnode &node){};
	virtual void visit(SimpleStatementASTnode &node){};
	virtual void visit(VarAccessIdASTnode &node){};
	virtual void visit(AssignmentStatementASTnode &node){};
	virtual void visit(StatementASTnode &node){};
	virtual void visit(FunctionArgsASTnode &node){};
	virtual void visit(FuncDecASTnode &node){};
	virtual void visit(VarDecID2dASTnode &node){};
	virtual void visit(VarDecID1dASTnode &node){};
	virtual void visit(VarDecIDSimpleASTnode &node){};
	virtual void visit(VarDecIDASTnode &node){};
	virtual void visit(VarInitializeComplexASTnode &node){};
	virtual void visit(VarInitializeSimpleASTnode &node){};
	virtual void visit(VarInitializeASTnode &node){};
	virtual void visit(VarDecListASTnode &node){};

	virtual void visit(TypeSpecifierASTnode &node){};
	virtual void visit(VarDecStatementASTnode &node){};
	virtual void visit(DeclarationASTnode &node){};
	virtual void visit(DeclarationListASTnode &node){};
	virtual void visit(ProgramASTnode &node){};
};