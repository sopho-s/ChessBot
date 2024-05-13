#ifndef POSITIONINFO_H
#define POSITIONINFO_H
#include "Board.h"
#include <vector>
namespace MoveGenerator {
    namespace Objects {
        struct PositionInfo {
            Board currentboard;
            std::vector<Board> children;
            unsigned long long blackattacks;
            unsigned long long whiteattacks;
            unsigned long long pawnattacks;
            unsigned long long knightattacks;
            unsigned long long bishopattacks;
            unsigned long long rookattacks;
            unsigned long long queenattacks;
            unsigned long long kingattacks;
            unsigned long long pawnmoves;
            const long long safewhitelong = 0b1110;
            const long long safewhiteshort = 0b1100000;
            const long long safeblacklong = 0b111000000000000000000000000000000000000000000000000000000000;
            const long long safeblackshort = 0b110000000000000000000000000000000000000000000000000000000000000;
            inline void SetPawnAttacks() {
                unsigned long long whitepawns = currentboard.WhitePawns();
                unsigned long long whitepawnsright = whitepawns << 9 & 0b111111101111111011111110111111101111111011111110111111101111111;
                unsigned long long whitepawnsleft = whitepawns << 7 & 0b1111111011111110111111101111111011111110111111101111111011111110;
                unsigned long long blackpawns = currentboard.BlackPawns();
                unsigned long long blackpawnsright = blackpawns >> 9 & 0b111111101111111011111110111111101111111011111110111111101111111;
                unsigned long long blackpawnsleft = blackpawns >> 7 & 0b1111111011111110111111101111111011111110111111101111111011111110;
                whiteattacks |= blackpawnsleft || whitepawnsright;
                blackattacks |= whitepawnsleft || blackpawnsright;
                pawnattacks |= blackpawnsleft || blackpawnsright || whitepawnsleft || blackpawnsright;
            }
            inline void SetKnightMoves() {
            }
        };
    }
}
#endif