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
#include<unordered_map>
///the class provides a function to extract token one by one
class Lexer{
public:
    Lexer(const std::string& text_path, const std::string &toke_path, const std::string &error_path):text(text_path),token_output(toke_path)
    ,error_output(error_path){
        if(!text.is_open()){
            std::cerr << "can`t open file" << std::endl;
            return;
        }
    };
    std::ifstream text;
    std::ofstream error_output;
    std::ofstream token_output;
    char current_char=1;
    char next_char;
    std::string current_word;//当前读取的单词
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
    void PrintAllToken();
};