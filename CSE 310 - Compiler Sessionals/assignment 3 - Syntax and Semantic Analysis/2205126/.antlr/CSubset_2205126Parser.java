// Generated from /home/shuvra/Downloads/Assignment3_v11_clear_korbo/CSubset_2205126.g4 by ANTLR 4.13.1
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast", "CheckReturnValue"})
public class CSubset_2205126Parser extends Parser {
	static { RuntimeMetaData.checkVersion("4.13.1", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		LINE_COMMENT=1, BLOCK_COMMENT=2, STRING=3, WS=4, IF=5, ELSE=6, FOR=7, 
		WHILE=8, PRINTLN=9, RETURN=10, INT=11, FLOAT=12, VOID=13, LPAREN=14, RPAREN=15, 
		LCURL=16, RCURL=17, LTHIRD=18, RTHIRD=19, SEMICOLON=20, COMMA=21, ADDOP=22, 
		MULOP=23, INCOP=24, DECOP=25, NOT=26, RELOP=27, LOGICOP=28, ASSIGNOP=29, 
		ID=30, CONST_INT=31, CONST_FLOAT=32;
	public static final int
		RULE_start = 0, RULE_program = 1, RULE_unit = 2, RULE_func_declaration = 3, 
		RULE_func_definition = 4, RULE_parameter_list = 5, RULE_compound_statement = 6, 
		RULE_var_declaration = 7, RULE_type_specifier = 8, RULE_declaration_list = 9, 
		RULE_statements = 10, RULE_statement = 11, RULE_expression_statement = 12, 
		RULE_variable = 13, RULE_expression = 14, RULE_logic_expression = 15, 
		RULE_rel_expression = 16, RULE_simple_expression = 17, RULE_term = 18, 
		RULE_unary_expression = 19, RULE_factor = 20, RULE_argument_list = 21, 
		RULE_arguments = 22;
	private static String[] makeRuleNames() {
		return new String[] {
			"start", "program", "unit", "func_declaration", "func_definition", "parameter_list", 
			"compound_statement", "var_declaration", "type_specifier", "declaration_list", 
			"statements", "statement", "expression_statement", "variable", "expression", 
			"logic_expression", "rel_expression", "simple_expression", "term", "unary_expression", 
			"factor", "argument_list", "arguments"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, null, null, null, null, "'if'", "'else'", "'for'", "'while'", "'printf'", 
			"'return'", "'int'", "'float'", "'void'", "'('", "')'", "'{'", "'}'", 
			"'['", "']'", "';'", "','", null, null, "'++'", "'--'", "'!'", null, 
			null, "'='"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, "LINE_COMMENT", "BLOCK_COMMENT", "STRING", "WS", "IF", "ELSE", 
			"FOR", "WHILE", "PRINTLN", "RETURN", "INT", "FLOAT", "VOID", "LPAREN", 
			"RPAREN", "LCURL", "RCURL", "LTHIRD", "RTHIRD", "SEMICOLON", "COMMA", 
			"ADDOP", "MULOP", "INCOP", "DECOP", "NOT", "RELOP", "LOGICOP", "ASSIGNOP", 
			"ID", "CONST_INT", "CONST_FLOAT"
		};
	}
	private static final String[] _SYMBOLIC_NAMES = makeSymbolicNames();
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}

	@Override
	public String getGrammarFileName() { return "CSubset_2205126.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public ATN getATN() { return _ATN; }

	public CSubset_2205126Parser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@SuppressWarnings("CheckReturnValue")
	public static class StartContext extends ParserRuleContext {
		public ProgramContext program() {
			return getRuleContext(ProgramContext.class,0);
		}
		public TerminalNode EOF() { return getToken(CSubset_2205126Parser.EOF, 0); }
		public StartContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_start; }
	}

	public final StartContext start() throws RecognitionException {
		StartContext _localctx = new StartContext(_ctx, getState());
		enterRule(_localctx, 0, RULE_start);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(46);
			program(0);
			setState(47);
			match(EOF);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ProgramContext extends ParserRuleContext {
		public ProgramContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_program; }
	 
		public ProgramContext() { }
		public void copyFrom(ProgramContext ctx) {
			super.copyFrom(ctx);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class SingleUnitContext extends ProgramContext {
		public UnitContext unit() {
			return getRuleContext(UnitContext.class,0);
		}
		public SingleUnitContext(ProgramContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class ProgUnitContext extends ProgramContext {
		public ProgramContext program() {
			return getRuleContext(ProgramContext.class,0);
		}
		public UnitContext unit() {
			return getRuleContext(UnitContext.class,0);
		}
		public ProgUnitContext(ProgramContext ctx) { copyFrom(ctx); }
	}

	public final ProgramContext program() throws RecognitionException {
		return program(0);
	}

	private ProgramContext program(int _p) throws RecognitionException {
		ParserRuleContext _parentctx = _ctx;
		int _parentState = getState();
		ProgramContext _localctx = new ProgramContext(_ctx, _parentState);
		ProgramContext _prevctx = _localctx;
		int _startState = 2;
		enterRecursionRule(_localctx, 2, RULE_program, _p);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			{
			_localctx = new SingleUnitContext(_localctx);
			_ctx = _localctx;
			_prevctx = _localctx;

			setState(50);
			unit();
			}
			_ctx.stop = _input.LT(-1);
			setState(56);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,0,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( _parseListeners!=null ) triggerExitRuleEvent();
					_prevctx = _localctx;
					{
					{
					_localctx = new ProgUnitContext(new ProgramContext(_parentctx, _parentState));
					pushNewRecursionContext(_localctx, _startState, RULE_program);
					setState(52);
					if (!(precpred(_ctx, 2))) throw new FailedPredicateException(this, "precpred(_ctx, 2)");
					setState(53);
					unit();
					}
					} 
				}
				setState(58);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,0,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			unrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class UnitContext extends ParserRuleContext {
		public UnitContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_unit; }
	 
		public UnitContext() { }
		public void copyFrom(UnitContext ctx) {
			super.copyFrom(ctx);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class UnitVarDeclContext extends UnitContext {
		public Var_declarationContext var_declaration() {
			return getRuleContext(Var_declarationContext.class,0);
		}
		public UnitVarDeclContext(UnitContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class UnitFuncDefContext extends UnitContext {
		public Func_definitionContext func_definition() {
			return getRuleContext(Func_definitionContext.class,0);
		}
		public UnitFuncDefContext(UnitContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class UnitFuncDeclContext extends UnitContext {
		public Func_declarationContext func_declaration() {
			return getRuleContext(Func_declarationContext.class,0);
		}
		public UnitFuncDeclContext(UnitContext ctx) { copyFrom(ctx); }
	}

	public final UnitContext unit() throws RecognitionException {
		UnitContext _localctx = new UnitContext(_ctx, getState());
		enterRule(_localctx, 4, RULE_unit);
		try {
			setState(62);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,1,_ctx) ) {
			case 1:
				_localctx = new UnitVarDeclContext(_localctx);
				enterOuterAlt(_localctx, 1);
				{
				setState(59);
				var_declaration();
				}
				break;
			case 2:
				_localctx = new UnitFuncDeclContext(_localctx);
				enterOuterAlt(_localctx, 2);
				{
				setState(60);
				func_declaration();
				}
				break;
			case 3:
				_localctx = new UnitFuncDefContext(_localctx);
				enterOuterAlt(_localctx, 3);
				{
				setState(61);
				func_definition();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Func_declarationContext extends ParserRuleContext {
		public Func_declarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_func_declaration; }
	 
		public Func_declarationContext() { }
		public void copyFrom(Func_declarationContext ctx) {
			super.copyFrom(ctx);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class FuncDeclWithParamsContext extends Func_declarationContext {
		public Type_specifierContext type_specifier() {
			return getRuleContext(Type_specifierContext.class,0);
		}
		public TerminalNode ID() { return getToken(CSubset_2205126Parser.ID, 0); }
		public TerminalNode LPAREN() { return getToken(CSubset_2205126Parser.LPAREN, 0); }
		public Parameter_listContext parameter_list() {
			return getRuleContext(Parameter_listContext.class,0);
		}
		public TerminalNode RPAREN() { return getToken(CSubset_2205126Parser.RPAREN, 0); }
		public TerminalNode SEMICOLON() { return getToken(CSubset_2205126Parser.SEMICOLON, 0); }
		public FuncDeclWithParamsContext(Func_declarationContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class FuncDeclNoParamsContext extends Func_declarationContext {
		public Type_specifierContext type_specifier() {
			return getRuleContext(Type_specifierContext.class,0);
		}
		public TerminalNode ID() { return getToken(CSubset_2205126Parser.ID, 0); }
		public TerminalNode LPAREN() { return getToken(CSubset_2205126Parser.LPAREN, 0); }
		public TerminalNode RPAREN() { return getToken(CSubset_2205126Parser.RPAREN, 0); }
		public TerminalNode SEMICOLON() { return getToken(CSubset_2205126Parser.SEMICOLON, 0); }
		public FuncDeclNoParamsContext(Func_declarationContext ctx) { copyFrom(ctx); }
	}

	public final Func_declarationContext func_declaration() throws RecognitionException {
		Func_declarationContext _localctx = new Func_declarationContext(_ctx, getState());
		enterRule(_localctx, 6, RULE_func_declaration);
		try {
			setState(77);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,2,_ctx) ) {
			case 1:
				_localctx = new FuncDeclWithParamsContext(_localctx);
				enterOuterAlt(_localctx, 1);
				{
				setState(64);
				type_specifier();
				setState(65);
				match(ID);
				setState(66);
				match(LPAREN);
				setState(67);
				parameter_list(0);
				setState(68);
				match(RPAREN);
				setState(69);
				match(SEMICOLON);
				}
				break;
			case 2:
				_localctx = new FuncDeclNoParamsContext(_localctx);
				enterOuterAlt(_localctx, 2);
				{
				setState(71);
				type_specifier();
				setState(72);
				match(ID);
				setState(73);
				match(LPAREN);
				setState(74);
				match(RPAREN);
				setState(75);
				match(SEMICOLON);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Func_definitionContext extends ParserRuleContext {
		public Func_definitionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_func_definition; }
	 
		public Func_definitionContext() { }
		public void copyFrom(Func_definitionContext ctx) {
			super.copyFrom(ctx);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class FuncDefNoParamsContext extends Func_definitionContext {
		public Type_specifierContext type_specifier() {
			return getRuleContext(Type_specifierContext.class,0);
		}
		public TerminalNode ID() { return getToken(CSubset_2205126Parser.ID, 0); }
		public TerminalNode LPAREN() { return getToken(CSubset_2205126Parser.LPAREN, 0); }
		public TerminalNode RPAREN() { return getToken(CSubset_2205126Parser.RPAREN, 0); }
		public Compound_statementContext compound_statement() {
			return getRuleContext(Compound_statementContext.class,0);
		}
		public FuncDefNoParamsContext(Func_definitionContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class FuncDefWithParamsContext extends Func_definitionContext {
		public Type_specifierContext type_specifier() {
			return getRuleContext(Type_specifierContext.class,0);
		}
		public TerminalNode ID() { return getToken(CSubset_2205126Parser.ID, 0); }
		public TerminalNode LPAREN() { return getToken(CSubset_2205126Parser.LPAREN, 0); }
		public Parameter_listContext parameter_list() {
			return getRuleContext(Parameter_listContext.class,0);
		}
		public TerminalNode RPAREN() { return getToken(CSubset_2205126Parser.RPAREN, 0); }
		public Compound_statementContext compound_statement() {
			return getRuleContext(Compound_statementContext.class,0);
		}
		public FuncDefWithParamsContext(Func_definitionContext ctx) { copyFrom(ctx); }
	}

	public final Func_definitionContext func_definition() throws RecognitionException {
		Func_definitionContext _localctx = new Func_definitionContext(_ctx, getState());
		enterRule(_localctx, 8, RULE_func_definition);
		try {
			setState(92);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,3,_ctx) ) {
			case 1:
				_localctx = new FuncDefWithParamsContext(_localctx);
				enterOuterAlt(_localctx, 1);
				{
				setState(79);
				type_specifier();
				setState(80);
				match(ID);
				setState(81);
				match(LPAREN);
				setState(82);
				parameter_list(0);
				setState(83);
				match(RPAREN);
				setState(84);
				compound_statement();
				}
				break;
			case 2:
				_localctx = new FuncDefNoParamsContext(_localctx);
				enterOuterAlt(_localctx, 2);
				{
				setState(86);
				type_specifier();
				setState(87);
				match(ID);
				setState(88);
				match(LPAREN);
				setState(89);
				match(RPAREN);
				setState(90);
				compound_statement();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Parameter_listContext extends ParserRuleContext {
		public Parameter_listContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_parameter_list; }
	 
		public Parameter_listContext() { }
		public void copyFrom(Parameter_listContext ctx) {
			super.copyFrom(ctx);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class ParamListErrorSubMultipleContext extends Parameter_listContext {
		public Parameter_listContext parameter_list() {
			return getRuleContext(Parameter_listContext.class,0);
		}
		public TerminalNode COMMA() { return getToken(CSubset_2205126Parser.COMMA, 0); }
		public Type_specifierContext type_specifier() {
			return getRuleContext(Type_specifierContext.class,0);
		}
		public TerminalNode ADDOP() { return getToken(CSubset_2205126Parser.ADDOP, 0); }
		public ParamListErrorSubMultipleContext(Parameter_listContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class ParamListSingleContext extends Parameter_listContext {
		public Type_specifierContext type_specifier() {
			return getRuleContext(Type_specifierContext.class,0);
		}
		public TerminalNode ID() { return getToken(CSubset_2205126Parser.ID, 0); }
		public ParamListSingleContext(Parameter_listContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class ParamListMultipleNoIDContext extends Parameter_listContext {
		public Parameter_listContext parameter_list() {
			return getRuleContext(Parameter_listContext.class,0);
		}
		public TerminalNode COMMA() { return getToken(CSubset_2205126Parser.COMMA, 0); }
		public Type_specifierContext type_specifier() {
			return getRuleContext(Type_specifierContext.class,0);
		}
		public ParamListMultipleNoIDContext(Parameter_listContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class ParamListMultipleContext extends Parameter_listContext {
		public Parameter_listContext parameter_list() {
			return getRuleContext(Parameter_listContext.class,0);
		}
		public TerminalNode COMMA() { return getToken(CSubset_2205126Parser.COMMA, 0); }
		public Type_specifierContext type_specifier() {
			return getRuleContext(Type_specifierContext.class,0);
		}
		public TerminalNode ID() { return getToken(CSubset_2205126Parser.ID, 0); }
		public ParamListMultipleContext(Parameter_listContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class ParamListSingleNoIDContext extends Parameter_listContext {
		public Type_specifierContext type_specifier() {
			return getRuleContext(Type_specifierContext.class,0);
		}
		public ParamListSingleNoIDContext(Parameter_listContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class ParamListErrorSubContext extends Parameter_listContext {
		public Type_specifierContext type_specifier() {
			return getRuleContext(Type_specifierContext.class,0);
		}
		public TerminalNode ADDOP() { return getToken(CSubset_2205126Parser.ADDOP, 0); }
		public ParamListErrorSubContext(Parameter_listContext ctx) { copyFrom(ctx); }
	}

	public final Parameter_listContext parameter_list() throws RecognitionException {
		return parameter_list(0);
	}

	private Parameter_listContext parameter_list(int _p) throws RecognitionException {
		ParserRuleContext _parentctx = _ctx;
		int _parentState = getState();
		Parameter_listContext _localctx = new Parameter_listContext(_ctx, _parentState);
		Parameter_listContext _prevctx = _localctx;
		int _startState = 10;
		enterRecursionRule(_localctx, 10, RULE_parameter_list, _p);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(102);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,4,_ctx) ) {
			case 1:
				{
				_localctx = new ParamListSingleContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;

				setState(95);
				type_specifier();
				setState(96);
				match(ID);
				}
				break;
			case 2:
				{
				_localctx = new ParamListSingleNoIDContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(98);
				type_specifier();
				}
				break;
			case 3:
				{
				_localctx = new ParamListErrorSubContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(99);
				type_specifier();
				setState(100);
				match(ADDOP);
				}
				break;
			}
			_ctx.stop = _input.LT(-1);
			setState(119);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,6,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( _parseListeners!=null ) triggerExitRuleEvent();
					_prevctx = _localctx;
					{
					setState(117);
					_errHandler.sync(this);
					switch ( getInterpreter().adaptivePredict(_input,5,_ctx) ) {
					case 1:
						{
						_localctx = new ParamListMultipleContext(new Parameter_listContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_parameter_list);
						setState(104);
						if (!(precpred(_ctx, 6))) throw new FailedPredicateException(this, "precpred(_ctx, 6)");
						setState(105);
						match(COMMA);
						setState(106);
						type_specifier();
						setState(107);
						match(ID);
						}
						break;
					case 2:
						{
						_localctx = new ParamListMultipleNoIDContext(new Parameter_listContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_parameter_list);
						setState(109);
						if (!(precpred(_ctx, 5))) throw new FailedPredicateException(this, "precpred(_ctx, 5)");
						setState(110);
						match(COMMA);
						setState(111);
						type_specifier();
						}
						break;
					case 3:
						{
						_localctx = new ParamListErrorSubMultipleContext(new Parameter_listContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_parameter_list);
						setState(112);
						if (!(precpred(_ctx, 1))) throw new FailedPredicateException(this, "precpred(_ctx, 1)");
						setState(113);
						match(COMMA);
						setState(114);
						type_specifier();
						setState(115);
						match(ADDOP);
						}
						break;
					}
					} 
				}
				setState(121);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,6,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			unrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Compound_statementContext extends ParserRuleContext {
		public Compound_statementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_compound_statement; }
	 
		public Compound_statementContext() { }
		public void copyFrom(Compound_statementContext ctx) {
			super.copyFrom(ctx);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class CompoundStmtEmptyContext extends Compound_statementContext {
		public TerminalNode LCURL() { return getToken(CSubset_2205126Parser.LCURL, 0); }
		public TerminalNode RCURL() { return getToken(CSubset_2205126Parser.RCURL, 0); }
		public CompoundStmtEmptyContext(Compound_statementContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class CompoundStmtWithBodyContext extends Compound_statementContext {
		public TerminalNode LCURL() { return getToken(CSubset_2205126Parser.LCURL, 0); }
		public StatementsContext statements() {
			return getRuleContext(StatementsContext.class,0);
		}
		public TerminalNode RCURL() { return getToken(CSubset_2205126Parser.RCURL, 0); }
		public CompoundStmtWithBodyContext(Compound_statementContext ctx) { copyFrom(ctx); }
	}

	public final Compound_statementContext compound_statement() throws RecognitionException {
		Compound_statementContext _localctx = new Compound_statementContext(_ctx, getState());
		enterRule(_localctx, 12, RULE_compound_statement);
		try {
			setState(128);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,7,_ctx) ) {
			case 1:
				_localctx = new CompoundStmtWithBodyContext(_localctx);
				enterOuterAlt(_localctx, 1);
				{
				setState(122);
				match(LCURL);
				setState(123);
				statements(0);
				setState(124);
				match(RCURL);
				}
				break;
			case 2:
				_localctx = new CompoundStmtEmptyContext(_localctx);
				enterOuterAlt(_localctx, 2);
				{
				setState(126);
				match(LCURL);
				setState(127);
				match(RCURL);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Var_declarationContext extends ParserRuleContext {
		public Var_declarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_var_declaration; }
	 
		public Var_declarationContext() { }
		public void copyFrom(Var_declarationContext ctx) {
			super.copyFrom(ctx);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class VarDeclContext extends Var_declarationContext {
		public Type_specifierContext type_specifier() {
			return getRuleContext(Type_specifierContext.class,0);
		}
		public Declaration_listContext declaration_list() {
			return getRuleContext(Declaration_listContext.class,0);
		}
		public TerminalNode SEMICOLON() { return getToken(CSubset_2205126Parser.SEMICOLON, 0); }
		public VarDeclContext(Var_declarationContext ctx) { copyFrom(ctx); }
	}

	public final Var_declarationContext var_declaration() throws RecognitionException {
		Var_declarationContext _localctx = new Var_declarationContext(_ctx, getState());
		enterRule(_localctx, 14, RULE_var_declaration);
		try {
			_localctx = new VarDeclContext(_localctx);
			enterOuterAlt(_localctx, 1);
			{
			setState(130);
			type_specifier();
			setState(131);
			declaration_list(0);
			setState(132);
			match(SEMICOLON);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Type_specifierContext extends ParserRuleContext {
		public Type_specifierContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_type_specifier; }
	 
		public Type_specifierContext() { }
		public void copyFrom(Type_specifierContext ctx) {
			super.copyFrom(ctx);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class TypeFloatContext extends Type_specifierContext {
		public TerminalNode FLOAT() { return getToken(CSubset_2205126Parser.FLOAT, 0); }
		public TypeFloatContext(Type_specifierContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class TypeVoidContext extends Type_specifierContext {
		public TerminalNode VOID() { return getToken(CSubset_2205126Parser.VOID, 0); }
		public TypeVoidContext(Type_specifierContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class TypeIntContext extends Type_specifierContext {
		public TerminalNode INT() { return getToken(CSubset_2205126Parser.INT, 0); }
		public TypeIntContext(Type_specifierContext ctx) { copyFrom(ctx); }
	}

	public final Type_specifierContext type_specifier() throws RecognitionException {
		Type_specifierContext _localctx = new Type_specifierContext(_ctx, getState());
		enterRule(_localctx, 16, RULE_type_specifier);
		try {
			setState(137);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case INT:
				_localctx = new TypeIntContext(_localctx);
				enterOuterAlt(_localctx, 1);
				{
				setState(134);
				match(INT);
				}
				break;
			case FLOAT:
				_localctx = new TypeFloatContext(_localctx);
				enterOuterAlt(_localctx, 2);
				{
				setState(135);
				match(FLOAT);
				}
				break;
			case VOID:
				_localctx = new TypeVoidContext(_localctx);
				enterOuterAlt(_localctx, 3);
				{
				setState(136);
				match(VOID);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Declaration_listContext extends ParserRuleContext {
		public Declaration_listContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_declaration_list; }
	 
		public Declaration_listContext() { }
		public void copyFrom(Declaration_listContext ctx) {
			super.copyFrom(ctx);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class DeclListSingleContext extends Declaration_listContext {
		public TerminalNode ID() { return getToken(CSubset_2205126Parser.ID, 0); }
		public DeclListSingleContext(Declaration_listContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class DeclListMultipleArrayContext extends Declaration_listContext {
		public Declaration_listContext declaration_list() {
			return getRuleContext(Declaration_listContext.class,0);
		}
		public TerminalNode COMMA() { return getToken(CSubset_2205126Parser.COMMA, 0); }
		public TerminalNode ID() { return getToken(CSubset_2205126Parser.ID, 0); }
		public TerminalNode LTHIRD() { return getToken(CSubset_2205126Parser.LTHIRD, 0); }
		public TerminalNode CONST_INT() { return getToken(CSubset_2205126Parser.CONST_INT, 0); }
		public TerminalNode RTHIRD() { return getToken(CSubset_2205126Parser.RTHIRD, 0); }
		public DeclListMultipleArrayContext(Declaration_listContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class DeclListMultipleContext extends Declaration_listContext {
		public Declaration_listContext declaration_list() {
			return getRuleContext(Declaration_listContext.class,0);
		}
		public TerminalNode COMMA() { return getToken(CSubset_2205126Parser.COMMA, 0); }
		public TerminalNode ID() { return getToken(CSubset_2205126Parser.ID, 0); }
		public DeclListMultipleContext(Declaration_listContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class DeclListSingleArrayContext extends Declaration_listContext {
		public TerminalNode ID() { return getToken(CSubset_2205126Parser.ID, 0); }
		public TerminalNode LTHIRD() { return getToken(CSubset_2205126Parser.LTHIRD, 0); }
		public TerminalNode CONST_INT() { return getToken(CSubset_2205126Parser.CONST_INT, 0); }
		public TerminalNode RTHIRD() { return getToken(CSubset_2205126Parser.RTHIRD, 0); }
		public DeclListSingleArrayContext(Declaration_listContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class DeclListErrorSubContext extends Declaration_listContext {
		public List<TerminalNode> ID() { return getTokens(CSubset_2205126Parser.ID); }
		public TerminalNode ID(int i) {
			return getToken(CSubset_2205126Parser.ID, i);
		}
		public TerminalNode ADDOP() { return getToken(CSubset_2205126Parser.ADDOP, 0); }
		public DeclListErrorSubContext(Declaration_listContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class DeclListErrorSubMultipleContext extends Declaration_listContext {
		public Declaration_listContext declaration_list() {
			return getRuleContext(Declaration_listContext.class,0);
		}
		public TerminalNode COMMA() { return getToken(CSubset_2205126Parser.COMMA, 0); }
		public List<TerminalNode> ID() { return getTokens(CSubset_2205126Parser.ID); }
		public TerminalNode ID(int i) {
			return getToken(CSubset_2205126Parser.ID, i);
		}
		public TerminalNode ADDOP() { return getToken(CSubset_2205126Parser.ADDOP, 0); }
		public DeclListErrorSubMultipleContext(Declaration_listContext ctx) { copyFrom(ctx); }
	}

	public final Declaration_listContext declaration_list() throws RecognitionException {
		return declaration_list(0);
	}

	private Declaration_listContext declaration_list(int _p) throws RecognitionException {
		ParserRuleContext _parentctx = _ctx;
		int _parentState = getState();
		Declaration_listContext _localctx = new Declaration_listContext(_ctx, _parentState);
		Declaration_listContext _prevctx = _localctx;
		int _startState = 18;
		enterRecursionRule(_localctx, 18, RULE_declaration_list, _p);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(148);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,9,_ctx) ) {
			case 1:
				{
				_localctx = new DeclListSingleContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;

				setState(140);
				match(ID);
				}
				break;
			case 2:
				{
				_localctx = new DeclListSingleArrayContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(141);
				match(ID);
				setState(142);
				match(LTHIRD);
				setState(143);
				match(CONST_INT);
				setState(144);
				match(RTHIRD);
				}
				break;
			case 3:
				{
				_localctx = new DeclListErrorSubContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(145);
				match(ID);
				setState(146);
				match(ADDOP);
				setState(147);
				match(ID);
				}
				break;
			}
			_ctx.stop = _input.LT(-1);
			setState(166);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,11,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( _parseListeners!=null ) triggerExitRuleEvent();
					_prevctx = _localctx;
					{
					setState(164);
					_errHandler.sync(this);
					switch ( getInterpreter().adaptivePredict(_input,10,_ctx) ) {
					case 1:
						{
						_localctx = new DeclListMultipleContext(new Declaration_listContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_declaration_list);
						setState(150);
						if (!(precpred(_ctx, 6))) throw new FailedPredicateException(this, "precpred(_ctx, 6)");
						setState(151);
						match(COMMA);
						setState(152);
						match(ID);
						}
						break;
					case 2:
						{
						_localctx = new DeclListMultipleArrayContext(new Declaration_listContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_declaration_list);
						setState(153);
						if (!(precpred(_ctx, 5))) throw new FailedPredicateException(this, "precpred(_ctx, 5)");
						setState(154);
						match(COMMA);
						setState(155);
						match(ID);
						setState(156);
						match(LTHIRD);
						setState(157);
						match(CONST_INT);
						setState(158);
						match(RTHIRD);
						}
						break;
					case 3:
						{
						_localctx = new DeclListErrorSubMultipleContext(new Declaration_listContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_declaration_list);
						setState(159);
						if (!(precpred(_ctx, 1))) throw new FailedPredicateException(this, "precpred(_ctx, 1)");
						setState(160);
						match(COMMA);
						setState(161);
						match(ID);
						setState(162);
						match(ADDOP);
						setState(163);
						match(ID);
						}
						break;
					}
					} 
				}
				setState(168);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,11,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			unrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class StatementsContext extends ParserRuleContext {
		public StatementsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_statements; }
	 
		public StatementsContext() { }
		public void copyFrom(StatementsContext ctx) {
			super.copyFrom(ctx);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class StmtsSingleContext extends StatementsContext {
		public StatementContext statement() {
			return getRuleContext(StatementContext.class,0);
		}
		public StmtsSingleContext(StatementsContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class StmtsMultipleContext extends StatementsContext {
		public StatementsContext statements() {
			return getRuleContext(StatementsContext.class,0);
		}
		public StatementContext statement() {
			return getRuleContext(StatementContext.class,0);
		}
		public StmtsMultipleContext(StatementsContext ctx) { copyFrom(ctx); }
	}

	public final StatementsContext statements() throws RecognitionException {
		return statements(0);
	}

	private StatementsContext statements(int _p) throws RecognitionException {
		ParserRuleContext _parentctx = _ctx;
		int _parentState = getState();
		StatementsContext _localctx = new StatementsContext(_ctx, _parentState);
		StatementsContext _prevctx = _localctx;
		int _startState = 20;
		enterRecursionRule(_localctx, 20, RULE_statements, _p);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			{
			_localctx = new StmtsSingleContext(_localctx);
			_ctx = _localctx;
			_prevctx = _localctx;

			setState(170);
			statement();
			}
			_ctx.stop = _input.LT(-1);
			setState(176);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,12,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( _parseListeners!=null ) triggerExitRuleEvent();
					_prevctx = _localctx;
					{
					{
					_localctx = new StmtsMultipleContext(new StatementsContext(_parentctx, _parentState));
					pushNewRecursionContext(_localctx, _startState, RULE_statements);
					setState(172);
					if (!(precpred(_ctx, 1))) throw new FailedPredicateException(this, "precpred(_ctx, 1)");
					setState(173);
					statement();
					}
					} 
				}
				setState(178);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,12,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			unrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class StatementContext extends ParserRuleContext {
		public StatementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_statement; }
	 
		public StatementContext() { }
		public void copyFrom(StatementContext ctx) {
			super.copyFrom(ctx);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class StmtReturnContext extends StatementContext {
		public TerminalNode RETURN() { return getToken(CSubset_2205126Parser.RETURN, 0); }
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public TerminalNode SEMICOLON() { return getToken(CSubset_2205126Parser.SEMICOLON, 0); }
		public StmtReturnContext(StatementContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class StmtCompoundContext extends StatementContext {
		public Compound_statementContext compound_statement() {
			return getRuleContext(Compound_statementContext.class,0);
		}
		public StmtCompoundContext(StatementContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class StmtVarDeclContext extends StatementContext {
		public Var_declarationContext var_declaration() {
			return getRuleContext(Var_declarationContext.class,0);
		}
		public StmtVarDeclContext(StatementContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class StmtExprContext extends StatementContext {
		public Expression_statementContext expression_statement() {
			return getRuleContext(Expression_statementContext.class,0);
		}
		public StmtExprContext(StatementContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class StmtWhileContext extends StatementContext {
		public TerminalNode WHILE() { return getToken(CSubset_2205126Parser.WHILE, 0); }
		public TerminalNode LPAREN() { return getToken(CSubset_2205126Parser.LPAREN, 0); }
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public TerminalNode RPAREN() { return getToken(CSubset_2205126Parser.RPAREN, 0); }
		public StatementContext statement() {
			return getRuleContext(StatementContext.class,0);
		}
		public StmtWhileContext(StatementContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class StmtIfElseContext extends StatementContext {
		public TerminalNode IF() { return getToken(CSubset_2205126Parser.IF, 0); }
		public TerminalNode LPAREN() { return getToken(CSubset_2205126Parser.LPAREN, 0); }
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public TerminalNode RPAREN() { return getToken(CSubset_2205126Parser.RPAREN, 0); }
		public List<StatementContext> statement() {
			return getRuleContexts(StatementContext.class);
		}
		public StatementContext statement(int i) {
			return getRuleContext(StatementContext.class,i);
		}
		public TerminalNode ELSE() { return getToken(CSubset_2205126Parser.ELSE, 0); }
		public StmtIfElseContext(StatementContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class StmtPrintContext extends StatementContext {
		public TerminalNode PRINTLN() { return getToken(CSubset_2205126Parser.PRINTLN, 0); }
		public TerminalNode LPAREN() { return getToken(CSubset_2205126Parser.LPAREN, 0); }
		public TerminalNode ID() { return getToken(CSubset_2205126Parser.ID, 0); }
		public TerminalNode RPAREN() { return getToken(CSubset_2205126Parser.RPAREN, 0); }
		public TerminalNode SEMICOLON() { return getToken(CSubset_2205126Parser.SEMICOLON, 0); }
		public StmtPrintContext(StatementContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class StmtForContext extends StatementContext {
		public TerminalNode FOR() { return getToken(CSubset_2205126Parser.FOR, 0); }
		public TerminalNode LPAREN() { return getToken(CSubset_2205126Parser.LPAREN, 0); }
		public List<Expression_statementContext> expression_statement() {
			return getRuleContexts(Expression_statementContext.class);
		}
		public Expression_statementContext expression_statement(int i) {
			return getRuleContext(Expression_statementContext.class,i);
		}
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public TerminalNode RPAREN() { return getToken(CSubset_2205126Parser.RPAREN, 0); }
		public StatementContext statement() {
			return getRuleContext(StatementContext.class,0);
		}
		public StmtForContext(StatementContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class StmtIfContext extends StatementContext {
		public TerminalNode IF() { return getToken(CSubset_2205126Parser.IF, 0); }
		public TerminalNode LPAREN() { return getToken(CSubset_2205126Parser.LPAREN, 0); }
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public TerminalNode RPAREN() { return getToken(CSubset_2205126Parser.RPAREN, 0); }
		public StatementContext statement() {
			return getRuleContext(StatementContext.class,0);
		}
		public StmtIfContext(StatementContext ctx) { copyFrom(ctx); }
	}

	public final StatementContext statement() throws RecognitionException {
		StatementContext _localctx = new StatementContext(_ctx, getState());
		enterRule(_localctx, 22, RULE_statement);
		try {
			setState(219);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,13,_ctx) ) {
			case 1:
				_localctx = new StmtVarDeclContext(_localctx);
				enterOuterAlt(_localctx, 1);
				{
				setState(179);
				var_declaration();
				}
				break;
			case 2:
				_localctx = new StmtExprContext(_localctx);
				enterOuterAlt(_localctx, 2);
				{
				setState(180);
				expression_statement();
				}
				break;
			case 3:
				_localctx = new StmtCompoundContext(_localctx);
				enterOuterAlt(_localctx, 3);
				{
				setState(181);
				compound_statement();
				}
				break;
			case 4:
				_localctx = new StmtForContext(_localctx);
				enterOuterAlt(_localctx, 4);
				{
				setState(182);
				match(FOR);
				setState(183);
				match(LPAREN);
				setState(184);
				expression_statement();
				setState(185);
				expression_statement();
				setState(186);
				expression();
				setState(187);
				match(RPAREN);
				setState(188);
				statement();
				}
				break;
			case 5:
				_localctx = new StmtIfElseContext(_localctx);
				enterOuterAlt(_localctx, 5);
				{
				setState(190);
				match(IF);
				setState(191);
				match(LPAREN);
				setState(192);
				expression();
				setState(193);
				match(RPAREN);
				setState(194);
				statement();
				setState(195);
				match(ELSE);
				setState(196);
				statement();
				}
				break;
			case 6:
				_localctx = new StmtIfContext(_localctx);
				enterOuterAlt(_localctx, 6);
				{
				setState(198);
				match(IF);
				setState(199);
				match(LPAREN);
				setState(200);
				expression();
				setState(201);
				match(RPAREN);
				setState(202);
				statement();
				}
				break;
			case 7:
				_localctx = new StmtWhileContext(_localctx);
				enterOuterAlt(_localctx, 7);
				{
				setState(204);
				match(WHILE);
				setState(205);
				match(LPAREN);
				setState(206);
				expression();
				setState(207);
				match(RPAREN);
				setState(208);
				statement();
				}
				break;
			case 8:
				_localctx = new StmtPrintContext(_localctx);
				enterOuterAlt(_localctx, 8);
				{
				setState(210);
				match(PRINTLN);
				setState(211);
				match(LPAREN);
				setState(212);
				match(ID);
				setState(213);
				match(RPAREN);
				setState(214);
				match(SEMICOLON);
				}
				break;
			case 9:
				_localctx = new StmtReturnContext(_localctx);
				enterOuterAlt(_localctx, 9);
				{
				setState(215);
				match(RETURN);
				setState(216);
				expression();
				setState(217);
				match(SEMICOLON);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expression_statementContext extends ParserRuleContext {
		public Expression_statementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expression_statement; }
	 
		public Expression_statementContext() { }
		public void copyFrom(Expression_statementContext ctx) {
			super.copyFrom(ctx);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class ExprStmtMissingSemicolonContext extends Expression_statementContext {
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public ExprStmtMissingSemicolonContext(Expression_statementContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class ExprStmtEmptyContext extends Expression_statementContext {
		public TerminalNode SEMICOLON() { return getToken(CSubset_2205126Parser.SEMICOLON, 0); }
		public ExprStmtEmptyContext(Expression_statementContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class ExprStmtExprContext extends Expression_statementContext {
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public TerminalNode SEMICOLON() { return getToken(CSubset_2205126Parser.SEMICOLON, 0); }
		public ExprStmtExprContext(Expression_statementContext ctx) { copyFrom(ctx); }
	}

	public final Expression_statementContext expression_statement() throws RecognitionException {
		Expression_statementContext _localctx = new Expression_statementContext(_ctx, getState());
		enterRule(_localctx, 24, RULE_expression_statement);
		try {
			setState(226);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,14,_ctx) ) {
			case 1:
				_localctx = new ExprStmtEmptyContext(_localctx);
				enterOuterAlt(_localctx, 1);
				{
				setState(221);
				match(SEMICOLON);
				}
				break;
			case 2:
				_localctx = new ExprStmtExprContext(_localctx);
				enterOuterAlt(_localctx, 2);
				{
				setState(222);
				expression();
				setState(223);
				match(SEMICOLON);
				}
				break;
			case 3:
				_localctx = new ExprStmtMissingSemicolonContext(_localctx);
				enterOuterAlt(_localctx, 3);
				{
				setState(225);
				expression();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class VariableContext extends ParserRuleContext {
		public VariableContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_variable; }
	 
		public VariableContext() { }
		public void copyFrom(VariableContext ctx) {
			super.copyFrom(ctx);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class VarArrayContext extends VariableContext {
		public TerminalNode ID() { return getToken(CSubset_2205126Parser.ID, 0); }
		public TerminalNode LTHIRD() { return getToken(CSubset_2205126Parser.LTHIRD, 0); }
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public TerminalNode RTHIRD() { return getToken(CSubset_2205126Parser.RTHIRD, 0); }
		public VarArrayContext(VariableContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class VarIdContext extends VariableContext {
		public TerminalNode ID() { return getToken(CSubset_2205126Parser.ID, 0); }
		public VarIdContext(VariableContext ctx) { copyFrom(ctx); }
	}

	public final VariableContext variable() throws RecognitionException {
		VariableContext _localctx = new VariableContext(_ctx, getState());
		enterRule(_localctx, 26, RULE_variable);
		try {
			setState(234);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,15,_ctx) ) {
			case 1:
				_localctx = new VarIdContext(_localctx);
				enterOuterAlt(_localctx, 1);
				{
				setState(228);
				match(ID);
				}
				break;
			case 2:
				_localctx = new VarArrayContext(_localctx);
				enterOuterAlt(_localctx, 2);
				{
				setState(229);
				match(ID);
				setState(230);
				match(LTHIRD);
				setState(231);
				expression();
				setState(232);
				match(RTHIRD);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ExpressionContext extends ParserRuleContext {
		public ExpressionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expression; }
	 
		public ExpressionContext() { }
		public void copyFrom(ExpressionContext ctx) {
			super.copyFrom(ctx);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class ExprAssignContext extends ExpressionContext {
		public VariableContext variable() {
			return getRuleContext(VariableContext.class,0);
		}
		public TerminalNode ASSIGNOP() { return getToken(CSubset_2205126Parser.ASSIGNOP, 0); }
		public Logic_expressionContext logic_expression() {
			return getRuleContext(Logic_expressionContext.class,0);
		}
		public ExprAssignContext(ExpressionContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class ExprLogicContext extends ExpressionContext {
		public Logic_expressionContext logic_expression() {
			return getRuleContext(Logic_expressionContext.class,0);
		}
		public ExprLogicContext(ExpressionContext ctx) { copyFrom(ctx); }
	}

	public final ExpressionContext expression() throws RecognitionException {
		ExpressionContext _localctx = new ExpressionContext(_ctx, getState());
		enterRule(_localctx, 28, RULE_expression);
		try {
			setState(241);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,16,_ctx) ) {
			case 1:
				_localctx = new ExprLogicContext(_localctx);
				enterOuterAlt(_localctx, 1);
				{
				setState(236);
				logic_expression();
				}
				break;
			case 2:
				_localctx = new ExprAssignContext(_localctx);
				enterOuterAlt(_localctx, 2);
				{
				setState(237);
				variable();
				setState(238);
				match(ASSIGNOP);
				setState(239);
				logic_expression();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Logic_expressionContext extends ParserRuleContext {
		public Logic_expressionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_logic_expression; }
	 
		public Logic_expressionContext() { }
		public void copyFrom(Logic_expressionContext ctx) {
			super.copyFrom(ctx);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class LogicRelContext extends Logic_expressionContext {
		public Rel_expressionContext rel_expression() {
			return getRuleContext(Rel_expressionContext.class,0);
		}
		public LogicRelContext(Logic_expressionContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class LogicOpContext extends Logic_expressionContext {
		public List<Rel_expressionContext> rel_expression() {
			return getRuleContexts(Rel_expressionContext.class);
		}
		public Rel_expressionContext rel_expression(int i) {
			return getRuleContext(Rel_expressionContext.class,i);
		}
		public TerminalNode LOGICOP() { return getToken(CSubset_2205126Parser.LOGICOP, 0); }
		public LogicOpContext(Logic_expressionContext ctx) { copyFrom(ctx); }
	}

	public final Logic_expressionContext logic_expression() throws RecognitionException {
		Logic_expressionContext _localctx = new Logic_expressionContext(_ctx, getState());
		enterRule(_localctx, 30, RULE_logic_expression);
		try {
			setState(248);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,17,_ctx) ) {
			case 1:
				_localctx = new LogicRelContext(_localctx);
				enterOuterAlt(_localctx, 1);
				{
				setState(243);
				rel_expression();
				}
				break;
			case 2:
				_localctx = new LogicOpContext(_localctx);
				enterOuterAlt(_localctx, 2);
				{
				setState(244);
				rel_expression();
				setState(245);
				match(LOGICOP);
				setState(246);
				rel_expression();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Rel_expressionContext extends ParserRuleContext {
		public Rel_expressionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_rel_expression; }
	 
		public Rel_expressionContext() { }
		public void copyFrom(Rel_expressionContext ctx) {
			super.copyFrom(ctx);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class RelOpContext extends Rel_expressionContext {
		public List<Simple_expressionContext> simple_expression() {
			return getRuleContexts(Simple_expressionContext.class);
		}
		public Simple_expressionContext simple_expression(int i) {
			return getRuleContext(Simple_expressionContext.class,i);
		}
		public TerminalNode RELOP() { return getToken(CSubset_2205126Parser.RELOP, 0); }
		public RelOpContext(Rel_expressionContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class RelSimpleContext extends Rel_expressionContext {
		public Simple_expressionContext simple_expression() {
			return getRuleContext(Simple_expressionContext.class,0);
		}
		public RelSimpleContext(Rel_expressionContext ctx) { copyFrom(ctx); }
	}

	public final Rel_expressionContext rel_expression() throws RecognitionException {
		Rel_expressionContext _localctx = new Rel_expressionContext(_ctx, getState());
		enterRule(_localctx, 32, RULE_rel_expression);
		try {
			setState(255);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,18,_ctx) ) {
			case 1:
				_localctx = new RelSimpleContext(_localctx);
				enterOuterAlt(_localctx, 1);
				{
				setState(250);
				simple_expression(0);
				}
				break;
			case 2:
				_localctx = new RelOpContext(_localctx);
				enterOuterAlt(_localctx, 2);
				{
				setState(251);
				simple_expression(0);
				setState(252);
				match(RELOP);
				setState(253);
				simple_expression(0);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Simple_expressionContext extends ParserRuleContext {
		public Simple_expressionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_simple_expression; }
	 
		public Simple_expressionContext() { }
		public void copyFrom(Simple_expressionContext ctx) {
			super.copyFrom(ctx);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class SimpTermContext extends Simple_expressionContext {
		public TermContext term() {
			return getRuleContext(TermContext.class,0);
		}
		public SimpTermContext(Simple_expressionContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class SimpAddContext extends Simple_expressionContext {
		public Simple_expressionContext simple_expression() {
			return getRuleContext(Simple_expressionContext.class,0);
		}
		public TerminalNode ADDOP() { return getToken(CSubset_2205126Parser.ADDOP, 0); }
		public TermContext term() {
			return getRuleContext(TermContext.class,0);
		}
		public SimpAddContext(Simple_expressionContext ctx) { copyFrom(ctx); }
	}

	public final Simple_expressionContext simple_expression() throws RecognitionException {
		return simple_expression(0);
	}

	private Simple_expressionContext simple_expression(int _p) throws RecognitionException {
		ParserRuleContext _parentctx = _ctx;
		int _parentState = getState();
		Simple_expressionContext _localctx = new Simple_expressionContext(_ctx, _parentState);
		Simple_expressionContext _prevctx = _localctx;
		int _startState = 34;
		enterRecursionRule(_localctx, 34, RULE_simple_expression, _p);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			{
			_localctx = new SimpTermContext(_localctx);
			_ctx = _localctx;
			_prevctx = _localctx;

			setState(258);
			term(0);
			}
			_ctx.stop = _input.LT(-1);
			setState(265);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,19,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( _parseListeners!=null ) triggerExitRuleEvent();
					_prevctx = _localctx;
					{
					{
					_localctx = new SimpAddContext(new Simple_expressionContext(_parentctx, _parentState));
					pushNewRecursionContext(_localctx, _startState, RULE_simple_expression);
					setState(260);
					if (!(precpred(_ctx, 1))) throw new FailedPredicateException(this, "precpred(_ctx, 1)");
					setState(261);
					match(ADDOP);
					setState(262);
					term(0);
					}
					} 
				}
				setState(267);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,19,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			unrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class TermContext extends ParserRuleContext {
		public TermContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_term; }
	 
		public TermContext() { }
		public void copyFrom(TermContext ctx) {
			super.copyFrom(ctx);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class TermUnaryContext extends TermContext {
		public Unary_expressionContext unary_expression() {
			return getRuleContext(Unary_expressionContext.class,0);
		}
		public TermUnaryContext(TermContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class TermMulContext extends TermContext {
		public TermContext term() {
			return getRuleContext(TermContext.class,0);
		}
		public TerminalNode MULOP() { return getToken(CSubset_2205126Parser.MULOP, 0); }
		public Unary_expressionContext unary_expression() {
			return getRuleContext(Unary_expressionContext.class,0);
		}
		public TermMulContext(TermContext ctx) { copyFrom(ctx); }
	}

	public final TermContext term() throws RecognitionException {
		return term(0);
	}

	private TermContext term(int _p) throws RecognitionException {
		ParserRuleContext _parentctx = _ctx;
		int _parentState = getState();
		TermContext _localctx = new TermContext(_ctx, _parentState);
		TermContext _prevctx = _localctx;
		int _startState = 36;
		enterRecursionRule(_localctx, 36, RULE_term, _p);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			{
			_localctx = new TermUnaryContext(_localctx);
			_ctx = _localctx;
			_prevctx = _localctx;

			setState(269);
			unary_expression();
			}
			_ctx.stop = _input.LT(-1);
			setState(276);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,20,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( _parseListeners!=null ) triggerExitRuleEvent();
					_prevctx = _localctx;
					{
					{
					_localctx = new TermMulContext(new TermContext(_parentctx, _parentState));
					pushNewRecursionContext(_localctx, _startState, RULE_term);
					setState(271);
					if (!(precpred(_ctx, 1))) throw new FailedPredicateException(this, "precpred(_ctx, 1)");
					setState(272);
					match(MULOP);
					setState(273);
					unary_expression();
					}
					} 
				}
				setState(278);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,20,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			unrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Unary_expressionContext extends ParserRuleContext {
		public Unary_expressionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_unary_expression; }
	 
		public Unary_expressionContext() { }
		public void copyFrom(Unary_expressionContext ctx) {
			super.copyFrom(ctx);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class UnaryNotContext extends Unary_expressionContext {
		public TerminalNode NOT() { return getToken(CSubset_2205126Parser.NOT, 0); }
		public Unary_expressionContext unary_expression() {
			return getRuleContext(Unary_expressionContext.class,0);
		}
		public UnaryNotContext(Unary_expressionContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class UnaryFactorContext extends Unary_expressionContext {
		public FactorContext factor() {
			return getRuleContext(FactorContext.class,0);
		}
		public UnaryFactorContext(Unary_expressionContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class UnaryAddContext extends Unary_expressionContext {
		public TerminalNode ADDOP() { return getToken(CSubset_2205126Parser.ADDOP, 0); }
		public Unary_expressionContext unary_expression() {
			return getRuleContext(Unary_expressionContext.class,0);
		}
		public UnaryAddContext(Unary_expressionContext ctx) { copyFrom(ctx); }
	}

	public final Unary_expressionContext unary_expression() throws RecognitionException {
		Unary_expressionContext _localctx = new Unary_expressionContext(_ctx, getState());
		enterRule(_localctx, 38, RULE_unary_expression);
		try {
			setState(284);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case ADDOP:
				_localctx = new UnaryAddContext(_localctx);
				enterOuterAlt(_localctx, 1);
				{
				setState(279);
				match(ADDOP);
				setState(280);
				unary_expression();
				}
				break;
			case NOT:
				_localctx = new UnaryNotContext(_localctx);
				enterOuterAlt(_localctx, 2);
				{
				setState(281);
				match(NOT);
				setState(282);
				unary_expression();
				}
				break;
			case LPAREN:
			case ID:
			case CONST_INT:
			case CONST_FLOAT:
				_localctx = new UnaryFactorContext(_localctx);
				enterOuterAlt(_localctx, 3);
				{
				setState(283);
				factor();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class FactorContext extends ParserRuleContext {
		public FactorContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_factor; }
	 
		public FactorContext() { }
		public void copyFrom(FactorContext ctx) {
			super.copyFrom(ctx);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class FactorFuncCallContext extends FactorContext {
		public TerminalNode ID() { return getToken(CSubset_2205126Parser.ID, 0); }
		public TerminalNode LPAREN() { return getToken(CSubset_2205126Parser.LPAREN, 0); }
		public Argument_listContext argument_list() {
			return getRuleContext(Argument_listContext.class,0);
		}
		public TerminalNode RPAREN() { return getToken(CSubset_2205126Parser.RPAREN, 0); }
		public FactorFuncCallContext(FactorContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class FactorIntContext extends FactorContext {
		public TerminalNode CONST_INT() { return getToken(CSubset_2205126Parser.CONST_INT, 0); }
		public FactorIntContext(FactorContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class FactorParenContext extends FactorContext {
		public TerminalNode LPAREN() { return getToken(CSubset_2205126Parser.LPAREN, 0); }
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public TerminalNode RPAREN() { return getToken(CSubset_2205126Parser.RPAREN, 0); }
		public FactorParenContext(FactorContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class FactorDecContext extends FactorContext {
		public VariableContext variable() {
			return getRuleContext(VariableContext.class,0);
		}
		public TerminalNode DECOP() { return getToken(CSubset_2205126Parser.DECOP, 0); }
		public FactorDecContext(FactorContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class FactorFloatContext extends FactorContext {
		public TerminalNode CONST_FLOAT() { return getToken(CSubset_2205126Parser.CONST_FLOAT, 0); }
		public FactorFloatContext(FactorContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class FactorIncContext extends FactorContext {
		public VariableContext variable() {
			return getRuleContext(VariableContext.class,0);
		}
		public TerminalNode INCOP() { return getToken(CSubset_2205126Parser.INCOP, 0); }
		public FactorIncContext(FactorContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class FactorVarContext extends FactorContext {
		public VariableContext variable() {
			return getRuleContext(VariableContext.class,0);
		}
		public FactorVarContext(FactorContext ctx) { copyFrom(ctx); }
	}

	public final FactorContext factor() throws RecognitionException {
		FactorContext _localctx = new FactorContext(_ctx, getState());
		enterRule(_localctx, 40, RULE_factor);
		try {
			setState(304);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,22,_ctx) ) {
			case 1:
				_localctx = new FactorVarContext(_localctx);
				enterOuterAlt(_localctx, 1);
				{
				setState(286);
				variable();
				}
				break;
			case 2:
				_localctx = new FactorFuncCallContext(_localctx);
				enterOuterAlt(_localctx, 2);
				{
				setState(287);
				match(ID);
				setState(288);
				match(LPAREN);
				setState(289);
				argument_list();
				setState(290);
				match(RPAREN);
				}
				break;
			case 3:
				_localctx = new FactorParenContext(_localctx);
				enterOuterAlt(_localctx, 3);
				{
				setState(292);
				match(LPAREN);
				setState(293);
				expression();
				setState(294);
				match(RPAREN);
				}
				break;
			case 4:
				_localctx = new FactorIntContext(_localctx);
				enterOuterAlt(_localctx, 4);
				{
				setState(296);
				match(CONST_INT);
				}
				break;
			case 5:
				_localctx = new FactorFloatContext(_localctx);
				enterOuterAlt(_localctx, 5);
				{
				setState(297);
				match(CONST_FLOAT);
				}
				break;
			case 6:
				_localctx = new FactorIncContext(_localctx);
				enterOuterAlt(_localctx, 6);
				{
				setState(298);
				variable();
				setState(299);
				match(INCOP);
				}
				break;
			case 7:
				_localctx = new FactorDecContext(_localctx);
				enterOuterAlt(_localctx, 7);
				{
				setState(301);
				variable();
				setState(302);
				match(DECOP);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Argument_listContext extends ParserRuleContext {
		public Argument_listContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_argument_list; }
	 
		public Argument_listContext() { }
		public void copyFrom(Argument_listContext ctx) {
			super.copyFrom(ctx);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class ArgListEmptyContext extends Argument_listContext {
		public ArgListEmptyContext(Argument_listContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class ArgListArgsContext extends Argument_listContext {
		public ArgumentsContext arguments() {
			return getRuleContext(ArgumentsContext.class,0);
		}
		public ArgListArgsContext(Argument_listContext ctx) { copyFrom(ctx); }
	}

	public final Argument_listContext argument_list() throws RecognitionException {
		Argument_listContext _localctx = new Argument_listContext(_ctx, getState());
		enterRule(_localctx, 42, RULE_argument_list);
		try {
			setState(308);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case LPAREN:
			case ADDOP:
			case NOT:
			case ID:
			case CONST_INT:
			case CONST_FLOAT:
				_localctx = new ArgListArgsContext(_localctx);
				enterOuterAlt(_localctx, 1);
				{
				setState(306);
				arguments(0);
				}
				break;
			case RPAREN:
				_localctx = new ArgListEmptyContext(_localctx);
				enterOuterAlt(_localctx, 2);
				{
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ArgumentsContext extends ParserRuleContext {
		public ArgumentsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_arguments; }
	 
		public ArgumentsContext() { }
		public void copyFrom(ArgumentsContext ctx) {
			super.copyFrom(ctx);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class ArgsSingleContext extends ArgumentsContext {
		public Logic_expressionContext logic_expression() {
			return getRuleContext(Logic_expressionContext.class,0);
		}
		public ArgsSingleContext(ArgumentsContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class ArgsMultipleContext extends ArgumentsContext {
		public ArgumentsContext arguments() {
			return getRuleContext(ArgumentsContext.class,0);
		}
		public TerminalNode COMMA() { return getToken(CSubset_2205126Parser.COMMA, 0); }
		public Logic_expressionContext logic_expression() {
			return getRuleContext(Logic_expressionContext.class,0);
		}
		public ArgsMultipleContext(ArgumentsContext ctx) { copyFrom(ctx); }
	}

	public final ArgumentsContext arguments() throws RecognitionException {
		return arguments(0);
	}

	private ArgumentsContext arguments(int _p) throws RecognitionException {
		ParserRuleContext _parentctx = _ctx;
		int _parentState = getState();
		ArgumentsContext _localctx = new ArgumentsContext(_ctx, _parentState);
		ArgumentsContext _prevctx = _localctx;
		int _startState = 44;
		enterRecursionRule(_localctx, 44, RULE_arguments, _p);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			{
			_localctx = new ArgsSingleContext(_localctx);
			_ctx = _localctx;
			_prevctx = _localctx;

			setState(311);
			logic_expression();
			}
			_ctx.stop = _input.LT(-1);
			setState(318);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,24,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( _parseListeners!=null ) triggerExitRuleEvent();
					_prevctx = _localctx;
					{
					{
					_localctx = new ArgsMultipleContext(new ArgumentsContext(_parentctx, _parentState));
					pushNewRecursionContext(_localctx, _startState, RULE_arguments);
					setState(313);
					if (!(precpred(_ctx, 2))) throw new FailedPredicateException(this, "precpred(_ctx, 2)");
					setState(314);
					match(COMMA);
					setState(315);
					logic_expression();
					}
					} 
				}
				setState(320);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,24,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			unrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}

	public boolean sempred(RuleContext _localctx, int ruleIndex, int predIndex) {
		switch (ruleIndex) {
		case 1:
			return program_sempred((ProgramContext)_localctx, predIndex);
		case 5:
			return parameter_list_sempred((Parameter_listContext)_localctx, predIndex);
		case 9:
			return declaration_list_sempred((Declaration_listContext)_localctx, predIndex);
		case 10:
			return statements_sempred((StatementsContext)_localctx, predIndex);
		case 17:
			return simple_expression_sempred((Simple_expressionContext)_localctx, predIndex);
		case 18:
			return term_sempred((TermContext)_localctx, predIndex);
		case 22:
			return arguments_sempred((ArgumentsContext)_localctx, predIndex);
		}
		return true;
	}
	private boolean program_sempred(ProgramContext _localctx, int predIndex) {
		switch (predIndex) {
		case 0:
			return precpred(_ctx, 2);
		}
		return true;
	}
	private boolean parameter_list_sempred(Parameter_listContext _localctx, int predIndex) {
		switch (predIndex) {
		case 1:
			return precpred(_ctx, 6);
		case 2:
			return precpred(_ctx, 5);
		case 3:
			return precpred(_ctx, 1);
		}
		return true;
	}
	private boolean declaration_list_sempred(Declaration_listContext _localctx, int predIndex) {
		switch (predIndex) {
		case 4:
			return precpred(_ctx, 6);
		case 5:
			return precpred(_ctx, 5);
		case 6:
			return precpred(_ctx, 1);
		}
		return true;
	}
	private boolean statements_sempred(StatementsContext _localctx, int predIndex) {
		switch (predIndex) {
		case 7:
			return precpred(_ctx, 1);
		}
		return true;
	}
	private boolean simple_expression_sempred(Simple_expressionContext _localctx, int predIndex) {
		switch (predIndex) {
		case 8:
			return precpred(_ctx, 1);
		}
		return true;
	}
	private boolean term_sempred(TermContext _localctx, int predIndex) {
		switch (predIndex) {
		case 9:
			return precpred(_ctx, 1);
		}
		return true;
	}
	private boolean arguments_sempred(ArgumentsContext _localctx, int predIndex) {
		switch (predIndex) {
		case 10:
			return precpred(_ctx, 2);
		}
		return true;
	}

	public static final String _serializedATN =
		"\u0004\u0001 \u0142\u0002\u0000\u0007\u0000\u0002\u0001\u0007\u0001\u0002"+
		"\u0002\u0007\u0002\u0002\u0003\u0007\u0003\u0002\u0004\u0007\u0004\u0002"+
		"\u0005\u0007\u0005\u0002\u0006\u0007\u0006\u0002\u0007\u0007\u0007\u0002"+
		"\b\u0007\b\u0002\t\u0007\t\u0002\n\u0007\n\u0002\u000b\u0007\u000b\u0002"+
		"\f\u0007\f\u0002\r\u0007\r\u0002\u000e\u0007\u000e\u0002\u000f\u0007\u000f"+
		"\u0002\u0010\u0007\u0010\u0002\u0011\u0007\u0011\u0002\u0012\u0007\u0012"+
		"\u0002\u0013\u0007\u0013\u0002\u0014\u0007\u0014\u0002\u0015\u0007\u0015"+
		"\u0002\u0016\u0007\u0016\u0001\u0000\u0001\u0000\u0001\u0000\u0001\u0001"+
		"\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0005\u00017\b\u0001"+
		"\n\u0001\f\u0001:\t\u0001\u0001\u0002\u0001\u0002\u0001\u0002\u0003\u0002"+
		"?\b\u0002\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0003"+
		"\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0003"+
		"\u0001\u0003\u0001\u0003\u0003\u0003N\b\u0003\u0001\u0004\u0001\u0004"+
		"\u0001\u0004\u0001\u0004\u0001\u0004\u0001\u0004\u0001\u0004\u0001\u0004"+
		"\u0001\u0004\u0001\u0004\u0001\u0004\u0001\u0004\u0001\u0004\u0003\u0004"+
		"]\b\u0004\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005"+
		"\u0001\u0005\u0001\u0005\u0001\u0005\u0003\u0005g\b\u0005\u0001\u0005"+
		"\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005"+
		"\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005"+
		"\u0005\u0005v\b\u0005\n\u0005\f\u0005y\t\u0005\u0001\u0006\u0001\u0006"+
		"\u0001\u0006\u0001\u0006\u0001\u0006\u0001\u0006\u0003\u0006\u0081\b\u0006"+
		"\u0001\u0007\u0001\u0007\u0001\u0007\u0001\u0007\u0001\b\u0001\b\u0001"+
		"\b\u0003\b\u008a\b\b\u0001\t\u0001\t\u0001\t\u0001\t\u0001\t\u0001\t\u0001"+
		"\t\u0001\t\u0001\t\u0003\t\u0095\b\t\u0001\t\u0001\t\u0001\t\u0001\t\u0001"+
		"\t\u0001\t\u0001\t\u0001\t\u0001\t\u0001\t\u0001\t\u0001\t\u0001\t\u0001"+
		"\t\u0005\t\u00a5\b\t\n\t\f\t\u00a8\t\t\u0001\n\u0001\n\u0001\n\u0001\n"+
		"\u0001\n\u0005\n\u00af\b\n\n\n\f\n\u00b2\t\n\u0001\u000b\u0001\u000b\u0001"+
		"\u000b\u0001\u000b\u0001\u000b\u0001\u000b\u0001\u000b\u0001\u000b\u0001"+
		"\u000b\u0001\u000b\u0001\u000b\u0001\u000b\u0001\u000b\u0001\u000b\u0001"+
		"\u000b\u0001\u000b\u0001\u000b\u0001\u000b\u0001\u000b\u0001\u000b\u0001"+
		"\u000b\u0001\u000b\u0001\u000b\u0001\u000b\u0001\u000b\u0001\u000b\u0001"+
		"\u000b\u0001\u000b\u0001\u000b\u0001\u000b\u0001\u000b\u0001\u000b\u0001"+
		"\u000b\u0001\u000b\u0001\u000b\u0001\u000b\u0001\u000b\u0001\u000b\u0001"+
		"\u000b\u0001\u000b\u0003\u000b\u00dc\b\u000b\u0001\f\u0001\f\u0001\f\u0001"+
		"\f\u0001\f\u0003\f\u00e3\b\f\u0001\r\u0001\r\u0001\r\u0001\r\u0001\r\u0001"+
		"\r\u0003\r\u00eb\b\r\u0001\u000e\u0001\u000e\u0001\u000e\u0001\u000e\u0001"+
		"\u000e\u0003\u000e\u00f2\b\u000e\u0001\u000f\u0001\u000f\u0001\u000f\u0001"+
		"\u000f\u0001\u000f\u0003\u000f\u00f9\b\u000f\u0001\u0010\u0001\u0010\u0001"+
		"\u0010\u0001\u0010\u0001\u0010\u0003\u0010\u0100\b\u0010\u0001\u0011\u0001"+
		"\u0011\u0001\u0011\u0001\u0011\u0001\u0011\u0001\u0011\u0005\u0011\u0108"+
		"\b\u0011\n\u0011\f\u0011\u010b\t\u0011\u0001\u0012\u0001\u0012\u0001\u0012"+
		"\u0001\u0012\u0001\u0012\u0001\u0012\u0005\u0012\u0113\b\u0012\n\u0012"+
		"\f\u0012\u0116\t\u0012\u0001\u0013\u0001\u0013\u0001\u0013\u0001\u0013"+
		"\u0001\u0013\u0003\u0013\u011d\b\u0013\u0001\u0014\u0001\u0014\u0001\u0014"+
		"\u0001\u0014\u0001\u0014\u0001\u0014\u0001\u0014\u0001\u0014\u0001\u0014"+
		"\u0001\u0014\u0001\u0014\u0001\u0014\u0001\u0014\u0001\u0014\u0001\u0014"+
		"\u0001\u0014\u0001\u0014\u0001\u0014\u0003\u0014\u0131\b\u0014\u0001\u0015"+
		"\u0001\u0015\u0003\u0015\u0135\b\u0015\u0001\u0016\u0001\u0016\u0001\u0016"+
		"\u0001\u0016\u0001\u0016\u0001\u0016\u0005\u0016\u013d\b\u0016\n\u0016"+
		"\f\u0016\u0140\t\u0016\u0001\u0016\u0000\u0007\u0002\n\u0012\u0014\"$"+
		",\u0017\u0000\u0002\u0004\u0006\b\n\f\u000e\u0010\u0012\u0014\u0016\u0018"+
		"\u001a\u001c\u001e \"$&(*,\u0000\u0000\u0157\u0000.\u0001\u0000\u0000"+
		"\u0000\u00021\u0001\u0000\u0000\u0000\u0004>\u0001\u0000\u0000\u0000\u0006"+
		"M\u0001\u0000\u0000\u0000\b\\\u0001\u0000\u0000\u0000\nf\u0001\u0000\u0000"+
		"\u0000\f\u0080\u0001\u0000\u0000\u0000\u000e\u0082\u0001\u0000\u0000\u0000"+
		"\u0010\u0089\u0001\u0000\u0000\u0000\u0012\u0094\u0001\u0000\u0000\u0000"+
		"\u0014\u00a9\u0001\u0000\u0000\u0000\u0016\u00db\u0001\u0000\u0000\u0000"+
		"\u0018\u00e2\u0001\u0000\u0000\u0000\u001a\u00ea\u0001\u0000\u0000\u0000"+
		"\u001c\u00f1\u0001\u0000\u0000\u0000\u001e\u00f8\u0001\u0000\u0000\u0000"+
		" \u00ff\u0001\u0000\u0000\u0000\"\u0101\u0001\u0000\u0000\u0000$\u010c"+
		"\u0001\u0000\u0000\u0000&\u011c\u0001\u0000\u0000\u0000(\u0130\u0001\u0000"+
		"\u0000\u0000*\u0134\u0001\u0000\u0000\u0000,\u0136\u0001\u0000\u0000\u0000"+
		"./\u0003\u0002\u0001\u0000/0\u0005\u0000\u0000\u00010\u0001\u0001\u0000"+
		"\u0000\u000012\u0006\u0001\uffff\uffff\u000023\u0003\u0004\u0002\u0000"+
		"38\u0001\u0000\u0000\u000045\n\u0002\u0000\u000057\u0003\u0004\u0002\u0000"+
		"64\u0001\u0000\u0000\u00007:\u0001\u0000\u0000\u000086\u0001\u0000\u0000"+
		"\u000089\u0001\u0000\u0000\u00009\u0003\u0001\u0000\u0000\u0000:8\u0001"+
		"\u0000\u0000\u0000;?\u0003\u000e\u0007\u0000<?\u0003\u0006\u0003\u0000"+
		"=?\u0003\b\u0004\u0000>;\u0001\u0000\u0000\u0000><\u0001\u0000\u0000\u0000"+
		">=\u0001\u0000\u0000\u0000?\u0005\u0001\u0000\u0000\u0000@A\u0003\u0010"+
		"\b\u0000AB\u0005\u001e\u0000\u0000BC\u0005\u000e\u0000\u0000CD\u0003\n"+
		"\u0005\u0000DE\u0005\u000f\u0000\u0000EF\u0005\u0014\u0000\u0000FN\u0001"+
		"\u0000\u0000\u0000GH\u0003\u0010\b\u0000HI\u0005\u001e\u0000\u0000IJ\u0005"+
		"\u000e\u0000\u0000JK\u0005\u000f\u0000\u0000KL\u0005\u0014\u0000\u0000"+
		"LN\u0001\u0000\u0000\u0000M@\u0001\u0000\u0000\u0000MG\u0001\u0000\u0000"+
		"\u0000N\u0007\u0001\u0000\u0000\u0000OP\u0003\u0010\b\u0000PQ\u0005\u001e"+
		"\u0000\u0000QR\u0005\u000e\u0000\u0000RS\u0003\n\u0005\u0000ST\u0005\u000f"+
		"\u0000\u0000TU\u0003\f\u0006\u0000U]\u0001\u0000\u0000\u0000VW\u0003\u0010"+
		"\b\u0000WX\u0005\u001e\u0000\u0000XY\u0005\u000e\u0000\u0000YZ\u0005\u000f"+
		"\u0000\u0000Z[\u0003\f\u0006\u0000[]\u0001\u0000\u0000\u0000\\O\u0001"+
		"\u0000\u0000\u0000\\V\u0001\u0000\u0000\u0000]\t\u0001\u0000\u0000\u0000"+
		"^_\u0006\u0005\uffff\uffff\u0000_`\u0003\u0010\b\u0000`a\u0005\u001e\u0000"+
		"\u0000ag\u0001\u0000\u0000\u0000bg\u0003\u0010\b\u0000cd\u0003\u0010\b"+
		"\u0000de\u0005\u0016\u0000\u0000eg\u0001\u0000\u0000\u0000f^\u0001\u0000"+
		"\u0000\u0000fb\u0001\u0000\u0000\u0000fc\u0001\u0000\u0000\u0000gw\u0001"+
		"\u0000\u0000\u0000hi\n\u0006\u0000\u0000ij\u0005\u0015\u0000\u0000jk\u0003"+
		"\u0010\b\u0000kl\u0005\u001e\u0000\u0000lv\u0001\u0000\u0000\u0000mn\n"+
		"\u0005\u0000\u0000no\u0005\u0015\u0000\u0000ov\u0003\u0010\b\u0000pq\n"+
		"\u0001\u0000\u0000qr\u0005\u0015\u0000\u0000rs\u0003\u0010\b\u0000st\u0005"+
		"\u0016\u0000\u0000tv\u0001\u0000\u0000\u0000uh\u0001\u0000\u0000\u0000"+
		"um\u0001\u0000\u0000\u0000up\u0001\u0000\u0000\u0000vy\u0001\u0000\u0000"+
		"\u0000wu\u0001\u0000\u0000\u0000wx\u0001\u0000\u0000\u0000x\u000b\u0001"+
		"\u0000\u0000\u0000yw\u0001\u0000\u0000\u0000z{\u0005\u0010\u0000\u0000"+
		"{|\u0003\u0014\n\u0000|}\u0005\u0011\u0000\u0000}\u0081\u0001\u0000\u0000"+
		"\u0000~\u007f\u0005\u0010\u0000\u0000\u007f\u0081\u0005\u0011\u0000\u0000"+
		"\u0080z\u0001\u0000\u0000\u0000\u0080~\u0001\u0000\u0000\u0000\u0081\r"+
		"\u0001\u0000\u0000\u0000\u0082\u0083\u0003\u0010\b\u0000\u0083\u0084\u0003"+
		"\u0012\t\u0000\u0084\u0085\u0005\u0014\u0000\u0000\u0085\u000f\u0001\u0000"+
		"\u0000\u0000\u0086\u008a\u0005\u000b\u0000\u0000\u0087\u008a\u0005\f\u0000"+
		"\u0000\u0088\u008a\u0005\r\u0000\u0000\u0089\u0086\u0001\u0000\u0000\u0000"+
		"\u0089\u0087\u0001\u0000\u0000\u0000\u0089\u0088\u0001\u0000\u0000\u0000"+
		"\u008a\u0011\u0001\u0000\u0000\u0000\u008b\u008c\u0006\t\uffff\uffff\u0000"+
		"\u008c\u0095\u0005\u001e\u0000\u0000\u008d\u008e\u0005\u001e\u0000\u0000"+
		"\u008e\u008f\u0005\u0012\u0000\u0000\u008f\u0090\u0005\u001f\u0000\u0000"+
		"\u0090\u0095\u0005\u0013\u0000\u0000\u0091\u0092\u0005\u001e\u0000\u0000"+
		"\u0092\u0093\u0005\u0016\u0000\u0000\u0093\u0095\u0005\u001e\u0000\u0000"+
		"\u0094\u008b\u0001\u0000\u0000\u0000\u0094\u008d\u0001\u0000\u0000\u0000"+
		"\u0094\u0091\u0001\u0000\u0000\u0000\u0095\u00a6\u0001\u0000\u0000\u0000"+
		"\u0096\u0097\n\u0006\u0000\u0000\u0097\u0098\u0005\u0015\u0000\u0000\u0098"+
		"\u00a5\u0005\u001e\u0000\u0000\u0099\u009a\n\u0005\u0000\u0000\u009a\u009b"+
		"\u0005\u0015\u0000\u0000\u009b\u009c\u0005\u001e\u0000\u0000\u009c\u009d"+
		"\u0005\u0012\u0000\u0000\u009d\u009e\u0005\u001f\u0000\u0000\u009e\u00a5"+
		"\u0005\u0013\u0000\u0000\u009f\u00a0\n\u0001\u0000\u0000\u00a0\u00a1\u0005"+
		"\u0015\u0000\u0000\u00a1\u00a2\u0005\u001e\u0000\u0000\u00a2\u00a3\u0005"+
		"\u0016\u0000\u0000\u00a3\u00a5\u0005\u001e\u0000\u0000\u00a4\u0096\u0001"+
		"\u0000\u0000\u0000\u00a4\u0099\u0001\u0000\u0000\u0000\u00a4\u009f\u0001"+
		"\u0000\u0000\u0000\u00a5\u00a8\u0001\u0000\u0000\u0000\u00a6\u00a4\u0001"+
		"\u0000\u0000\u0000\u00a6\u00a7\u0001\u0000\u0000\u0000\u00a7\u0013\u0001"+
		"\u0000\u0000\u0000\u00a8\u00a6\u0001\u0000\u0000\u0000\u00a9\u00aa\u0006"+
		"\n\uffff\uffff\u0000\u00aa\u00ab\u0003\u0016\u000b\u0000\u00ab\u00b0\u0001"+
		"\u0000\u0000\u0000\u00ac\u00ad\n\u0001\u0000\u0000\u00ad\u00af\u0003\u0016"+
		"\u000b\u0000\u00ae\u00ac\u0001\u0000\u0000\u0000\u00af\u00b2\u0001\u0000"+
		"\u0000\u0000\u00b0\u00ae\u0001\u0000\u0000\u0000\u00b0\u00b1\u0001\u0000"+
		"\u0000\u0000\u00b1\u0015\u0001\u0000\u0000\u0000\u00b2\u00b0\u0001\u0000"+
		"\u0000\u0000\u00b3\u00dc\u0003\u000e\u0007\u0000\u00b4\u00dc\u0003\u0018"+
		"\f\u0000\u00b5\u00dc\u0003\f\u0006\u0000\u00b6\u00b7\u0005\u0007\u0000"+
		"\u0000\u00b7\u00b8\u0005\u000e\u0000\u0000\u00b8\u00b9\u0003\u0018\f\u0000"+
		"\u00b9\u00ba\u0003\u0018\f\u0000\u00ba\u00bb\u0003\u001c\u000e\u0000\u00bb"+
		"\u00bc\u0005\u000f\u0000\u0000\u00bc\u00bd\u0003\u0016\u000b\u0000\u00bd"+
		"\u00dc\u0001\u0000\u0000\u0000\u00be\u00bf\u0005\u0005\u0000\u0000\u00bf"+
		"\u00c0\u0005\u000e\u0000\u0000\u00c0\u00c1\u0003\u001c\u000e\u0000\u00c1"+
		"\u00c2\u0005\u000f\u0000\u0000\u00c2\u00c3\u0003\u0016\u000b\u0000\u00c3"+
		"\u00c4\u0005\u0006\u0000\u0000\u00c4\u00c5\u0003\u0016\u000b\u0000\u00c5"+
		"\u00dc\u0001\u0000\u0000\u0000\u00c6\u00c7\u0005\u0005\u0000\u0000\u00c7"+
		"\u00c8\u0005\u000e\u0000\u0000\u00c8\u00c9\u0003\u001c\u000e\u0000\u00c9"+
		"\u00ca\u0005\u000f\u0000\u0000\u00ca\u00cb\u0003\u0016\u000b\u0000\u00cb"+
		"\u00dc\u0001\u0000\u0000\u0000\u00cc\u00cd\u0005\b\u0000\u0000\u00cd\u00ce"+
		"\u0005\u000e\u0000\u0000\u00ce\u00cf\u0003\u001c\u000e\u0000\u00cf\u00d0"+
		"\u0005\u000f\u0000\u0000\u00d0\u00d1\u0003\u0016\u000b\u0000\u00d1\u00dc"+
		"\u0001\u0000\u0000\u0000\u00d2\u00d3\u0005\t\u0000\u0000\u00d3\u00d4\u0005"+
		"\u000e\u0000\u0000\u00d4\u00d5\u0005\u001e\u0000\u0000\u00d5\u00d6\u0005"+
		"\u000f\u0000\u0000\u00d6\u00dc\u0005\u0014\u0000\u0000\u00d7\u00d8\u0005"+
		"\n\u0000\u0000\u00d8\u00d9\u0003\u001c\u000e\u0000\u00d9\u00da\u0005\u0014"+
		"\u0000\u0000\u00da\u00dc\u0001\u0000\u0000\u0000\u00db\u00b3\u0001\u0000"+
		"\u0000\u0000\u00db\u00b4\u0001\u0000\u0000\u0000\u00db\u00b5\u0001\u0000"+
		"\u0000\u0000\u00db\u00b6\u0001\u0000\u0000\u0000\u00db\u00be\u0001\u0000"+
		"\u0000\u0000\u00db\u00c6\u0001\u0000\u0000\u0000\u00db\u00cc\u0001\u0000"+
		"\u0000\u0000\u00db\u00d2\u0001\u0000\u0000\u0000\u00db\u00d7\u0001\u0000"+
		"\u0000\u0000\u00dc\u0017\u0001\u0000\u0000\u0000\u00dd\u00e3\u0005\u0014"+
		"\u0000\u0000\u00de\u00df\u0003\u001c\u000e\u0000\u00df\u00e0\u0005\u0014"+
		"\u0000\u0000\u00e0\u00e3\u0001\u0000\u0000\u0000\u00e1\u00e3\u0003\u001c"+
		"\u000e\u0000\u00e2\u00dd\u0001\u0000\u0000\u0000\u00e2\u00de\u0001\u0000"+
		"\u0000\u0000\u00e2\u00e1\u0001\u0000\u0000\u0000\u00e3\u0019\u0001\u0000"+
		"\u0000\u0000\u00e4\u00eb\u0005\u001e\u0000\u0000\u00e5\u00e6\u0005\u001e"+
		"\u0000\u0000\u00e6\u00e7\u0005\u0012\u0000\u0000\u00e7\u00e8\u0003\u001c"+
		"\u000e\u0000\u00e8\u00e9\u0005\u0013\u0000\u0000\u00e9\u00eb\u0001\u0000"+
		"\u0000\u0000\u00ea\u00e4\u0001\u0000\u0000\u0000\u00ea\u00e5\u0001\u0000"+
		"\u0000\u0000\u00eb\u001b\u0001\u0000\u0000\u0000\u00ec\u00f2\u0003\u001e"+
		"\u000f\u0000\u00ed\u00ee\u0003\u001a\r\u0000\u00ee\u00ef\u0005\u001d\u0000"+
		"\u0000\u00ef\u00f0\u0003\u001e\u000f\u0000\u00f0\u00f2\u0001\u0000\u0000"+
		"\u0000\u00f1\u00ec\u0001\u0000\u0000\u0000\u00f1\u00ed\u0001\u0000\u0000"+
		"\u0000\u00f2\u001d\u0001\u0000\u0000\u0000\u00f3\u00f9\u0003 \u0010\u0000"+
		"\u00f4\u00f5\u0003 \u0010\u0000\u00f5\u00f6\u0005\u001c\u0000\u0000\u00f6"+
		"\u00f7\u0003 \u0010\u0000\u00f7\u00f9\u0001\u0000\u0000\u0000\u00f8\u00f3"+
		"\u0001\u0000\u0000\u0000\u00f8\u00f4\u0001\u0000\u0000\u0000\u00f9\u001f"+
		"\u0001\u0000\u0000\u0000\u00fa\u0100\u0003\"\u0011\u0000\u00fb\u00fc\u0003"+
		"\"\u0011\u0000\u00fc\u00fd\u0005\u001b\u0000\u0000\u00fd\u00fe\u0003\""+
		"\u0011\u0000\u00fe\u0100\u0001\u0000\u0000\u0000\u00ff\u00fa\u0001\u0000"+
		"\u0000\u0000\u00ff\u00fb\u0001\u0000\u0000\u0000\u0100!\u0001\u0000\u0000"+
		"\u0000\u0101\u0102\u0006\u0011\uffff\uffff\u0000\u0102\u0103\u0003$\u0012"+
		"\u0000\u0103\u0109\u0001\u0000\u0000\u0000\u0104\u0105\n\u0001\u0000\u0000"+
		"\u0105\u0106\u0005\u0016\u0000\u0000\u0106\u0108\u0003$\u0012\u0000\u0107"+
		"\u0104\u0001\u0000\u0000\u0000\u0108\u010b\u0001\u0000\u0000\u0000\u0109"+
		"\u0107\u0001\u0000\u0000\u0000\u0109\u010a\u0001\u0000\u0000\u0000\u010a"+
		"#\u0001\u0000\u0000\u0000\u010b\u0109\u0001\u0000\u0000\u0000\u010c\u010d"+
		"\u0006\u0012\uffff\uffff\u0000\u010d\u010e\u0003&\u0013\u0000\u010e\u0114"+
		"\u0001\u0000\u0000\u0000\u010f\u0110\n\u0001\u0000\u0000\u0110\u0111\u0005"+
		"\u0017\u0000\u0000\u0111\u0113\u0003&\u0013\u0000\u0112\u010f\u0001\u0000"+
		"\u0000\u0000\u0113\u0116\u0001\u0000\u0000\u0000\u0114\u0112\u0001\u0000"+
		"\u0000\u0000\u0114\u0115\u0001\u0000\u0000\u0000\u0115%\u0001\u0000\u0000"+
		"\u0000\u0116\u0114\u0001\u0000\u0000\u0000\u0117\u0118\u0005\u0016\u0000"+
		"\u0000\u0118\u011d\u0003&\u0013\u0000\u0119\u011a\u0005\u001a\u0000\u0000"+
		"\u011a\u011d\u0003&\u0013\u0000\u011b\u011d\u0003(\u0014\u0000\u011c\u0117"+
		"\u0001\u0000\u0000\u0000\u011c\u0119\u0001\u0000\u0000\u0000\u011c\u011b"+
		"\u0001\u0000\u0000\u0000\u011d\'\u0001\u0000\u0000\u0000\u011e\u0131\u0003"+
		"\u001a\r\u0000\u011f\u0120\u0005\u001e\u0000\u0000\u0120\u0121\u0005\u000e"+
		"\u0000\u0000\u0121\u0122\u0003*\u0015\u0000\u0122\u0123\u0005\u000f\u0000"+
		"\u0000\u0123\u0131\u0001\u0000\u0000\u0000\u0124\u0125\u0005\u000e\u0000"+
		"\u0000\u0125\u0126\u0003\u001c\u000e\u0000\u0126\u0127\u0005\u000f\u0000"+
		"\u0000\u0127\u0131\u0001\u0000\u0000\u0000\u0128\u0131\u0005\u001f\u0000"+
		"\u0000\u0129\u0131\u0005 \u0000\u0000\u012a\u012b\u0003\u001a\r\u0000"+
		"\u012b\u012c\u0005\u0018\u0000\u0000\u012c\u0131\u0001\u0000\u0000\u0000"+
		"\u012d\u012e\u0003\u001a\r\u0000\u012e\u012f\u0005\u0019\u0000\u0000\u012f"+
		"\u0131\u0001\u0000\u0000\u0000\u0130\u011e\u0001\u0000\u0000\u0000\u0130"+
		"\u011f\u0001\u0000\u0000\u0000\u0130\u0124\u0001\u0000\u0000\u0000\u0130"+
		"\u0128\u0001\u0000\u0000\u0000\u0130\u0129\u0001\u0000\u0000\u0000\u0130"+
		"\u012a\u0001\u0000\u0000\u0000\u0130\u012d\u0001\u0000\u0000\u0000\u0131"+
		")\u0001\u0000\u0000\u0000\u0132\u0135\u0003,\u0016\u0000\u0133\u0135\u0001"+
		"\u0000\u0000\u0000\u0134\u0132\u0001\u0000\u0000\u0000\u0134\u0133\u0001"+
		"\u0000\u0000\u0000\u0135+\u0001\u0000\u0000\u0000\u0136\u0137\u0006\u0016"+
		"\uffff\uffff\u0000\u0137\u0138\u0003\u001e\u000f\u0000\u0138\u013e\u0001"+
		"\u0000\u0000\u0000\u0139\u013a\n\u0002\u0000\u0000\u013a\u013b\u0005\u0015"+
		"\u0000\u0000\u013b\u013d\u0003\u001e\u000f\u0000\u013c\u0139\u0001\u0000"+
		"\u0000\u0000\u013d\u0140\u0001\u0000\u0000\u0000\u013e\u013c\u0001\u0000"+
		"\u0000\u0000\u013e\u013f\u0001\u0000\u0000\u0000\u013f-\u0001\u0000\u0000"+
		"\u0000\u0140\u013e\u0001\u0000\u0000\u0000\u00198>M\\fuw\u0080\u0089\u0094"+
		"\u00a4\u00a6\u00b0\u00db\u00e2\u00ea\u00f1\u00f8\u00ff\u0109\u0114\u011c"+
		"\u0130\u0134\u013e";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}