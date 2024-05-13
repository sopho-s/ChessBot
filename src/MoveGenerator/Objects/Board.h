#ifndef BOARD_H
#define BOARD_H
namespace MoveGenerator {
    namespace Objects {
        struct Board {
            unsigned long long blackpeices = 0;
            unsigned long long whitepeices = 0;
            unsigned long long pawns = 0;
            unsigned long long knights = 0;
            unsigned long long bishops = 0;
            unsigned long long rooks = 0;
            unsigned long long queens = 0;
            unsigned long long kings = 0;
            char castlinginfo = 0;
            inline unsigned long long GetPeices() {return whitepeices | blackpeices;}
            inline unsigned long long GetSideToPlayPeices(int side) {return side == 0 ? whitepeices : blackpeices;}
            inline unsigned long long GetOppositionsPeices(int side) {return side == 1 ? whitepeices : blackpeices;}
            inline unsigned long long GetSideToPlayPawns(int side) {return side == 0 ? whitepeices & pawns : blackpeices & pawns;}
            inline unsigned long long GetSideToPlayKnights(int side) {return side == 0 ? whitepeices & knights : blackpeices & knights;}
            inline unsigned long long GetSideToPlayBishops(int side) {return side == 0 ? whitepeices & bishops : blackpeices & bishops;}
            inline unsigned long long GetSideToPlayRooks(int side) {return side == 0 ? whitepeices & rooks : blackpeices & rooks;}
            inline unsigned long long GetSideToPlayQueens(int side) {return side == 0 ? whitepeices & queens : blackpeices & queens;}
            inline unsigned long long GetSideToPlayKings(int side) {return side == 0 ? whitepeices & kings : blackpeices & kings;}
            inline unsigned long long BlackPawns() {return blackpeices & pawns;}
            inline unsigned long long BlackKnights() {return blackpeices & knights;}
            inline unsigned long long BlackBishops() {return blackpeices & bishops;}
            inline unsigned long long BlackRooks() {return blackpeices & rooks;}
            inline unsigned long long BlackQueens() {return blackpeices & queens;}
            inline unsigned long long BlackKings() {return blackpeices & kings;}
            inline unsigned long long WhitePawns() {return whitepeices & pawns;}
            inline unsigned long long WhiteKnights() {return whitepeices & knights;}
            inline unsigned long long WhiteBishops() {return whitepeices & bishops;}
            inline unsigned long long WhiteRooks() {return whitepeices & rooks;}
            inline unsigned long long WhiteQueens() {return whitepeices & queens;}
            inline unsigned long long WhiteKings() {return whitepeices & kings;}
            inline bool CouldWhiteCastleLong() {return castlinginfo & 0b11000000 == 0 ? true : false;}
            inline bool CouldWhiteCastleShort() {return castlinginfo & 0b01100000 == 0 ? true : false;}
            inline bool CouldBlackCastleLong() {return castlinginfo & 0b00011000 == 0 ? true : false;}
            inline bool CouldBlackCastleShort() {return castlinginfo & 0b00001100 == 0 ? true : false;}
        };
    }
}
#endif