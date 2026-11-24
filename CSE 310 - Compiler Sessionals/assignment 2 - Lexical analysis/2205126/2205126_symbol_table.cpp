#include <bits/stdc++.h>
using namespace std;

class SymbolInfo {
 private:
    string name;
    string type;
    SymbolInfo* next;

 public:
    SymbolInfo(string name, string type) {
        this->name = name;
        this->type = type;
        this->next = nullptr;
    }

    ~SymbolInfo() {
        this->next = nullptr;
    }

    void setName(string name) {
        this->name = name;
    }

    void setType(string type) {
        this->type = type;
    }
    
    void setNext(SymbolInfo* next) {
        this->next = next;
    }

    string getName() {
        return this->name;
    }

    string getType() {
        return this->type;
    }
    
    SymbolInfo* getNext() {
        return this->next;
    }
};

class ScopeTable {
 private:
    SymbolInfo** array_symbols;
    ScopeTable* parent_scopeTable;
    int totalnum_buckets;
    string unique_id;
    int child_count;

 public:
    ScopeTable(ScopeTable* parent_scopeTable, int totalnum_buckets, string unique_id) {
        this->parent_scopeTable = parent_scopeTable;
        this->totalnum_buckets = totalnum_buckets;
        this->unique_id = unique_id;
        this->child_count = 0;
        this->array_symbols = new SymbolInfo*[totalnum_buckets];

        for(int i = 0 ; i < totalnum_buckets ; i++) {
            array_symbols[i] = nullptr;
        }
    }

    ~ScopeTable() {
        SymbolInfo* next;
        SymbolInfo* temp;

        for(int i = 0 ; i < totalnum_buckets ; i++) {
            temp = array_symbols[i];
            while(temp != nullptr) {
                next = temp->getNext();
                delete temp;
                temp = next;
            }
        }
        delete[] this->array_symbols;
    }

    void setParent_scopeTable(ScopeTable* parent_scopeTable) {
        this->parent_scopeTable = parent_scopeTable;
    }

    void setUnique_id(string unique_id) {
        this->unique_id = unique_id;
    }

    ScopeTable* getParent_scopeTable() {
        return this->parent_scopeTable;
    }

    string getUnique_id() {
        return this->unique_id;
    }

    int getChild_count() {
        return this->child_count;
    }

    void incrementChild_count() {
        this->child_count++;
    }

    unsigned int SDBMHash(string name, unsigned int num_buckets) {
        unsigned int hash = 0;
        const char *p = name.c_str(); 
        auto *str = (unsigned char *) p;
        int c{};
        
        while ((c = *str++)) {
            hash = c + (hash << 6) + (hash << 16) - hash;
        }
        return hash % num_buckets;
    }

    bool insertSymbol(SymbolInfo* symbol) {
        unsigned int index = this->SDBMHash(symbol->getName(), this->totalnum_buckets);
        SymbolInfo* temp = this->array_symbols[index];
        
        int insert_position = 0; 

        if(temp == nullptr) {
            this->array_symbols[index] = symbol;
        } else {
            while(true) {
                if(temp->getName() == symbol->getName()) {
                    cout << "< " << temp->getName() << " : " << temp->getType() 
                         << " > already exists in ScopeTable# " << this->unique_id 
                         << " at position " << index << ", " << insert_position << "\n\n";
                    return false;
                }
                if(temp->getNext() == nullptr) {
                    temp->setNext(symbol);
                    break;
                }
                temp = temp->getNext();
                insert_position++;
            }
        }
        return true;
    }

    SymbolInfo* lookup(string symbol, int& returnIndex, int& returnPosition) {
        unsigned int index = this->SDBMHash(symbol, this->totalnum_buckets);
        SymbolInfo* temp = this->array_symbols[index];
        
      
        int insert_position = 0; 

        while(temp != nullptr) {
            if(temp->getName() == symbol) {
                returnIndex = index; 
                returnPosition = insert_position; 
                return temp;
            }
            temp = temp->getNext();
            insert_position++;
        }
        return nullptr;
    }

    bool deleteSymbol(string symbol) {
        unsigned int index = this->SDBMHash(symbol, this->totalnum_buckets);
        SymbolInfo* target_symbol = this->array_symbols[index];
        SymbolInfo* temp = nullptr;

        while(target_symbol != nullptr) {
            if(target_symbol->getName() == symbol) {
                if(temp == nullptr) {
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

    void print() {
        cout << "ScopeTable # " << unique_id << "\n";
        for (int i = 0; i < totalnum_buckets; i++) {
            SymbolInfo* temp = array_symbols[i];
            if (temp != nullptr) {
                cout << i << " --> ";
                while (temp != nullptr) {
                    cout << "< " << temp->getName() << " : " << temp->getType() << " >";
                    temp = temp->getNext();
                }
                cout << "\n";
            }
        }
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
        while(current_scopeTable != nullptr) {
            ScopeTable* temp = current_scopeTable;
            current_scopeTable = current_scopeTable->getParent_scopeTable();
            delete temp;
        }
    }

    bool isRootScope() {
        return (current_scopeTable != nullptr && current_scopeTable->getParent_scopeTable() == nullptr);
    }

    void enterScope() {
        if (current_scopeTable != nullptr) {
            current_scopeTable->incrementChild_count();
            string new_id = current_scopeTable->getUnique_id() + "." + to_string(current_scopeTable->getChild_count());
            ScopeTable* newTable = new ScopeTable(current_scopeTable, totalnum_buckets, new_id);
            current_scopeTable = newTable;
        }
    }

    void exitScope() {
        if(current_scopeTable == nullptr || isRootScope()) return;
        ScopeTable* temp = current_scopeTable;
        current_scopeTable = current_scopeTable->getParent_scopeTable();
        delete temp;
    }

    bool insert(string name, string type) {
        if(current_scopeTable == nullptr) return false;
        SymbolInfo* newSymbol = new SymbolInfo(name, type);
        bool success = current_scopeTable->insertSymbol(newSymbol);
        if(!success) delete newSymbol;
        return success;
    }

    bool remove(string name) {
        if(current_scopeTable == nullptr) return false;
        return current_scopeTable->deleteSymbol(name);
    }

    SymbolInfo* lookup(string name) {
        ScopeTable* tempTable = current_scopeTable;
        int index, position;

        while(tempTable != nullptr) {
            SymbolInfo* target_symbol = tempTable->lookup(name, index, position);
            if(target_symbol != nullptr) {
                return target_symbol;
            }
            tempTable = tempTable->getParent_scopeTable();
        }
        return nullptr;
    }

    void printCurrent() {
        if (current_scopeTable != nullptr) current_scopeTable->print();
    }

    void printAll() {
        ScopeTable* temp = current_scopeTable;
        while (temp != nullptr) {
            temp->print();
            temp = temp->getParent_scopeTable();
        }
        cout << "\n";
    }
};