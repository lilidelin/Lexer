//
// Created by 林明江 on 2025/11/6.
//
#include "lexer.h"

Lexer::Lexer(std::string &path) {
    error_output = std::ofstream("result/lexer.err");
    token_output = std::ofstream("result/lexer.dyd");
    text = std::ifstream(path);
    current_state=0;
    current_line=1;
    flag= false;
    if(!text.is_open()){
        std::cerr << "无法打开文件" << std::endl;
        return;
    }
}
Token Lexer::get_next_token() {
    current_word="";
    flag= false;
    current_state=0;
    while(!flag&&(current_char=text.get())){
        if(current_char==-1){
            return {"EOF", 25};
        }
        switch (current_state) {
            case 0:
                start(current_char);
                break;
            case 1:
                state1(current_char,front_char);
                break;
            case 2:
                state2(current_char,front_char);
                break;
            case 3:
                state3(current_char,front_char);
                break;
            case 4:
                state4(current_char,front_char);
                break;
            case 5:
                state5(current_char,front_char);
                break;
            case 6:
                state6(current_char,front_char);
                break;
            case 7:
                state7(current_char,front_char);
                break;
            case 8:
                state8(current_char,front_char);
                break;
            case 9:
                state9(current_char,front_char);
                break;
            case 10:
                state10(current_char,front_char);
                break;
            case 11:
                state11(current_char);
                break;
            case 12:
                state12(current_char);
                break;
            case 13:
                state13(current_char,front_char);
                break;
            case 14:
                state14(current_char,front_char);
                break;
            case 15:
                state15(current_char);
                break;
            case 16:
                state16(current_char,front_char);
                break;
            case 17:
                state17(current_char);
                break;
            case 18:
                state18(current_char);
                break;
            case 19:
                state19(current_char);
                break;
            case 20:
                state20(current_char,front_char);
                break;
            case 21:
                state21(current_char);
                break;
            case 22:
                state22(current_char);
                break;
            case 23:
                state23(current_char);
                break;
            case 24:
                state24();
                break;
            default:
                state26();
                break;
        }
        front_char = current_char;
        if(current_char!=' ') {
            current_word += current_char;
        }
    }
    if(current_char!=' ') {
        text.unget();
    }
    //将token写入文件
    if (flag&&current_state!=26) {
        token_output<<current_token.value<<" "<<current_token.type<<std::endl;
    }
    if (current_token.type == 0) {
        return {"EOF", 25};
    } else {
        return current_token;
    }
}
//开始状态
void Lexer::start(char &current_char) {
    if(current_char=='b')current_state=1;
    else if(current_char=='e')current_state=2;
    else if(current_char=='i')current_state=3;
    else if(current_char=='t')current_state=5;
    else if(current_char=='f')current_state=7;
    else if(current_char=='r')current_state=8;
    else if(current_char=='w')current_state=9;
    else if(current_char-'0'>=0&&current_char-'0'<=9)current_state=11;
    else if(current_char=='=')current_state=12;
    else if(current_char=='<')current_state=15;
    else if(current_char=='>')current_state=17;
    else if(current_char=='-')current_state=18;
    else if(current_char=='*')current_state=19;
    else if(current_char==':')current_state=20;
    else if(current_char=='(')current_state=21;
    else if(current_char==')')current_state=22;
    else if(current_char==';')current_state=23;
    else if(current_char=='\n')current_state=24;
    else if(current_char==' '){
        current_state=0;
        current_word="";
    }
    else if (isalpha(current_char)) {
        current_state=10;
    }
    else {
        current_state=26;
    }
}
//begin状态
void Lexer::state1(char &current_char, char &front_char) {
    if(!std::isdigit(current_char)&&!std::isalpha(current_char)){
        if(current_word=="begin"){
            current_token={current_word,1};
        }
        else{
            current_token={current_word,10};
        }
        flag= true;
    }
    else{
        if(front_char=='b'){
            if(current_char=='e'){
                current_state=1;
                return;
            }
            else{
                current_state=10;
            }
        }
        else if(front_char=='e'){
            if(current_char=='g'){
                current_state=1;
                return;
            }
            else{
                current_state=10;
            }
        }
        else if(front_char=='g'){
            if(current_char=='i'){
                current_state=1;
                return;
            }
            else{
                current_state=10;
            }
        }
        else if(front_char=='i'){
            if(current_char=='n'){
                current_state=1;
                return;
            }
            else{
                current_state=10;
            }
        }
        else{
            current_state=10;
        }
    }
}
//标识符状态
void Lexer::state10(char &current_char, char &front_char) {
    if(!std::isdigit(current_char)&&!std::isalpha(current_char)){
        current_token={current_word,10};
        flag= true;
    }
    else{
        current_state=10;
    }
}
//end状态
void Lexer::state2(char &current_char, char &front_char) {
    if(!std::isdigit(current_char)&&!std::isalpha(current_char)){
        if(!std::isdigit(current_char)&&!std::isalpha(current_char)){
            if(current_word=="end"){
                current_token={current_word,2};
            }
            else{
                current_token={current_word,10};
            }
            flag= true;
        }
    }
    else{
        if(front_char=='e'){
            if(current_char=='n'){
                current_state=2;
            }
            else if(current_char=='l'){
                current_state=6;
            }
            else{
                current_state=10;
            }
        }
        else if(front_char=='n'){
            if(current_char=='d'){
                current_state=2;
            }
            else{
                current_state=10;
            }
        }
        else{
            current_state=10;
        }
    }
}
//integer状态
void Lexer::state3(char &current_char, char &front_char) {
    // 如果当前字符为其他字符说明该词已结束，只需判断是关键字还是标识符
    if(!std::isdigit(current_char)&&!std::isalpha(current_char)){
        if(current_word=="integer"){
            current_token={current_word,3};
        }
        else{
            current_token={current_word,10};
        }
        flag= true;
    }
    else{
        if(front_char=='i'){
            if(current_char=='n'){
                current_state=3;
            }
            else if(current_char=='f'){
                current_state=4;
            }
            else{
                current_state=10;
            }
        }
        else if(front_char=='n'){
            if(current_char=='t'){
                current_state=3;
            }
            else{
                current_state=10;
            }
        }
        else if(front_char=='t'){
            if(current_char=='e'){
                current_state=3;
            }
            else{
                current_state=10;
            }
        }
        else if(front_char=='e'){
            if(current_char=='g'&&current_word=="inte"||current_char=='r'&&current_word=="intege"){
                current_state=3;
            }
            else{
                current_state=10;
            }
        }
        else if(front_char=='g'){
            if(current_char=='e'){
                current_state=3;
            }
            else{
                current_state=10;
            }
        }
        else{
            current_state=10;
        }
    }
}
//if状态
void Lexer::state4(char &current_char, char &front_char) {
    if(!std::isdigit(current_char)&&!std::isalpha(current_char)){
        if(current_word=="if"){
            current_token={current_word,4};
        }
        else{
            current_token={current_word,10};
        }
        flag= true;
    }
    else{
        current_state=10;
    }
}
//then状态
void Lexer::state5(char &current_char, char &front_char) {
    if(!std::isdigit(current_char)&&!std::isalpha(current_char)){
        if(current_word=="then"){
            current_token={current_word,5};
        }
        else{
            current_token={current_word,10};
        }
        flag= true;
    }
    else{
        if((front_char=='t'&&current_char=='h')||(front_char=='h'&&current_char=='e')||(front_char=='e'&&current_char=='n')){
            current_state=5;
        }
        else{
            current_state=10;
        }
    }
}
//else状态
void Lexer::state6(char &current_char, char &front_char) {
    if(!std::isdigit(current_char)&&!std::isalpha(current_char)){
        if(current_word=="else"){
            current_token={current_word,6};
        }
        else{
            current_token={current_word,10};
        }
        flag= true;
    }
    else{
        if((front_char=='l'&&current_char=='s')||(front_char=='s'&&current_char=='e')){
            current_state=6;
        }
        else{
            current_state=10;
        }
    }
}
//function状态
void Lexer::state7(char &current_char, char &front_char) {
    if(!std::isdigit(current_char)&&!std::isalpha(current_char)){
        if(current_word=="function"){
            current_token={current_word,7};
        }
        else{
            current_token={current_word,10};
        }
        flag= true;
    }
    else{
        if((front_char=='f'&&current_char=='u')||(front_char=='u'&&current_char=='n')||(front_char=='n'&&current_char=='c')||(front_char=='c'&&current_char=='t')||(front_char=='t'&&current_char=='i')
        ||(front_char=='i'&&current_char=='o')||(front_char=='o'&&current_char=='n')){
            current_state=7;
        }
        else{
            current_state=10;
        }
    }
}
//read状态
void Lexer::state8(char &current_char, char &front_char) {
    if(!std::isdigit(current_char)&&!std::isalpha(current_char)){
        if(current_word=="read"){
            current_token={current_word,8};
        }
        else{
            current_token={current_word,10};
        }
        flag= true;
    }
    else if((front_char=='r'&&current_char=='e')||(front_char=='e'&&current_char=='a')||(front_char=='a'&&current_char=='d')){
        current_state=8;
    }
    else{
        current_state=10;
    }

}
//write状态
void Lexer::state9(char &current_char, char &front_char) {
    if(!std::isdigit(current_char)&&!std::isalpha(current_char)){
        if(current_word=="write"){
            current_token={current_word,9};
        }
        else{
            current_token={current_word,10};
        }
        flag= true;
    }
    else if((front_char=='w'&&current_char=='r')||(front_char=='r'&&current_char=='i')||(front_char=='i'&&current_char=='t')||(front_char=='t'&&current_char=='e')){
        current_state=9;
    }
    else{
        current_state=10;
    }

}

void Lexer::state11(char &current_char) {
    if(!std::isdigit(current_char)&&!std::isalpha(current_char)){
        current_token={current_word,11};
        flag= true;
    }
    else if(std::isdigit(current_char)){
        current_state=11;
    }
    else{
        current_state=10;
    }
}

void Lexer::state12(char &current_char) {
    current_token={current_word,12};
    flag= true;
}

void Lexer::state15(char &current_char) {
    if(current_char!='='&&current_char!='>'){
        current_token={current_word,15};
        flag= true;
    }
    else if(current_char=='>'){
        current_state=13;
    }
    else{
        current_state=14;
    }
}

void Lexer::state17(char &current_char) {
    if(current_char!='='){
        current_token={current_word,17};
        flag= true;
    }
    else{
        current_state=16;
    }
}

void Lexer::state18(char &current_char) {
    current_token={current_word,18};
    flag= true;
}

void Lexer::state19(char &current_char) {
    current_token={current_word,19};
    flag= true;
}

void Lexer::state21(char &current_char) {
    current_token={current_word,21};
    flag= true;
}

void Lexer::state22(char &current_char) {
    current_token={current_word,22};
    flag= true;
}

void Lexer::state23(char &current_char) {
    current_token={current_word,23};
    flag= true;
}

void Lexer::state13(char &current_char, char &front_char) {
    current_token={current_word,13};
    flag= true;
}

void Lexer::state14(char &current_char, char &front_char) {
    current_token={current_word,14};
    flag= true;
}

void Lexer::state16(char &current_char, char &front_char) {
    current_token={current_word,16};
    flag= true;
}

void Lexer::state20(char &current_char, char &front_char) {
    if(front_char=='='){
        current_token={current_word,20};
        flag= true;
    }
    else if(current_char=='='){
        current_state=20;
    }
    else{
        std::cerr<<":=不匹配，出错"<<std::endl;
    }
}

void Lexer::state24() {
    current_token={"EOLN",24};
    current_line+=1;
    flag= true;
}

void Lexer::state26() {
    error_output<<"LINE: "<<current_line<<" unrecognized identifier "<<current_word<<std::endl;
    flag= true;
}

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
    do {
        current_token = get_next_token_1_1();
        token_output<<current_token.value<<" "<<current_token.type<<std::endl;
    }while (current_token.type != 25);
}





