#ifndef BOARD_H
#define BOARD_H
#include "Display.h"
#include <iostream>
#include <algorithm>
#include <iterator>
//#include <string>
#include "Hash.h"
namespace MoveGenerator {
    namespace Objects {
        enum Side : int {
            black, white, nocolour
        };
        enum Piece : int {
            pawn, knight, bishop, rook, queen, king, nopiece
        };
        struct Board {
            int pieces[64];
            int colour[64];
            int startpiece = nopiece;
            int endpiece = nopiece;
            int startposition = -1;
            int endposition = -1;
            unsigned int zorbisthash = 0;
            unsigned long long blackpieces = 0ull;
            unsigned long long whitepieces = 0ull;
            unsigned long long pawns = 0ull;
            unsigned long long knights = 0ull;
            unsigned long long bishops = 0ull;
            unsigned long long rooks = 0ull;
            unsigned long long queens = 0ull;
            unsigned long long kings = 0ull;
            unsigned long long enpassantpos = 0ull;
            unsigned long long castlinginfo = 0b11111100;
            Board() {;}
            Board(const Board& oldboard) : blackpieces(oldboard.blackpieces), whitepieces(oldboard.whitepieces), pawns(oldboard.pawns), knights(oldboard.knights), bishops(oldboard.bishops), rooks(oldboard.rooks), queens(oldboard.queens), kings(oldboard.kings), enpassantpos(oldboard.enpassantpos), castlinginfo(oldboard.castlinginfo) {
                std::copy(std::begin(oldboard.pieces), std::end(oldboard.pieces), std::begin(pieces));
                std::copy(std::begin(oldboard.colour), std::end(oldboard.colour), std::begin(colour));
            };
            Board& operator=(const Board& oldboard) {
                blackpieces = oldboard.blackpieces;
                whitepieces = oldboard.whitepieces;
                pawns = oldboard.pawns;
                knights = oldboard.knights;
                bishops = oldboard.bishops;
                rooks = oldboard.rooks;
                queens = oldboard.queens;
                kings = oldboard.kings;
                enpassantpos = 0ull;
                castlinginfo = oldboard.castlinginfo;
                std::copy(std::begin(oldboard.pieces), std::end(oldboard.pieces), std::begin(pieces));
                std::copy(std::begin(oldboard.colour), std::end(oldboard.colour), std::begin(colour));
                return *this;
            }
            inline unsigned int GetHashKey() {
                return Utilities::Hash::ZorbistHash(pieces, colour);
            }
            inline void SetHashKey() {
                zorbisthash = Utilities::Hash::AddPosition(pieces, colour);
            }
            void GetMove() {
                Display::print_move(startpiece, startposition, endposition, endpiece != nopiece ? true : false);
            }
            std::string GetFEN() {
                std::string piecenot = "pnbrqk";
                std::string fen = "";
                int count = 0;
                for (int i = 0; i < 64; i++) {
                    if (i % 8 == 0 && i != 0) {
                        if (count > 0) {
                            fen = fen + std::to_string(count);
                        }
                        fen = fen + "/";
                        count = 0;
                    }
                    if (pieces[i] != pawn && pieces[i] != knight && pieces[i] != bishop && pieces[i] != rook && pieces[i] != queen && pieces[i] != king) {
                        count++;
                    } else {
                        if (count > 0){
                            fen += std::to_string(count);
                            count = 0;
                        }
                        fen += colour[i] == 0 ? std::toupper(piecenot[pieces[i]]) : piecenot[pieces[i]];
                    }
                }
                if (count > 0){
                    fen += std::to_string(count);
                    count = 0;
                }
                std::reverse(fen.begin(), fen.end());
                return fen;
            }
            void DefaultPosition() {
                int firstrow[8] = {rook, knight, bishop, king, queen, bishop, knight, rook};
                int secondrow[8] = {pawn, pawn, pawn, pawn, pawn, pawn, pawn, pawn};
                int thirdrow[8] = {nopiece, nopiece, nopiece, nopiece, nopiece, nopiece, nopiece, nopiece};
                int fourthrow[8] = {nopiece, nopiece, nopiece, nopiece, nopiece, nopiece, nopiece, nopiece};
                int fithrow[8] = {nopiece, nopiece, nopiece, nopiece, nopiece, nopiece, nopiece, nopiece};
                int sixthrow[8] = {nopiece, nopiece, nopiece, nopiece, nopiece, nopiece, nopiece, nopiece};
                int seventhrow[8] = {pawn, pawn, pawn, pawn, pawn, pawn, pawn, pawn};
                int eighthrow[8] = {rook, knight, bishop, king, queen, bishop, knight, rook};
                for (int i = 0; i < 8; i++) {
                    pieces[i] = firstrow[i];
                    pieces[i + 8] = secondrow[i];
                    pieces[i + 16] = thirdrow[i];
                    pieces[i + 24] = fourthrow[i];
                    pieces[i + 32] = fithrow[i];
                    pieces[i + 40] = sixthrow[i];
                    pieces[i + 48] = seventhrow[i];
                    pieces[i + 56] = eighthrow[i];
                }
                for (int i = 0; i < 64; i++) {
                    switch (pieces[i]) {
                    case pawn:
                        pawns |= 1ull << i;
                        break;
                    case knight:
                        knights |= 1ull << i;
                        break;
                    case bishop:
                        bishops |= 1ull << i;
                        break;
                    case rook:
                        rooks |= 1ull << i;
                        break;
                    case queen:
                        queens |= 1ull << i;
                        break;
                    case king:
                        kings |= 1ull << i;
                        break;
                    }
                    if (i < 16) {
                        colour[i] = 0;
                        whitepieces |= 1ull << i;
                    } else if (i >= 48) {
                        colour[i] = 1;
                        blackpieces |= 1ull << i;
                    } else {
                        colour[i] = 2;
                    }
                }
            }

            inline unsigned long long GetPieces() {return whitepieces | blackpieces;}
            inline unsigned long long GetSideToPlayPieces(int side) {return side == 0 ? whitepieces : blackpieces;}
            inline unsigned long long GetOppositionsPieces(int side) {return side == 1 ? whitepieces : blackpieces;}
            inline unsigned long long GetSideToPlayPawns(int side) {return side == 0 ? whitepieces & pawns : blackpieces & pawns;}
            inline unsigned long long GetSideToPlayKnights(int side) {return side == 0 ? whitepieces & knights : blackpieces & knights;}
            inline unsigned long long GetSideToPlayBishops(int side) {return side == 0 ? whitepieces & bishops : blackpieces & bishops;}
            inline unsigned long long GetSideToPlayRooks(int side) {return side == 0 ? whitepieces & rooks : blackpieces & rooks;}
            inline unsigned long long GetSideToPlayQueens(int side) {return side == 0 ? whitepieces & queens : blackpieces & queens;}
            inline unsigned long long GetSideToPlayKings(int side) {return side == 0 ? whitepieces & kings : blackpieces & kings;}
            inline unsigned long long GetOppositionsKings(int side) {return side == 1 ? whitepieces & kings : blackpieces & kings;}
            inline unsigned long long BlackPawns() {return blackpieces & pawns;}
            inline unsigned long long BlackKnights() {return blackpieces & knights;}
            inline unsigned long long BlackBishops() {return blackpieces & bishops;}
            inline unsigned long long BlackRooks() {return blackpieces & rooks;}
            inline unsigned long long BlackQueens() {return blackpieces & queens;}
            inline unsigned long long BlackKings() {return blackpieces & kings;}
            inline unsigned long long WhitePawns() {return whitepieces & pawns;}
            inline unsigned long long WhiteKnights() {return whitepieces & knights;}
            inline unsigned long long WhiteBishops() {return whitepieces & bishops;}
            inline unsigned long long WhiteRooks() {return whitepieces & rooks;}
            inline unsigned long long WhiteQueens() {return whitepieces & queens;}
            inline unsigned long long WhiteKings() {return whitepieces & kings;}
            inline bool CouldWhiteCastleLong() {return castlinginfo & 0b11000000 == 0 ? true : false;}
            inline bool CouldWhiteCastleShort() {return castlinginfo & 0b01100000 == 0 ? true : false;}
            inline bool CouldBlackCastleLong() {return castlinginfo & 0b00011000 == 0 ? true : false;}
            inline bool CouldBlackCastleShort() {return castlinginfo & 0b00001100 == 0 ? true : false;}
            inline void UpdateCastlingInfo() {
                castlinginfo &= (1ull & rooks & whitepieces) << 7 +
                                (128ull & rooks & whitepieces) >> 2 +
                                (72057594037927936ull & rooks & blackpieces) >> 54 +
                                (9223372036854775808ull & rooks & blackpieces) >> 59;
            }
            inline void MovePiece(int startpos, int endpos, bool couldbeenpassant = false) {
                startposition = startpos;
                endposition = endpos;
                startpiece = pieces[startpos];
                endpiece = pieces[endpos];
                int startcolour = colour[startpos];
                int endcolour = colour[endpos];
                pieces[startpos] = nopiece;
                pieces[endpos] = startpiece;
                colour[startpos] = 2;
                colour[endpos] = startcolour;
                if (couldbeenpassant) {
                    int checkpos = startpos > endpos ? endpos + 8 : endpos - 8;
                    if (checkpos != startpos) {
                        if ((colour[checkpos] == 1 && colour[startpos] == 0) || (colour[checkpos] == 0 && colour[startpos] == 1 )) {
                            if (pieces[checkpos] == 0) {
                                pieces[checkpos] = nopiece;
                                colour[checkpos] = nocolour;
                                unsigned long long mask = ~(1ull << checkpos);
                                blackpieces &= mask;
                                whitepieces &= mask;
                                pawns &= mask;
                            }
                        }
                    }
                }
                unsigned long long startmask = 1ull << startpos;
                unsigned long long endmask = 1ull << endpos;
                switch (startpiece) {
                case pawn:
                    pawns |= endmask;
                    pawns ^= startmask;
                    break;
                case knight:
                    knights |= endmask;
                    knights ^= startmask;
                    break;
                case bishop:
                    bishops |= endmask;
                    bishops ^= startmask;
                    break;
                case rook:
                    rooks |= endmask;
                    rooks ^= startmask;
                    break;
                case queen:
                    queens |= endmask;
                    queens ^= startmask;
                    break;
                case king:
                    kings |= endmask;
                    kings ^= startmask;
                    break;
                }
                if (startcolour == 0) {
                    whitepieces |= endmask;
                    whitepieces ^= startmask;
                } else {
                    blackpieces |= endmask;
                    blackpieces ^= startmask;
                }
                switch (endpiece) {
                case pawn:
                    pawns |= endmask;
                    break;
                case knight:
                    knights |= endmask;
                    break;
                case bishop:
                    bishops |= endmask;
                    break;
                case rook:
                    rooks |= endmask;
                    break;
                case queen:
                    queens |= endmask;
                    break;
                case king:
                    kings |= endmask;
                    break;
                }
                if (endcolour == 0) {
                    whitepieces ^= endmask;
                } else if (endcolour == 1) {
                    blackpieces ^= endmask;
                }
                //SetHashKey();
            }
        };
    }
}
#endif