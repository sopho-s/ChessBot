#ifndef DISPLAY_H
#define DISPLAY_H
#include <sstream>
#include <ostream>
#include <string>
namespace Display {
    std::ostream& operator<< (std::ostream& os, const int*& p);
    void print_bitboard(unsigned long long bitboard);
    void print_intboard(int intboard[64]);
}
#endif