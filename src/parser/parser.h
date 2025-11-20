//
// Created by 林明江 on 2025/11/13.
//

#ifndef LEXER_PARSER_H
#define LEXER_PARSER_H
#include "../lexer/lexer.h"
#include"../symbol/SymbolTable.h"
#include<stack>
class Parser {
public:
    Parser(Lexer& lexer,const std::string& var_path,const std::string &proc_path,const std::string& error_path)
    :lexer(lexer),symbolTable(var_path,proc_path),parser_error(error_path){
        proc_stack.emplace("main");
        current_token = lexer.get_next_token_1_1();
        symbolTable.addToProcList("main","integer",0,0);
        symbolTable.ladr_list["main"]=0;
    }
    SymbolTable symbolTable;
    Lexer& lexer;
    std::stack<std::string> proc_stack;
    int linecount=1;
    int current_lev=0;
    int var_count=0;
    int vKind=0;
    Token current_token;
    std::string current_proc="main";
    std::ofstream parser_error;
    std::unordered_map<int, std::string> keyword_map_rev = {
        {1, "begin"}, {2, "end"}, {3, "integer"},
        {4, "if"}, {5, "then"}, {6, "else"},
        {7, "function"}, {8, "read"}, {9, "write"},
        {12, "="}, {13, "<>"}, {14, "<="},
        {15, "<"}, {16, ">="}, {17, ">"},
        {18, "-"}, {19, "*"}, {20, ":="},
        {21, "("}, {22, ")"}, {23, ";"}
    };

    void Match(int type);

    void Program();//主程序
    void SubProgram();//分程序
    void parserDeclarationStmtList();

    void parserExecutionStmtList();

    void parserDeclarationStmt();

    void reverseDeclarationStmtList();

    void parserVariableDeclaration();

    void parserFunctionDeclaration();

    void resolveIdentifier();

    void parserVariable();

    void parserFunctionBody();

    void parserExecutionStmt();

    void reverseExecutionStmtList();

    void parserReadStmt();

    void parserWriteStmt();

    void parserAssignmentStmt();

    void parserConditionalStmt();

    void parserArithmeticExpr();

    void parserTerm();

    void reverseArithmeticExpr();

    void parserFunctionCall();

    void parserFactor();

    void reverseTerm();

    void parseUnsignedInt();

    void parserConditionalExpr();

    void parserRationalOpt();
};


#endif //LEXER_PARSER_H
