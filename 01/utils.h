#pragma once
#include <iostream>
#include <vector>

void make_operation(char operation, std::vector<int>& buf_num);
void str_to_num(std::vector<int>& buf_num);
const char* skip_white_spaces(const char* str);