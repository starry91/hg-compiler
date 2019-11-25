#include "ast.h"

class PostFixVisitor : public ASTvisitor
{
public:
	virtual void visit(BinaryASTnode &node)
	{
		node.getLeft()->accept(*this);
		node.getRight()->accept(*this);
		std::cout << node.getBin_operator() << " ";
	}

	virtual void visit(TernaryASTnode &node)
	{
		node.getFirst()->accept(*this);
		node.getSecond()->accept(*this);
		node.getThird()->accept(*this);
		std::cout << "? ";
	}

	virtual void visit(ControlStatementASTnode &node)
	{
		node.getIfExpr()->accept(*this);
		node.getIfBody()->accept(*this);
		if (node.getElseBody())
		{
			node.getElseBody()->accept(*this);
		}
	}

	virtual void visit(NumConstASTnode &node)
	{
		cout << node.getIntLit() << " ";
	}

	virtual void visit(CharConstASTnode &node)
	{
		cout << node.getCharConst() << " ";
	};
	virtual void visit(BoolConstASTnode &node)
	{
		cout << node.getBoolConst() << " ";
	};
	virtual void visit(UnaryASTnode &node)
	{
		cout << node.getOpType() << " ";
		node.getExprItem()->accept(*this);
	};
	virtual void visit(ConstASTnode &node){

	};
	virtual void visit(EnclosedExprASTnode &node)
	{
		node.getExprItem()->accept(*this);
	};
	virtual void visit(ExprASTnode &node){

	};
	virtual void visit(StatementListASTnode &node)
	{
		auto x = node.getStmntList();
		for (auto y : x)
		{
			y->accept(*this);
		}
	};
	virtual void visit(ParamsListASTnode &node)
	{
		auto x = node.getSimpleStmntList();
		for (auto y : x)
		{
			y->accept(*this);
		}
	};
	virtual void visit(StdoutStatementASTnode &node)
	{
		node.getExprItem()->accept(*this);
	};
	virtual void visit(StdinStatementASTnode &node)
	{
		node.getExprItem()->accept(*this);
	};
	virtual void visit(ContinueStatementASTnode &node){

	};
	virtual void visit(BreakStatementASTnode &node){

	};
	virtual void visit(ReturnStatementASTnode &node)
	{
		if (!node.checkIsEmpty() && !node.isConstReturn())
			cout << node.getID() << " ";
		else if (!node.checkIsEmpty())
			node.getConstItem()->accept(*this);
	};
	virtual void visit(FuncCallASTnode &node)
	{
		cout << node.getFuncID() << " ";
		node.getParamsListItem()->accept(*this);
	};
	virtual void visit(WhileStatementASTnode &node)
	{
		node.getloopCond()->accept(*this);
		node.getloopBody()->accept(*this);
	};
	virtual void visit(ForStatementASTnode &node)
	{
		node.getStartStmnt()->accept(*this);
		node.getloopCond()->accept(*this);
		node.getEndStmnt()->accept(*this);
		node.getloopBody()->accept(*this);
	};
	virtual void visit(IterationStatementASTnode &node){

	};
	virtual void visit(BlockStatementASTnode &node)
	{
		node.getStmntListItem()->accept(*this);
	};
	virtual void visit(SimpleStatementASTnode &node){

	};
	virtual void visit(EmptyStatementASTnode &node){

	};
	virtual void visit(VarAccessIdASTnode &node)
	{
		cout << node.getID() << " ";
		auto x = node.getDimsValList();
		for (auto y : x)
		{
			y->accept(*this);
		}
	};
	virtual void visit(AssignmentStatementASTnode &node)
	{
		auto x = node.getAssignmentStmntList();
		for (auto y : x)
		{
			y.first->accept(*this);
			y.second->accept(*this);
		}
	};
	virtual void visit(StatementASTnode &node){

	};
	virtual void visit(FunctionArgsASTnode &node)
	{
		auto x = node.getFuncArgsList();
		for (auto y : x)
		{
			y.first->accept(*this);
			cout << y.second << " ";
		}
	};
	virtual void visit(FuncDecASTnode &node)
	{
		node.getTypeSpecifier()->accept(*this);
		cout << node.getID() << " ";
		node.getFuncArgs()->accept(*this);
		node.getBlockStmnt()->accept(*this);
	};
	virtual void visit(VarDecIDASTnode &node)
	{
		cout << node.getID() << " ";
		auto x = node.getDimsSizeList();
		for (auto y : x)
		{
			y->accept(*this);
		}
	};
	virtual void visit(VarInitializeASTnode &node)
	{
		node.getVarDecID()->accept(*this);
		if (node.getInitializeType() == ::INITIALIZE_COMPLEX)
			node.getSimpleStmnt()->accept(*this);
	};
	virtual void visit(VarDecListASTnode &node)
	{
		auto x = node.getVarInitList();
		for (auto y : x)
		{
			y->accept(*this);
		}
	};

	virtual void visit(TypeSpecifierASTnode &node)
	{
		cout << node.getType() << " ";
	};
	virtual void visit(VarDecStatementASTnode &node)
	{
		node.getTypeSpecifier()->accept(*this);
		node.getVarDecListItem()->accept(*this);
	};
	virtual void visit(DeclarationASTnode &node)
	{
		node.getDecItem()->accept(*this);
	};
	virtual void visit(DeclarationListASTnode &node)
	{
		auto x = node.getDecList();
		for (auto y : x)
		{
			y->accept(*this);
		}
	};
	virtual void visit(ProgramASTnode &node)
	{
		node.getDecListItem()->accept(*this);
	};
};