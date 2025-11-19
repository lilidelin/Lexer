//
// Created by 林明江 on 2025/11/13.
//

#ifndef LEXER_PARSER_H
#define LEXER_PARSER_H
#include "../lexer/lexer.h"
#include "map"
#include "vector"
class Parser {
public:
    Parser(Lexer& lexer):lexer(lexer){
        current_rownum = 1;
        current_token = lexer.get_next_token();
        current_lev=0;
        current_proc="main";
        var_count=0;
        vkind=0;
        vtype="integer";
        ladr_list["main"]=0;
        proc_list.push_back({"main",0,0});
        var_output = std::ofstream("result/parser.var");
        proc_output = std::ofstream("result/parser.pro");
        parser_error = std::ofstream("result/parser.err");
    }

    std::map<std::string, int> ladr_list;
    struct procInfo {
        std::string proc;
        int plev;
        int fadr;
    };
    std::vector<procInfo> proc_list;
    Lexer& lexer;
    int current_rownum;
    Token current_token;
    std::string current_proc;
    int current_lev;
    int var_count;
    std::ofstream var_output;
    std::ofstream proc_output;
    std::ofstream parser_error;
    int vkind;
    std::string vtype;

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
    void printProcToFile();
};


#endif //LEXER_PARSER_H
