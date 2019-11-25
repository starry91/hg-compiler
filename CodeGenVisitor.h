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
#include "llvm/Transforms/Utils/FunctionComparator.h"
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
static std::map<std::string, llvm::Value *> Named_Values;

class CodeGenVisitorImpl : public CodeGenVisitor
{
public:
  Value *ReportError(const char *e)
  {
    fprintf(stderr, "LogError: %s\n", e);
    return nullptr;
  }

  void printCode(std::string file)
  {
    std::error_code EC;
    raw_fd_ostream f{file, EC};
    Module_Ob->print(f, nullptr);
    Module_Ob->print(errs(), nullptr);
  }

  Value *smartAdd(Value *L, Value *R)
  {
    Type *t = L->getType();
    if (t->isIntegerTy())
    {
      return Builder.CreateAdd(L, R, "addtmp");
    }
    else if (t->isFloatTy() || t->isDoubleTy())
    {
      return Builder.CreateFAdd(L, R, "addtmp");
    }
    else
    {
      return ReportError("Ivalid type for bin operation");
    }
  }

  Value *smartSub(Value *L, Value *R)
  {
    Type *t = L->getType();
    if (t->isIntegerTy())
    {
      return Builder.CreateSub(L, R, "addtmp");
    }
    else if (t->isFloatTy() || t->isDoubleTy())
    {
      return Builder.CreateFSub(L, R, "addtmp");
    }
    else
    {
      return ReportError("Ivalid type for bin operation");
    }
  }

  Value *smartMul(Value *L, Value *R)
  {
    Type *t = L->getType();
    if (t->isIntegerTy())
    {
      return Builder.CreateMul(L, R, "addtmp");
    }
    else if (t->isFloatTy() || t->isDoubleTy())
    {
      return Builder.CreateFMul(L, R, "addtmp");
    }
    else
    {
      return ReportError("Ivalid type for bin operation");
    }
  }

  Value *smartLT(Value *L, Value *R)
  {
    Type *t = L->getType();
    if (t->isIntegerTy())
    {
      return Builder.CreateICmpSLT(L, R, "cmptmp");
    }
    else if (t->isFloatTy() || t->isDoubleTy())
    {
      return Builder.CreateFCmpULT(L, R, "cmptmp");
    }
    else
    {
      return ReportError("Ivalid type for bin operation");
    }
  }

  Value *smartGT(Value *L, Value *R)
  {
    Type *t = L->getType();
    if (t->isIntegerTy())
    {
      return Builder.CreateICmpSGT(L, R, "cmptmp");
    }
    else if (t->isFloatTy() || t->isDoubleTy())
    {
      return Builder.CreateFCmpUGT(L, R, "cmptmp");
    }
    else
    {
      return ReportError("Ivalid type for bin operation");
    }
  }

  Value *smartLE(Value *L, Value *R)
  {
    Type *t = L->getType();
    if (t->isIntegerTy())
    {
      return Builder.CreateICmpSLE(L, R, "cmptmp");
    }
    else if (t->isFloatTy() || t->isDoubleTy())
    {
      return Builder.CreateFCmpULE(L, R, "cmptmp");
    }
    else
    {
      return ReportError("Ivalid type for bin operation");
    }
  }

  Value *smartGE(Value *L, Value *R)
  {
    Type *t = L->getType();
    if (t->isIntegerTy())
    {
      return Builder.CreateICmpSGE(L, R, "cmptmp");
    }
    else if (t->isFloatTy() || t->isDoubleTy())
    {
      return Builder.CreateFCmpUGE(L, R, "cmptmp");
    }
    else
    {
      return ReportError("Ivalid type for bin operation");
    }
  }

  // Value *smartPow(Value *L, Value *R)
  // {
  //   Type *t = L->getType();
  //   if (t->isIntegerTy())
  //   {
  //     return Builder.CreateICmpSGT(L, R, "cmptmp")
  //   }
  //   else if (t->isFloatTy() || t->isDoubleTy())
  //   {
  //     return Builder.CreateFCmpUGT(L, R, "cmptmp")
  //   }
  //   else
  //   {
  //     return ReportError("Ivalid type for bin operation");
  //   }
  // }

  Value *smartEQ(Value *L, Value *R)
  {
    Type *t = L->getType();
    if (t->isIntegerTy())
    {
      return Builder.CreateICmpEQ(L, R, "IEQ");
    }
    else if (t->isFloatTy() || t->isDoubleTy())
    {
      return Builder.CreateFCmpUEQ(L, R, "FEQ");
    }
    else
    {
      return ReportError("Ivalid type for bin operation");
    }
  }

  Value *getBinValue(Value *L, Value *R, string op)
  {
    L->print(errs(), false);
    if (L->getType()->isPtrOrPtrVectorTy())
    {
      L = Builder.CreateLoad(L);
    }
    if (R->getType()->isPtrOrPtrVectorTy())
    {
      R = Builder.CreateLoad(R);
    }
    if (L->getType()->getTypeID() != R->getType()->getTypeID())
    {
      ReportError("Operand types do not match");
    }
    // TODO: Add other operators
    // auto op = node.getBin_operator();
    if (op == "+")
      return smartAdd(L, R);
    else if (op == "-")
      return smartSub(L, R);
    else if (op == "*")
      return smartMul(L, R);
    else if (op == "/")
      return Builder.CreateUDiv(L, R, "divtmp");
    else if (op == "<")
      return smartLT(L, R);
    else if (op == "<=")
      return smartLE(L, R);
    else if (op == ">")
      return smartGT(L, R);
    else if (op == ">=")
      return smartGE(L, R);
    else if (op == "==")
      return smartEQ(L, R);
    else
    {
      cout << "Invalid op: " << op << endl;
      return ReportError("invalid binary operator");
    }
  }

  virtual Value *codeGen(BinaryASTnode &node)
      override
  {
    Value *L = node.getLeft()->codeGen(*this);
    Value *R = node.getRight()->codeGen(*this);
    if (!L || !R)
      return nullptr;

    L->print(errs(), false);
    if (L->getType()->isPtrOrPtrVectorTy())
    {
      L = Builder.CreateLoad(L);
    }
    if (R->getType()->isPtrOrPtrVectorTy())
    {
      R = Builder.CreateLoad(R);
    }

    // TODO: Add other operators
    auto op = node.getBin_operator();
    return getBinValue(L, R, op);
  }
  virtual Value *codeGen(TernaryASTnode &node)
      override
  {
    auto *cond = node.getFirst();
    Value *CondV = cond->codeGen(*this);
    auto *second = node.getSecond();
    auto *third = node.getThird();
    if (!CondV)
    {
      ReportError("Condition creation failed");
      return nullptr;
    }
    Function *parent = Builder.GetInsertBlock()->getParent();
    BasicBlock *thenBB = BasicBlock::Create(mycontext, "then", parent);
    BasicBlock *elseBB = BasicBlock::Create(mycontext, "else");
    BasicBlock *mergeBB = BasicBlock::Create(mycontext, "merge");

    Builder.CreateCondBr(CondV, thenBB, elseBB);
    Builder.SetInsertPoint(thenBB);
    Value *second_cd = second->codeGen(*this);
    if (!second_cd)
    {
      ReportError("Then creation failed");
      return nullptr;
    }
    Builder.CreateBr(mergeBB);
    parent->getBasicBlockList().push_back(elseBB);
    Builder.SetInsertPoint(elseBB);
    Value *third_cd = third->codeGen(*this);
    if (!third_cd)
    {
      ReportError("Then creation failed");
      return nullptr;
    }
    Builder.CreateBr(mergeBB);
    parent->getBasicBlockList().push_back(mergeBB);
    Builder.SetInsertPoint(mergeBB);
    PHINode *PN =
        Builder.CreatePHI(second_cd->getType(), 2, "iftmp"); // Type::getInt32Ty(mycontext)

    PN->addIncoming(second_cd, thenBB);
    PN->addIncoming(third_cd, elseBB);
    return PN;
  }
  virtual Value *codeGen(BoolConstASTnode &node)
      override
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
      override
  {
    //TODO
    return NULL;
  }
  virtual Value *codeGen(NumConstASTnode &node)
      override
  {
    return ConstantInt::get(mycontext, APInt(32, node.getIntLit()));
  }
  virtual Value *codeGen(UnaryASTnode &node)
      override
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
      override
  {
    return nullptr;
  }
  virtual Value *codeGen(ExprASTnode &node)
      override
  {
    return nullptr;
  }
  virtual Value *codeGen(EnclosedExprASTnode &node)
      override
  {
    return nullptr;
  }
  virtual Value *codeGen(StatementListASTnode &node)
      override
  {
    auto &stmnts_list = node.getStmntList();
    cout << "statement list size: " << stmnts_list.size() << endl;
    int i = 1;
    Value *v = Builder.GetInsertBlock();
    for (auto &stmnt : stmnts_list)
    {
      cout << "Generating statement: " << i++ << endl;
      v = stmnt->codeGen(*this);
      if (!v)
      {
        return ReportError("Unable to create statement");
      }
    }
    return v;
  }
  virtual Value *codeGen(ParamsListASTnode &node)
      override
  {
    //TODO
    return nullptr;
  }
  virtual Value *codeGen(StdoutStatementASTnode &node)
      override
  {
    vector<Value *> args;
    vector<Type *> types;
    auto expr_item = node.getExprItem();
    Value *v = expr_item->codeGen(*this);
    if (v->getType()->isPtrOrPtrVectorTy())
    {
      v = Builder.CreateLoad(v);
    }
    cout << "Type: " << v->getType() << endl;
    if (v->getType()->isIntegerTy())
    {
      args.push_back(Builder.CreateGlobalStringPtr("%d\n"));
    }
    args.push_back(v);
    /*https://stackoverflow.com/questions/35526075/llvm-how-to-implement-print-function-in-my-language*/
    auto *printFunc = Module_Ob->getOrInsertFunction("printf",
                                                     FunctionType::get(
                                                         IntegerType::getInt32Ty(mycontext),
                                                         PointerType::get(Type::getInt8Ty(mycontext), 0),
                                                         //  v->getType(),
                                                         true));
    if (!printFunc)
    {
      return ReportError("UNable to generate printf call");
    }
    v = Builder.CreateCall(printFunc, args, "printfCall");
    return v;
  }
  virtual Value *codeGen(StdinStatementASTnode &node)
      override
  {
    vector<Value *> args;
    vector<Type *> types;
    auto expr_item = node.getExprItem();
    Value *v = expr_item->codeGen(*this);
    if (!v->getType()->isPointerTy())
    {
      return ReportError("Is not a pointer type in cin");
    }
    // cout << "Type: " << v->getType() << endl;
    if (Builder.CreateLoad(v)->getType()->isIntegerTy())
    {
      args.push_back(Builder.CreateGlobalStringPtr("%d"));
    }
    args.push_back(v);
    /*https://stackoverflow.com/questions/35526075/llvm-how-to-implement-print-function-in-my-language*/
    auto *printFunc = Module_Ob->getOrInsertFunction("scanf",
                                                     FunctionType::get(
                                                         IntegerType::getInt32Ty(mycontext),
                                                         PointerType::get(Type::getInt8Ty(mycontext), 0),
                                                         //  v->getType(),
                                                         true));
    if (!printFunc)
    {
      return ReportError("UNable to generate scanf call");
    }
    v = Builder.CreateCall(printFunc, args, "scanfCall");
    return v;
  }
  virtual Value *codeGen(ContinueStatementASTnode &node)
      override
  {
    //TODO
    return nullptr;
  }
  virtual Value *codeGen(BreakStatementASTnode &node)
      override
  {
    //TODO
    return nullptr;
  }
  virtual Value *codeGen(ReturnStatementASTnode &node)
      override
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
    return nullptr;
    // else
    // {
    //   //Generate varcode
    //   auto expr_item = node.getID();
    //   // Value *v = expr_item->codeGen(*this);
    //   return v;
    // }
  }
  virtual Value *codeGen(FuncCallASTnode &node)
      override
  {
    auto func_name = node.getFuncID();
    auto *params_list_ast_node = dynamic_cast<ParamsListASTnode *>(node.getParamsListItem());
    if (params_list_ast_node)
    {
      auto args_list = params_list_ast_node->getSimpleStmntList();

      Function *Func = Module_Ob->getFunction(func_name);
      if (Func == NULL)
      {
        ReportError("Function not defined");
      }

      vector<Value *> args;

      for (auto arg : args_list)
      {
        Value *v = arg->codeGen(*this);
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
      override
  {
    Function *parent = Builder.GetInsertBlock()->getParent();

    auto *loopBB = BasicBlock::Create(mycontext, "loop", parent);
    Builder.CreateBr(loopBB);

    Builder.SetInsertPoint(loopBB);

    auto *cond_st = node.getloopCond()->codeGen(*this);
    if (!cond_st)
    {
      ReportError("unable to generate loop condition");
      return nullptr;
    }

    auto *loopinnerBB = BasicBlock::Create(mycontext, "loopinner");
    auto *loopexitBB = BasicBlock::Create(mycontext, "loopexit");
    auto *condV = Builder.CreateCondBr(cond_st, loopinnerBB, loopexitBB);

    parent->getBasicBlockList().push_back(loopinnerBB);
    Builder.SetInsertPoint(loopinnerBB);
    auto *body = node.getloopBody()->codeGen(*this);
    if (!body)
    {
      ReportError("unable to generate loop body");
      return nullptr;
    }
    Builder.CreateBr(loopBB);

    parent->getBasicBlockList().push_back(loopexitBB);
    Builder.SetInsertPoint(loopexitBB);
    return loopexitBB;
  }
  virtual Value *codeGen(ForStatementASTnode &node)
      override
  {
    auto *start_st = node.getStartStmnt()->codeGen(*this);
    if (!start_st)
    {
      ReportError("unable to generate start statement");
      return nullptr;
    }

    Function *parent = Builder.GetInsertBlock()->getParent();
    BasicBlock *preloopBB = Builder.GetInsertBlock();

    auto *loopBB = BasicBlock::Create(mycontext, "loop", parent);
    Builder.CreateBr(loopBB);

    Builder.SetInsertPoint(loopBB);

    auto *cond_st = node.getloopCond()->codeGen(*this);
    if (!cond_st)
    {
      ReportError("unable to generate loop condition");
      return nullptr;
    }

    auto *loopinnerBB = BasicBlock::Create(mycontext, "loopinner");
    auto *loopexitBB = BasicBlock::Create(mycontext, "loopexit");
    auto *condV = Builder.CreateCondBr(cond_st, loopinnerBB, loopexitBB);

    parent->getBasicBlockList().push_back(loopinnerBB);
    Builder.SetInsertPoint(loopinnerBB);
    auto *body = node.getloopBody()->codeGen(*this);
    if (!body)
    {
      ReportError("unable to generate loop body");
      return nullptr;
    }

    auto *step_st = node.getEndStmnt()->codeGen(*this);
    if (!step_st)
    {
      ReportError("unable to generate loop step");
      return nullptr;
    }
    Builder.CreateBr(loopBB);

    parent->getBasicBlockList().push_back(loopexitBB);
    Builder.SetInsertPoint(loopexitBB);
    return loopexitBB;
  }
  virtual Value *codeGen(IterationStatementASTnode &node)
      override
  {
    return nullptr;
  }
  virtual Value *codeGen(BlockStatementASTnode &node)
      override
  {
    Value *v = node.getStmntListItem()->codeGen(*this);
    return v;
  }
  virtual Value *codeGen(SimpleStatementASTnode &node)
      override
  {
    return nullptr;
  }
  virtual Value *codeGen(VarAccessIdASTnode &node)
      override
  {
    auto var_id = node.getID();
    Value *v = Named_Values[var_id];
    if (!v)
    {
      v = Module_Ob->getNamedGlobal(var_id);
      if (!v)
      {
        return ReportError("Unknown variable");
      }
    }

    if (node.getDimsValList().size() == 0)
    {
      // v = Builder.CreateLoad(v);
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
      override
  {
    auto assign_stmnt_list = node.getAssignmentStmntList();
    Value *v;
    for (int i = 0; i < assign_stmnt_list.size(); i++)
    {
      auto var_val = assign_stmnt_list[i].first->codeGen(*this);
      if (!var_val)
      {
        return ReportError("Variable access code gen failed");
      }
      auto assign_val = assign_stmnt_list[i].second->codeGen(*this);
      if (!assign_val)
      {
        return ReportError("variable assignment statement codegen failed");
      }
      v = Builder.CreateAlignedStore(assign_val, var_val, 4);
      if (!v)
      {
        return ReportError("aligned store codegen failed");
      }
    }
    return v;
  }
  virtual Value *codeGen(StatementASTnode &node)
      override
  {
    return nullptr;
  }
  virtual Value *codeGen(FunctionArgsASTnode &node)
      override
  {
    return nullptr;
  }
  virtual Value *codeGen(FuncDecASTnode &node)
      override
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
    {
      ReportError("Invalid return type");
      return nullptr;
    }

    vector<Type *> argTypes;
    vector<string> argNames;
    vector<string> arryt;
    auto arg_list_item = dynamic_cast<FunctionArgsASTnode *>(node.getFuncArgs());
    auto arg_list = arg_list_item->getFuncArgsList();

    for (auto &arg : arg_list)
    {
      Type *datatype;
      auto data_type = dynamic_cast<TypeSpecifierASTnode *>(arg.first)->getType();
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
    Function *TheFunction = Function::Create(functiontype, Function::ExternalLinkage, func_name, Module_Ob);
    // Function::arg_iterator arg_it = TheFunction->arg_begin();
    /* set the name of each of the function’s arguments according to the names given in the Prototype. */
    /* This step isn’t strictly necessary, but keeping the names consistent makes the IR more readable, and allows 
		subsequent code to refer directly to the arguments for their names, rather than having to look up them up in the Prototype AST.*/

    BasicBlock *BB = BasicBlock::Create(mycontext, "entry", TheFunction);
    Builder.SetInsertPoint(BB);

    // Record the function arguments in the NamedValues map.
    unsigned Idx = 0;
    Named_Values.clear();
    for (auto &Arg : TheFunction->args())
    {
      Arg.setName(argNames[Idx]);
      // AllocaInst *alloca = CreateEntryBlockAlloca(TheFunction, argNames[Idx], argTypes[Idx]);
      // if (arryt[Idx] == "int")
      // {
      //   alloca->setAlignment(4);
      //   /* initializing variables to 0 */
      //   Builder.CreateAlignedStore(&Arg, alloca, 4);
      // }
      // else
      // {
      //   // Value * initval = ConstantInt::get(mycontext, APInt(1,0));
      //   Builder.CreateStore(&Arg, alloca);
      // }
      Named_Values[Arg.getName()] = &Arg;
      Idx++;
    }
    Value *retval = func_body->codeGen(*this);
    if (retval)
    {
      Builder.CreateRet(retval);
    }
    verifyFunction(*TheFunction);
    return TheFunction;
  }
  virtual Value *codeGen(VarDecIDASTnode &node)
      override
  {
    return nullptr;
  }
  virtual Value *codeGen(VarInitializeASTnode &node)
      override
  {
    return nullptr;
  }
  virtual Value *codeGen(VarDecListASTnode &node)
      override
  {
    return nullptr;
  }

  virtual Value *codeGen(TypeSpecifierASTnode &node)
  {
    return nullptr;
  }
  virtual Value *codeGen(VarDecStatementASTnode &node)
      override
  {
    Function *TheFunction = Builder.GetInsertBlock()->getParent();
    Type *datatype;
    auto type_specifier = dynamic_cast<TypeSpecifierASTnode *>(node.getTypeSpecifier());
    auto data_type = type_specifier->getType();
    if (data_type == "int")
      datatype = Type::getInt32Ty(mycontext);
    else if (data_type == "bool")
      datatype = Type::getInt1Ty(mycontext);
    else if (data_type == "void")
      datatype = Type::getVoidTy(mycontext);
    else
    {
      return ReportError("Invalid data type");
    }
    auto varlist = dynamic_cast<VarDecListASTnode *>(node.getVarDecListItem());
    auto var_init_list = varlist->getVarInitList();
    cout << "Var init list size: " << var_init_list.size() << endl;
    for (auto var_init_item : var_init_list)
    {
      auto init_item = dynamic_cast<VarInitializeASTnode *>(var_init_item);
      auto var_dec_id_item = dynamic_cast<VarDecIDASTnode *>(init_item->getVarDecID());
      auto var_name = var_dec_id_item->getID();
      // AllocaInst *alloca;
      AllocaInst *alloca = nullptr;
      IRBuilder<> TmpB(&TheFunction->getEntryBlock(),
                       TheFunction->getEntryBlock().begin());
      alloca = TmpB.CreateAlloca(datatype, 0,
                                 var_name.c_str());
      if (!alloca)
      {
        return ReportError("CreateEntryBlockAlloca failed");
      }
      // if (data_type == "int")
      // {
      //   alloca->setAlignment(4);
      //   /* initializing variables to 0 */
      //   alloca = Builder.CreateAlloca(Type::getInt32Ty(mycontext), 0, nullptr, "var");
      //   Value *initval = ConstantInt::get(mycontext, APInt(32, 0));
      //   Builder.CreateAlignedStore(initval, alloca, 4);
      // }
      // else
      // {
      //   alloca = Builder.CreateAlloca(Type::getInt1Ty(mycontext), 0, nullptr, "var");
      //   Value *initval = ConstantInt::get(mycontext, APInt(1, 0));
      //   Builder.CreateStore(initval, alloca);
      // }
      // Old_vals[var] = NamedValues[var];
      Named_Values[var_name] = alloca;
    }
    return Builder.GetInsertBlock();
  }
  virtual Value *codeGen(DeclarationASTnode &node)
      override
  {
    return nullptr;
  }
  virtual Value *codeGen(DeclarationListASTnode &node)
      override
  {
    auto dec_list = node.getDecList();
    Value *v;
    for (auto dec_item : dec_list)
    {
      v = dec_item->codeGen(*this);
    }
    return v;
  }
  virtual Value *codeGen(ProgramASTnode &node)
      override
  {
    return nullptr;
  }
  virtual Value *codeGen(EmptyStatementASTnode &node)
  {
    return nullptr;
  };
};

#endif