#include "PreMoveGen.h"
#define MAGICSHIFT 42
namespace {
    std::string strings[64];
}
namespace MoveGenerator {
    namespace PreGen {
        void KingMoveGen() {
            std::map<int, unsigned long long> kingmap;
            for (int i = 0; i < 8; i++) {
                for (int t = 0; t < 8; t++) {
                    unsigned long long currentpos = 0b0;
                    for (int x = -1; x < 2; x++) {
                        for (int y = -1; y < 2; y++) {
                            if (x != 0 || y != 0) {
                                int yi = y + i;
                                int xt = x + t;
                                if (xt >= 0 && xt <= 7 && yi >= 0 && yi <= 7) {
                                    currentpos |= ((unsigned long long)1) << (xt + yi * 8);
                                }
                            }
                        }
                    }
                    kingmap[t + i * 8] = currentpos;
                }
            }
            std::ofstream File("kingmoves.csv");
            std::stringstream str;
            for (int i = 0; i < 64; i++) {
                str << kingmap[i];
                std::string val;
                str >> val;
                str.clear();
                File << val;
                File << ",";
            }
            File.close();
        }
        void KnightMoveGen() {
            std::map<int, unsigned long long> knightmap;
            int moves[8][2] {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};
            for (int i = 0; i < 8; i++) {
                for (int t = 0; t < 8; t++) {
                    unsigned long long currentpos = 0b0;
                    for (int s = 0; s < 8; s++) {
                        int yi = moves[s][1] + i;
                        int xt = moves[s][0] + t;
                        if (xt >= 0 && xt <= 7 && yi >= 0 && yi <= 7) {
                            currentpos |= ((unsigned long long)1) << (xt + yi * 8);
                        }
                    }
                    knightmap[t + i * 8] = currentpos;
                }
            }
            std::ofstream File("knightmoves.csv");
            std::stringstream str;
            for (int i = 0; i < 64; i++) {
                str << knightmap[i];
                std::string val;
                str >> val;
                str.clear();
                File << val;
                File << ",";
            }
            File.close();
        }
        void BishopMoveGen() {
            unsigned long long* out;
            out = new unsigned long long[64];
            out = MoveGenerator::BishopMoveGen();
            std::ofstream File("bishopmoves.csv");
            std::stringstream str;
            for (int i = 0; i < 64; i++) {
                str << out[i];
                std::string val;
                str >> val;
                str.clear();
                File << val;
                File << ",";
            }
            File.close();
            delete[] out;
        }
        void RookMoveGen() {
            unsigned long long* out;
            out = new unsigned long long[64];
            out = MoveGenerator::RookMoveGen();
            std::ofstream File("rookmoves.csv");
            std::stringstream str;
            for (int i = 0; i < 64; i++) {
                str << out[i];
                std::string val;
                str >> val;
                str.clear();
                File << val;
                File << ",";
            }
            File.close();
            delete[] out;
        }
        void Init() {
            KingMoveGen();
            KnightMoveGen();
            RookMoveGen();
            BishopMoveGen();
            MoveGenerator::InitRookTable();
            MoveGenerator::InitBishopTable();
        }
        inline void split(std::string str) {
            int currindex = 0, i = 0;
            int startindex = 0, endindex = 0;
            while (str.length() <= i) {
                if (str[i] == ',') {
                    endindex = i;
                    std::string substr = "";
                    substr.append(str, startindex, endindex - startindex);
                    strings[currindex] = substr;
                    currindex++;
                    startindex = endindex + 1;
                }
                i++;
            }
        }
        std::map<int, unsigned long long> GetKnightMoves() {
            std::ifstream File("knightmoves.csv");
            std::string knightmovestxt;
            getline(File, knightmovestxt);
            std::map<int, unsigned long long> knightmap;
            split(knightmovestxt);
            for (int i = 0; i < 64; i++) {
                knightmap[i] = std::stoull(strings[i]);
            }
            return knightmap;
        }
        std::map<int, unsigned long long> GetKingMoves() {
            std::ifstream File("kingmoves.csv");
            std::string kingmovestxt;
            getline(File, kingmovestxt);
            std::map<int, unsigned long long> kingmap;
            split(kingmovestxt);
            for (int i = 0; i < 64; i++) {
                kingmap[i] = std::stoull(strings[i]);
            }
            return kingmap;
        }
    }
}