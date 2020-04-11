#ifndef _KEYWORD_RESERVED_WORD_H_
#define _KEYWORD_RESERVED_WORD_H_

#include <string>
#include <unordered_map>

const std::unordered_map<std::string, int> KeywordReservedWord{
    {"class", 0}, {"constructor", 0}, {"function", 0}, {"method", 0},
    {"field", 0}, {"static", 0},      {"var", 0},      {"int", 0},
    {"char", 0},  {"boolean", 0},     {"void", 0},     {"true", 0},
    {"false", 0}, {"null", 0},        {"this", 0},     {"let", 0},
    {"do", 0},    {"if", 0},          {"else", 0},     {"while", 0},
    {"return", 0}};

#endif
