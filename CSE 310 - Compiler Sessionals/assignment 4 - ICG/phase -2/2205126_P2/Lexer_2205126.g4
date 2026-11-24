lexer grammar Lexer_2205126;

@lexer::header {
    #pragma once
    #include <iostream>
    #include <fstream>
    #include <string>

    extern std::ofstream lexLogFile;
}

@lexer::members {
    void writeIntoLexLogFile(const std::string &message) {
        if (!lexLogFile.is_open()) {
            lexLogFile.open("log.txt", std::ios::app);
            if (!lexLogFile) {
                std::cerr << "Error opening log.txt" << std::endl;
                return;
            }
        }
        lexLogFile << message << std::endl;
        lexLogFile.flush();
    }
}

LINE_COMMENT
    : '//' ~[\r\n]* {
        writeIntoLexLogFile(
          "Line# " + std::to_string(getLine())
          + ": Token <SINGLE LINE COMMENT> Lexeme "
          + getText()
        );
    } -> skip
    ;

BLOCK_COMMENT
  : '/*' ( . | '\r' | '\n' )*? '*/' {
      {
        std::string txt = getText();
        std::string content = txt.substr(2, txt.size() - 4);
        writeIntoLexLogFile(
          "Line# " + std::to_string(getLine())
          + ": Token <MULTI LINE COMMENT> Lexeme /*"
          + content + "*/"
        );
      }
    }
    -> skip
  ;

STRING
    : '"' ( '\\' . | ~["\\\r\n] )* '"' {
        writeIntoLexLogFile(
          "Line# " + std::to_string(getLine())
          + ": Token <STRING> Lexeme " + getText()
        );
    } -> skip
    ;

WS      : [ \t\f\r\n]+ -> skip ;

IF       : 'if' ;
ELSE     : 'else' ;
FOR      : 'for' ;
WHILE    : 'while' ;
PRINTLN  : 'println' ;
RETURN   : 'return' ;
INT      : 'int' ;
FLOAT    : 'float' ;
VOID     : 'void' ;

LPAREN   : '(' ;
RPAREN   : ')' ;
LCURL    : '{' ;
RCURL    : '}' ;
LTHIRD   : '[' ;
RTHIRD   : ']' ;
SEMICOLON: ';' ;
COMMA    : ',' ;

ADDOP    : [+\-] ;
MULOP    : [*/%] ;
INCOP    : '++' ;
DECOP    : '--' ;
NOT      : '!' ;
RELOP    : '<=' | '==' | '>=' | '>' | '<' | '!=' ;
LOGICOP  : '&&' | '||' ;
ASSIGNOP : '=' ;

ID         : [A-Za-z_] [A-Za-z0-9_]* ;
CONST_INT  : [0-9]+ ;
CONST_FLOAT
    : [0-9]+ ('.' [0-9]*)? ([Ee][+\-]? [0-9]+)?
    | '.' [0-9]+
    | [0-9]+ '.'
    ;
