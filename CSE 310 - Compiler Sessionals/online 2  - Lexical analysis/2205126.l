%option noyywrap

%{
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
ofstream logout;

vector<char> v;
bool is_valid = true;

void check_match(char expected_open) {
    if (v.empty()) {
        is_valid = false;
    } else if (v.back() != expected_open) {
        is_valid = false;
    } else {
        v.pop_back();
    }
}

%}


LETTER     [a-zA-Z_]
INTEGER     [0-9]+
NEWLINE    [\r]?\n
ALNUM      [A-Za-z_0-9]



%%

"{" { v.push_back('{'); }


"}" { 
    check_match('{'); 
    if (!is_valid){
        logout<<"Error: unmatched {"<<endl;
        return 0;
    } 
}

"\""{ALNUM}"\"" | {INTEGER} [ \t\n]*":" {

}

"\""{ALNUM}"\"" | ({DIGIT}*\.{DIGIT}+([Ee][+-]?{DIGIT}+)?)|({DIGIT}+[Ee][+-]?{DIGIT}+)[ \t\n]*":" {
     logout<<"Error: invalid dictionary key"<<endl;
}


[ \t\n\r]+ { 
    
}

. {
    
}


<INITIAL><<EOF>> { 
    return 0; 
}



%%

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./a.out <input_file>\n");
        return 0;
    }
    
    FILE *fin = fopen(argv[1], "r");
    if (fin == NULL) {
        printf("Cannot open specified file\n");
        return 0;
    }

    logout.open("log.txt");

   
    streambuf *coutbuf = cout.rdbuf(); 
    cout.rdbuf(logout.rdbuf());

    yyin = fin; 
    yylex();    
    fclose(yyin);


    cout.rdbuf(coutbuf); 
    logout.close();

    return 0;


}