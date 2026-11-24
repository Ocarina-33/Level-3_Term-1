#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "antlr4-runtime.h"
#include "CSubset_2205126Lexer.h"
#include "CSubset_2205126Parser.h"
#include "EvaluateVisitor.h"

using namespace antlr4;
using namespace std;

ofstream lexLogFile; 
ofstream logFile;
ofstream errorFile;

std::vector<std::pair<int, string>> globalErrors;
std::map<int, std::vector<string>> globalParserErrors;

class CustomErrorListener : public BaseErrorListener {
public:
    CustomErrorListener() {}

    virtual void syntaxError(Recognizer *recognizer, Token * offendingSymbol, size_t line, size_t charPositionInLine,
                             const std::string &msg, std::exception_ptr e) override {
        string customMsg = msg;
        if (offendingSymbol != nullptr) {
            string text = offendingSymbol->getText();
            
            CommonTokenStream* tokens = nullptr;
            
            CSubset_2205126Parser* parser = dynamic_cast<CSubset_2205126Parser*>(recognizer);
            if (parser != nullptr) {
                tokens = dynamic_cast<CommonTokenStream*>(parser->getInputStream());
            }

            if (tokens != nullptr) {
                size_t index = offendingSymbol->getTokenIndex();
                size_t size = tokens->size();
                Token* prevToken = (index > 0 && index - 1 < size) ? tokens->get(index - 1) : nullptr;
                Token* nextToken = (index + 1 < size) ? tokens->get(index + 1) : nullptr;

                if (((text == "-" && nextToken != nullptr && nextToken->getText() == ")") ||
                     (text == ")" && prevToken != nullptr && prevToken->getText() == "-"))) {
                    customMsg = "unexpected token(s) '-' before ')'";
                } else if (text == "-" && nextToken != nullptr && nextToken->getType() == CSubset_2205126Lexer::ID) {
                    customMsg = "unexpected token(s) '- " + nextToken->getText() + "' in declaration list";
                } else if (text == "=" && prevToken != nullptr && (prevToken->getText() == "+" || prevToken->getText() == "-")) {
                    customMsg = "invalid operand '=' after '" + prevToken->getText() + "'";
                }
            }
        }

        globalParserErrors[line].push_back("syntax error, " + customMsg);
    }
};

int main(int argc, const char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        cerr << "Error opening input file: " << argv[1] << endl;
        return 1;
    }

    logFile.open("log.txt");
    errorFile.open("error.txt");

    if (!logFile.is_open() || !errorFile.is_open()) {
        cerr << "Error opening output files (log.txt or error.txt)" << endl;
        return 1;
    }

    ANTLRInputStream input(inputFile);
    CSubset_2205126Lexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    CSubset_2205126Parser parser(&tokens);

    CustomErrorListener errorListener;
    parser.removeErrorListeners();
    parser.addErrorListener(&errorListener);
    lexer.removeErrorListeners();
    lexer.addErrorListener(&errorListener);

    CSubset_2205126Parser::StartContext* tree = parser.start();

    EvaluateVisitor visitor(logFile, errorFile);
    visitor.visitStart(tree);

    std::stable_sort(globalErrors.begin(), globalErrors.end(), [](const std::pair<int, string>& a, const std::pair<int, string>& b) {
        return a.first < b.first;
    });

    for (const auto& err : globalErrors) {
        errorFile << "Error at line " << err.first << ": " << err.second << "\n\n";
    }

    errorFile.close();
    logFile.close();
    inputFile.close();

    if (lexLogFile.is_open()) {
        lexLogFile.close();
    }

    cout << "Parsing completed." << endl;
    return 0;
}
