//
// Created by 林明江 on 2025/11/13.
//

#include "parser.h"

void Parser::Match(int type) {
    if(current_token.type == type){
        current_token = lexer.get_next_token();
        while (current_token.type == 24){
            current_rownum+=1;
            current_token = lexer.get_next_token();
        }
    }
    else{
        parser_error<<"LINE:"<<current_rownum<<" "<<"Expected`"<<type<<"but Found`"<<current_token.type<<std::endl;
    }
}

void Parser::Program() {
    SubProgram();
    printProcToFile();
}

void Parser::SubProgram() {
    Match(1);
    parserDeclarationStmtList();
    //Match(23);
    parserExecutionStmtList();
    Match(2);
}

void Parser::parserDeclarationStmtList() {
    parserDeclarationStmt();//说明语句
    reverseDeclarationStmtList();//新建说明语句表
}

void Parser::parserExecutionStmtList() {
    parserExecutionStmt();
    reverseExecutionStmtList();
}

void Parser::parserDeclarationStmt() {
    Match(3);
    if(current_token.type==10) {
        parserVariableDeclaration();
    }
    else if(current_token.type==7) {
        parserFunctionDeclaration();
    }
}

void Parser::reverseDeclarationStmtList() {
    if(current_token.type==23){
        Match(23);
        if(current_token.type==3) {
            parserDeclarationStmt();
            reverseDeclarationStmtList();
        }
    }
}

void Parser::parserVariableDeclaration() {
    ladr_list[current_proc]=var_count;
    var_output << current_token.value << " " << current_proc << " " << vkind << " " << vtype << " " << current_lev <<
        " " << var_count++ << std::endl;
    parserVariable();
}

void Parser::parserFunctionDeclaration() {
    Match(7);
    current_proc=current_token.value;
    current_lev+=1;
    vkind=1;
    resolveIdentifier();
    Match(21);
    parserVariable();
    proc_list.push_back({current_proc,current_lev,var_count});
    Match(22);
    Match(23);
    parserFunctionBody();
    current_proc="main";
    current_lev-=1;
}

void Parser::resolveIdentifier() {
    Match(10);
}

void Parser::parserVariable() {
    resolveIdentifier();
}

void Parser::parserFunctionBody() {
    Match(1);
    parserDeclarationStmtList();
    //Match(23);
    parserExecutionStmtList();
    Match(2);
}

void Parser::parserExecutionStmt() {
    if(current_token.type==8){
        parserReadStmt();
    }
    else if(current_token.type==9){
        parserWriteStmt();
    }
    else if(current_token.type==10){
        parserAssignmentStmt();
    }
    else if(current_token.type==4){
        parserConditionalStmt();
    }
}

void Parser::reverseExecutionStmtList() {
    if(current_token.type==23){
        Match(23);
        parserExecutionStmt();
        reverseExecutionStmtList();
    }
}

void Parser::parserReadStmt() {
    Match(8);
    Match(21);
    parserVariable();
    Match(22);
}

void Parser::parserWriteStmt() {
    Match(9);
    Match(21);
    parserVariable();
    Match(22);
}

void Parser::parserAssignmentStmt() {
    Match(10);
    Match(20);
    parserArithmeticExpr();
}

void Parser::parserConditionalStmt() {
    Match(4);
    parserConditionalExpr();
    Match(5);
    parserExecutionStmt();
    Match(6);
    parserExecutionStmt();
}

void Parser::parserArithmeticExpr() {
    parserTerm();
    reverseArithmeticExpr();
}

void Parser::parserTerm() {
    parserFactor();
    reverseTerm();
}

void Parser::reverseArithmeticExpr() {
    if(current_token.type==18){
        Match(18);
        parserTerm();
        reverseArithmeticExpr();
    }
}

void Parser::parserFunctionCall() {
    Match(21);
    parserArithmeticExpr();
    Match(22);
}

void Parser::parserFactor() {
    if(current_token.type==10){
        Match(10);
        if (current_token.type==21) {
            parserFunctionCall();
        }
    }
    else if(current_token.type==11){
        parseUnsignedInt();
    }
}

void Parser::reverseTerm() {
    if(current_token.type==19){
        Match(19);
        parserTerm();
        reverseTerm();
    }
}

void Parser::parseUnsignedInt() {
    Match(11);
}

void Parser::parserConditionalExpr() {
    parserArithmeticExpr();
    parserRationalOpt();
    parserArithmeticExpr();
}

void Parser::parserRationalOpt() {
    if(current_token.type==15){
        Match(15);
    }
    else if(current_token.type==14){
        Match(14);
    }
    else if(current_token.type==17){
        Match(17);
    }
    else if(current_token.type==16){
        Match(16);
    }
    else if(current_token.type==12){
        Match(12);
    }
    else if(current_token.type==13){
        Match(13);
    }
}

void Parser::printProcToFile() {
    for (auto i : proc_list) {
        proc_output<<i.proc<<" "<<"integer"<<" "<<i.plev<<" "<<i.fadr<<" "<<ladr_list[i.proc]<<std::endl;
    }
}




