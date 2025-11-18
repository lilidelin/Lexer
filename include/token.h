//
// Created by 林明江 on 2025/11/6.
//

#ifndef LEXER_TOKEN_H
#define LEXER_TOKEN_H

#endif //LEXER_TOKEN_H
#include <utility>

#include "string"
///this class defines the structure of the token
class Token{
public:
    Token(std::string  value="0", int id=0):value(std::move(value)),type(id){

    }

    std::string value;
    int type;
};