#pragma once

const char* num(const char* str, std::vector<int>& poliz);
const char* s_num(const char* str, bool negative, std::vector<int>& poliz);
const char* digit(const char* str, std::vector<int>& poliz);
const char* term(const char* str, std::vector<int>& poliz);
const char* expr(const char* str, std::vector<int>& poliz);
int calculator(const std::string& expression);