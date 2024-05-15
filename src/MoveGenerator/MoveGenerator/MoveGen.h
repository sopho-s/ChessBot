#ifndef MOVEGEN_H
#define MOVEGEN_H
#include <cstdint>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <intrin.h>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <string>
#include "PositionInfo.h"
#include "Display.h"
namespace MoveGenerator {
    const size_t NDIRS = 8;
    enum Direction : int {
        NORTH = 8, NORTH_EAST = 9, EAST = 1, SOUTH_EAST = -7,
        SOUTH = -8, SOUTH_WEST = -9, WEST = -1, NORTH_WEST = 7,
        NORTH_NORTH = 16, SOUTH_SOUTH = -16
    };
    enum Square : int {
        a1, b1, c1, d1, e1, f1, g1, h1,
        a2, b2, c2, d2, e2, f2, g2, h2,
        a3, b3, c3, d3, e3, f3, g3, h3,
        a4, b4, c4, d4, e4, f4, g4, h4,
        a5, b5, c5, d5, e5, f5, g5, h5,
        a6, b6, c6, d6, e6, f6, g6, h6,
        a7, b7, c7, d7, e7, f7, g7, h7,
        a8, b8, c8, d8, e8, f8, g8, h8,
        NO_SQUARE
    };
    enum Side : int {
        black, white, nocolour
    };
    enum Piece : int {
        pawn, knight, bishop, rook, queen, king, nopiece
    };
    inline Square& operator++(Square& s) { return s = Square(int(s) + 1); }
    constexpr Square operator+(Square s, Direction d) { return Square(int(s) + int(d)); }
    constexpr Square operator-(Square s, Direction d) { return Square(int(s) - int(d)); }
    inline Square& operator+=(Square& s, Direction d) { return s = s + d; }
    inline Square& operator-=(Square& s, Direction d) { return s = s - d; }
    inline int pop_count(unsigned long long x);
    unsigned long long* RookMoveGen();
    unsigned long long* BishopMoveGen();
    void InitRookTable();
    void InitBishopTable();
    void InitKnightTable();
    void InitKingTable();
    inline unsigned long long PawnAttackGen(int &pos, int &sidetomove);
    inline unsigned long long PawnMoveGen(int &pos, int &sidetomove, unsigned long long pieces);
    inline unsigned long long KingMoveGen(int &pos);
    inline unsigned long long KnightMoveGen(int &pos);
    inline unsigned long long RookMoveGen(int &pos, unsigned long long &blockers);
    inline unsigned long long BishopMoveGen(int &pos, unsigned long long &blockers);
    inline unsigned long long QueenMoveGen(int &pos, unsigned long long &blockers);
    std::vector<Objects::PositionInfo> GetMovesFromPostion(Objects::PositionInfo &currposition, int sidetomove, bool print = false);
}
#endif