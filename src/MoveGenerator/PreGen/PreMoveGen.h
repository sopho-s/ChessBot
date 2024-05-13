#ifndef PREMOVEGEN_H
#define PREMOVEGEN_H
#include <map>
#include <fstream>
#include <sstream>
#include <string>
#include "MoveGen.h"
#include "Display.h"
namespace MoveGenerator {
    namespace PreGen {
        void KnightMoveGen();
        void KingMoveGen();
        void BishopMoveGen();
        void RookMoveGen();
        void Init();
        inline void split(std::string str);
        std::map<int, unsigned long long> GetKnightMoves();
    }
}
#endif