#pragma once

#include "CSubset_2205126BaseVisitor.h"
#include "SymbolTable.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct VarAccessInfo {
    string name;
    bool isArray;
    int stackOffset;
    bool isGlobal;
};

class ICGVisitor : public CSubset_2205126BaseVisitor {
private:
    SymbolTable st;
    ofstream& codeFile;
    int labelCount = 0;
    int currentOffset = 0;
    string currentFuncName = "";
    
    string bssSegment = "segment readable writeable\n";
    string codeSegment = "segment readable executable\ninclude 'printProc.lib'\n_start:\n    call main\n    mov eax, 1\n    xor ebx, ebx\n    int 0x80\n\n";

    string newLabel(string prefix = "L") {
        return prefix + to_string(++labelCount);
    }
    
    void emitCode(const string& code) {
        codeSegment += code;
    }
    
    void emitBss(const string& code) {
        bssSegment += code;
    }

public:
    ICGVisitor(ofstream& codeOut);
    ~ICGVisitor();

    void printAssembly();

    std::any visitStart(CSubset_2205126Parser::StartContext *ctx) override;
    std::any visitProgUnit(CSubset_2205126Parser::ProgUnitContext *ctx) override;
    std::any visitSingleUnit(CSubset_2205126Parser::SingleUnitContext *ctx) override;
    
    std::any visitUnitVarDecl(CSubset_2205126Parser::UnitVarDeclContext *ctx) override;
    std::any visitUnitFuncDecl(CSubset_2205126Parser::UnitFuncDeclContext *ctx) override;
    std::any visitUnitFuncDef(CSubset_2205126Parser::UnitFuncDefContext *ctx) override;
    
    std::any visitFuncDeclWithParams(CSubset_2205126Parser::FuncDeclWithParamsContext *ctx) override;
    std::any visitFuncDeclNoParams(CSubset_2205126Parser::FuncDeclNoParamsContext *ctx) override;
    std::any visitFuncDefWithParams(CSubset_2205126Parser::FuncDefWithParamsContext *ctx) override;
    std::any visitFuncDefNoParams(CSubset_2205126Parser::FuncDefNoParamsContext *ctx) override;
    
    std::any visitCompoundStmtWithBody(CSubset_2205126Parser::CompoundStmtWithBodyContext *ctx) override;
    std::any visitCompoundStmtEmpty(CSubset_2205126Parser::CompoundStmtEmptyContext *ctx) override;
    
    std::any visitStmtVarDecl(CSubset_2205126Parser::StmtVarDeclContext *ctx) override;
    std::any visitStmtExpr(CSubset_2205126Parser::StmtExprContext *ctx) override;
    std::any visitStmtCompound(CSubset_2205126Parser::StmtCompoundContext *ctx) override;
    std::any visitStmtFor(CSubset_2205126Parser::StmtForContext *ctx) override;
    std::any visitStmtIfElse(CSubset_2205126Parser::StmtIfElseContext *ctx) override;
    std::any visitStmtIf(CSubset_2205126Parser::StmtIfContext *ctx) override;
    std::any visitStmtWhile(CSubset_2205126Parser::StmtWhileContext *ctx) override;
    std::any visitStmtPrint(CSubset_2205126Parser::StmtPrintContext *ctx) override;
    std::any visitStmtReturn(CSubset_2205126Parser::StmtReturnContext *ctx) override;
    
    std::any visitVarDecl(CSubset_2205126Parser::VarDeclContext *ctx) override;
    std::any visitDeclListMultiple(CSubset_2205126Parser::DeclListMultipleContext *ctx) override;
    std::any visitDeclListMultipleArray(CSubset_2205126Parser::DeclListMultipleArrayContext *ctx) override;
    std::any visitDeclListSingle(CSubset_2205126Parser::DeclListSingleContext *ctx) override;
    std::any visitDeclListSingleArray(CSubset_2205126Parser::DeclListSingleArrayContext *ctx) override;
    
    std::any visitExprStmtEmpty(CSubset_2205126Parser::ExprStmtEmptyContext *ctx) override;
    std::any visitExprStmtExpr(CSubset_2205126Parser::ExprStmtExprContext *ctx) override;
    
    std::any visitVarId(CSubset_2205126Parser::VarIdContext *ctx) override;
    std::any visitVarArray(CSubset_2205126Parser::VarArrayContext *ctx) override;
    
    std::any visitExprLogic(CSubset_2205126Parser::ExprLogicContext *ctx) override;
    std::any visitExprAssign(CSubset_2205126Parser::ExprAssignContext *ctx) override;
    
    std::any visitLogicRel(CSubset_2205126Parser::LogicRelContext *ctx) override;
    std::any visitLogicOp(CSubset_2205126Parser::LogicOpContext *ctx) override;
    
    std::any visitRelSimple(CSubset_2205126Parser::RelSimpleContext *ctx) override;
    std::any visitRelOp(CSubset_2205126Parser::RelOpContext *ctx) override;
    
    std::any visitSimpTerm(CSubset_2205126Parser::SimpTermContext *ctx) override;
    std::any visitSimpAdd(CSubset_2205126Parser::SimpAddContext *ctx) override;
    
    std::any visitTermUnary(CSubset_2205126Parser::TermUnaryContext *ctx) override;
    std::any visitTermMul(CSubset_2205126Parser::TermMulContext *ctx) override;
    
    std::any visitUnaryAdd(CSubset_2205126Parser::UnaryAddContext *ctx) override;
    std::any visitUnaryNot(CSubset_2205126Parser::UnaryNotContext *ctx) override;
    std::any visitUnaryFactor(CSubset_2205126Parser::UnaryFactorContext *ctx) override;
    
    std::any visitFactorVar(CSubset_2205126Parser::FactorVarContext *ctx) override;
    std::any visitFactorFuncCall(CSubset_2205126Parser::FactorFuncCallContext *ctx) override;
    std::any visitFactorParen(CSubset_2205126Parser::FactorParenContext *ctx) override;
    std::any visitFactorInt(CSubset_2205126Parser::FactorIntContext *ctx) override;
    std::any visitFactorFloat(CSubset_2205126Parser::FactorFloatContext *ctx) override;
    std::any visitFactorInc(CSubset_2205126Parser::FactorIncContext *ctx) override;
    std::any visitFactorDec(CSubset_2205126Parser::FactorDecContext *ctx) override;
    
    void annotateLine(antlr4::ParserRuleContext* ctx);
};
