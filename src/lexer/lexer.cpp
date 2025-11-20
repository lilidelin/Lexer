//
// Created by 林明江 on 2025/11/6.
//
#include "lexer.h"

void Lexer::IsLegalIdentifier() {
    if (IsAllDigit(current_word)&&isalpha(current_char)) {
        text.unget();
        error_output<<"LINE: "<<current_line<<" identifier can`t start with number "<<current_word<<std::endl;
        current_word.clear();
    }
    else {
        current_word+=current_char;
    }
}
bool Lexer::SingleCharactor(Token &value) {
    if (current_word.empty()) {
        current_word+=current_char;
        if (current_char=='\n') {
            current_line++;
            value = {"ENOL",24};
            return true;
        }
        else if (keyword_map.count(current_word)) {
            value = {current_word,keyword_map[current_word]};
            return true;
        }
        else {
            current_word.clear();
        }
    }
    else {
        text.unget();
        if (IsAllDigit(current_word)) {
            value = {current_word,11};
            return true;
        }
        else {
            if (keyword_map.count(current_word)) {
                value = {current_word,keyword_map[current_word]};
                return true;
            }
            else {
                value = {current_word,10};
                return true;
            }
        }
    }
    return false;
}
Token Lexer::get_next_token_1_1() {
    current_word.clear();
    while ((current_char=text.get())) {
        if (isalpha(current_char)||isdigit(current_char)) {
            if (current_word.empty()) {
                current_word+=current_char;
            }
            else {
                IsLegalIdentifier();
            }
        }
        else if (current_char==' '||current_char=='\n'||current_char=='\t'||current_char=='='||
                 current_char=='-'||current_char=='*'||current_char=='('||current_char==')'||current_char==';') {
            Token value;
            if (SingleCharactor(value)) return value;
        }
        else if (current_char=='<'||current_char=='>'||current_char==':') {
            if (current_word.empty()) {
                current_word+=current_char;
                next_char=text.get();
                if (next_char=='>'||next_char=='<'||next_char=='=') {
                    current_word+=next_char;
                }
                else {
                    text.unget();
                }
                if (keyword_map.count(current_word)) {
                    return {current_word,keyword_map[current_word]};
                }
                else {
                    error_output<<"LINE: "<<current_line<<" unrecognized identifier "<<current_word<<std::endl;
                    current_word.clear();
                }
            }
            else {
                text.unget();
                if (keyword_map.count(current_word)) {
                    return {current_word,keyword_map[current_word]};
                }
                else {
                    return {current_word,10};
                }
            }
        }
        else if (current_char==EOF) {
            return {"EOF",25};
        }
        else {
            error_output<<"LINE: "<<current_line<<" unrecognized identifier "<<current_word<<std::endl;
            current_word.clear();
        }
    }
}
bool Lexer::IsAllDigit(std::string &word) {
    for (char c : word) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}
void Lexer::PrintAllToken() {
    Token current_token;
    do {
        current_token = get_next_token_1_1();
        token_output<<current_token.value<<" "<<current_token.type<<std::endl;
    }while (current_token.type != 25);
}





