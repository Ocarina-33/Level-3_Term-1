#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "antlr4-runtime.h"
#include "CSubset_2205126Lexer.h"
#include "CSubset_2205126Parser.h"
#include "ICGVisitor.h"

using namespace antlr4;
using namespace std;

std::ofstream lexLogFile;


void optimizeCode(const string& inputFile, const string& outputFile) {
    ifstream in(inputFile);
    ofstream out(outputFile);
    string line;
    vector<string> instructions;

    while (getline(in, line)) {
        instructions.push_back(line);
    }

    //Remove redundant labels
    map<string, string> labelMap;
    vector<string> tempInstructions;
    for (size_t i = 0; i < instructions.size(); i++) {
        string current = instructions[i];
        if (current.find(":") != string::npos && current.find(";") == string::npos) {
            string currentLabel = current.substr(0, current.find(":"));
            
            currentLabel.erase(0, currentLabel.find_first_not_of(" \t"));
            currentLabel.erase(currentLabel.find_last_not_of(" \t") + 1);
            
            size_t j = i + 1;
            while (j < instructions.size()) {
                string next = instructions[j];
                if (next.empty() || next.find_first_not_of(" \t") == string::npos) {
                    j++;
                    continue;
                }
                if (next.find(":") != string::npos && next.find(";") == string::npos) {
                    string nextLabel = next.substr(0, next.find(":"));
                    nextLabel.erase(0, nextLabel.find_first_not_of(" \t"));
                    nextLabel.erase(nextLabel.find_last_not_of(" \t") + 1);
                    labelMap[nextLabel] = currentLabel;
                    tempInstructions.push_back("; Optimized: redundant label " + nextLabel + " merged into " + currentLabel);
                    j++;
                } else {
                    break;
                }
            }
            tempInstructions.push_back(current);
            i = j - 1;
        } else {
            tempInstructions.push_back(current);
        }
    }

    //Instruction substitutions
    for (size_t i = 0; i < tempInstructions.size(); i++) {
        string current = tempInstructions[i];
        
        for (auto const& [oldLabel, newLabel] : labelMap) {
            size_t pos = current.find(oldLabel);
            while (pos != string::npos) {
                bool match = true;
                if (pos > 0 && (isalnum(current[pos - 1]) || current[pos - 1] == '_')) match = false;
                if (pos + oldLabel.length() < current.length() && (isalnum(current[pos + oldLabel.length()]) || current[pos + oldLabel.length()] == '_')) match = false;
                
                if (match) {
                    current.replace(pos, oldLabel.length(), newLabel);
                    pos = current.find(oldLabel, pos + newLabel.length());
                } else {
                    pos = current.find(oldLabel, pos + oldLabel.length());
                }
            }
        }

        // Find the next actual instruction
        size_t nextIdx = i + 1;
        while (nextIdx < tempInstructions.size()) {
            if (tempInstructions[nextIdx].empty() || tempInstructions[nextIdx].find(";") != string::npos) {
                nextIdx++;
            } else {
                break;
            }
        }

        if (nextIdx < tempInstructions.size()) {
            string next = tempInstructions[nextIdx];
            
            // push/pop same register
            if (current.find("push ") != string::npos && next.find("pop ") != string::npos) {
                string reg1 = current.substr(current.find("push ") + 5);
                string reg2 = next.substr(next.find("pop ") + 4);
                reg1.erase(0, reg1.find_first_not_of(" \t")); reg1.erase(reg1.find_last_not_of(" \t") + 1);
                reg2.erase(0, reg2.find_first_not_of(" \t")); reg2.erase(reg2.find_last_not_of(" \t") + 1);
                if (reg1 == reg2) {
                    out << "; Optimized: removed redundant push/pop of " << reg1 << "\n";
                    // Skip all lines up to nextIdx
                    i = nextIdx;
                    continue;
                }
            }
            
            // redundant movs
            if (current.find("mov ") != string::npos && next.find("mov ") != string::npos) {
                string currentArgs = current.substr(current.find("mov ") + 4);
                string nextArgs = next.substr(next.find("mov ") + 4);
                
                size_t comma1 = currentArgs.find(",");
                size_t comma2 = nextArgs.find(",");
                if (comma1 != string::npos && comma2 != string::npos) {
                    string cDest = currentArgs.substr(0, comma1);
                    string cSrc = currentArgs.substr(comma1 + 1);
                    string nDest = nextArgs.substr(0, comma2);
                    string nSrc = nextArgs.substr(comma2 + 1);
                    
                    auto trim = [](string& s) { s.erase(0, s.find_first_not_of(" \t")); s.erase(s.find_last_not_of(" \t") + 1); };
                    trim(cDest); trim(cSrc); trim(nDest); trim(nSrc);
                    
                    if (cDest == nSrc && cSrc == nDest) {
                        out << current << "\n";
                        // Print the comments that were in between
                        for (size_t k = i + 1; k < nextIdx; k++) {
                            out << tempInstructions[k] << "\n";
                        }
                        out << "; Optimized: removed redundant mov\n";
                        i = nextIdx;
                        continue;
                    }
                }
            }
        }
        
        // add 0 or sub 0
        if (current.find("add eax, 0") != string::npos || current.find("sub eax, 0") != string::npos) {
            continue;
        }
        
        // imul 1
        if (current.find("imul 1") != string::npos) {
             continue;
        }
        
        out << current << "\n";
    }
    
    in.close();
    out.close();
}

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

    ANTLRInputStream input(inputFile);
    CSubset_2205126Lexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    CSubset_2205126Parser parser(&tokens);

    CSubset_2205126Parser::StartContext* tree = parser.start();

    ofstream codeOut("code.asm");
    ICGVisitor visitor(codeOut);
    visitor.visitStart(tree);
    codeOut.close();

    optimizeCode("code.asm", "optimized_code.asm");

    cout << "Intermediate Code Generation completed successfully." << endl;
    return 0;
}
