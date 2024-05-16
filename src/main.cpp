#include "PreMoveGen.h"
#include "MoveGen.h"
#include <vector>
#include <chrono>
#include <random>
#include <string>
int main() {
    MoveGenerator::PreGen::Init();
    MoveGenerator::Objects::PositionInfo startpos;
    startpos.currentboard.DefaultPosition();
    std::vector<std::shared_ptr<MoveGenerator::Objects::PositionInfo>> moves;
    MoveGenerator::GetMovesFromPostion(startpos, 0, moves);
    std::vector<std::shared_ptr<MoveGenerator::Objects::PositionInfo>> tempmoves = std::vector<std::shared_ptr<MoveGenerator::Objects::PositionInfo>>();
    std::cout << "Moves generated: " << moves.size() << std::endl;
    int ilegalcount = 0;
    std::cout << "Ilegal moves generated: " << ilegalcount << std::endl;
    Utilities::Hash::Clear();
    Utilities::Hash::InitTable();
    for (int i = 1; i < 5; i++) {
        ilegalcount = 0;
        auto start = std::chrono::high_resolution_clock::now();
        for (std::shared_ptr<MoveGenerator::Objects::PositionInfo> move : moves) {
            MoveGenerator::GetMovesFromPostion(*move, i % 2, tempmoves);
        }
        auto end = std::chrono::high_resolution_clock::now();
        long long diff = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << "Moves per second: " << ((long float)tempmoves.size() / ((long float)diff / (long float)1000)) << std::endl;
        std::cout << "Milliseconds: " << diff << std::endl;
        std::cout << "Moves generated: " << tempmoves.size() << std::endl;
        std::cout << "Unique positions generated: " << Utilities::Hash::GetUnique() << std::endl;
        Utilities::Hash::Clear();
        moves.clear();
        moves = tempmoves;
        tempmoves.clear();
    }
    return 0;
}