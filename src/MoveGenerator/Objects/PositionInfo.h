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
            unsigned long long safewhitelong = 0b1110;
            unsigned long long safewhiteshort = 0b1100000;
            unsigned long long safeblacklong = 0b111000000000000000000000000000000000000000000000000000000000;
            unsigned long long safeblackshort = 0b110000000000000000000000000000000000000000000000000000000000000;
        };
    }
}
#endif