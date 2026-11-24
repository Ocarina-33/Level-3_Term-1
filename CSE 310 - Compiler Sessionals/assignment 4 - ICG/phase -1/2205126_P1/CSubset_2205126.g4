grammar CSubset_2205126;
import Lexer_2205126;

start : program EOF ;

program
    : program unit #ProgUnit
    | unit         #SingleUnit
    ;

unit
    : var_declaration  #UnitVarDecl
    | func_declaration #UnitFuncDecl
    | func_definition  #UnitFuncDef
    ;

func_declaration
    : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON #FuncDeclWithParams
    | type_specifier ID LPAREN RPAREN SEMICOLON                #FuncDeclNoParams
    ;

func_definition
    : type_specifier ID LPAREN parameter_list RPAREN compound_statement #FuncDefWithParams
    | type_specifier ID LPAREN RPAREN compound_statement                #FuncDefNoParams
    ;

parameter_list
    : parameter_list COMMA type_specifier ID #ParamListMultiple
    | parameter_list COMMA type_specifier    #ParamListMultipleNoID
    | type_specifier ID                      #ParamListSingle
    | type_specifier                         #ParamListSingleNoID
    | type_specifier ADDOP                   #ParamListErrorSub
    | parameter_list COMMA type_specifier ADDOP #ParamListErrorSubMultiple
    ;

compound_statement
    : LCURL statements RCURL #CompoundStmtWithBody
    | LCURL RCURL            #CompoundStmtEmpty
    ;

var_declaration
    : type_specifier declaration_list SEMICOLON #VarDecl
    ;

type_specifier
    : INT   #TypeInt
    | FLOAT #TypeFloat
    | VOID  #TypeVoid
    ;

declaration_list
    : declaration_list COMMA ID                        #DeclListMultiple
    | declaration_list COMMA ID LTHIRD CONST_INT RTHIRD #DeclListMultipleArray
    | ID                                               #DeclListSingle
    | ID LTHIRD CONST_INT RTHIRD                       #DeclListSingleArray
    | ID ADDOP ID                                      #DeclListErrorSub
    | declaration_list COMMA ID ADDOP ID               #DeclListErrorSubMultiple
    ;

statements
    : statement            #StmtsSingle
    | statements statement #StmtsMultiple
    ;

statement
    : var_declaration                                                               #StmtVarDecl
    | expression_statement                                                          #StmtExpr
    | compound_statement                                                            #StmtCompound
    | FOR LPAREN expression_statement expression_statement expression RPAREN statement #StmtFor
    | IF LPAREN expression RPAREN statement ELSE statement                          #StmtIfElse
    | IF LPAREN expression RPAREN statement                                         #StmtIf
    | WHILE LPAREN expression RPAREN statement                                      #StmtWhile
    | PRINTLN LPAREN ID RPAREN SEMICOLON                                            #StmtPrint
    | RETURN expression SEMICOLON                                                   #StmtReturn
    ;

expression_statement
    : SEMICOLON            #ExprStmtEmpty
    | expression SEMICOLON #ExprStmtExpr
    | expression           #ExprStmtMissingSemicolon
    ;

variable
    : ID                         #VarId
    | ID LTHIRD expression RTHIRD #VarArray
    ;

expression
    : logic_expression                      #ExprLogic
    | variable ASSIGNOP logic_expression    #ExprAssign
    ;

logic_expression
    : rel_expression                            #LogicRel
    | rel_expression LOGICOP rel_expression     #LogicOp
    ;

rel_expression
    : simple_expression                         #RelSimple
    | simple_expression RELOP simple_expression #RelOp
    ;

simple_expression
    : term                                #SimpTerm
    | simple_expression ADDOP term        #SimpAdd
    ;

term
    : unary_expression                    #TermUnary
    | term MULOP unary_expression         #TermMul
    ;

unary_expression
    : ADDOP unary_expression              #UnaryAdd
    | NOT unary_expression                #UnaryNot
    | factor                              #UnaryFactor
    ;

factor
    : variable                            #FactorVar
    | ID LPAREN argument_list RPAREN      #FactorFuncCall
    | LPAREN expression RPAREN            #FactorParen
    | CONST_INT                           #FactorInt
    | CONST_FLOAT                         #FactorFloat
    | variable INCOP                      #FactorInc
    | variable DECOP                      #FactorDec
    ;

argument_list
    : arguments                           #ArgListArgs
    |                                     #ArgListEmpty
    ;

arguments
    : arguments COMMA logic_expression    #ArgsMultiple
    | logic_expression                    #ArgsSingle
    ;
