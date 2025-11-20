//
// Created by lmj_0 on 2025/11/20.
//

#ifndef LEXER_SYMBOLTABLE_H
#define LEXER_SYMBOLTABLE_H

#endif //LEXER_SYMBOLTABLE_H

#include<string>
#include<vector>
#include<map>
#include<fstream>
class SymbolTable {
    public:
    SymbolTable(const std::string &varTablePath, const std::string &procTablePath):var_output(varTablePath),proc_output(procTablePath){}

    std::ofstream var_output;
    std::ofstream proc_output;
    std::map<std::string, int> ladr_list;
    struct procInfo {
        std::string proc;
        std::string ptype;
        int plev;
        int fadr;
    };
    std::vector<procInfo> proc_list;
    void addToVarTable(const std::string &varName, const std::string &varProc,int vKind, const std::string &vType,int vLevel,int adder);
    void addToProcList(const std::string &procName,const std::string &procType, int pLevel,int fAdder);
    void updateLadrList(const std::string &pName, int adder);
    void addToProcTable();
};

inline void SymbolTable::addToVarTable(const std::string &varName, const std::string &varProc, int vKind, const std::string &vType,
    const int vLevel, const int adder) {
    var_output << varName << " " << varProc << " " << vKind << " " << vType << " " << vLevel <<
        " " << adder << std::endl;
}

inline void SymbolTable::addToProcList(const std::string &procName, const std::string &procType, int pLevel,
    int fAdder) {
    proc_list.push_back({procName, procType, pLevel, fAdder});
}

inline void SymbolTable::updateLadrList(const std::string &pName, int adder) {
    ladr_list[pName] = adder;
}

inline void SymbolTable::addToProcTable() {
    for (auto i : proc_list) {
        proc_output<<i.proc<<" "<<i.ptype<<" "<<i.plev<<" "<<i.fadr<<" "<<ladr_list[i.proc]<<std::endl;
    }
}
