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
    std::vector<MoveGenerator::Objects::PositionInfo> moves = MoveGenerator::GetMovesFromPostion(startpos, 0);
    std::vector<MoveGenerator::Objects::PositionInfo> tempmoves = std::vector<MoveGenerator::Objects::PositionInfo>();
    std::vector<MoveGenerator::Objects::PositionInfo> newmoves = std::vector<MoveGenerator::Objects::PositionInfo>();
    std::cout << "Moves generated: " << moves.size() << std::endl;
    int ilegalcount = 0;
    std::cout << "Ilegal moves generated: " << ilegalcount << std::endl;
    Utilities::Hash::Clear();
    Utilities::Hash::InitTable();
    for (int i = 1; i < 5; i++) {
        ilegalcount = 0;
        auto start = std::chrono::high_resolution_clock::now();
        for (MoveGenerator::Objects::PositionInfo move : moves) {
            newmoves = MoveGenerator::GetMovesFromPostion(move, i % 2);
            if (newmoves.size() == 0) {
                ilegalcount++;
            } else {
                tempmoves.insert(tempmoves.end(), newmoves.begin(), newmoves.end());
            }
        }
        auto end = std::chrono::high_resolution_clock::now();
        long long diff = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << "Moves per second: " << ((long float)tempmoves.size() / ((long float)diff / (long float)1000)) << std::endl;
        std::cout << "Milliseconds: " << diff << std::endl;
        std::cout << "Moves generated: " << tempmoves.size() << std::endl;
        std::cout << "Unique positions generated: " << Utilities::Hash::GetUnique() << std::endl;
        std::cout << "Ilegal moves generated: " << ilegalcount << std::endl;
        Utilities::Hash::Clear();
        moves.clear();
        moves.insert(moves.end(), tempmoves.begin(), tempmoves.end());
        tempmoves.clear();
        std::string fen;
        std::ofstream File("ply" + std::to_string(i) + ".csv");
        for (MoveGenerator::Objects::PositionInfo nmove : moves) {
            File << nmove.currentboard.GetFEN();
            File << "\n";
        }
        File.close();
    }
    return 0;
}