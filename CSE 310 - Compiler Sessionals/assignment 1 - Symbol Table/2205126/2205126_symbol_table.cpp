#include <bits/stdc++.h>
using namespace std;

class SymbolInfo{
 private:
    string name;
    string type;
    SymbolInfo* next;

 public:
    SymbolInfo(string name, string type){
        this->name = name;
        this->type = type;
        this->next = nullptr;
    }

    ~SymbolInfo(){
        this->next = nullptr;
    }

    void setName(string name){
        this->name = name;
    }

    void setType(string type){
        this->type = type;
    }
    
    void setNext(SymbolInfo* next){
        this->next = next;
    }

    string getName(){
        return this->name;
    }

    string getType(){
        return this->type;
    }
    
    SymbolInfo* getNext(){
        return this->next;
    }
    
};



class ScopeTable{

 private:
    SymbolInfo**  array_symbols;
    ScopeTable* parent_scopeTable;
    int totalnum_buckets;
    int unique_id;

 public:
    
    ScopeTable(ScopeTable* parent_scopeTable, int totalnum_buckets, int unique_id){
        this->parent_scopeTable = parent_scopeTable;
        this->totalnum_buckets = totalnum_buckets;
        this->unique_id = unique_id;
        this->array_symbols = new SymbolInfo*[totalnum_buckets];

        for(int i = 0 ; i<totalnum_buckets ; i++){
            array_symbols[i] = nullptr;
        }
        cout << "\tScopeTable# " << this->unique_id << " created\n";

    }

    ~ScopeTable(){
        SymbolInfo* next;
        SymbolInfo* temp;

        for(int i = 0 ;i < totalnum_buckets ; i++){
            temp = array_symbols[i];

            while(temp!=nullptr){
                next = temp->getNext();
                delete temp;
                temp = next;

            }
        }

        delete[] this->array_symbols;
        cout << "\tScopeTable# " << this->unique_id << " removed\n";

    }

    void setParent_scopeTable(ScopeTable* setParent_scopeTable){
        this->parent_scopeTable = parent_scopeTable;
    }

    void setUnique_id(int unique_id){
        this->unique_id = unique_id;
    }

    ScopeTable* getParent_scopeTable(){
        return this->parent_scopeTable;
    }

    int getUnique_id(){
        return this->unique_id;
    }

    unsigned int SDBMHash ( string name , unsigned int num_buckets ) {

        unsigned int hash = 0;
        unsigned int len = name.length();

        for (unsigned int i = 0; i < len; i++)
        {
            hash = ((name[i]) + (hash << 6) + (hash << 16) - hash) % num_buckets;
        }

        return hash;
    }

    bool insertSymbol (SymbolInfo* symbol){
        unsigned int index = this->SDBMHash(symbol->getName(), this->totalnum_buckets);
        
        SymbolInfo* temp = this->array_symbols[index];

        int insert_position = 1;

        if(temp == nullptr){
            this->array_symbols[index] = symbol;
        }

        else{

            while(true){
                
                insert_position++;
    
                if(temp->getName() == symbol->getName()){
                    cout << "\t'" << symbol->getName() << "' already exists in the current ScopeTable\n";
                    return false;
                }
                if(temp->getNext() == nullptr){
                    temp->setNext(symbol);
                    break;
                }
    
                temp = temp->getNext();

            }
        }

        cout<<"\tInserted in ScopeTable# "<<this->unique_id<< " at position "<< index+1<<", "<<insert_position<<endl;
        return true;

    }

    SymbolInfo* lookup(string symbol, int& returnIndex, int& returnPosition){
        unsigned int index = this->SDBMHash(symbol,this->totalnum_buckets);
        SymbolInfo* temp = this->array_symbols[index];

        int insert_position = 1;

        while(temp!=nullptr){
            if(temp->getName() == symbol){
                returnIndex = index+1;
                returnPosition = insert_position; 
                return temp;
            }

            temp = temp->getNext();
            insert_position++;
        }

        return nullptr;

    }

    bool deleteSymbol (string symbol){
        unsigned int index = this->SDBMHash(symbol,this->totalnum_buckets);
        int insert_position = 1;
        SymbolInfo* target_symbol = this->array_symbols[index];
        SymbolInfo* temp = nullptr;

        while(target_symbol != nullptr){
            if(target_symbol->getName() == symbol){
                if(temp==nullptr){
                    this->array_symbols[index] = target_symbol->getNext();
                }
                else{
                    temp->setNext(target_symbol->getNext());
                }

                delete target_symbol;
                cout << "\tDeleted '" << symbol << "' from ScopeTable# " << this->unique_id << " at position " << index + 1 << ", " << insert_position << endl;
                return true;
            }
            else{
                temp = target_symbol;
                target_symbol = target_symbol->getNext();
                insert_position++;
            }
        }

        cout << "\tNot found in the current ScopeTable" << endl;
        return false;

    }

    void print(int tabCount = 1) {
        string tabs = string(tabCount, '\t');
        cout << tabs << "ScopeTable# " << unique_id << "\n";
        for (int i = 0; i < totalnum_buckets; i++) {
            cout << tabs << i + 1 << "--> ";
            SymbolInfo* temp = array_symbols[i];
            while (temp != nullptr) {
                cout << "<" << temp->getName() << "," << temp->getType() << "> ";
                temp = temp->getNext();
            }
            cout << "\n";
        }
    }

};


class SymbolTable{

private:
    ScopeTable* current_scopeTable;
    int totalnum_buckets; 
    int scope_count;

public:  
    SymbolTable(int totalnum_buckets){
        this->totalnum_buckets = totalnum_buckets;
        this->scope_count = 1;
        this->current_scopeTable = new ScopeTable(nullptr, totalnum_buckets, scope_count);
    }

    ~SymbolTable(){
        while(current_scopeTable != nullptr){
            ScopeTable* temp = current_scopeTable;
            current_scopeTable = current_scopeTable->getParent_scopeTable();
            delete temp;
        }
    }

    bool isRootScope(){
        return (current_scopeTable!= nullptr and current_scopeTable->getParent_scopeTable() == nullptr );
    }

    void enterScope(){
        scope_count++;
        ScopeTable* newTable = new ScopeTable(current_scopeTable, totalnum_buckets, scope_count);
        current_scopeTable = newTable;
    }

    void exitScope(){
        if(current_scopeTable == nullptr) return;
        ScopeTable* temp = current_scopeTable;
        current_scopeTable = current_scopeTable->getParent_scopeTable();
        delete temp;
    }

    bool insert(string name, string type){
        if(current_scopeTable == nullptr) return false;
        SymbolInfo* newSymbol = new SymbolInfo(name, type);
        bool success = current_scopeTable->insertSymbol(newSymbol);
        if(!success) delete newSymbol;
        return success;
    }

    bool remove(string name){
        if(current_scopeTable == nullptr) return false;
        return current_scopeTable->deleteSymbol(name);
    }

    SymbolInfo* lookup(string name){
        ScopeTable* tempTable = current_scopeTable;
        int index, position;

        while(tempTable != nullptr){
            SymbolInfo* target_symbol = tempTable->lookup(name, index, position);
            if(target_symbol != nullptr){
                cout << "\t'" << name << "' found in ScopeTable# " << tempTable->getUnique_id() << " at position " << index << ", " << position << "\n";
                return target_symbol;
            }
            tempTable = tempTable->getParent_scopeTable();
        }
        cout << "\t'" << name << "' not found in any of the ScopeTables\n";
        return nullptr;
    }

    void printCurrent() {
        if (current_scopeTable != nullptr) current_scopeTable->print(1);
    }

    void printAll() {
        ScopeTable* temp = current_scopeTable;
        int tabs = 1;
        while (temp != nullptr) {
            temp->print(tabs);
            temp = temp->getParent_scopeTable();
            tabs++;
        }
    }

};




int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Usage: ./a.out <input_file> <output_file>\n";
        return 1;
    }

    if (freopen(argv[1], "r", stdin) == nullptr) {
        cout << "Error: Cannot open input file " << argv[1] << "\n";
        return 1;
    }
    if (freopen(argv[2], "w", stdout) == nullptr) {
        cout << "Error: Cannot open output file " << argv[2] << "\n";
        return 1;
    }

    int N;
    if (!(cin >> N)) return 0;
    
    SymbolTable st(N);
    string line;
    int cmdNo = 1;

    getline(cin, line); 

    while (getline(cin, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back(); 
        if (line.empty()) continue;

        string tokens[100];
        int numTokens = 0;
        stringstream ss(line);
        string word;
        
        while (ss >> word) {
            tokens[numTokens++] = word;
        }
        if (numTokens == 0) continue;

        string op = tokens[0];

        if (op != "I" && op != "L" && op != "D" && op != "P" && op != "S" && op != "E" && op != "Q") {
            continue;
        }

        if (op == "P" && (numTokens >= 2 && tokens[1] != "A" && tokens[1] != "C")) {
            continue;
        }

        if (op == "E" && st.isRootScope()) {
            continue;
        }

        string cmdStr = tokens[0];
        for (int i = 1; i < numTokens; ++i) {
            cmdStr += " " + tokens[i];
        }

        cout << "Cmd " << cmdNo << ": " << cmdStr << "\n";

        bool paramMismatch = false;
        if (op == "I" && numTokens < 3) paramMismatch = true;
        if (op == "L" && numTokens != 2) paramMismatch = true;
        if (op == "D" && numTokens != 2) paramMismatch = true;
        if (op == "P" && numTokens != 2) paramMismatch = true;
        if (op == "S" && numTokens != 1) paramMismatch = true;
        if (op == "E" && numTokens != 1) paramMismatch = true;
        if (op == "Q" && numTokens != 1) paramMismatch = true;

        if (paramMismatch) {
            cout << "\tNumber of parameters mismatch for the command " << op << "\n";
            cmdNo++;
            continue;
        }
        if (op == "I") {
            string name = tokens[1];
            string type = tokens[2];
            string mergedType = type;

            if (type == "FUNCTION" && numTokens >= 4) {
                mergedType += "," + tokens[3] + "<==(";
                for (int i = 4; i < numTokens; ++i) {
                    mergedType += tokens[i];
                    if (i < numTokens - 1) mergedType += ",";
                }
                mergedType += ")";
            } 
            else if ((type == "STRUCT" || type == "UNION") && numTokens >= 5) {
                mergedType += ",{";
                for (int i = 3; i < numTokens; i += 2) {
                    mergedType += "(" + tokens[i] + ",";
                    if (i + 1 < numTokens) mergedType += tokens[i + 1];
                    mergedType += ")";
                    if (i + 2 < numTokens) mergedType += ",";
                }
                mergedType += "}";
            }

            st.insert(name, mergedType);
        } 
        else if (op == "L") {
            st.lookup(tokens[1]);
        } 
        else if (op == "D") {
            st.remove(tokens[1]);
        } 
        else if (op == "P") {
            if (tokens[1] == "A") st.printAll();
            else if (tokens[1] == "C") st.printCurrent();
        } 
        else if (op == "S") {
            st.enterScope();
        } 
        else if (op == "E") {
            st.exitScope();
        } 
        else if (op == "Q") {
            break;
        }

        cmdNo++;
    }

    return 0;
}