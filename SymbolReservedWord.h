#ifndef _SYMBOL_RESERVED_WORD_H_
#define _SYMBOL_RESERVED_WORD_H_

#include <unordered_map>

const std::unordered_map<char, int> SymbolReserverdWord{
    {'{', 0}, {'}', 0}, {'(', 0}, {')', 0}, {'[', 0}, {']', 0}, {'.', 0},
    {',', 0}, {';', 0}, {'+', 0}, {'-', 0}, {'*', 0}, {'/', 0}, {'&', 0},
    {'|', 0}, {'<', 0}, {'>', 0}, {'=', 0}, {'~', 0}};

#endif
