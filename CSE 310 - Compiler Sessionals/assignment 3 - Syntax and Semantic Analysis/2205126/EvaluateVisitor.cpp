#include "EvaluateVisitor.h"
#include <iostream>
#include <regex>
#include <iomanip>
#include <sstream>

using namespace std;

EvaluateVisitor::EvaluateVisitor(ofstream& log, ofstream& err) : st(30), logFile(log), errorFile(err) {}

string EvaluateVisitor::getText(antlr4::ParserRuleContext* ctx) {
    if (ctx->getStart() == nullptr || ctx->getStop() == nullptr) return "";
    antlr4::misc::Interval interval(ctx->getStart()->getStartIndex(), ctx->getStop()->getStopIndex());
    string rawText = ctx->getStart()->getInputStream()->getText(interval);

    regex floatRegex(R"(\b\d+\.\d+\b|\b\d+\.(?!\w)|\.\d+\b)");
    auto words_begin = sregex_iterator(rawText.begin(), rawText.end(), floatRegex);
    auto words_end = sregex_iterator();

    string result = "";
    size_t lastPos = 0;
    for (sregex_iterator i = words_begin; i != words_end; ++i) {
        smatch match = *i;
        result += rawText.substr(lastPos, match.position() - lastPos);
        
        double val = stod(match.str());
        stringstream ss;
        ss << fixed << setprecision(2) << val;
        result += ss.str();
        
        lastPos = match.position() + match.length();
    }
    result += rawText.substr(lastPos);
    return result;
}

extern std::vector<std::pair<int, string>> globalErrors;
extern std::map<int, std::vector<string>> globalParserErrors;

void EvaluateVisitor::reportError(int line, const string& msg) {
    globalErrors.push_back({line, msg});
    logFile << "Error at line " << line << ": " << msg << "\n\n";
    errorCount++;
}

void EvaluateVisitor::logRule(antlr4::ParserRuleContext* ctx, const string& ruleName) {
    int line = ctx->getStart()->getLine();
    if (globalParserErrors.find(line) != globalParserErrors.end()) {
        for (const string& msg : globalParserErrors[line]) {
            reportError(line, msg);
        }
        globalParserErrors.erase(line);
    }
    logFile << "Line " << line << ": " << ruleName << "\n\n" << getText(ctx) << "\n\n";
}

void EvaluateVisitor::printGlobalScopeAndSummary() {
    st.printCurrent(logFile);
}

int EvaluateVisitor::getErrorCount() { return errorCount; }
void EvaluateVisitor::addErrorCount(int c) { errorCount += c; }

ExprTypeInfo EvaluateVisitor::safeGetExprType(std::any a) {
    if (!a.has_value()) return ExprTypeInfo("error");
    try {
        return std::any_cast<ExprTypeInfo>(a);
    } catch (const std::bad_any_cast&) {
        return ExprTypeInfo("error");
    }
}

string EvaluateVisitor::safeGetTypeSpecifier(std::any a) {
    if (!a.has_value()) return "error";
    try {
        return std::any_cast<string>(a);
    } catch (const std::bad_any_cast&) {
        return "error";
    }
}

std::any EvaluateVisitor::visitStart(CSubset_2205126Parser::StartContext *ctx) {
    auto res = visit(ctx->program());
    logRule(ctx, "start : program");
    st.exitScope(logFile); 
    
    
    for (auto const& [line, msgs] : globalParserErrors) {
        for (const string& msg : msgs) {
            reportError(line, msg);
        }
    }
    globalParserErrors.clear();

    logFile << "Total lines: " << ctx->getStop()->getLine() << "\n";
    logFile << "Total errors: " << errorCount << "\n";
    return res;
}

std::any EvaluateVisitor::visitProgUnit(CSubset_2205126Parser::ProgUnitContext *ctx) {
    visit(ctx->program());
    visit(ctx->unit());
    logRule(ctx, "program : program unit");
    return nullptr;
}

std::any EvaluateVisitor::visitSingleUnit(CSubset_2205126Parser::SingleUnitContext *ctx) {
    visit(ctx->unit());
    logRule(ctx, "program : unit");
    return nullptr;
}

std::any EvaluateVisitor::visitUnitVarDecl(CSubset_2205126Parser::UnitVarDeclContext *ctx) {
    visit(ctx->var_declaration());
    logRule(ctx, "unit : var_declaration");
    return nullptr;
}

std::any EvaluateVisitor::visitUnitFuncDecl(CSubset_2205126Parser::UnitFuncDeclContext *ctx) {
    visit(ctx->func_declaration());
    logRule(ctx, "unit : func_declaration");
    return nullptr;
}

std::any EvaluateVisitor::visitUnitFuncDef(CSubset_2205126Parser::UnitFuncDefContext *ctx) {
    visit(ctx->func_definition());
    logRule(ctx, "unit : func_definition");
    return nullptr;
}

std::any EvaluateVisitor::visitFuncDeclWithParams(CSubset_2205126Parser::FuncDeclWithParamsContext *ctx) {
    string retType = safeGetTypeSpecifier(visit(ctx->type_specifier()));
    string funcName = ctx->ID()->getText();
    int line = ctx->getStart()->getLine();

    st.enterScope();
    currentParamDeclList.clear();
    visit(ctx->parameter_list());
    st.exitScope(); 

    SymbolInfo* sym = st.lookupCurrentScope(funcName);
    if (sym != nullptr) {
        reportError(line, "Multiple declaration of " + funcName);
    } else {
        SymbolInfo* newSym = new SymbolInfo(funcName, "ID");
        newSym->setIsFunction(true);
        newSym->setIsDefined(false);
        newSym->setReturnType(retType);
        for (auto& p : currentParamDeclList) {
            newSym->addParamType(p.first);
        }
        st.insert(newSym);
    }
    logRule(ctx, "func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON");
    return nullptr;
}

std::any EvaluateVisitor::visitFuncDeclNoParams(CSubset_2205126Parser::FuncDeclNoParamsContext *ctx) {
    string retType = safeGetTypeSpecifier(visit(ctx->type_specifier()));
    string funcName = ctx->ID()->getText();
    int line = ctx->getStart()->getLine();

    st.enterScope();
    st.exitScope(); 

    SymbolInfo* sym = st.lookupCurrentScope(funcName);
    if (sym != nullptr) {
        reportError(line, "Multiple declaration of " + funcName);
    } else {
        SymbolInfo* newSym = new SymbolInfo(funcName, "ID");
        newSym->setIsFunction(true);
        newSym->setIsDefined(false);
        newSym->setReturnType(retType);
        st.insert(newSym);
    }
    logRule(ctx, "func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON");
    return nullptr;
}

std::any EvaluateVisitor::visitFuncDefWithParams(CSubset_2205126Parser::FuncDefWithParamsContext *ctx) {
    string retType = safeGetTypeSpecifier(visit(ctx->type_specifier()));
    string funcName = ctx->ID()->getText();
    int line = ctx->getStart()->getLine();
    
    currentFunctionReturnType = retType;
    
    currentParamDeclList.clear();
    visit(ctx->parameter_list());

    SymbolInfo* sym = st.lookupCurrentScope(funcName);
    if (sym != nullptr) {
        if (sym->getIsDefined()) {
            reportError(line, "Multiple definition of function " + funcName);
        } else if (sym->getIsFunction()) {
            if (sym->getReturnType() != retType) {
                reportError(line, "Return type mismatch with function declaration in function " + funcName);
            }
            vector<string> declParams = sym->getParamTypes();
            if (declParams.size() != currentParamDeclList.size()) {
                reportError(line, "Total number of arguments mismatch with declaration in function " + funcName);
            } else {
                for (size_t i = 0; i < declParams.size(); i++) {
                    if (declParams[i] != currentParamDeclList[i].first) {
                        reportError(line, to_string(i+1) + "th argument mismatch in function " + funcName);
                    }
                }
            }
            sym->setIsDefined(true);
        } else {
            reportError(line, "Multiple declaration of " + funcName);
        }
    } else {
        SymbolInfo* newSym = new SymbolInfo(funcName, "ID");
        newSym->setIsFunction(true);
        newSym->setIsDefined(true);
        newSym->setReturnType(retType);
        for (auto& p : currentParamDeclList) {
            newSym->addParamType(p.first);
        }
        st.insert(newSym);
    }

    st.enterScope();
    for (size_t i = 0; i < currentParamDeclList.size(); i++) {
        auto& p = currentParamDeclList[i];
        if (p.second == "") {
            reportError(line, to_string(i+1) + "th parameter's name not given in function definition of " + funcName);
        } else if (p.first == "void") {
            reportError(line, "Variable type cannot be void");
        } else {
            SymbolInfo* paramSym = st.lookupCurrentScope(p.second);
            if (paramSym != nullptr) {
                reportError(line, "Multiple declaration of " + p.second + " in parameter");
            } else {
                SymbolInfo* newParam = new SymbolInfo(p.second, "ID");
                newParam->setDataType(p.first);
                st.insert(newParam);
            }
        }
    }
    
    visit(ctx->compound_statement());
    logRule(ctx, "func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement");
    return nullptr;
}

std::any EvaluateVisitor::visitFuncDefNoParams(CSubset_2205126Parser::FuncDefNoParamsContext *ctx) {
    string retType = safeGetTypeSpecifier(visit(ctx->type_specifier()));
    string funcName = ctx->ID()->getText();
    int line = ctx->getStart()->getLine();
    
    currentFunctionReturnType = retType;

    SymbolInfo* sym = st.lookupCurrentScope(funcName);
    if (sym != nullptr) {
        if (sym->getIsDefined()) {
            reportError(line, "Multiple definition of function " + funcName);
        } else if (sym->getIsFunction()) {
            if (sym->getReturnType() != retType) {
                reportError(line, "Return type mismatch with function declaration in function " + funcName);
            }
            if (sym->getParamTypes().size() != 0) {
                reportError(line, "Total number of arguments mismatch with declaration in function " + funcName);
            }
            sym->setIsDefined(true);
        } else {
            reportError(line, "Multiple declaration of " + funcName);
        }
    } else {
        SymbolInfo* newSym = new SymbolInfo(funcName, "ID");
        newSym->setIsFunction(true);
        newSym->setIsDefined(true);
        newSym->setReturnType(retType);
        st.insert(newSym);
    }

    st.enterScope();
    visit(ctx->compound_statement());
    logRule(ctx, "func_definition : type_specifier ID LPAREN RPAREN compound_statement");
    return nullptr;
}

std::any EvaluateVisitor::visitParamListMultiple(CSubset_2205126Parser::ParamListMultipleContext *ctx) {
    visit(ctx->parameter_list());
    string type = safeGetTypeSpecifier(visit(ctx->type_specifier()));
    string name = ctx->ID()->getText();
    currentParamDeclList.push_back({type, name});
    logRule(ctx, "parameter_list : parameter_list COMMA type_specifier ID");
    return nullptr;
}

std::any EvaluateVisitor::visitParamListMultipleNoID(CSubset_2205126Parser::ParamListMultipleNoIDContext *ctx) {
    visit(ctx->parameter_list());
    string type = safeGetTypeSpecifier(visit(ctx->type_specifier()));
    currentParamDeclList.push_back({type, ""});
    logRule(ctx, "parameter_list : parameter_list COMMA type_specifier");
    return nullptr;
}

std::any EvaluateVisitor::visitParamListSingle(CSubset_2205126Parser::ParamListSingleContext *ctx) {
    string type = safeGetTypeSpecifier(visit(ctx->type_specifier()));
    string name = ctx->ID()->getText();
    currentParamDeclList.push_back({type, name});
    logRule(ctx, "parameter_list : type_specifier ID");
    return nullptr;
}

std::any EvaluateVisitor::visitParamListSingleNoID(CSubset_2205126Parser::ParamListSingleNoIDContext *ctx) {
    string type = safeGetTypeSpecifier(visit(ctx->type_specifier()));
    currentParamDeclList.push_back({type, ""});
    logRule(ctx, "parameter_list : type_specifier");
    return nullptr;
}

std::any EvaluateVisitor::visitParamListErrorSub(CSubset_2205126Parser::ParamListErrorSubContext *ctx) {
    string type = safeGetTypeSpecifier(visit(ctx->type_specifier()));
    currentParamDeclList.push_back({type, ""});
    reportError(ctx->getStart()->getLine(), "syntax error, unexpected token(s) '" + ctx->ADDOP()->getText() + "' before ')'");
    logRule(ctx, "parameter_list : type_specifier ADDOP");
    return nullptr;
}

std::any EvaluateVisitor::visitParamListErrorSubMultiple(CSubset_2205126Parser::ParamListErrorSubMultipleContext *ctx) {
    visit(ctx->parameter_list());
    string type = safeGetTypeSpecifier(visit(ctx->type_specifier()));
    currentParamDeclList.push_back({type, ""});
    reportError(ctx->getStart()->getLine(), "syntax error, unexpected token(s) '" + ctx->ADDOP()->getText() + "' before ')'");
    logRule(ctx, "parameter_list : parameter_list COMMA type_specifier ADDOP");
    return nullptr;
}

std::any EvaluateVisitor::visitCompoundStmtWithBody(CSubset_2205126Parser::CompoundStmtWithBodyContext *ctx) {
    bool isFuncBody = (dynamic_cast<CSubset_2205126Parser::FuncDefWithParamsContext*>(ctx->parent) != nullptr) || 
                      (dynamic_cast<CSubset_2205126Parser::FuncDefNoParamsContext*>(ctx->parent) != nullptr);
    
    if (!isFuncBody) st.enterScope();
    visit(ctx->statements());
    logRule(ctx, "compound_statement : LCURL statements RCURL");
    st.exitScope(logFile); 
    return nullptr;
}

std::any EvaluateVisitor::visitCompoundStmtEmpty(CSubset_2205126Parser::CompoundStmtEmptyContext *ctx) {
    bool isFuncBody = (dynamic_cast<CSubset_2205126Parser::FuncDefWithParamsContext*>(ctx->parent) != nullptr) || 
                      (dynamic_cast<CSubset_2205126Parser::FuncDefNoParamsContext*>(ctx->parent) != nullptr);
    if (!isFuncBody) st.enterScope();
    logRule(ctx, "compound_statement : LCURL RCURL");
    st.exitScope(logFile);
    return nullptr;
}

std::any EvaluateVisitor::visitVarDecl(CSubset_2205126Parser::VarDeclContext *ctx) {
    string type = safeGetTypeSpecifier(visit(ctx->type_specifier()));
    currentVarDeclType = type;
    visit(ctx->declaration_list());
    logRule(ctx, "var_declaration : type_specifier declaration_list SEMICOLON");
    return nullptr;
}

std::any EvaluateVisitor::visitTypeInt(CSubset_2205126Parser::TypeIntContext *ctx) {
    logRule(ctx, "type_specifier : INT");
    return string("int");
}

std::any EvaluateVisitor::visitTypeFloat(CSubset_2205126Parser::TypeFloatContext *ctx) {
    logRule(ctx, "type_specifier : FLOAT");
    return string("float");
}

std::any EvaluateVisitor::visitTypeVoid(CSubset_2205126Parser::TypeVoidContext *ctx) {
    logRule(ctx, "type_specifier : VOID");
    return string("void");
}

std::any EvaluateVisitor::visitDeclListMultiple(CSubset_2205126Parser::DeclListMultipleContext *ctx) {
    visit(ctx->declaration_list());
    declareVariable(ctx->ID()->getText(), false, 0, ctx->getStart()->getLine());
    logRule(ctx, "declaration_list : declaration_list COMMA ID");
    return nullptr;
}

std::any EvaluateVisitor::visitDeclListMultipleArray(CSubset_2205126Parser::DeclListMultipleArrayContext *ctx) {
    visit(ctx->declaration_list());
    declareVariable(ctx->ID()->getText(), true, stoi(ctx->CONST_INT()->getText()), ctx->getStart()->getLine());
    logRule(ctx, "declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD");
    return nullptr;
}

std::any EvaluateVisitor::visitDeclListSingle(CSubset_2205126Parser::DeclListSingleContext *ctx) {
    declareVariable(ctx->ID()->getText(), false, 0, ctx->getStart()->getLine());
    logRule(ctx, "declaration_list : ID");
    return nullptr;
}

std::any EvaluateVisitor::visitDeclListSingleArray(CSubset_2205126Parser::DeclListSingleArrayContext *ctx) {
    declareVariable(ctx->ID()->getText(), true, stoi(ctx->CONST_INT()->getText()), ctx->getStart()->getLine());
    logRule(ctx, "declaration_list : ID LTHIRD CONST_INT RTHIRD");
    return nullptr;
}

std::any EvaluateVisitor::visitDeclListErrorSub(CSubset_2205126Parser::DeclListErrorSubContext *ctx) {
    string name1 = ctx->ID(0)->getText();
    string name2 = ctx->ID(1)->getText();
    string op = ctx->ADDOP()->getText();
    declareVariable(name1, false, 0, ctx->getStart()->getLine());
    reportError(ctx->getStart()->getLine(), "syntax error, unexpected token(s) '" + op + " " + name2 + "' in declaration list");
    logRule(ctx, "declaration_list : ID ADDOP ID");
    return nullptr;
}

std::any EvaluateVisitor::visitDeclListErrorSubMultiple(CSubset_2205126Parser::DeclListErrorSubMultipleContext *ctx) {
    visit(ctx->declaration_list());
    string name1 = ctx->ID(0)->getText();
    string name2 = ctx->ID(1)->getText();
    string op = ctx->ADDOP()->getText();
    declareVariable(name1, false, 0, ctx->getStart()->getLine());
    reportError(ctx->getStart()->getLine(), "syntax error, unexpected token(s) '" + op + " " + name2 + "' in declaration list");
    logRule(ctx, "declaration_list : declaration_list COMMA ID ADDOP ID");
    return nullptr;
}

void EvaluateVisitor::declareVariable(string name, bool isArray, int size, int line) {
    if (currentVarDeclType == "void") {
        reportError(line, "Variable type cannot be void");
        return;
    }
    if (st.lookupCurrentScope(name) != nullptr) {
        reportError(line, "Multiple declaration of " + name);
    } else {
        SymbolInfo* sym = new SymbolInfo(name, "ID");
        sym->setDataType(currentVarDeclType);
        if (isArray) {
            sym->setIsArray(true);
            sym->setArraySize(size);
        }
        st.insert(sym);
    }
}

std::any EvaluateVisitor::visitStmtsSingle(CSubset_2205126Parser::StmtsSingleContext *ctx) {
    visit(ctx->statement());
    logRule(ctx, "statements : statement");
    return nullptr;
}

std::any EvaluateVisitor::visitStmtsMultiple(CSubset_2205126Parser::StmtsMultipleContext *ctx) {
    visit(ctx->statements());
    visit(ctx->statement());
    logRule(ctx, "statements : statements statement");
    return nullptr;
}

std::any EvaluateVisitor::visitStmtVarDecl(CSubset_2205126Parser::StmtVarDeclContext *ctx) {
    visit(ctx->var_declaration());
    logRule(ctx, "statement : var_declaration");
    return nullptr;
}

std::any EvaluateVisitor::visitStmtExpr(CSubset_2205126Parser::StmtExprContext *ctx) {
    visit(ctx->expression_statement());
    logRule(ctx, "statement : expression_statement");
    return nullptr;
}

std::any EvaluateVisitor::visitStmtCompound(CSubset_2205126Parser::StmtCompoundContext *ctx) {
    visit(ctx->compound_statement());
    logRule(ctx, "statement : compound_statement");
    return nullptr;
}

std::any EvaluateVisitor::visitStmtFor(CSubset_2205126Parser::StmtForContext *ctx) {
    visit(ctx->expression_statement(0));
    visit(ctx->expression_statement(1));
    visit(ctx->expression());
    visit(ctx->statement());
    logRule(ctx, "statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement");
    return nullptr;
}

std::any EvaluateVisitor::visitStmtIfElse(CSubset_2205126Parser::StmtIfElseContext *ctx) {
    visit(ctx->expression());
    visit(ctx->statement(0));
    visit(ctx->statement(1));
    logRule(ctx, "statement : IF LPAREN expression RPAREN statement ELSE statement");
    return nullptr;
}

std::any EvaluateVisitor::visitStmtIf(CSubset_2205126Parser::StmtIfContext *ctx) {
    visit(ctx->expression());
    visit(ctx->statement());
    logRule(ctx, "statement : IF LPAREN expression RPAREN statement");
    return nullptr;
}

std::any EvaluateVisitor::visitStmtWhile(CSubset_2205126Parser::StmtWhileContext *ctx) {
    visit(ctx->expression());
    visit(ctx->statement());
    logRule(ctx, "statement : WHILE LPAREN expression RPAREN statement");
    return nullptr;
}

std::any EvaluateVisitor::visitStmtPrint(CSubset_2205126Parser::StmtPrintContext *ctx) {
    string name = ctx->ID()->getText();
    if (st.lookup(name) == nullptr) {
        reportError(ctx->getStart()->getLine(), "Undeclared variable " + name);
    }
    logRule(ctx, "statement : PRINTLN LPAREN ID RPAREN SEMICOLON");
    return nullptr;
}

std::any EvaluateVisitor::visitStmtReturn(CSubset_2205126Parser::StmtReturnContext *ctx) {
    ExprTypeInfo expType = safeGetExprType(visit(ctx->expression()));
    if (currentFunctionReturnType != "void" && expType.type == "void") {
        reportError(ctx->getStart()->getLine(), "Return type mismatch");
    }
    logRule(ctx, "statement : RETURN expression SEMICOLON");
    return nullptr;
}

std::any EvaluateVisitor::visitExprStmtEmpty(CSubset_2205126Parser::ExprStmtEmptyContext *ctx) {
    logRule(ctx, "expression_statement : SEMICOLON");
    return nullptr;
}

std::any EvaluateVisitor::visitExprStmtExpr(CSubset_2205126Parser::ExprStmtExprContext *ctx) {
    visit(ctx->expression());
    logRule(ctx, "expression_statement : expression SEMICOLON");
    return nullptr;
}

std::any EvaluateVisitor::visitExprStmtMissingSemicolon(CSubset_2205126Parser::ExprStmtMissingSemicolonContext *ctx) {
    visit(ctx->expression());
    reportError(ctx->getStart()->getLine(), "syntax error, missing ';' after expression '" + getText(ctx) + "'");
    logRule(ctx, "expression_statement : expression (missing SEMICOLON)");
    return nullptr;
}

std::any EvaluateVisitor::visitVarId(CSubset_2205126Parser::VarIdContext *ctx) {
    string name = ctx->ID()->getText();
    int line = ctx->getStart()->getLine();
    SymbolInfo* sym = st.lookup(name);
    
    logRule(ctx, "variable : ID");
    
    if (sym == nullptr) {
        reportError(line, "Undeclared variable " + name);
        return ExprTypeInfo("error");
    }
    if (sym->getIsArray()) {
        reportError(line, "Type mismatch, " + name + " is an array");
        return ExprTypeInfo("error");
    }
    return ExprTypeInfo(sym->getDataType());
}

std::any EvaluateVisitor::visitVarArray(CSubset_2205126Parser::VarArrayContext *ctx) {
    string name = ctx->ID()->getText();
    int line = ctx->getStart()->getLine();
    SymbolInfo* sym = st.lookup(name);
    
    ExprTypeInfo idxType = safeGetExprType(visit(ctx->expression()));
    if (idxType.type != "int" && idxType.type != "error") {
        reportError(line, "Expression inside third brackets not an integer");
    }
    
    logRule(ctx, "variable : ID LTHIRD expression RTHIRD");

    if (sym == nullptr) {
        reportError(line, "Undeclared variable " + name);
        return ExprTypeInfo("error");
    }
    if (!sym->getIsArray()) {
        reportError(line, name + " not an array");
        return ExprTypeInfo("error");
    }
    return ExprTypeInfo(sym->getDataType());
}

std::any EvaluateVisitor::visitExprLogic(CSubset_2205126Parser::ExprLogicContext *ctx) {
    auto res = visit(ctx->logic_expression());
    logRule(ctx, "expression : logic_expression");
    return res;
}

std::any EvaluateVisitor::visitExprAssign(CSubset_2205126Parser::ExprAssignContext *ctx) {
    ExprTypeInfo leftType = safeGetExprType(visit(ctx->variable()));
    ExprTypeInfo rightType = safeGetExprType(visit(ctx->logic_expression()));
    int line = ctx->getStart()->getLine();

    if (leftType.type != "error" && rightType.type != "error") {
        if (rightType.type == "void" || leftType.type == "void") {
            reportError(line, "Void function used in expression");
        } else if (leftType.type == "int" && rightType.type == "float") {
            reportError(line, "Type Mismatch");
        }
    }
    logRule(ctx, "expression : variable ASSIGNOP logic_expression");
    return leftType;
}

std::any EvaluateVisitor::visitLogicRel(CSubset_2205126Parser::LogicRelContext *ctx) {
    auto res = visit(ctx->rel_expression());
    logRule(ctx, "logic_expression : rel_expression");
    return res;
}

std::any EvaluateVisitor::visitLogicOp(CSubset_2205126Parser::LogicOpContext *ctx) {
    ExprTypeInfo leftType = safeGetExprType(visit(ctx->rel_expression(0)));
    ExprTypeInfo rightType = safeGetExprType(visit(ctx->rel_expression(1)));
    if (leftType.type == "void" || rightType.type == "void") {
        reportError(ctx->getStart()->getLine(), "Void function used in expression");
    }
    logRule(ctx, "logic_expression : rel_expression LOGICOP rel_expression");
    return ExprTypeInfo("int");
}

std::any EvaluateVisitor::visitRelSimple(CSubset_2205126Parser::RelSimpleContext *ctx) {
    auto res = visit(ctx->simple_expression());
    logRule(ctx, "rel_expression : simple_expression");
    return res;
}

std::any EvaluateVisitor::visitRelOp(CSubset_2205126Parser::RelOpContext *ctx) {
    ExprTypeInfo leftType = safeGetExprType(visit(ctx->simple_expression(0)));
    ExprTypeInfo rightType = safeGetExprType(visit(ctx->simple_expression(1)));
    if (leftType.type == "void" || rightType.type == "void") {
        reportError(ctx->getStart()->getLine(), "Void function used in expression");
    }
    logRule(ctx, "rel_expression : simple_expression RELOP simple_expression");
    return ExprTypeInfo("int");
}

std::any EvaluateVisitor::visitSimpTerm(CSubset_2205126Parser::SimpTermContext *ctx) {
    auto res = visit(ctx->term());
    logRule(ctx, "simple_expression : term");
    return res;
}

std::any EvaluateVisitor::visitSimpAdd(CSubset_2205126Parser::SimpAddContext *ctx) {
    ExprTypeInfo leftType = safeGetExprType(visit(ctx->simple_expression()));
    ExprTypeInfo rightType = safeGetExprType(visit(ctx->term()));
    if (leftType.type == "void" || rightType.type == "void") {
        reportError(ctx->getStart()->getLine(), "Void function used in expression");
    }
    logRule(ctx, "simple_expression : simple_expression ADDOP term");
    if (leftType.type == "float" || rightType.type == "float") {
        return ExprTypeInfo("float");
    }
    return ExprTypeInfo("int");
}

std::any EvaluateVisitor::visitTermUnary(CSubset_2205126Parser::TermUnaryContext *ctx) {
    auto res = visit(ctx->unary_expression());
    logRule(ctx, "term : unary_expression");
    return res;
}

std::any EvaluateVisitor::visitTermMul(CSubset_2205126Parser::TermMulContext *ctx) {
    ExprTypeInfo leftType = safeGetExprType(visit(ctx->term()));
    ExprTypeInfo rightType = safeGetExprType(visit(ctx->unary_expression()));
    int line = ctx->getStart()->getLine();

    if (leftType.type == "void" || rightType.type == "void") {
        reportError(line, "Void function used in expression");
    }

    string op = ctx->MULOP()->getText();
    logRule(ctx, "term : term MULOP unary_expression");

    if (op == "%") {
        if (leftType.type != "int" || rightType.type != "int") {
            reportError(line, "Non-Integer operand on modulus operator");
        }
        if (rightType.textVal == "0") {
            reportError(line, "Modulus by Zero");
        }
        return ExprTypeInfo("int");
    } else {
        if (leftType.type == "float" || rightType.type == "float") {
            return ExprTypeInfo("float");
        }
        return ExprTypeInfo("int");
    }
}

std::any EvaluateVisitor::visitUnaryAdd(CSubset_2205126Parser::UnaryAddContext *ctx) {
    auto res = visit(ctx->unary_expression());
    logRule(ctx, "unary_expression : ADDOP unary_expression");
    return res;
}

std::any EvaluateVisitor::visitUnaryNot(CSubset_2205126Parser::UnaryNotContext *ctx) {
    visit(ctx->unary_expression());
    logRule(ctx, "unary_expression : NOT unary_expression");
    return ExprTypeInfo("int");
}

std::any EvaluateVisitor::visitUnaryFactor(CSubset_2205126Parser::UnaryFactorContext *ctx) {
    auto res = visit(ctx->factor());
    logRule(ctx, "unary_expression : factor");
    return res;
}

std::any EvaluateVisitor::visitFactorVar(CSubset_2205126Parser::FactorVarContext *ctx) {
    auto res = visit(ctx->variable());
    logRule(ctx, "factor : variable");
    return res;
}

std::any EvaluateVisitor::visitFactorFuncCall(CSubset_2205126Parser::FactorFuncCallContext *ctx) {
    string funcName = ctx->ID()->getText();
    int line = ctx->getStart()->getLine();
    
    currentArgTypes.clear();
    visit(ctx->argument_list()); 
    vector<ExprTypeInfo> args = currentArgTypes;

    SymbolInfo* sym = st.lookup(funcName);
    logRule(ctx, "factor : ID LPAREN argument_list RPAREN");

    if (sym == nullptr) {
        reportError(line, "Undeclared function " + funcName);
        return ExprTypeInfo("error");
    }
    if (!sym->getIsFunction()) {
        reportError(line, funcName + " is not a function");
        return ExprTypeInfo("error");
    }

    vector<string> paramTypes = sym->getParamTypes();
    if (paramTypes.size() != args.size()) {
        reportError(line, "Total number of arguments mismatch in function " + funcName);
    } else {
        for (size_t i = 0; i < args.size(); i++) {
            if (args[i].type != "error" && paramTypes[i] != args[i].type) {
                if (args[i].type == "float" && paramTypes[i] == "int") {
                    reportError(line, to_string(i+1) + "th argument mismatch in function " + funcName);
                } else if (args[i].type == "void") {
                    reportError(line, "Void function used in expression");
                }
            }
        }
    }

    return ExprTypeInfo(sym->getReturnType());
}

std::any EvaluateVisitor::visitFactorParen(CSubset_2205126Parser::FactorParenContext *ctx) {
    auto res = safeGetExprType(visit(ctx->expression()));
    logRule(ctx, "factor : LPAREN expression RPAREN");
    return res;
}

std::any EvaluateVisitor::visitFactorInt(CSubset_2205126Parser::FactorIntContext *ctx) {
    ExprTypeInfo t("int");
    t.textVal = ctx->CONST_INT()->getText();
    logRule(ctx, "factor : CONST_INT");
    return t;
}

std::any EvaluateVisitor::visitFactorFloat(CSubset_2205126Parser::FactorFloatContext *ctx) {
    ExprTypeInfo t("float");
    t.textVal = ctx->CONST_FLOAT()->getText();
    logRule(ctx, "factor : CONST_FLOAT");
    return t;
}

std::any EvaluateVisitor::visitFactorInc(CSubset_2205126Parser::FactorIncContext *ctx) {
    auto res = visit(ctx->variable());
    logRule(ctx, "factor : variable INCOP");
    return res;
}

std::any EvaluateVisitor::visitFactorDec(CSubset_2205126Parser::FactorDecContext *ctx) {
    auto res = visit(ctx->variable());
    logRule(ctx, "factor : variable DECOP");
    return res;
}

std::any EvaluateVisitor::visitArgListArgs(CSubset_2205126Parser::ArgListArgsContext *ctx) {
    visit(ctx->arguments());
    logRule(ctx, "argument_list : arguments");
    return nullptr;
}

std::any EvaluateVisitor::visitArgListEmpty(CSubset_2205126Parser::ArgListEmptyContext *ctx) {
    logRule(ctx, "argument_list : ");
    return nullptr;
}

std::any EvaluateVisitor::visitArgsMultiple(CSubset_2205126Parser::ArgsMultipleContext *ctx) {
    visit(ctx->arguments());
    ExprTypeInfo t = safeGetExprType(visit(ctx->logic_expression()));
    currentArgTypes.push_back(t);
    logRule(ctx, "arguments : arguments COMMA logic_expression");
    return nullptr;
}

std::any EvaluateVisitor::visitArgsSingle(CSubset_2205126Parser::ArgsSingleContext *ctx) {
    ExprTypeInfo t = safeGetExprType(visit(ctx->logic_expression()));
    currentArgTypes.push_back(t);
    logRule(ctx, "arguments : logic_expression");
    return nullptr;
}
