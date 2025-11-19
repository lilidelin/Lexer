//
// Created by 林明江 on 2025/11/6.
//

#ifndef LEXER_LEXER_H
#define LEXER_LEXER_H

#endif //LEXER_LEXER_H
#include <utility>
#include "iostream"
#include "../../include/token.h"
#include "fstream"
#include "sstream"
#include<unordered_map>
///the class provides a function to extract token one by one
class Lexer{
public:
    Lexer(std::string& path);
    Token get_next_token();
    void start(char& current_char);
    void state1(char& current_char, char& front_char);
    void state10(char& current_char, char& front_char);
    void state2(char& current_char, char& front_char);
    void state3(char& current_char, char& front_char);
    void state4(char& current_char, char& front_char);
    void state5(char& current_char, char& front_char);
    void state6(char& current_char, char& front_char);
    void state7(char& current_char, char& front_char);
    void state8(char& current_char, char& front_char);
    void state9(char& current_char, char& front_char);
    void state13(char& current_char, char& front_char);
    void state14(char& current_char, char& front_char);
    void state16(char& current_char, char& front_char);
    void state20(char& current_char, char& front_char);
    void state11(char& current_char);
    void state12(char& current_char);
    void state15(char& current_char);
    void state17(char& current_char);
    void state18(char& current_char);
    void state19(char& current_char);
    void state21(char& current_char);
    void state22(char& current_char);
    void state23(char& current_char);
    void state24();
    void state26();
    std::ifstream text;
    std::ofstream error_output;
    std::ofstream token_output;
    char current_char;
    char next_char;
    char front_char;
    int current_state;
    Token current_token;
    std::string current_word;//当前读取的单词
    bool flag;//判断是否完整读取一个词
    int current_line;
    std::unordered_map<std::string,int> keyword_map = {
        {"begin",1},{"end",2},{"integer",3},
        {"if",4},{"then",5},{"else",6},
        {"function",7},{"read",8},{"write",9},
        {"=",12},{"<>",13},{"<=",14},
        {"<",15},{">=",16},{">",17},
        {"-",18},{"*",19},{":=",20},
        {"(",21},{")",22},{";",23}
    };
    void IsLegalIdentifier();
    bool SingleCharactor(Token &value);
    Token get_next_token_1_1();
    bool IsAllDigit(std::string& word);
};