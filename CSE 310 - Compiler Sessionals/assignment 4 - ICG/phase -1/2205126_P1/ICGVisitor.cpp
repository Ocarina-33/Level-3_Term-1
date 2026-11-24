#include "ICGVisitor.h"

ICGVisitor::ICGVisitor(ofstream& codeOut) : st(11), codeFile(codeOut) {}

ICGVisitor::~ICGVisitor() {}

void ICGVisitor::printAssembly() {
    codeFile << "format ELF executable 3\n";
    codeFile << "entry _start\n";
    codeFile << bssSegment << "\n";
    codeFile << codeSegment << "\n";
}

void ICGVisitor::annotateLine(antlr4::ParserRuleContext* ctx) {
    emitCode("    ; Line " + to_string(ctx->getStart()->getLine()) + ": " + ctx->getText() + "\n");
}

std::any ICGVisitor::visitStart(CSubset_2205126Parser::StartContext *ctx) {
    visitChildren(ctx);
    printAssembly();
    return {};
}

std::any ICGVisitor::visitUnitVarDecl(CSubset_2205126Parser::UnitVarDeclContext *ctx) {
    return visit(ctx->var_declaration());
}

std::any ICGVisitor::visitUnitFuncDef(CSubset_2205126Parser::UnitFuncDefContext *ctx) {
    return visit(ctx->func_definition());
}

std::any ICGVisitor::visitFuncDefNoParams(CSubset_2205126Parser::FuncDefNoParamsContext *ctx) {
    string funcName = ctx->ID()->getText();
    currentFuncName = funcName;
    
    emitCode(funcName + ":\n");
    emitCode("    push ebp\n");
    emitCode("    mov ebp, esp\n");
    
    currentOffset = 0;
    st.enterScope();
    
    visit(ctx->compound_statement());
    
    emitCode("L_" + funcName + "_exit:\n");
    emitCode("    mov esp, ebp\n");
    emitCode("    pop ebp\n");
    emitCode("    ret\n\n");
    
    st.exitScope();
    currentFuncName = "";
    return {};
}

std::any ICGVisitor::visitCompoundStmtWithBody(CSubset_2205126Parser::CompoundStmtWithBodyContext *ctx) {
    st.enterScope();
    visit(ctx->statements());
    st.exitScope();
    return {};
}

std::any ICGVisitor::visitCompoundStmtEmpty(CSubset_2205126Parser::CompoundStmtEmptyContext *ctx) {
    return {};
}

std::any ICGVisitor::visitStmtVarDecl(CSubset_2205126Parser::StmtVarDeclContext *ctx) {
    return visit(ctx->var_declaration());
}

std::any ICGVisitor::visitStmtExpr(CSubset_2205126Parser::StmtExprContext *ctx) {
    return visit(ctx->expression_statement());
}

std::any ICGVisitor::visitStmtCompound(CSubset_2205126Parser::StmtCompoundContext *ctx) {
    return visit(ctx->compound_statement());
}

std::any ICGVisitor::visitStmtPrint(CSubset_2205126Parser::StmtPrintContext *ctx) {
    annotateLine(ctx);
    string varName = ctx->ID()->getText();
    SymbolInfo* sym = st.lookup(varName);
    if (sym != nullptr) {
        string varLocation;
        int offset = sym->getStackOffset();
        if (offset == 0) {
            varLocation = "dword [" + sym->getName() + "]";
        } else if (offset < 0) {
            varLocation = "dword [ebp - " + to_string(-offset) + "]";
        } else {
            varLocation = "dword [ebp + " + to_string(offset) + "]";
        }
        emitCode("    mov eax, " + varLocation + "\n");
        emitCode("    call print_number\n");
    }
    return {};
}

std::any ICGVisitor::visitStmtReturn(CSubset_2205126Parser::StmtReturnContext *ctx) {
    annotateLine(ctx);
    visit(ctx->expression());
    emitCode("    jmp L_" + currentFuncName + "_exit\n");
    return {};
}

std::any ICGVisitor::visitVarDecl(CSubset_2205126Parser::VarDeclContext *ctx) {
    annotateLine(ctx);
    return visit(ctx->declaration_list());
}

std::any ICGVisitor::visitDeclListMultiple(CSubset_2205126Parser::DeclListMultipleContext *ctx) {
    visit(ctx->declaration_list());
    string varName = ctx->ID()->getText();
    SymbolInfo* sym = new SymbolInfo(varName, "ID");
    if (st.isRootScope()) {
        emitBss("    " + varName + " rd 1\n");
        sym->setStackOffset(0);
    } else {
        currentOffset -= 4;
        emitCode("    sub esp, 4\n");
        sym->setStackOffset(currentOffset);
    }
    st.insert(sym);
    return {};
}

std::any ICGVisitor::visitDeclListSingle(CSubset_2205126Parser::DeclListSingleContext *ctx) {
    string varName = ctx->ID()->getText();
    SymbolInfo* sym = new SymbolInfo(varName, "ID");
    if (st.isRootScope()) {
        emitBss("    " + varName + " rd 1\n");
        sym->setStackOffset(0);
    } else {
        currentOffset -= 4;
        emitCode("    sub esp, 4\n");
        sym->setStackOffset(currentOffset);
    }
    st.insert(sym);
    return {};
}

std::any ICGVisitor::visitExprStmtEmpty(CSubset_2205126Parser::ExprStmtEmptyContext *ctx) {
    return {};
}

std::any ICGVisitor::visitExprStmtExpr(CSubset_2205126Parser::ExprStmtExprContext *ctx) {
    annotateLine(ctx);
    return visit(ctx->expression());
}

std::any ICGVisitor::visitVarId(CSubset_2205126Parser::VarIdContext *ctx) {
    string varName = ctx->ID()->getText();
    SymbolInfo* sym = st.lookup(varName);
    string varLocation = "";
    if (sym != nullptr) {
        int offset = sym->getStackOffset();
        if (offset == 0) {
            varLocation = "dword [" + sym->getName() + "]";
        } else if (offset < 0) {
            varLocation = "dword [ebp - " + to_string(-offset) + "]";
        } else {
            varLocation = "dword [ebp + " + to_string(offset) + "]";
        }
    }
    return varLocation;
}

std::any ICGVisitor::visitExprLogic(CSubset_2205126Parser::ExprLogicContext *ctx) {
    return visit(ctx->logic_expression());
}

std::any ICGVisitor::visitExprAssign(CSubset_2205126Parser::ExprAssignContext *ctx) {
    string varLocation = std::any_cast<string>(visit(ctx->variable()));
    visit(ctx->logic_expression());
    emitCode("    mov " + varLocation + ", eax\n");
    return {};
}

std::any ICGVisitor::visitLogicRel(CSubset_2205126Parser::LogicRelContext *ctx) {
    return visit(ctx->rel_expression());
}

std::any ICGVisitor::visitLogicOp(CSubset_2205126Parser::LogicOpContext *ctx) {
    string logic_op = ctx->LOGICOP()->getText();
    visit(ctx->rel_expression(0));
    
    if (logic_op == "&&") {
        string falseLabel = newLabel("L_AND_FALSE_");
        string endLabel = newLabel("L_AND_END_");
        emitCode("    cmp eax, 0\n");
        emitCode("    je " + falseLabel + "\n");
        visit(ctx->rel_expression(1));
        emitCode("    cmp eax, 0\n");
        emitCode("    je " + falseLabel + "\n");
        emitCode("    mov eax, 1\n");
        emitCode("    jmp " + endLabel + "\n");
        emitCode(falseLabel + ":\n");
        emitCode("    mov eax, 0\n");
        emitCode(endLabel + ":\n");
    } else if (logic_op == "||") {
        string trueLabel = newLabel("L_OR_TRUE_");
        string endLabel = newLabel("L_OR_END_");
        emitCode("    cmp eax, 0\n");
        emitCode("    jne " + trueLabel + "\n");
        visit(ctx->rel_expression(1));
        emitCode("    cmp eax, 0\n");
        emitCode("    jne " + trueLabel + "\n");
        emitCode("    mov eax, 0\n");
        emitCode("    jmp " + endLabel + "\n");
        emitCode(trueLabel + ":\n");
        emitCode("    mov eax, 1\n");
        emitCode(endLabel + ":\n");
    }
    return {};
}

std::any ICGVisitor::visitRelSimple(CSubset_2205126Parser::RelSimpleContext *ctx) {
    return visit(ctx->simple_expression());
}

std::any ICGVisitor::visitRelOp(CSubset_2205126Parser::RelOpContext *ctx) {
    visit(ctx->simple_expression(0));
    emitCode("    push eax\n");
    visit(ctx->simple_expression(1));
    emitCode("    mov ebx, eax\n");
    emitCode("    pop eax\n");
    emitCode("    cmp eax, ebx\n");
    
    string rel_op = ctx->RELOP()->getText();
    string trueLabel = newLabel("L_REL_TRUE_");
    string endLabel = newLabel("L_REL_END_");
    
    if (rel_op == "<") emitCode("    jl " + trueLabel + "\n");
    else if (rel_op == "<=") emitCode("    jle " + trueLabel + "\n");
    else if (rel_op == ">") emitCode("    jg " + trueLabel + "\n");
    else if (rel_op == ">=") emitCode("    jge " + trueLabel + "\n");
    else if (rel_op == "==") emitCode("    je " + trueLabel + "\n");
    else if (rel_op == "!=") emitCode("    jne " + trueLabel + "\n");
    
    emitCode("    mov eax, 0\n");
    emitCode("    jmp " + endLabel + "\n");
    emitCode(trueLabel + ":\n");
    emitCode("    mov eax, 1\n");
    emitCode(endLabel + ":\n");
    return {};
}

std::any ICGVisitor::visitSimpTerm(CSubset_2205126Parser::SimpTermContext *ctx) {
    return visit(ctx->term());
}

std::any ICGVisitor::visitSimpAdd(CSubset_2205126Parser::SimpAddContext *ctx) {
    visit(ctx->simple_expression());
    emitCode("    push eax\n");
    visit(ctx->term());
    emitCode("    mov ebx, eax\n");
    emitCode("    pop eax\n");
    
    string add_op = ctx->ADDOP()->getText();
    if (add_op == "+") emitCode("    add eax, ebx\n");
    else emitCode("    sub eax, ebx\n");
    return {};
}

std::any ICGVisitor::visitTermUnary(CSubset_2205126Parser::TermUnaryContext *ctx) {
    return visit(ctx->unary_expression());
}

std::any ICGVisitor::visitTermMul(CSubset_2205126Parser::TermMulContext *ctx) {
    visit(ctx->term());
    emitCode("    push eax\n");
    visit(ctx->unary_expression());
    emitCode("    mov ebx, eax\n");
    emitCode("    pop eax\n");
    
    string mul_op = ctx->MULOP()->getText();
    if (mul_op == "*") {
        emitCode("    imul ebx\n");
    } else if (mul_op == "/") {
        emitCode("    cdq\n");
        emitCode("    idiv ebx\n");
    } else if (mul_op == "%") {
        emitCode("    cdq\n");
        emitCode("    idiv ebx\n");
        emitCode("    mov eax, edx\n");
    }
    return {};
}

std::any ICGVisitor::visitUnaryAdd(CSubset_2205126Parser::UnaryAddContext *ctx) {
    visit(ctx->unary_expression());
    string add_op = ctx->ADDOP()->getText();
    if (add_op == "-") emitCode("    neg eax\n");
    return {};
}

std::any ICGVisitor::visitUnaryNot(CSubset_2205126Parser::UnaryNotContext *ctx) {
    visit(ctx->unary_expression());
    emitCode("    cmp eax, 0\n");
    string trueLabel = newLabel("L_NOT_TRUE_");
    string endLabel = newLabel("L_NOT_END_");
    emitCode("    je " + trueLabel + "\n");
    emitCode("    mov eax, 0\n");
    emitCode("    jmp " + endLabel + "\n");
    emitCode(trueLabel + ":\n");
    emitCode("    mov eax, 1\n");
    emitCode(endLabel + ":\n");
    return {};
}

std::any ICGVisitor::visitUnaryFactor(CSubset_2205126Parser::UnaryFactorContext *ctx) {
    return visit(ctx->factor());
}

std::any ICGVisitor::visitFactorVar(CSubset_2205126Parser::FactorVarContext *ctx) {
    string varLocation = std::any_cast<string>(visit(ctx->variable()));
    emitCode("    mov eax, " + varLocation + "\n");
    return {};
}

std::any ICGVisitor::visitFactorParen(CSubset_2205126Parser::FactorParenContext *ctx) {
    return visit(ctx->expression());
}

std::any ICGVisitor::visitFactorInt(CSubset_2205126Parser::FactorIntContext *ctx) {
    emitCode("    mov eax, " + ctx->CONST_INT()->getText() + "\n");
    return {};
}

std::any ICGVisitor::visitFactorInc(CSubset_2205126Parser::FactorIncContext *ctx) {
    string varLocation = std::any_cast<string>(visit(ctx->variable()));
    emitCode("    mov eax, " + varLocation + "\n");
    emitCode("    mov ebx, eax\n");
    emitCode("    add ebx, 1\n");
    emitCode("    mov " + varLocation + ", ebx\n");
    return {};
}

std::any ICGVisitor::visitFactorDec(CSubset_2205126Parser::FactorDecContext *ctx) {
    string varLocation = std::any_cast<string>(visit(ctx->variable()));
    emitCode("    mov eax, " + varLocation + "\n");
    emitCode("    mov ebx, eax\n");
    emitCode("    sub ebx, 1\n");
    emitCode("    mov " + varLocation + ", ebx\n");
    return {};
}
