#include "PreMoveGen.h"
#include "MoveGen.h"
#include <vector>
int main() {
    MoveGenerator::PreGen::Init();
    MoveGenerator::Objects::PositionInfo startpos;
    startpos.currentboard.DefaultPosition();
    std::vector<MoveGenerator::Objects::PositionInfo> moves = MoveGenerator::GetMovesFromPostion(startpos, 0);
    for (MoveGenerator::Objects::PositionInfo move : moves) {
        MoveGenerator::GetMovesFromPostion(move, 1);
    }
    return 0;
}