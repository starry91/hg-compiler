#ifndef _CodeGenVisitor_H
#define _CodeGenVisitor_H

#include "ast.h"
#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>
using namespace std;
static LLVMContext mycontext;
static Module *Module_Ob = new Module("compiler", mycontext);
static IRBuilder<> Builder(mycontext);
static std::map<std::string, llvm::AllocaInst *> Named_Values;

class CodeGenVisitorImpl : public CodeGenVisitor
{
public:
  Value *ReportError(const char *e)
  {
    fprintf(stderr, "LogError: %s\n", e);
    return nullptr;
  }

  virtual Value *codeGen(BinaryASTnode &node)
  {
    Value *L = node.getLeft()->codeGen(*this);
    Value *R = node.getRight()->codeGen(*this);
    if (!L || !R)
      return nullptr;

    // TODO: Add other operators
    auto op = node.getBin_operator();
    if (op == "+")
      return Builder.CreateFAdd(L, R, "addtmp");
    else if (op == "-")
      return Builder.CreateFSub(L, R, "subtmp");
    else if (op == "*")
      return Builder.CreateFMul(L, R, "multmp");
    else if (op == "/")
      return Builder.CreateFDiv(L, R, "divtmp");
    else if (op == "<")
    {
      L = Builder.CreateFCmpULT(L, R, "cmptmp");
      // Convert bool 0/1 to double 0.0 or 1.0
      return Builder.CreateUIToFP(L, Type::getDoubleTy(mycontext), "booltmp");
    }
    else
      return ReportError("invalid binary operator");
  }
  virtual Value *codeGen(TernaryASTnode &node)
  {
    auto *cond = node.getFirst();
    Value *CondV = cond->codeGen(*this);
    auto *second = node.getSecond();
    Value *second_cd = second->codeGen(*this);
    auto *third = node.getThird();
    Value *third_cd = third->codeGen(*this);
    if (!CondV)
    {
      ReportError("Condition creation failed");
      return nullptr;
    }
    BasicBlock *thenBB = BasicBlock::Create(mycontext, "then");
    BasicBlock *elseBB = BasicBlock::Create(mycontext, "else");

    Builder.CreateCondBr(CondV, thenBB, elseBB);
    Builder.SetInsertPoint(thenBB);
    Builder.CreateRet(second_cd);
    Builder.SetInsertPoint(elseBB);
    Builder.CreateRet(third_cd);
  }
  virtual Value *codeGen(BoolConstASTnode &node)
  {
    auto bool_type = node.getBoolConst();
    bool val;
    if (bool_type == "true")
    {
      val = true;
    }
    else
    {
      val = false;
    }
    auto ret_val = ConstantInt::get(mycontext, APInt(1, val));
    return ret_val;
  }
  virtual Value *codeGen(CharConstASTnode &node)
  {
    //TODO
    return NULL;
  }
  virtual Value *codeGen(NumConstASTnode &node)
  {
    return ConstantInt::get(mycontext, APInt(32, node.getIntLit()));
  }
  virtual Value *codeGen(UnaryASTnode &node)
  {
    auto *expr_item = node.getExprItem();
    Value *val = expr_item->codeGen(*this);
    auto unary_operator = node.getOpType();
    if (unary_operator == "!")
      return Builder.CreateNot(val, "not");
    else if (unary_operator == "-")
      return Builder.CreateNeg(val, "minus");

    return ReportError("Unknown unary_operator");
  }
  virtual Value *codeGen(ConstASTnode &node)
  {
  }
  virtual Value *codeGen(ExprASTnode &node)
  {
  }
  virtual Value *codeGen(EnclosedExprASTnode &node)
  {
    //TODO
  }
  virtual Value *codeGen(StatementListASTnode &node)
  {
    auto stmnts_list = node.getStmntList();
    Value *v = ConstantInt::get(mycontext, APInt(32, 0));
    for (auto &stmnt : stmnts_list)
    {
      v = stmnt->codeGen(*this);
    }
    return v;
  }
  virtual Value *codeGen(ParamsListASTnode &node)
  {
    //TODO
    return nullptr;
  }
  virtual Value *codeGen(StdoutStatementASTnode &node)
  {
    vector<Value *> args;
    auto expr_item = node.getExprItem();
    Value *v = expr_item->codeGen(*this);
    args.push_back(v);
    /*https://stackoverflow.com/questions/35526075/llvm-how-to-implement-print-function-in-my-language*/
    Constant *printFunc = Module_Ob->getOrInsertFunction("printf",
                                                         FunctionType::get(IntegerType::getInt32Ty(mycontext),
                                                                           PointerType::get(Type::getInt8Ty(mycontext), 0),
                                                                           true));
    if (!printFunc)
      return NULL;
    Value *v = Builder.CreateCall(printFunc, args, "printfCall");
    return v;
  }
  virtual Value *codeGen(StdinStatementASTnode &node)
  {
    //TODO;
    return nullptr;
  }
  virtual Value *codeGen(ContinueStatementASTnode &node)
  {
    //TODO
    return nullptr;
  }
  virtual Value *codeGen(BreakStatementASTnode &node)
  {
    //TODO
    return nullptr;
  }
  virtual Value *codeGen(ReturnStatementASTnode &node)
  {
    if (node.checkIsEmpty())
    {
      return Builder.getInt32(0);
    }
    else if (node.isConstReturn())
    {
      //Generate const code
      auto expr_item = node.getConstItem();
      Value *v = expr_item->codeGen(*this);
      return v;
    }
    else
    {
      //Generate varcode
      auto expr_item = node.getID();
      // Value *v = expr_item->codeGen(*this);
      return v;
    }
  }
  virtual Value *codeGen(FuncCallASTnode &node)
  {
    auto func_name = node.getFuncID();
    auto *params_list_ast_node = dynamic_cast<ParamsListASTnode *> node.getParamsListItem();
    if (params_list_ast_node)
    {
      class MethodArgsASTnode *argslist = node.getArgsList();
      auto args_list = params_list_ast_node->getSimpleStmntList();

      Function *Func = Module_Ob->getFunction(func_name);
      if (Func == NULL)
      {
        ReportError("Function not defined");
      }

      vector<Value *> args;

      for (auto arg : args_list)
      {
        Value *v = arg->codegen(*this);
        args.push_back(v);
      }

      Value *v = Builder.CreateCall(Func, args);
      return v;
    }
    else
    {
      ReportError("In Func Call: Dynamic Cast Failed");
    }
    return nullptr;
  }
  virtual Value *codeGen(WhileStatementASTnode &node)
  {
    //TODO
    return nullptr;
  }
  virtual Value *codeGen(ForStatementASTnode &node)
  {
    //TODO
  }
  virtual Value *codeGen(IterationStatementASTnode &node)
  {
    //TODO
  }
  virtual Value *codeGen(BlockStatementASTnode &node)
  {
    Value *v = node.getStmntListItem()->codeGen(*this);
    return v;
  }
  virtual Value *codeGen(SimpleStatementASTnode &node)
  {
    return nullptr;
  }
  virtual Value *codeGen(VarAccessIdASTnode &node)
  {
    auto var_id = node.getID();
    Value *v = Named_Values[var_id];
    if (!v)
    {
      v = Module_Ob->getNamedGlobal(var_id);
    }
    if (!v)
    {
      ReportError("Unknown variable");
    }
    if (node.getDimsValList().size() == 0)
    {
      v = Builder.CreateLoad(v);
      return v;
    }
    vector<Value *> indices;
    for (auto dim_expr : node.getDimsValList())
    {
      Value *pos = dim_expr->codeGen(*this);
      if (!pos)
      {
        return NULL;
      }
      indices.push_back(Builder.getInt32(0));
      indices.push_back(pos);
    }
    // v = Builder.CreateGEP(Type::getInt32Ty(mycontext), v, indices);
    v = Builder.CreateGEP(v, indices, var_id + "INDEX");
    // v = Builder.CreateLoad(v);
    return v;
  }
  virtual Value *codeGen(AssignmentStatementASTnode &node)
  {
    auto assign_stmnt_list = node.getAssignmentStmntList();
    Value *v;
    for (int i = 0; i < assign_stmnt_list.size(); i++)
    {
      auto var_val = assign_stmnt_list[i].first->codeGen(*this);
      auto assign_val = assign_stmnt_list[i].second->codeGen(*this);
      v = Builder.CreateAlignedStore(assign_val, var_val, 4);
    }
    return v;
  }
  virtual Value *codeGen(StatementASTnode &node)
  {
  }
  virtual Value *codeGen(FunctionArgsASTnode &node)
  {
  }
  virtual Value *codeGen(FuncDecASTnode &node)
  {
    auto func_name = node.getID();
    auto func_body = node.getBlockStmnt();

    Type *returntype;
    auto type_specifier = dynamic_cast<TypeSpecifierASTnode *>(node.getTypeSpecifier());
    auto ret_type = type_specifier->getType();
    if (ret_type == "int")
      returntype = Type::getInt32Ty(mycontext);
    else if (ret_type == "bool")
      returntype = Type::getInt1Ty(mycontext);
    else if (ret_type == "void")
      returntype = Type::getVoidTy(mycontext);
    else
      ReportError("Invalid return type");

    vector<Type *> argTypes;
    vector<string> argNames;
    vector<string> arryt;
    auto arg_list_item = dynamic_cast<FunctionArgsASTnode *>(node.getFuncArgs());
    auto arg_list = arg_list_item->getFuncArgsList();

    for (auto arg : arg_list)
    {
      Type *datatype;
      auto data_type = dynamic_cast<TypeSpecifierASTnode *>(arg.first)->getTypeSpecifier();
      auto var_id = arg.second;
      if (data_type == "int")
        datatype = Type::getInt32Ty(mycontext);
      else if (data_type == "bool")
        datatype = Type::getInt1Ty(mycontext);
      else
        ReportError("Invalid data type of Function argument");
      argTypes.push_back(datatype);
      argNames.push_back(var_id);
      arryt.push_back(data_type);
    }

    /* https://llvm.org/docs/tutorial/LangImpl03.html */
    FunctionType *functiontype = FunctionType::get(returntype, argTypes, false);
    Function *TheFunction = Function::Create(functiontype, Function::ExternalLinkage, methodName, Module_Ob);
    // Function::arg_iterator arg_it = TheFunction->arg_begin();
    /*set the name of each of the function’s arguments according to the names given in the Prototype. */
    /* This step isn’t strictly necessary, but keeping the names consistent makes the IR more readable, and allows 
		subsequent code to refer directly to the arguments for their names, rather than having to look up them up in the Prototype AST.*/

    BasicBlock *BB = BasicBlock::Create(mycontext, "entry", TheFunction);
    Builder.SetInsertPoint(BB);

    // Record the function arguments in the NamedValues map.
    unsigned Idx = 0;
    for (auto &Arg : TheFunction->args())
    {
      Arg.setName(argNames[Idx]);
      AllocaInst *alloca = CreateEntryBlockAlloca(TheFunction, argNames[Idx], argTypes[Idx]);
      if (arryt[Idx] == "int")
      {
        alloca->setAlignment(4);
        /* initializing variables to 0 */
        Builder.CreateAlignedStore(&Arg, alloca, 4);
      }
      else
      {
        // Value * initval = ConstantInt::get(mycontext, APInt(1,0));
        Builder.CreateStore(&Arg, alloca);
      }
      Named_Values[argNames[Idx]] = alloca;
      Idx++;
    }
    Value *retval = func_body->codegen(*this);
    // if(return_type == "void")
    // Builder.CreateRet(NULL);

    if (retval)
    {
      if (return_type != "void")
      {
        Builder.CreateRet(retval);
      }
      else
      {
        Builder.CreateRet(NULL);
      }
    }
    else
    {
      Builder.CreateRet(NULL);
    }

    // verifyFunction(*TheFunction);
    return TheFunction;
  }
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

#endif