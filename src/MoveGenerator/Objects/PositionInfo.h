#ifndef POSITIONINFO_H
#define POSITIONINFO_H
#include "Board.h"
#include <vector>
namespace MoveGenerator {
    namespace Objects {
        struct PositionInfo {
            Board currentboard;
            unsigned long long blackattacks = 0ull;
            unsigned long long whiteattacks = 0ull;
            unsigned long long pawnattacks = 0ull;
            unsigned long long knightattacks = 0ull;
            unsigned long long bishopattacks = 0ull;
            unsigned long long rookattacks = 0ull;
            unsigned long long queenattacks = 0ull;
            unsigned long long kingattacks = 0ull;
            //unsigned long long pawnmoves = 0ull;
            //unsigned long long safewhitelong = 0b1110;
            //unsigned long long safewhiteshort = 0b1100000;
            //unsigned long long safeblacklong = 0b111000000000000000000000000000000000000000000000000000000000;
            //unsigned long long safeblackshort = 0b110000000000000000000000000000000000000000000000000000000000000;
        };
    }
}
#endif