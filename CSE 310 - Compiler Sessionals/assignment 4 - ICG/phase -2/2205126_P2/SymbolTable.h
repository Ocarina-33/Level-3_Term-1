#pragma once
#include <bits/stdc++.h>
using namespace std;

class SymbolInfo {
private:
    string name;
    string type;
    SymbolInfo* next;

    
    string dataType;      
    bool isFunction;      
    bool isDefined;       
    bool isArray;         
    int arraySize;        
    vector<string> paramTypes; 
    string returnType;    
    int stackOffset;

public:
    SymbolInfo(string name, string type) {
        this->name = name;
        this->type = type;
        this->next = nullptr;
        
        this->dataType = "";
        this->isFunction = false;
        this->isDefined = false;
        this->isArray = false;
        this->arraySize = 0;
        this->returnType = "";
        this->stackOffset = 0;
    }

    ~SymbolInfo() {
        this->next = nullptr;
    }

    void setName(string name) { this->name = name; }
    void setType(string type) { this->type = type; }
    void setNext(SymbolInfo* next) { this->next = next; }
    
    void setDataType(string dataType) { this->dataType = dataType; }
    void setIsFunction(bool isFunction) { this->isFunction = isFunction; }
    void setIsDefined(bool isDefined) { this->isDefined = isDefined; }
    void setIsArray(bool isArray) { this->isArray = isArray; }
    void setArraySize(int arraySize) { this->arraySize = arraySize; }
    void addParamType(string paramType) { this->paramTypes.push_back(paramType); }
    void setParamTypes(const vector<string>& params) { this->paramTypes = params; }
    void setReturnType(string returnType) { this->returnType = returnType; }
    void setStackOffset(int offset) { this->stackOffset = offset; }

    string getName() { return this->name; }
    string getType() { return this->type; }
    SymbolInfo* getNext() { return this->next; }

    string getDataType() { return this->dataType; }
    bool getIsFunction() { return this->isFunction; }
    bool getIsDefined() { return this->isDefined; }
    bool getIsArray() { return this->isArray; }
    int getArraySize() { return this->arraySize; }
    vector<string> getParamTypes() { return this->paramTypes; }
    string getReturnType() { return this->returnType; }
    int getStackOffset() { return this->stackOffset; }
};

class ScopeTable {
private:
    SymbolInfo** array_symbols;
    ScopeTable* parent_scopeTable;
    int totalnum_buckets;
    string scope_id;
    int child_count;

public:
    ScopeTable(ScopeTable* parent_scopeTable, int totalnum_buckets, string scope_id) {
        this->parent_scopeTable = parent_scopeTable;
        this->totalnum_buckets = totalnum_buckets;
        this->scope_id = scope_id;
        this->child_count = 0;
        this->array_symbols = new SymbolInfo*[totalnum_buckets];

        for (int i = 0; i < totalnum_buckets; i++) {
            array_symbols[i] = nullptr;
        }
    }

    ~ScopeTable() {
        SymbolInfo* next;
        SymbolInfo* temp;
        for (int i = 0; i < totalnum_buckets; i++) {
            temp = array_symbols[i];
            while (temp != nullptr) {
                next = temp->getNext();
                delete temp;
                temp = next;
            }
        }
        delete[] this->array_symbols;
    }

    void setParent_scopeTable(ScopeTable* parent_scopeTable) { this->parent_scopeTable = parent_scopeTable; }
    ScopeTable* getParent_scopeTable() { return this->parent_scopeTable; }
    string getScope_id() { return this->scope_id; }
    void incrementChildCount() { this->child_count++; }
    int getChildCount() { return this->child_count; }

    int hashOf(const std::string& name) {
        unsigned long sum = 0;
        for (char c : name) sum += (unsigned char)c;
        return (int)(sum % totalnum_buckets);
    }

    bool insertSymbol(SymbolInfo* symbol) {
        unsigned int index = this->hashOf(symbol->getName());
        SymbolInfo* temp = this->array_symbols[index];
        if (temp == nullptr) {
            this->array_symbols[index] = symbol;
        } else {
            while (true) {
                if (temp->getName() == symbol->getName()) {
                    return false;  
                }
                if (temp->getNext() == nullptr) {
                    temp->setNext(symbol);
                    break;
                }
                temp = temp->getNext();
            }
        }
        return true;
    }

    SymbolInfo* lookup(string symbol) {
        unsigned int index = this->hashOf(symbol);
        SymbolInfo* temp = this->array_symbols[index];
        while (temp != nullptr) {
            if (temp->getName() == symbol) {
                return temp;
            }
            temp = temp->getNext();
        }
        return nullptr;
    }

    bool deleteSymbol(string symbol) {
        unsigned int index = this->hashOf(symbol);
        SymbolInfo* target_symbol = this->array_symbols[index];
        SymbolInfo* temp = nullptr;

        while (target_symbol != nullptr) {
            if (target_symbol->getName() == symbol) {
                if (temp == nullptr) {
                    this->array_symbols[index] = target_symbol->getNext();
                } else {
                    temp->setNext(target_symbol->getNext());
                }
                delete target_symbol;
                return true;
            } else {
                temp = target_symbol;
                target_symbol = target_symbol->getNext();
            }
        }
        return false;
    }

    void print(ofstream& out) {
        out << "ScopeTable # " << scope_id << "\n";
        for (int i = 0; i < totalnum_buckets; i++) {
            SymbolInfo* temp = array_symbols[i];
            if (temp != nullptr) {
                out << " " << i << " --> ";
                while (temp != nullptr) {
                    out << "< " << temp->getName() << " , " << temp->getType() << " > ";
                    temp = temp->getNext();
                }
                out << "\n";
            }
        }
        out << "\n";
    }
};

class SymbolTable {
private:
    ScopeTable* current_scopeTable;
    int totalnum_buckets;

public:
    SymbolTable(int totalnum_buckets) {
        this->totalnum_buckets = totalnum_buckets;
        this->current_scopeTable = new ScopeTable(nullptr, totalnum_buckets, "1");
    }

    ~SymbolTable() {
        while (current_scopeTable != nullptr) {
            ScopeTable* temp = current_scopeTable;
            current_scopeTable = current_scopeTable->getParent_scopeTable();
            delete temp;
        }
    }

    bool isRootScope() {
        return (current_scopeTable != nullptr && current_scopeTable->getParent_scopeTable() == nullptr);
    }

    void enterScope() {
        if (current_scopeTable == nullptr) return;
        current_scopeTable->incrementChildCount();
        string newId = current_scopeTable->getScope_id() + "." + to_string(current_scopeTable->getChildCount());
        ScopeTable* newTable = new ScopeTable(current_scopeTable, totalnum_buckets, newId);
        current_scopeTable = newTable;
    }

    void exitScope() {
        if (current_scopeTable == nullptr) return;
        ScopeTable* temp = current_scopeTable;
        current_scopeTable = current_scopeTable->getParent_scopeTable();
        delete temp;
    }

    void exitScope(ofstream& out) {
        if (current_scopeTable == nullptr) return;
        printAll(out);
        exitScope();
    }

    bool insert(SymbolInfo* symbol) {
        if (current_scopeTable == nullptr) return false;
        return current_scopeTable->insertSymbol(symbol);
    }

    bool remove(string name) {
        if (current_scopeTable == nullptr) return false;
        return current_scopeTable->deleteSymbol(name);
    }

    
    SymbolInfo* lookup(string name) {
        ScopeTable* tempTable = current_scopeTable;
        while (tempTable != nullptr) {
            SymbolInfo* target_symbol = tempTable->lookup(name);
            if (target_symbol != nullptr) {
                return target_symbol;
            }
            tempTable = tempTable->getParent_scopeTable();
        }
        return nullptr;
    }

    SymbolInfo* lookupCurrentScope(string name) {
        if (current_scopeTable == nullptr) return nullptr;
        return current_scopeTable->lookup(name);
    }

    void printCurrent(ofstream& out) {
        if (current_scopeTable != nullptr) current_scopeTable->print(out);
    }

    void printAll(ofstream& out) {
        ScopeTable* temp = current_scopeTable;
        while (temp != nullptr) {
            temp->print(out);
            temp = temp->getParent_scopeTable();
        }
    }
};
