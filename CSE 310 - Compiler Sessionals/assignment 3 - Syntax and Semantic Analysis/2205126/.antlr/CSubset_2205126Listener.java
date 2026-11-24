// Generated from /home/shuvra/Downloads/Assignment3_v11_clear_korbo/CSubset_2205126.g4 by ANTLR 4.13.1
import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link CSubset_2205126Parser}.
 */
public interface CSubset_2205126Listener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by {@link CSubset_2205126Parser#start}.
	 * @param ctx the parse tree
	 */
	void enterStart(CSubset_2205126Parser.StartContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSubset_2205126Parser#start}.
	 * @param ctx the parse tree
	 */
	void exitStart(CSubset_2205126Parser.StartContext ctx);
	/**
	 * Enter a parse tree produced by the {@code SingleUnit}
	 * labeled alternative in {@link CSubset_2205126Parser#program}.
	 * @param ctx the parse tree
	 */
	void enterSingleUnit(CSubset_2205126Parser.SingleUnitContext ctx);
	/**
	 * Exit a parse tree produced by the {@code SingleUnit}
	 * labeled alternative in {@link CSubset_2205126Parser#program}.
	 * @param ctx the parse tree
	 */
	void exitSingleUnit(CSubset_2205126Parser.SingleUnitContext ctx);
	/**
	 * Enter a parse tree produced by the {@code ProgUnit}
	 * labeled alternative in {@link CSubset_2205126Parser#program}.
	 * @param ctx the parse tree
	 */
	void enterProgUnit(CSubset_2205126Parser.ProgUnitContext ctx);
	/**
	 * Exit a parse tree produced by the {@code ProgUnit}
	 * labeled alternative in {@link CSubset_2205126Parser#program}.
	 * @param ctx the parse tree
	 */
	void exitProgUnit(CSubset_2205126Parser.ProgUnitContext ctx);
	/**
	 * Enter a parse tree produced by the {@code UnitVarDecl}
	 * labeled alternative in {@link CSubset_2205126Parser#unit}.
	 * @param ctx the parse tree
	 */
	void enterUnitVarDecl(CSubset_2205126Parser.UnitVarDeclContext ctx);
	/**
	 * Exit a parse tree produced by the {@code UnitVarDecl}
	 * labeled alternative in {@link CSubset_2205126Parser#unit}.
	 * @param ctx the parse tree
	 */
	void exitUnitVarDecl(CSubset_2205126Parser.UnitVarDeclContext ctx);
	/**
	 * Enter a parse tree produced by the {@code UnitFuncDecl}
	 * labeled alternative in {@link CSubset_2205126Parser#unit}.
	 * @param ctx the parse tree
	 */
	void enterUnitFuncDecl(CSubset_2205126Parser.UnitFuncDeclContext ctx);
	/**
	 * Exit a parse tree produced by the {@code UnitFuncDecl}
	 * labeled alternative in {@link CSubset_2205126Parser#unit}.
	 * @param ctx the parse tree
	 */
	void exitUnitFuncDecl(CSubset_2205126Parser.UnitFuncDeclContext ctx);
	/**
	 * Enter a parse tree produced by the {@code UnitFuncDef}
	 * labeled alternative in {@link CSubset_2205126Parser#unit}.
	 * @param ctx the parse tree
	 */
	void enterUnitFuncDef(CSubset_2205126Parser.UnitFuncDefContext ctx);
	/**
	 * Exit a parse tree produced by the {@code UnitFuncDef}
	 * labeled alternative in {@link CSubset_2205126Parser#unit}.
	 * @param ctx the parse tree
	 */
	void exitUnitFuncDef(CSubset_2205126Parser.UnitFuncDefContext ctx);
	/**
	 * Enter a parse tree produced by the {@code FuncDeclWithParams}
	 * labeled alternative in {@link CSubset_2205126Parser#func_declaration}.
	 * @param ctx the parse tree
	 */
	void enterFuncDeclWithParams(CSubset_2205126Parser.FuncDeclWithParamsContext ctx);
	/**
	 * Exit a parse tree produced by the {@code FuncDeclWithParams}
	 * labeled alternative in {@link CSubset_2205126Parser#func_declaration}.
	 * @param ctx the parse tree
	 */
	void exitFuncDeclWithParams(CSubset_2205126Parser.FuncDeclWithParamsContext ctx);
	/**
	 * Enter a parse tree produced by the {@code FuncDeclNoParams}
	 * labeled alternative in {@link CSubset_2205126Parser#func_declaration}.
	 * @param ctx the parse tree
	 */
	void enterFuncDeclNoParams(CSubset_2205126Parser.FuncDeclNoParamsContext ctx);
	/**
	 * Exit a parse tree produced by the {@code FuncDeclNoParams}
	 * labeled alternative in {@link CSubset_2205126Parser#func_declaration}.
	 * @param ctx the parse tree
	 */
	void exitFuncDeclNoParams(CSubset_2205126Parser.FuncDeclNoParamsContext ctx);
	/**
	 * Enter a parse tree produced by the {@code FuncDefWithParams}
	 * labeled alternative in {@link CSubset_2205126Parser#func_definition}.
	 * @param ctx the parse tree
	 */
	void enterFuncDefWithParams(CSubset_2205126Parser.FuncDefWithParamsContext ctx);
	/**
	 * Exit a parse tree produced by the {@code FuncDefWithParams}
	 * labeled alternative in {@link CSubset_2205126Parser#func_definition}.
	 * @param ctx the parse tree
	 */
	void exitFuncDefWithParams(CSubset_2205126Parser.FuncDefWithParamsContext ctx);
	/**
	 * Enter a parse tree produced by the {@code FuncDefNoParams}
	 * labeled alternative in {@link CSubset_2205126Parser#func_definition}.
	 * @param ctx the parse tree
	 */
	void enterFuncDefNoParams(CSubset_2205126Parser.FuncDefNoParamsContext ctx);
	/**
	 * Exit a parse tree produced by the {@code FuncDefNoParams}
	 * labeled alternative in {@link CSubset_2205126Parser#func_definition}.
	 * @param ctx the parse tree
	 */
	void exitFuncDefNoParams(CSubset_2205126Parser.FuncDefNoParamsContext ctx);
	/**
	 * Enter a parse tree produced by the {@code ParamListErrorSubMultiple}
	 * labeled alternative in {@link CSubset_2205126Parser#parameter_list}.
	 * @param ctx the parse tree
	 */
	void enterParamListErrorSubMultiple(CSubset_2205126Parser.ParamListErrorSubMultipleContext ctx);
	/**
	 * Exit a parse tree produced by the {@code ParamListErrorSubMultiple}
	 * labeled alternative in {@link CSubset_2205126Parser#parameter_list}.
	 * @param ctx the parse tree
	 */
	void exitParamListErrorSubMultiple(CSubset_2205126Parser.ParamListErrorSubMultipleContext ctx);
	/**
	 * Enter a parse tree produced by the {@code ParamListSingle}
	 * labeled alternative in {@link CSubset_2205126Parser#parameter_list}.
	 * @param ctx the parse tree
	 */
	void enterParamListSingle(CSubset_2205126Parser.ParamListSingleContext ctx);
	/**
	 * Exit a parse tree produced by the {@code ParamListSingle}
	 * labeled alternative in {@link CSubset_2205126Parser#parameter_list}.
	 * @param ctx the parse tree
	 */
	void exitParamListSingle(CSubset_2205126Parser.ParamListSingleContext ctx);
	/**
	 * Enter a parse tree produced by the {@code ParamListMultipleNoID}
	 * labeled alternative in {@link CSubset_2205126Parser#parameter_list}.
	 * @param ctx the parse tree
	 */
	void enterParamListMultipleNoID(CSubset_2205126Parser.ParamListMultipleNoIDContext ctx);
	/**
	 * Exit a parse tree produced by the {@code ParamListMultipleNoID}
	 * labeled alternative in {@link CSubset_2205126Parser#parameter_list}.
	 * @param ctx the parse tree
	 */
	void exitParamListMultipleNoID(CSubset_2205126Parser.ParamListMultipleNoIDContext ctx);
	/**
	 * Enter a parse tree produced by the {@code ParamListMultiple}
	 * labeled alternative in {@link CSubset_2205126Parser#parameter_list}.
	 * @param ctx the parse tree
	 */
	void enterParamListMultiple(CSubset_2205126Parser.ParamListMultipleContext ctx);
	/**
	 * Exit a parse tree produced by the {@code ParamListMultiple}
	 * labeled alternative in {@link CSubset_2205126Parser#parameter_list}.
	 * @param ctx the parse tree
	 */
	void exitParamListMultiple(CSubset_2205126Parser.ParamListMultipleContext ctx);
	/**
	 * Enter a parse tree produced by the {@code ParamListSingleNoID}
	 * labeled alternative in {@link CSubset_2205126Parser#parameter_list}.
	 * @param ctx the parse tree
	 */
	void enterParamListSingleNoID(CSubset_2205126Parser.ParamListSingleNoIDContext ctx);
	/**
	 * Exit a parse tree produced by the {@code ParamListSingleNoID}
	 * labeled alternative in {@link CSubset_2205126Parser#parameter_list}.
	 * @param ctx the parse tree
	 */
	void exitParamListSingleNoID(CSubset_2205126Parser.ParamListSingleNoIDContext ctx);
	/**
	 * Enter a parse tree produced by the {@code ParamListErrorSub}
	 * labeled alternative in {@link CSubset_2205126Parser#parameter_list}.
	 * @param ctx the parse tree
	 */
	void enterParamListErrorSub(CSubset_2205126Parser.ParamListErrorSubContext ctx);
	/**
	 * Exit a parse tree produced by the {@code ParamListErrorSub}
	 * labeled alternative in {@link CSubset_2205126Parser#parameter_list}.
	 * @param ctx the parse tree
	 */
	void exitParamListErrorSub(CSubset_2205126Parser.ParamListErrorSubContext ctx);
	/**
	 * Enter a parse tree produced by the {@code CompoundStmtWithBody}
	 * labeled alternative in {@link CSubset_2205126Parser#compound_statement}.
	 * @param ctx the parse tree
	 */
	void enterCompoundStmtWithBody(CSubset_2205126Parser.CompoundStmtWithBodyContext ctx);
	/**
	 * Exit a parse tree produced by the {@code CompoundStmtWithBody}
	 * labeled alternative in {@link CSubset_2205126Parser#compound_statement}.
	 * @param ctx the parse tree
	 */
	void exitCompoundStmtWithBody(CSubset_2205126Parser.CompoundStmtWithBodyContext ctx);
	/**
	 * Enter a parse tree produced by the {@code CompoundStmtEmpty}
	 * labeled alternative in {@link CSubset_2205126Parser#compound_statement}.
	 * @param ctx the parse tree
	 */
	void enterCompoundStmtEmpty(CSubset_2205126Parser.CompoundStmtEmptyContext ctx);
	/**
	 * Exit a parse tree produced by the {@code CompoundStmtEmpty}
	 * labeled alternative in {@link CSubset_2205126Parser#compound_statement}.
	 * @param ctx the parse tree
	 */
	void exitCompoundStmtEmpty(CSubset_2205126Parser.CompoundStmtEmptyContext ctx);
	/**
	 * Enter a parse tree produced by the {@code VarDecl}
	 * labeled alternative in {@link CSubset_2205126Parser#var_declaration}.
	 * @param ctx the parse tree
	 */
	void enterVarDecl(CSubset_2205126Parser.VarDeclContext ctx);
	/**
	 * Exit a parse tree produced by the {@code VarDecl}
	 * labeled alternative in {@link CSubset_2205126Parser#var_declaration}.
	 * @param ctx the parse tree
	 */
	void exitVarDecl(CSubset_2205126Parser.VarDeclContext ctx);
	/**
	 * Enter a parse tree produced by the {@code TypeInt}
	 * labeled alternative in {@link CSubset_2205126Parser#type_specifier}.
	 * @param ctx the parse tree
	 */
	void enterTypeInt(CSubset_2205126Parser.TypeIntContext ctx);
	/**
	 * Exit a parse tree produced by the {@code TypeInt}
	 * labeled alternative in {@link CSubset_2205126Parser#type_specifier}.
	 * @param ctx the parse tree
	 */
	void exitTypeInt(CSubset_2205126Parser.TypeIntContext ctx);
	/**
	 * Enter a parse tree produced by the {@code TypeFloat}
	 * labeled alternative in {@link CSubset_2205126Parser#type_specifier}.
	 * @param ctx the parse tree
	 */
	void enterTypeFloat(CSubset_2205126Parser.TypeFloatContext ctx);
	/**
	 * Exit a parse tree produced by the {@code TypeFloat}
	 * labeled alternative in {@link CSubset_2205126Parser#type_specifier}.
	 * @param ctx the parse tree
	 */
	void exitTypeFloat(CSubset_2205126Parser.TypeFloatContext ctx);
	/**
	 * Enter a parse tree produced by the {@code TypeVoid}
	 * labeled alternative in {@link CSubset_2205126Parser#type_specifier}.
	 * @param ctx the parse tree
	 */
	void enterTypeVoid(CSubset_2205126Parser.TypeVoidContext ctx);
	/**
	 * Exit a parse tree produced by the {@code TypeVoid}
	 * labeled alternative in {@link CSubset_2205126Parser#type_specifier}.
	 * @param ctx the parse tree
	 */
	void exitTypeVoid(CSubset_2205126Parser.TypeVoidContext ctx);
	/**
	 * Enter a parse tree produced by the {@code DeclListSingle}
	 * labeled alternative in {@link CSubset_2205126Parser#declaration_list}.
	 * @param ctx the parse tree
	 */
	void enterDeclListSingle(CSubset_2205126Parser.DeclListSingleContext ctx);
	/**
	 * Exit a parse tree produced by the {@code DeclListSingle}
	 * labeled alternative in {@link CSubset_2205126Parser#declaration_list}.
	 * @param ctx the parse tree
	 */
	void exitDeclListSingle(CSubset_2205126Parser.DeclListSingleContext ctx);
	/**
	 * Enter a parse tree produced by the {@code DeclListMultipleArray}
	 * labeled alternative in {@link CSubset_2205126Parser#declaration_list}.
	 * @param ctx the parse tree
	 */
	void enterDeclListMultipleArray(CSubset_2205126Parser.DeclListMultipleArrayContext ctx);
	/**
	 * Exit a parse tree produced by the {@code DeclListMultipleArray}
	 * labeled alternative in {@link CSubset_2205126Parser#declaration_list}.
	 * @param ctx the parse tree
	 */
	void exitDeclListMultipleArray(CSubset_2205126Parser.DeclListMultipleArrayContext ctx);
	/**
	 * Enter a parse tree produced by the {@code DeclListMultiple}
	 * labeled alternative in {@link CSubset_2205126Parser#declaration_list}.
	 * @param ctx the parse tree
	 */
	void enterDeclListMultiple(CSubset_2205126Parser.DeclListMultipleContext ctx);
	/**
	 * Exit a parse tree produced by the {@code DeclListMultiple}
	 * labeled alternative in {@link CSubset_2205126Parser#declaration_list}.
	 * @param ctx the parse tree
	 */
	void exitDeclListMultiple(CSubset_2205126Parser.DeclListMultipleContext ctx);
	/**
	 * Enter a parse tree produced by the {@code DeclListSingleArray}
	 * labeled alternative in {@link CSubset_2205126Parser#declaration_list}.
	 * @param ctx the parse tree
	 */
	void enterDeclListSingleArray(CSubset_2205126Parser.DeclListSingleArrayContext ctx);
	/**
	 * Exit a parse tree produced by the {@code DeclListSingleArray}
	 * labeled alternative in {@link CSubset_2205126Parser#declaration_list}.
	 * @param ctx the parse tree
	 */
	void exitDeclListSingleArray(CSubset_2205126Parser.DeclListSingleArrayContext ctx);
	/**
	 * Enter a parse tree produced by the {@code DeclListErrorSub}
	 * labeled alternative in {@link CSubset_2205126Parser#declaration_list}.
	 * @param ctx the parse tree
	 */
	void enterDeclListErrorSub(CSubset_2205126Parser.DeclListErrorSubContext ctx);
	/**
	 * Exit a parse tree produced by the {@code DeclListErrorSub}
	 * labeled alternative in {@link CSubset_2205126Parser#declaration_list}.
	 * @param ctx the parse tree
	 */
	void exitDeclListErrorSub(CSubset_2205126Parser.DeclListErrorSubContext ctx);
	/**
	 * Enter a parse tree produced by the {@code DeclListErrorSubMultiple}
	 * labeled alternative in {@link CSubset_2205126Parser#declaration_list}.
	 * @param ctx the parse tree
	 */
	void enterDeclListErrorSubMultiple(CSubset_2205126Parser.DeclListErrorSubMultipleContext ctx);
	/**
	 * Exit a parse tree produced by the {@code DeclListErrorSubMultiple}
	 * labeled alternative in {@link CSubset_2205126Parser#declaration_list}.
	 * @param ctx the parse tree
	 */
	void exitDeclListErrorSubMultiple(CSubset_2205126Parser.DeclListErrorSubMultipleContext ctx);
	/**
	 * Enter a parse tree produced by the {@code StmtsSingle}
	 * labeled alternative in {@link CSubset_2205126Parser#statements}.
	 * @param ctx the parse tree
	 */
	void enterStmtsSingle(CSubset_2205126Parser.StmtsSingleContext ctx);
	/**
	 * Exit a parse tree produced by the {@code StmtsSingle}
	 * labeled alternative in {@link CSubset_2205126Parser#statements}.
	 * @param ctx the parse tree
	 */
	void exitStmtsSingle(CSubset_2205126Parser.StmtsSingleContext ctx);
	/**
	 * Enter a parse tree produced by the {@code StmtsMultiple}
	 * labeled alternative in {@link CSubset_2205126Parser#statements}.
	 * @param ctx the parse tree
	 */
	void enterStmtsMultiple(CSubset_2205126Parser.StmtsMultipleContext ctx);
	/**
	 * Exit a parse tree produced by the {@code StmtsMultiple}
	 * labeled alternative in {@link CSubset_2205126Parser#statements}.
	 * @param ctx the parse tree
	 */
	void exitStmtsMultiple(CSubset_2205126Parser.StmtsMultipleContext ctx);
	/**
	 * Enter a parse tree produced by the {@code StmtVarDecl}
	 * labeled alternative in {@link CSubset_2205126Parser#statement}.
	 * @param ctx the parse tree
	 */
	void enterStmtVarDecl(CSubset_2205126Parser.StmtVarDeclContext ctx);
	/**
	 * Exit a parse tree produced by the {@code StmtVarDecl}
	 * labeled alternative in {@link CSubset_2205126Parser#statement}.
	 * @param ctx the parse tree
	 */
	void exitStmtVarDecl(CSubset_2205126Parser.StmtVarDeclContext ctx);
	/**
	 * Enter a parse tree produced by the {@code StmtExpr}
	 * labeled alternative in {@link CSubset_2205126Parser#statement}.
	 * @param ctx the parse tree
	 */
	void enterStmtExpr(CSubset_2205126Parser.StmtExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code StmtExpr}
	 * labeled alternative in {@link CSubset_2205126Parser#statement}.
	 * @param ctx the parse tree
	 */
	void exitStmtExpr(CSubset_2205126Parser.StmtExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code StmtCompound}
	 * labeled alternative in {@link CSubset_2205126Parser#statement}.
	 * @param ctx the parse tree
	 */
	void enterStmtCompound(CSubset_2205126Parser.StmtCompoundContext ctx);
	/**
	 * Exit a parse tree produced by the {@code StmtCompound}
	 * labeled alternative in {@link CSubset_2205126Parser#statement}.
	 * @param ctx the parse tree
	 */
	void exitStmtCompound(CSubset_2205126Parser.StmtCompoundContext ctx);
	/**
	 * Enter a parse tree produced by the {@code StmtFor}
	 * labeled alternative in {@link CSubset_2205126Parser#statement}.
	 * @param ctx the parse tree
	 */
	void enterStmtFor(CSubset_2205126Parser.StmtForContext ctx);
	/**
	 * Exit a parse tree produced by the {@code StmtFor}
	 * labeled alternative in {@link CSubset_2205126Parser#statement}.
	 * @param ctx the parse tree
	 */
	void exitStmtFor(CSubset_2205126Parser.StmtForContext ctx);
	/**
	 * Enter a parse tree produced by the {@code StmtIfElse}
	 * labeled alternative in {@link CSubset_2205126Parser#statement}.
	 * @param ctx the parse tree
	 */
	void enterStmtIfElse(CSubset_2205126Parser.StmtIfElseContext ctx);
	/**
	 * Exit a parse tree produced by the {@code StmtIfElse}
	 * labeled alternative in {@link CSubset_2205126Parser#statement}.
	 * @param ctx the parse tree
	 */
	void exitStmtIfElse(CSubset_2205126Parser.StmtIfElseContext ctx);
	/**
	 * Enter a parse tree produced by the {@code StmtIf}
	 * labeled alternative in {@link CSubset_2205126Parser#statement}.
	 * @param ctx the parse tree
	 */
	void enterStmtIf(CSubset_2205126Parser.StmtIfContext ctx);
	/**
	 * Exit a parse tree produced by the {@code StmtIf}
	 * labeled alternative in {@link CSubset_2205126Parser#statement}.
	 * @param ctx the parse tree
	 */
	void exitStmtIf(CSubset_2205126Parser.StmtIfContext ctx);
	/**
	 * Enter a parse tree produced by the {@code StmtWhile}
	 * labeled alternative in {@link CSubset_2205126Parser#statement}.
	 * @param ctx the parse tree
	 */
	void enterStmtWhile(CSubset_2205126Parser.StmtWhileContext ctx);
	/**
	 * Exit a parse tree produced by the {@code StmtWhile}
	 * labeled alternative in {@link CSubset_2205126Parser#statement}.
	 * @param ctx the parse tree
	 */
	void exitStmtWhile(CSubset_2205126Parser.StmtWhileContext ctx);
	/**
	 * Enter a parse tree produced by the {@code StmtPrint}
	 * labeled alternative in {@link CSubset_2205126Parser#statement}.
	 * @param ctx the parse tree
	 */
	void enterStmtPrint(CSubset_2205126Parser.StmtPrintContext ctx);
	/**
	 * Exit a parse tree produced by the {@code StmtPrint}
	 * labeled alternative in {@link CSubset_2205126Parser#statement}.
	 * @param ctx the parse tree
	 */
	void exitStmtPrint(CSubset_2205126Parser.StmtPrintContext ctx);
	/**
	 * Enter a parse tree produced by the {@code StmtReturn}
	 * labeled alternative in {@link CSubset_2205126Parser#statement}.
	 * @param ctx the parse tree
	 */
	void enterStmtReturn(CSubset_2205126Parser.StmtReturnContext ctx);
	/**
	 * Exit a parse tree produced by the {@code StmtReturn}
	 * labeled alternative in {@link CSubset_2205126Parser#statement}.
	 * @param ctx the parse tree
	 */
	void exitStmtReturn(CSubset_2205126Parser.StmtReturnContext ctx);
	/**
	 * Enter a parse tree produced by the {@code ExprStmtEmpty}
	 * labeled alternative in {@link CSubset_2205126Parser#expression_statement}.
	 * @param ctx the parse tree
	 */
	void enterExprStmtEmpty(CSubset_2205126Parser.ExprStmtEmptyContext ctx);
	/**
	 * Exit a parse tree produced by the {@code ExprStmtEmpty}
	 * labeled alternative in {@link CSubset_2205126Parser#expression_statement}.
	 * @param ctx the parse tree
	 */
	void exitExprStmtEmpty(CSubset_2205126Parser.ExprStmtEmptyContext ctx);
	/**
	 * Enter a parse tree produced by the {@code ExprStmtExpr}
	 * labeled alternative in {@link CSubset_2205126Parser#expression_statement}.
	 * @param ctx the parse tree
	 */
	void enterExprStmtExpr(CSubset_2205126Parser.ExprStmtExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code ExprStmtExpr}
	 * labeled alternative in {@link CSubset_2205126Parser#expression_statement}.
	 * @param ctx the parse tree
	 */
	void exitExprStmtExpr(CSubset_2205126Parser.ExprStmtExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code ExprStmtMissingSemicolon}
	 * labeled alternative in {@link CSubset_2205126Parser#expression_statement}.
	 * @param ctx the parse tree
	 */
	void enterExprStmtMissingSemicolon(CSubset_2205126Parser.ExprStmtMissingSemicolonContext ctx);
	/**
	 * Exit a parse tree produced by the {@code ExprStmtMissingSemicolon}
	 * labeled alternative in {@link CSubset_2205126Parser#expression_statement}.
	 * @param ctx the parse tree
	 */
	void exitExprStmtMissingSemicolon(CSubset_2205126Parser.ExprStmtMissingSemicolonContext ctx);
	/**
	 * Enter a parse tree produced by the {@code VarId}
	 * labeled alternative in {@link CSubset_2205126Parser#variable}.
	 * @param ctx the parse tree
	 */
	void enterVarId(CSubset_2205126Parser.VarIdContext ctx);
	/**
	 * Exit a parse tree produced by the {@code VarId}
	 * labeled alternative in {@link CSubset_2205126Parser#variable}.
	 * @param ctx the parse tree
	 */
	void exitVarId(CSubset_2205126Parser.VarIdContext ctx);
	/**
	 * Enter a parse tree produced by the {@code VarArray}
	 * labeled alternative in {@link CSubset_2205126Parser#variable}.
	 * @param ctx the parse tree
	 */
	void enterVarArray(CSubset_2205126Parser.VarArrayContext ctx);
	/**
	 * Exit a parse tree produced by the {@code VarArray}
	 * labeled alternative in {@link CSubset_2205126Parser#variable}.
	 * @param ctx the parse tree
	 */
	void exitVarArray(CSubset_2205126Parser.VarArrayContext ctx);
	/**
	 * Enter a parse tree produced by the {@code ExprLogic}
	 * labeled alternative in {@link CSubset_2205126Parser#expression}.
	 * @param ctx the parse tree
	 */
	void enterExprLogic(CSubset_2205126Parser.ExprLogicContext ctx);
	/**
	 * Exit a parse tree produced by the {@code ExprLogic}
	 * labeled alternative in {@link CSubset_2205126Parser#expression}.
	 * @param ctx the parse tree
	 */
	void exitExprLogic(CSubset_2205126Parser.ExprLogicContext ctx);
	/**
	 * Enter a parse tree produced by the {@code ExprAssign}
	 * labeled alternative in {@link CSubset_2205126Parser#expression}.
	 * @param ctx the parse tree
	 */
	void enterExprAssign(CSubset_2205126Parser.ExprAssignContext ctx);
	/**
	 * Exit a parse tree produced by the {@code ExprAssign}
	 * labeled alternative in {@link CSubset_2205126Parser#expression}.
	 * @param ctx the parse tree
	 */
	void exitExprAssign(CSubset_2205126Parser.ExprAssignContext ctx);
	/**
	 * Enter a parse tree produced by the {@code LogicRel}
	 * labeled alternative in {@link CSubset_2205126Parser#logic_expression}.
	 * @param ctx the parse tree
	 */
	void enterLogicRel(CSubset_2205126Parser.LogicRelContext ctx);
	/**
	 * Exit a parse tree produced by the {@code LogicRel}
	 * labeled alternative in {@link CSubset_2205126Parser#logic_expression}.
	 * @param ctx the parse tree
	 */
	void exitLogicRel(CSubset_2205126Parser.LogicRelContext ctx);
	/**
	 * Enter a parse tree produced by the {@code LogicOp}
	 * labeled alternative in {@link CSubset_2205126Parser#logic_expression}.
	 * @param ctx the parse tree
	 */
	void enterLogicOp(CSubset_2205126Parser.LogicOpContext ctx);
	/**
	 * Exit a parse tree produced by the {@code LogicOp}
	 * labeled alternative in {@link CSubset_2205126Parser#logic_expression}.
	 * @param ctx the parse tree
	 */
	void exitLogicOp(CSubset_2205126Parser.LogicOpContext ctx);
	/**
	 * Enter a parse tree produced by the {@code RelSimple}
	 * labeled alternative in {@link CSubset_2205126Parser#rel_expression}.
	 * @param ctx the parse tree
	 */
	void enterRelSimple(CSubset_2205126Parser.RelSimpleContext ctx);
	/**
	 * Exit a parse tree produced by the {@code RelSimple}
	 * labeled alternative in {@link CSubset_2205126Parser#rel_expression}.
	 * @param ctx the parse tree
	 */
	void exitRelSimple(CSubset_2205126Parser.RelSimpleContext ctx);
	/**
	 * Enter a parse tree produced by the {@code RelOp}
	 * labeled alternative in {@link CSubset_2205126Parser#rel_expression}.
	 * @param ctx the parse tree
	 */
	void enterRelOp(CSubset_2205126Parser.RelOpContext ctx);
	/**
	 * Exit a parse tree produced by the {@code RelOp}
	 * labeled alternative in {@link CSubset_2205126Parser#rel_expression}.
	 * @param ctx the parse tree
	 */
	void exitRelOp(CSubset_2205126Parser.RelOpContext ctx);
	/**
	 * Enter a parse tree produced by the {@code SimpTerm}
	 * labeled alternative in {@link CSubset_2205126Parser#simple_expression}.
	 * @param ctx the parse tree
	 */
	void enterSimpTerm(CSubset_2205126Parser.SimpTermContext ctx);
	/**
	 * Exit a parse tree produced by the {@code SimpTerm}
	 * labeled alternative in {@link CSubset_2205126Parser#simple_expression}.
	 * @param ctx the parse tree
	 */
	void exitSimpTerm(CSubset_2205126Parser.SimpTermContext ctx);
	/**
	 * Enter a parse tree produced by the {@code SimpAdd}
	 * labeled alternative in {@link CSubset_2205126Parser#simple_expression}.
	 * @param ctx the parse tree
	 */
	void enterSimpAdd(CSubset_2205126Parser.SimpAddContext ctx);
	/**
	 * Exit a parse tree produced by the {@code SimpAdd}
	 * labeled alternative in {@link CSubset_2205126Parser#simple_expression}.
	 * @param ctx the parse tree
	 */
	void exitSimpAdd(CSubset_2205126Parser.SimpAddContext ctx);
	/**
	 * Enter a parse tree produced by the {@code TermUnary}
	 * labeled alternative in {@link CSubset_2205126Parser#term}.
	 * @param ctx the parse tree
	 */
	void enterTermUnary(CSubset_2205126Parser.TermUnaryContext ctx);
	/**
	 * Exit a parse tree produced by the {@code TermUnary}
	 * labeled alternative in {@link CSubset_2205126Parser#term}.
	 * @param ctx the parse tree
	 */
	void exitTermUnary(CSubset_2205126Parser.TermUnaryContext ctx);
	/**
	 * Enter a parse tree produced by the {@code TermMul}
	 * labeled alternative in {@link CSubset_2205126Parser#term}.
	 * @param ctx the parse tree
	 */
	void enterTermMul(CSubset_2205126Parser.TermMulContext ctx);
	/**
	 * Exit a parse tree produced by the {@code TermMul}
	 * labeled alternative in {@link CSubset_2205126Parser#term}.
	 * @param ctx the parse tree
	 */
	void exitTermMul(CSubset_2205126Parser.TermMulContext ctx);
	/**
	 * Enter a parse tree produced by the {@code UnaryAdd}
	 * labeled alternative in {@link CSubset_2205126Parser#unary_expression}.
	 * @param ctx the parse tree
	 */
	void enterUnaryAdd(CSubset_2205126Parser.UnaryAddContext ctx);
	/**
	 * Exit a parse tree produced by the {@code UnaryAdd}
	 * labeled alternative in {@link CSubset_2205126Parser#unary_expression}.
	 * @param ctx the parse tree
	 */
	void exitUnaryAdd(CSubset_2205126Parser.UnaryAddContext ctx);
	/**
	 * Enter a parse tree produced by the {@code UnaryNot}
	 * labeled alternative in {@link CSubset_2205126Parser#unary_expression}.
	 * @param ctx the parse tree
	 */
	void enterUnaryNot(CSubset_2205126Parser.UnaryNotContext ctx);
	/**
	 * Exit a parse tree produced by the {@code UnaryNot}
	 * labeled alternative in {@link CSubset_2205126Parser#unary_expression}.
	 * @param ctx the parse tree
	 */
	void exitUnaryNot(CSubset_2205126Parser.UnaryNotContext ctx);
	/**
	 * Enter a parse tree produced by the {@code UnaryFactor}
	 * labeled alternative in {@link CSubset_2205126Parser#unary_expression}.
	 * @param ctx the parse tree
	 */
	void enterUnaryFactor(CSubset_2205126Parser.UnaryFactorContext ctx);
	/**
	 * Exit a parse tree produced by the {@code UnaryFactor}
	 * labeled alternative in {@link CSubset_2205126Parser#unary_expression}.
	 * @param ctx the parse tree
	 */
	void exitUnaryFactor(CSubset_2205126Parser.UnaryFactorContext ctx);
	/**
	 * Enter a parse tree produced by the {@code FactorVar}
	 * labeled alternative in {@link CSubset_2205126Parser#factor}.
	 * @param ctx the parse tree
	 */
	void enterFactorVar(CSubset_2205126Parser.FactorVarContext ctx);
	/**
	 * Exit a parse tree produced by the {@code FactorVar}
	 * labeled alternative in {@link CSubset_2205126Parser#factor}.
	 * @param ctx the parse tree
	 */
	void exitFactorVar(CSubset_2205126Parser.FactorVarContext ctx);
	/**
	 * Enter a parse tree produced by the {@code FactorFuncCall}
	 * labeled alternative in {@link CSubset_2205126Parser#factor}.
	 * @param ctx the parse tree
	 */
	void enterFactorFuncCall(CSubset_2205126Parser.FactorFuncCallContext ctx);
	/**
	 * Exit a parse tree produced by the {@code FactorFuncCall}
	 * labeled alternative in {@link CSubset_2205126Parser#factor}.
	 * @param ctx the parse tree
	 */
	void exitFactorFuncCall(CSubset_2205126Parser.FactorFuncCallContext ctx);
	/**
	 * Enter a parse tree produced by the {@code FactorParen}
	 * labeled alternative in {@link CSubset_2205126Parser#factor}.
	 * @param ctx the parse tree
	 */
	void enterFactorParen(CSubset_2205126Parser.FactorParenContext ctx);
	/**
	 * Exit a parse tree produced by the {@code FactorParen}
	 * labeled alternative in {@link CSubset_2205126Parser#factor}.
	 * @param ctx the parse tree
	 */
	void exitFactorParen(CSubset_2205126Parser.FactorParenContext ctx);
	/**
	 * Enter a parse tree produced by the {@code FactorInt}
	 * labeled alternative in {@link CSubset_2205126Parser#factor}.
	 * @param ctx the parse tree
	 */
	void enterFactorInt(CSubset_2205126Parser.FactorIntContext ctx);
	/**
	 * Exit a parse tree produced by the {@code FactorInt}
	 * labeled alternative in {@link CSubset_2205126Parser#factor}.
	 * @param ctx the parse tree
	 */
	void exitFactorInt(CSubset_2205126Parser.FactorIntContext ctx);
	/**
	 * Enter a parse tree produced by the {@code FactorFloat}
	 * labeled alternative in {@link CSubset_2205126Parser#factor}.
	 * @param ctx the parse tree
	 */
	void enterFactorFloat(CSubset_2205126Parser.FactorFloatContext ctx);
	/**
	 * Exit a parse tree produced by the {@code FactorFloat}
	 * labeled alternative in {@link CSubset_2205126Parser#factor}.
	 * @param ctx the parse tree
	 */
	void exitFactorFloat(CSubset_2205126Parser.FactorFloatContext ctx);
	/**
	 * Enter a parse tree produced by the {@code FactorInc}
	 * labeled alternative in {@link CSubset_2205126Parser#factor}.
	 * @param ctx the parse tree
	 */
	void enterFactorInc(CSubset_2205126Parser.FactorIncContext ctx);
	/**
	 * Exit a parse tree produced by the {@code FactorInc}
	 * labeled alternative in {@link CSubset_2205126Parser#factor}.
	 * @param ctx the parse tree
	 */
	void exitFactorInc(CSubset_2205126Parser.FactorIncContext ctx);
	/**
	 * Enter a parse tree produced by the {@code FactorDec}
	 * labeled alternative in {@link CSubset_2205126Parser#factor}.
	 * @param ctx the parse tree
	 */
	void enterFactorDec(CSubset_2205126Parser.FactorDecContext ctx);
	/**
	 * Exit a parse tree produced by the {@code FactorDec}
	 * labeled alternative in {@link CSubset_2205126Parser#factor}.
	 * @param ctx the parse tree
	 */
	void exitFactorDec(CSubset_2205126Parser.FactorDecContext ctx);
	/**
	 * Enter a parse tree produced by the {@code ArgListArgs}
	 * labeled alternative in {@link CSubset_2205126Parser#argument_list}.
	 * @param ctx the parse tree
	 */
	void enterArgListArgs(CSubset_2205126Parser.ArgListArgsContext ctx);
	/**
	 * Exit a parse tree produced by the {@code ArgListArgs}
	 * labeled alternative in {@link CSubset_2205126Parser#argument_list}.
	 * @param ctx the parse tree
	 */
	void exitArgListArgs(CSubset_2205126Parser.ArgListArgsContext ctx);
	/**
	 * Enter a parse tree produced by the {@code ArgListEmpty}
	 * labeled alternative in {@link CSubset_2205126Parser#argument_list}.
	 * @param ctx the parse tree
	 */
	void enterArgListEmpty(CSubset_2205126Parser.ArgListEmptyContext ctx);
	/**
	 * Exit a parse tree produced by the {@code ArgListEmpty}
	 * labeled alternative in {@link CSubset_2205126Parser#argument_list}.
	 * @param ctx the parse tree
	 */
	void exitArgListEmpty(CSubset_2205126Parser.ArgListEmptyContext ctx);
	/**
	 * Enter a parse tree produced by the {@code ArgsSingle}
	 * labeled alternative in {@link CSubset_2205126Parser#arguments}.
	 * @param ctx the parse tree
	 */
	void enterArgsSingle(CSubset_2205126Parser.ArgsSingleContext ctx);
	/**
	 * Exit a parse tree produced by the {@code ArgsSingle}
	 * labeled alternative in {@link CSubset_2205126Parser#arguments}.
	 * @param ctx the parse tree
	 */
	void exitArgsSingle(CSubset_2205126Parser.ArgsSingleContext ctx);
	/**
	 * Enter a parse tree produced by the {@code ArgsMultiple}
	 * labeled alternative in {@link CSubset_2205126Parser#arguments}.
	 * @param ctx the parse tree
	 */
	void enterArgsMultiple(CSubset_2205126Parser.ArgsMultipleContext ctx);
	/**
	 * Exit a parse tree produced by the {@code ArgsMultiple}
	 * labeled alternative in {@link CSubset_2205126Parser#arguments}.
	 * @param ctx the parse tree
	 */
	void exitArgsMultiple(CSubset_2205126Parser.ArgsMultipleContext ctx);
}