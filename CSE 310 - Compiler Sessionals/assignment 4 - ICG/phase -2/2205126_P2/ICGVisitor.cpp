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
    if (ctx && ctx->getStart()) {
        emitCode("    ; Line " + to_string(ctx->getStart()->getLine()) + ": " + ctx->getText() + "\n");
    }
}

std::any ICGVisitor::visitStart(CSubset_2205126Parser::StartContext *ctx) {
    visitChildren(ctx);
    printAssembly();
    return {};
}

std::any ICGVisitor::visitProgUnit(CSubset_2205126Parser::ProgUnitContext *ctx) {
    return visitChildren(ctx);
}

std::any ICGVisitor::visitSingleUnit(CSubset_2205126Parser::SingleUnitContext *ctx) {
    return visitChildren(ctx);
}

std::any ICGVisitor::visitUnitVarDecl(CSubset_2205126Parser::UnitVarDeclContext *ctx) {
    return visit(ctx->var_declaration());
}

std::any ICGVisitor::visitUnitFuncDecl(CSubset_2205126Parser::UnitFuncDeclContext *ctx) {
    return visit(ctx->func_declaration());
}

std::any ICGVisitor::visitUnitFuncDef(CSubset_2205126Parser::UnitFuncDefContext *ctx) {
    return visit(ctx->func_definition());
}

std::any ICGVisitor::visitFuncDeclWithParams(CSubset_2205126Parser::FuncDeclWithParamsContext *ctx) {
    return {};
}

std::any ICGVisitor::visitFuncDeclNoParams(CSubset_2205126Parser::FuncDeclNoParamsContext *ctx) {
    return {};
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

std::any ICGVisitor::visitFuncDefWithParams(CSubset_2205126Parser::FuncDefWithParamsContext *ctx) {
    string funcName = ctx->ID()->getText();
    currentFuncName = funcName;
    
    emitCode(funcName + ":\n");
    emitCode("    push ebp\n");
    emitCode("    mov ebp, esp\n");
    
    currentOffset = 0;
    st.enterScope();
    
    // Collect parameters
    vector<string> params;
    auto paramCtx = ctx->parameter_list();
    while (auto mult = dynamic_cast<CSubset_2205126Parser::ParamListMultipleContext*>(paramCtx)) {
        params.push_back(mult->ID()->getText());
        paramCtx = mult->parameter_list();
    }
    if (auto sgl = dynamic_cast<CSubset_2205126Parser::ParamListSingleContext*>(paramCtx)) {
        params.push_back(sgl->ID()->getText());
    }
    
    int paramOffset = 8;
    for (int i = (int)params.size() - 1; i >= 0; i--) {
        SymbolInfo* sym = new SymbolInfo(params[i], "ID");
        sym->setStackOffset(paramOffset);
        st.insert(sym);
        paramOffset += 4;
    }
    
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

std::any ICGVisitor::visitStmtIf(CSubset_2205126Parser::StmtIfContext *ctx) {
    annotateLine(ctx);
    string endLabel = newLabel("L_IF_END_");
    visit(ctx->expression());
    emitCode("    cmp eax, 0\n");
    emitCode("    je " + endLabel + "\n");
    visit(ctx->statement());
    emitCode(endLabel + ":\n");
    return {};
}

std::any ICGVisitor::visitStmtIfElse(CSubset_2205126Parser::StmtIfElseContext *ctx) {
    annotateLine(ctx);
    string elseLabel = newLabel("L_ELSE_");
    string endLabel = newLabel("L_IF_END_");
    visit(ctx->expression());
    emitCode("    cmp eax, 0\n");
    emitCode("    je " + elseLabel + "\n");
    visit(ctx->statement(0));
    emitCode("    jmp " + endLabel + "\n");
    emitCode(elseLabel + ":\n");
    visit(ctx->statement(1));
    emitCode(endLabel + ":\n");
    return {};
}

std::any ICGVisitor::visitStmtWhile(CSubset_2205126Parser::StmtWhileContext *ctx) {
    annotateLine(ctx);
    string startLabel = newLabel("L_WHILE_START_");
    string endLabel = newLabel("L_WHILE_END_");
    
    emitCode(startLabel + ":\n");
    visit(ctx->expression());
    emitCode("    cmp eax, 0\n");
    emitCode("    je " + endLabel + "\n");
    visit(ctx->statement());
    emitCode("    jmp " + startLabel + "\n");
    emitCode(endLabel + ":\n");
    return {};
}

std::any ICGVisitor::visitStmtFor(CSubset_2205126Parser::StmtForContext *ctx) {
    annotateLine(ctx);
    string startLabel = newLabel("L_FOR_START_");
    string endLabel = newLabel("L_FOR_END_");
    
    visit(ctx->expression_statement(0));
    emitCode(startLabel + ":\n");
    if (ctx->expression_statement(1)) {
        if (auto exprCtx = dynamic_cast<CSubset_2205126Parser::ExprStmtExprContext*>(ctx->expression_statement(1))) {
            visit(exprCtx->expression());
            emitCode("    cmp eax, 0\n");
            emitCode("    je " + endLabel + "\n");
        }
    }
    visit(ctx->statement());
    if (ctx->expression()) {
        visit(ctx->expression());
    }
    emitCode("    jmp " + startLabel + "\n");
    emitCode(endLabel + ":\n");
    return {};
}

std::any ICGVisitor::visitStmtPrint(CSubset_2205126Parser::StmtPrintContext *ctx) {
    annotateLine(ctx);
    string varName = ctx->ID()->getText();
    SymbolInfo* sym = st.lookup(varName);
    if (sym != nullptr) {
        if (sym->getStackOffset() == 0) {
            emitCode("    mov eax, dword [" + sym->getName() + "]\n");
        } else if (sym->getStackOffset() < 0) {
            emitCode("    mov eax, dword [ebp - " + to_string(-sym->getStackOffset()) + "]\n");
        } else {
            emitCode("    mov eax, dword [ebp + " + to_string(sym->getStackOffset()) + "]\n");
        }
        emitCode("    call print_number\n");
    }
    return {};
}

std::any ICGVisitor::visitStmtReturn(CSubset_2205126Parser::StmtReturnContext *ctx) {
    annotateLine(ctx);
    if (ctx->expression()) {
        visit(ctx->expression());
    }
    emitCode("    jmp L_" + currentFuncName + "_exit\n");
    return {};
}

std::any ICGVisitor::visitVarDecl(CSubset_2205126Parser::VarDeclContext *ctx) {
    annotateLine(ctx);
    return visit(ctx->declaration_list());
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

std::any ICGVisitor::visitDeclListSingleArray(CSubset_2205126Parser::DeclListSingleArrayContext *ctx) {
    string varName = ctx->ID()->getText();
    int size = stoi(ctx->CONST_INT()->getText());
    SymbolInfo* sym = new SymbolInfo(varName, "ID");
    sym->setIsArray(true);
    sym->setArraySize(size);
    if (st.isRootScope()) {
        emitBss("    " + varName + " rd " + to_string(size) + "\n");
        sym->setStackOffset(0);
    } else {
        currentOffset -= size * 4;
        emitCode("    sub esp, " + to_string(size * 4) + "\n");
        sym->setStackOffset(currentOffset);
    }
    st.insert(sym);
    return {};
}

std::any ICGVisitor::visitDeclListMultipleArray(CSubset_2205126Parser::DeclListMultipleArrayContext *ctx) {
    visit(ctx->declaration_list());
    string varName = ctx->ID()->getText();
    int size = stoi(ctx->CONST_INT()->getText());
    SymbolInfo* sym = new SymbolInfo(varName, "ID");
    sym->setIsArray(true);
    sym->setArraySize(size);
    if (st.isRootScope()) {
        emitBss("    " + varName + " rd " + to_string(size) + "\n");
        sym->setStackOffset(0);
    } else {
        currentOffset -= size * 4;
        emitCode("    sub esp, " + to_string(size * 4) + "\n");
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
    VarAccessInfo info;
    info.name = varName;
    info.isArray = false;
    info.stackOffset = sym ? sym->getStackOffset() : 0;
    info.isGlobal = (sym && sym->getStackOffset() == 0);
    return info;
}

std::any ICGVisitor::visitVarArray(CSubset_2205126Parser::VarArrayContext *ctx) {
    string arrName = ctx->ID()->getText();
    SymbolInfo* sym = st.lookup(arrName);
    
    // Evaluate array index (Result in EAX)
    visit(ctx->expression());
    
    // Compute address of array element into EAX
    if (sym && sym->getStackOffset() == 0) {
        emitCode("    lea eax, [" + arrName + " + eax*4]\n");
    } else if (sym) {
        int offset = sym->getStackOffset();
        if (offset < 0) {
            emitCode("    lea eax, [ebp + eax*4 - " + to_string(-offset) + "]\n");
        } else {
            emitCode("    lea eax, [ebp + eax*4 + " + to_string(offset) + "]\n");
        }
    }
    
    VarAccessInfo info;
    info.name = arrName;
    info.isArray = true;
    info.stackOffset = 0;
    info.isGlobal = false;
    return info;
}

std::any ICGVisitor::visitExprLogic(CSubset_2205126Parser::ExprLogicContext *ctx) {
    return visit(ctx->logic_expression());
}

std::any ICGVisitor::visitExprAssign(CSubset_2205126Parser::ExprAssignContext *ctx) {
    VarAccessInfo varInfo = std::any_cast<VarAccessInfo>(visit(ctx->variable()));
    
    if (varInfo.isArray) {
        emitCode("    push eax\n");                           // EAX contains the address of the array element, push it to stack
        visit(ctx->logic_expression());                       // Evaluate RHS (Result in EAX)
        emitCode("    pop edx\n");                            // Pop destination address into EDX  
        emitCode("    mov dword [edx], eax\n");
    } else {
        // Evaluate RHS (Result in EAX)
        visit(ctx->logic_expression());
        if (varInfo.isGlobal) {
            emitCode("    mov dword [" + varInfo.name + "], eax\n");
        } else if (varInfo.stackOffset < 0) {
            emitCode("    mov dword [ebp - " + to_string(-varInfo.stackOffset) + "], eax\n");
        } else {
            emitCode("    mov dword [ebp + " + to_string(varInfo.stackOffset) + "], eax\n");
        }
    }
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
    VarAccessInfo varInfo = std::any_cast<VarAccessInfo>(visit(ctx->variable()));
    if (varInfo.isArray) { 
        emitCode("    mov eax, dword [eax]\n");          // EAX holds address, dereference it
    } else {
        if (varInfo.isGlobal) {
            emitCode("    mov eax, dword [" + varInfo.name + "]\n");
        } else if (varInfo.stackOffset < 0) {
            emitCode("    mov eax, dword [ebp - " + to_string(-varInfo.stackOffset) + "]\n");
        } else {
            emitCode("    mov eax, dword [ebp + " + to_string(varInfo.stackOffset) + "]\n");
        }
    }
    return {};
}

std::any ICGVisitor::visitFactorFuncCall(CSubset_2205126Parser::FactorFuncCallContext *ctx) {
    string funcName = ctx->ID()->getText();
    int argCount = 0;
    
    if (ctx->argument_list()) {
        if (auto argListArgs = dynamic_cast<CSubset_2205126Parser::ArgListArgsContext*>(ctx->argument_list())) {
            auto argsCtx = argListArgs->arguments();
            vector<antlr4::ParserRuleContext*> exprs;
            while (auto mult = dynamic_cast<CSubset_2205126Parser::ArgsMultipleContext*>(argsCtx)) {
                exprs.push_back(mult->logic_expression());
                argsCtx = mult->arguments();
            }
            if (auto sgl = dynamic_cast<CSubset_2205126Parser::ArgsSingleContext*>(argsCtx)) {
                exprs.push_back(sgl->logic_expression());
            }
            
            // Pushing arguments right-to-left
            
            for (auto expr : exprs) {
                visit(expr);
                emitCode("    push eax\n");
                argCount++;
            }
        }
    }
    
    emitCode("    call " + funcName + "\n");
    
    if (argCount > 0) {
        emitCode("    add esp, " + to_string(argCount * 4) + "\n");
    }
    
    return {};
}

std::any ICGVisitor::visitFactorParen(CSubset_2205126Parser::FactorParenContext *ctx) {
    return visit(ctx->expression());
}

std::any ICGVisitor::visitFactorInt(CSubset_2205126Parser::FactorIntContext *ctx) {
    emitCode("    mov eax, " + ctx->CONST_INT()->getText() + "\n");
    return {};
}

std::any ICGVisitor::visitFactorFloat(CSubset_2205126Parser::FactorFloatContext *ctx) {
    emitCode("    mov eax, " + ctx->CONST_FLOAT()->getText() + "\n");
    return {};
}

std::any ICGVisitor::visitFactorInc(CSubset_2205126Parser::FactorIncContext *ctx) {
    VarAccessInfo varInfo = std::any_cast<VarAccessInfo>(visit(ctx->variable()));
    if (varInfo.isArray) {
        emitCode("    mov edx, eax\n");              // EDX = address
        emitCode("    mov eax, dword [edx]\n");        // EAX = old value
        emitCode("    mov ecx, eax\n");
        emitCode("    add ecx, 1\n");
        emitCode("    mov dword [edx], ecx\n");        // store incremented value
    } else {
        string loc = (varInfo.isGlobal) ? ("dword [" + varInfo.name + "]") : ((varInfo.stackOffset < 0) ? ("dword [ebp - " + to_string(-varInfo.stackOffset) + "]") : ("dword [ebp + " + to_string(varInfo.stackOffset) + "]"));
        emitCode("    mov eax, " + loc + "\n");        // EAX = old value
        emitCode("    mov edx, eax\n");
        emitCode("    add edx, 1\n");
        emitCode("    mov " + loc + ", edx\n");        // store incremented value
    }
    return {};
}

std::any ICGVisitor::visitFactorDec(CSubset_2205126Parser::FactorDecContext *ctx) {
    VarAccessInfo varInfo = std::any_cast<VarAccessInfo>(visit(ctx->variable()));
    if (varInfo.isArray) {
        emitCode("    mov edx, eax\n");              // EDX = address
        emitCode("    mov eax, dword [edx]\n");        // EAX = old value
        emitCode("    mov ecx, eax\n");
        emitCode("    sub ecx, 1\n");
        emitCode("    mov dword [edx], ecx\n");        // store decremented value
    } else {
        string loc = (varInfo.isGlobal) ? ("dword [" + varInfo.name + "]") : ((varInfo.stackOffset < 0) ? ("dword [ebp - " + to_string(-varInfo.stackOffset) + "]") : ("dword [ebp + " + to_string(varInfo.stackOffset) + "]"));
        emitCode("    mov eax, " + loc + "\n");        // EAX = old value
        emitCode("    mov edx, eax\n");
        emitCode("    sub edx, 1\n");
        emitCode("    mov " + loc + ", edx\n");        // store decremented value
    }
    return {};
}
