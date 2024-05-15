#ifndef DISPLAY_H
#define DISPLAY_H
#include <sstream>
#include <ostream>
#include <iostream>
#include <string>
namespace Display {
    std::ostream& operator<< (std::ostream& os, const int*& p);
    void print_bitboard(unsigned long long bitboard);
    void print_intboard(int intboard[64]);
    void print_move(int startpiece, int startpos, int endpos, bool istake = false, bool isshortcastle = false, bool islongcastle = false);
}
#endif