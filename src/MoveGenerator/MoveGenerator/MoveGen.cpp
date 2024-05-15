#include "MoveGen.h"
namespace {
    std::string strings[64];
}
namespace MoveGenerator {
    unsigned long long rookmoves[64];
    unsigned long long bishopmoves[64];
    unsigned long long kingmoves[64];
    unsigned long long knightmoves[64];

    const unsigned long long ROOK_MAGICS[64] = {
        0x8a80104000800020ULL,
        0x140002000100040ULL,
        0x2801880a0017001ULL,
        0x100081001000420ULL,
        0x200020010080420ULL,
        0x3001c0002010008ULL,
        0x8480008002000100ULL,
        0x2080088004402900ULL,
        0x800098204000ULL,
        0x2024401000200040ULL,
        0x100802000801000ULL,
        0x120800800801000ULL,
        0x208808088000400ULL,
        0x2802200800400ULL,
        0x2200800100020080ULL,
        0x801000060821100ULL,
        0x80044006422000ULL,
        0x100808020004000ULL,
        0x12108a0010204200ULL,
        0x140848010000802ULL,
        0x481828014002800ULL,
        0x8094004002004100ULL,
        0x4010040010010802ULL,
        0x20008806104ULL,
        0x100400080208000ULL,
        0x2040002120081000ULL,
        0x21200680100081ULL,
        0x20100080080080ULL,
        0x2000a00200410ULL,
        0x20080800400ULL,
        0x80088400100102ULL,
        0x80004600042881ULL,
        0x4040008040800020ULL,
        0x440003000200801ULL,
        0x4200011004500ULL,
        0x188020010100100ULL,
        0x14800401802800ULL,
        0x2080040080800200ULL,
        0x124080204001001ULL,
        0x200046502000484ULL,
        0x480400080088020ULL,
        0x1000422010034000ULL,
        0x30200100110040ULL,
        0x100021010009ULL,
        0x2002080100110004ULL,
        0x202008004008002ULL,
        0x20020004010100ULL,
        0x2048440040820001ULL,
        0x101002200408200ULL,
        0x40802000401080ULL,
        0x4008142004410100ULL,
        0x2060820c0120200ULL,
        0x1001004080100ULL,
        0x20c020080040080ULL,
        0x2935610830022400ULL,
        0x44440041009200ULL,
        0x280001040802101ULL,
        0x2100190040002085ULL,
        0x80c0084100102001ULL,
        0x4024081001000421ULL,
        0x20030a0244872ULL,
        0x12001008414402ULL,
        0x2006104900a0804ULL,
        0x1004081002402ULL,
    };

    const unsigned long long BISHOP_MAGICS[64]=
    {
        0x0002020202020200, 0x0002020202020000, 0x0004010202000000, 0x0004040080000000,
        0x0001104000000000, 0x0000821040000000, 0x0000410410400000, 0x0000104104104000,
        0x0000040404040400, 0x0000020202020200, 0x0000040102020000, 0x0000040400800000,
        0x0000011040000000, 0x0000008210400000, 0x0000004104104000, 0x0000002082082000,
        0x0004000808080800, 0x0002000404040400, 0x0001000202020200, 0x0000800802004000,
        0x0000800400A00000, 0x0000200100884000, 0x0000400082082000, 0x0000200041041000,
        0x0002080010101000, 0x0001040008080800, 0x0000208004010400, 0x0000404004010200,
        0x0000840000802000, 0x0000404002011000, 0x0000808001041000, 0x0000404000820800,
        0x0001041000202000, 0x0000820800101000, 0x0000104400080800, 0x0000020080080080,
        0x0000404040040100, 0x0000808100020100, 0x0001010100020800, 0x0000808080010400,
        0x0000820820004000, 0x0000410410002000, 0x0000082088001000, 0x0000002011000800,
        0x0000080100400400, 0x0001010101000200, 0x0002020202000400, 0x0001010101000200,
        0x0000410410400000, 0x0000208208200000, 0x0000002084100000, 0x0000000020880000,
        0x0000001002020000, 0x0000040408020000, 0x0004040404040000, 0x0002020202020000,
        0x0000104104104000, 0x0000002082082000, 0x0000000020841000, 0x0000000000208800,
        0x0000000010020200, 0x0000000404080200, 0x0000040404040400, 0x0002020202020200
    };

    const unsigned long long SQUARE_BB[65] = {
        0x1, 0x2, 0x4, 0x8,
        0x10, 0x20, 0x40, 0x80,
        0x100, 0x200, 0x400, 0x800,
        0x1000, 0x2000, 0x4000, 0x8000,
        0x10000, 0x20000, 0x40000, 0x80000,
        0x100000, 0x200000, 0x400000, 0x800000,
        0x1000000, 0x2000000, 0x4000000, 0x8000000,
        0x10000000, 0x20000000, 0x40000000, 0x80000000,
        0x100000000, 0x200000000, 0x400000000, 0x800000000,
        0x1000000000, 0x2000000000, 0x4000000000, 0x8000000000,
        0x10000000000, 0x20000000000, 0x40000000000, 0x80000000000,
        0x100000000000, 0x200000000000, 0x400000000000, 0x800000000000,
        0x1000000000000, 0x2000000000000, 0x4000000000000, 0x8000000000000,
        0x10000000000000, 0x20000000000000, 0x40000000000000, 0x80000000000000,
        0x100000000000000, 0x200000000000000, 0x400000000000000, 0x800000000000000,
        0x1000000000000000, 0x2000000000000000, 0x4000000000000000, 0x8000000000000000,
        0x0
    };
    const unsigned long long MASK_FILE[8] = {
        0x101010101010101, 0x202020202020202, 0x404040404040404, 0x808080808080808,
        0x1010101010101010, 0x2020202020202020, 0x4040404040404040, 0x8080808080808080,
    };
    const unsigned long long MASK_RANK[8] = {
        0xff, 0xff00, 0xff0000, 0xff000000,
        0xff00000000, 0xff0000000000, 0xff000000000000, 0xff00000000000000
    };
    const unsigned long long MASK_DIAGONAL[15] = {
        0x80, 0x8040, 0x804020,
        0x80402010, 0x8040201008, 0x804020100804,
        0x80402010080402, 0x8040201008040201, 0x4020100804020100,
        0x2010080402010000, 0x1008040201000000, 0x804020100000000,
        0x402010000000000, 0x201000000000000, 0x100000000000000,
    };

    const unsigned long long MASK_ANTI_DIAGONAL[15] = {
        0x1, 0x102, 0x10204,
        0x1020408, 0x102040810, 0x10204081020,
        0x1020408102040, 0x102040810204080, 0x204081020408000,
        0x408102040800000, 0x810204080000000, 0x1020408000000000,
        0x2040800000000000, 0x4080000000000000, 0x8000000000000000,
    };
    unsigned long long ROOK_ATTACK_MASKS[64];
    int ROOK_ATTACK_SHIFTS[64];
    unsigned long long rookattacks[64][4096];
    unsigned long long BISHOP_ATTACK_MASKS[64];
    int BISHOP_ATTACK_SHIFTS[64];
    unsigned long long bishopattacks[64][512];
    const unsigned long long k1 = 0x5555555555555555;
    const unsigned long long k2 = 0x3333333333333333;
    const unsigned long long k4 = 0x0f0f0f0f0f0f0f0f;
    const unsigned long long kf = 0x0101010101010101;

    // Returns number of set bits in bit board
    // TODO: There is probably a intrensic faster function for this but is not to necessary
    inline int pop_count(unsigned long long x) {
        x = x - ((x >> 1) & k1);
        x = (x & k2) + ((x >> 2) & k2);
        x = (x + (x >> 4)) & k4;
        x = (x * kf) >> 56;
        return int(x);
    }

    // Generates all unblocked rook moves
    // !Maybe should be depricated soon?
    unsigned long long* RookMoveGen() {
        unsigned long long* out = new unsigned long long[64]();
        for (int i = 0; i < 8; i++) {
            for (int t = 0; t < 8; t++) {
                unsigned long long move = 0;
                for (int x = -8; x <= 8; x++) {
                    if (x + t < 8 && x + t >= 0 && x != 0) {
                        move |= ((unsigned long long)1) << (x+t+i*8);
                    }
                }
                for (int y = -8; y <= 8; y++) {
                    if (y + i < 8 && y + i >= 0 && y != 0) {
                        move |= ((unsigned long long)1) << (t+(y+i)*8);
                    }
                }
                out[t+i*8] = move;
            }
        }
        std::memcpy(rookmoves, out, 64 * sizeof(unsigned long long));
        return out;
    }
    
    // Generates all unblocked bishop moves
    // !Maybe should be depricated soon?
    unsigned long long* BishopMoveGen() {
        unsigned long long* out = new unsigned long long[64]();
        for (int i = 0; i < 8; i++) {
            for (int t = 0; t < 8; t++) {
                unsigned long long move = 0;
                for (int x = -8; x <= 8; x++) {
                    for (int y = -8; y <= 8; y++) {
                        if (x != 0 || y != 0) {
                            if (x == y || -x == y) {
                                if (x + t < 8 && x + t >= 0 && y + i < 8 && y + i >= 0) {
                                    move |= ((unsigned long long)1) << (x+t+(y+i)*8);
                                }
                            }
                        }
                    }
                }
                out[t+i*8] = move;
            }
        }
        std::memcpy(bishopmoves, out, 64 * sizeof(unsigned long long));
        return out;
    }

    // Some of this was ripped of the web from public repos because I couldn't get the table working for the magic bitboards
    unsigned long long reverse(unsigned long long b) {
        b = (b & 0x5555555555555555) << 1 | (b >> 1) & 0x5555555555555555;
        b = (b & 0x3333333333333333) << 2 | (b >> 2) & 0x3333333333333333;
        b = (b & 0x0f0f0f0f0f0f0f0f) << 4 | (b >> 4) & 0x0f0f0f0f0f0f0f0f;
        b = (b & 0x00ff00ff00ff00ff) << 8 | (b >> 8) & 0x00ff00ff00ff00ff;

        return (b << 48) | ((b & 0xffff0000) << 16) |
            ((b >> 16) & 0xffff0000) | (b >> 48);
    }
    unsigned long long sliding_attacks(int square, unsigned long long occ, unsigned long long mask) {
        return (((mask & occ) - SQUARE_BB[square] * 2) ^
            reverse(reverse(mask & occ) - reverse(SQUARE_BB[square]) * 2)) & mask;
    }
    unsigned long long get_rook_attacks_for_init(int square, unsigned long long occ) {
        return sliding_attacks(square, occ, MASK_FILE[div(square, 8).rem]) |
            sliding_attacks(square, occ, MASK_RANK[div(square, 8).quot]);
    }
    // Creates the rook attack table
    void InitRookTable() {
        std::cout << "Bishop move generation: -------------------- 0.00%\r";
        unsigned long long edges, subset, index;

        for (Square sq = a1; sq <= h8; ++sq) {
            edges = ((MASK_RANK[0] | MASK_RANK[7]) & ~MASK_RANK[div(sq, 8).quot]) |
                ((MASK_FILE[0] | MASK_FILE[7]) & ~MASK_FILE[div(sq, 8).rem]);
            ROOK_ATTACK_MASKS[sq] = (MASK_RANK[div(sq, 8).quot]
                ^ MASK_FILE[div(sq, 8).rem]) & ~edges;
            ROOK_ATTACK_SHIFTS[sq] = 64 - pop_count(ROOK_ATTACK_MASKS[sq]);

            subset = 0;
            do {
                index = subset;
                index = index * ROOK_MAGICS[sq];
                index = index >> ROOK_ATTACK_SHIFTS[sq];
                rookattacks[sq][index] = get_rook_attacks_for_init(sq, subset);
                subset = (subset - ROOK_ATTACK_MASKS[sq]) & ROOK_ATTACK_MASKS[sq];
            } while (subset);
            std::cout << "\r" << "Rook move generation: ";
            float percent = sq / 64.0;
            int count = (int)(percent * 20.0);
            std::string bar = "";
            for (int t = 0; t < 20; t++) {
                if (t < count) {
                    bar += "=";
                } else if (t == count) {
                    bar += ">";
                } else {
                    bar += "-";
                }
            }
            std::cout << bar << " " << std::setprecision(2) << (percent * 100) << "%\r";
        }
        std::cout << "Rook move generation: ==================== 100.00%" << std::endl;
    }
    unsigned long long get_bishop_attacks_for_init(Square square, unsigned long long occ) {
        return sliding_attacks(square, occ, MASK_DIAGONAL[7 + div(square, 8).quot - div(square, 8).rem]) |
            sliding_attacks(square, occ, MASK_ANTI_DIAGONAL[div(square, 8).quot + div(square, 8).rem]);
    }
    // Creates the bishop attack table
    void InitBishopTable() {
        std::cout << "Bishop move generation: -------------------- 0.00%\r";
        unsigned long long edges, subset, index;

        for (Square sq = a1; sq <= h8; ++sq) {
            edges = ((MASK_RANK[0] | MASK_RANK[7]) & ~MASK_RANK[div(sq, 8).quot]) |
                ((MASK_FILE[0] | MASK_FILE[7]) & ~MASK_FILE[div(sq, 8).rem]);
            BISHOP_ATTACK_MASKS[sq] = (MASK_DIAGONAL[7 + div(sq, 8).quot - div(sq, 8).rem]
                ^ MASK_ANTI_DIAGONAL[div(sq, 8).quot + div(sq, 8).rem]) & ~edges;
            BISHOP_ATTACK_SHIFTS[sq] = 64 - pop_count(BISHOP_ATTACK_MASKS[sq]);

            subset = 0;
            do {
                index = subset;
                index = index * BISHOP_MAGICS[sq];
                index = index >> BISHOP_ATTACK_SHIFTS[sq];
                bishopattacks[sq][index] = get_bishop_attacks_for_init(sq, subset);
                subset = (subset - BISHOP_ATTACK_MASKS[sq]) & BISHOP_ATTACK_MASKS[sq];
            } while (subset);
            std::cout << "\r" << "Bishop move generation: ";
            float percent = sq / 64.0;
            int count = (int)(percent * 20.0);
            std::string bar = "";
            for (int t = 0; t < 20; t++) {
                if (t < count) {
                    bar += "=";
                } else if (t == count) {
                    bar += ">";
                } else {
                    bar += "-";
                }
            }
            std::cout << bar << " " << std::setprecision(2) << (percent * 100) << "%\r";
        }
        std::cout << "Bishop move generation: ==================== 100.00%" << std::endl;
    }
    // Splits a string
    inline void split(std::string str) {
        int currindex = 0, i = 0;
        int startindex = 0, endindex = 0;
        while (str.length() > i) {
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
    void InitKnightTable() {
        std::ifstream File("knightmoves.csv");
        std::string knightmovestxt;
        getline(File, knightmovestxt);
        split(knightmovestxt);
        for (int i = 0; i < 64; i++) {
            knightmoves[i] = std::stoull(strings[i]);
        }
    }
    void InitKingTable() {
        std::ifstream File("kingmoves.csv");
        std::string kingmovestxt;
        getline(File, kingmovestxt);
        split(kingmovestxt);
        for (int i = 0; i < 64; i++) {
            kingmoves[i] = std::stoull(strings[i]);
        }
    }
    inline unsigned long long PawnAttackGen(int &pos, int &sidetomove) {
        unsigned long long piecepos = 1ull << pos;
        unsigned long long attacks = 0ull;
        if (sidetomove == 0) {
            attacks = piecepos << 9 & 0b111111101111111011111110111111101111111011111110111111101111111;
            attacks |= piecepos << 7 & 0b1111111011111110111111101111111011111110111111101111111011111110;
        } else {
            attacks = piecepos >> 9 & 0b111111101111111011111110111111101111111011111110111111101111111;
            attacks |= piecepos >> 7 & 0b1111111011111110111111101111111011111110111111101111111011111110;
        }
        return attacks;
    }
    inline unsigned long long PawnMoveGen(int &pos, int &sidetomove, unsigned long long pieces) {
        unsigned long long piecepos = 1ull << pos;
        unsigned long long attacks = 0ull;
        if (sidetomove == 0) {
            pieces = pieces << 8;
            attacks = piecepos << 8;
            if (attacks & pieces > 0ull) {
                attacks = 0ull;
                return attacks;
            }
            pieces = pieces << 8;
            attacks |= (piecepos & 65280ull) << 16;
            if (attacks & pieces > 0ull) {
                attacks -= attacks & pieces;
            }
        } else {
            pieces = pieces >> 8;
            attacks = piecepos >> 8;
            if (attacks & pieces > 0ull) {
                attacks = 0ull;
                return attacks;
            }
            pieces = pieces >> 8;
            attacks |= (piecepos & 71776119061217280ull) >> 16;
            if (attacks & pieces > 0ull) {
                attacks -= attacks & pieces;
            }
        }
        return attacks;
    }
    inline unsigned long long KingMoveGen(int &pos) {
        return kingmoves[pos];
    }
    inline unsigned long long KnightMoveGen(int &pos) {
        return knightmoves[pos];
    }
    inline unsigned long long RookMoveGen(int &pos, unsigned long long &blockers) {
        return rookattacks[pos][((blockers & ROOK_ATTACK_MASKS[pos]) * ROOK_MAGICS[pos])
		    >> (ROOK_ATTACK_SHIFTS[pos])];
    }
    inline unsigned long long BishopMoveGen(int &pos, unsigned long long &blockers) {
        return bishopattacks[pos][((blockers & BISHOP_ATTACK_MASKS[pos]) * BISHOP_MAGICS[pos])
		    >> (BISHOP_ATTACK_SHIFTS[pos])];
    }
    inline unsigned long long QueenMoveGen(int &pos, unsigned long long &blockers) {
        return (rookattacks[pos][((blockers & ROOK_ATTACK_MASKS[pos]) * ROOK_MAGICS[pos])
		    >> (ROOK_ATTACK_SHIFTS[pos])]) | 
            (bishopattacks[pos][((blockers & BISHOP_ATTACK_MASKS[pos]) * BISHOP_MAGICS[pos])
		    >> (BISHOP_ATTACK_SHIFTS[pos])]);
    }
    std::vector<Objects::PositionInfo> GetMovesFromPostion(Objects::PositionInfo &currposition, int sidetomove, bool print) {
        std::vector<Objects::PositionInfo> childpositions = std::vector<Objects::PositionInfo>();
        unsigned long long position = currposition.currentboard.GetPieces();
        unsigned long long playerposition =  currposition.currentboard.GetSideToPlayPieces(sidetomove);
        unsigned long long oppositionposition = currposition.currentboard.GetOppositionsPieces(sidetomove);
        unsigned long long oppositionkingposition = currposition.currentboard.GetOppositionsKings(sidetomove);
        for (int i = 0; i < 6; i++) {
            unsigned long long currentpieceposition = 0;
            switch (i) {
            case 0:
                currentpieceposition = currposition.currentboard.GetSideToPlayPawns(sidetomove);
                break;
            case 1:
                currentpieceposition = currposition.currentboard.GetSideToPlayKnights(sidetomove);
                break;
            case 2:
                currentpieceposition = currposition.currentboard.GetSideToPlayBishops(sidetomove);
                break;
            case 3:
                currentpieceposition = currposition.currentboard.GetSideToPlayRooks(sidetomove);
                break;
            case 4:
                currentpieceposition = currposition.currentboard.GetSideToPlayQueens(sidetomove);
                break;
            case 5:
                currentpieceposition = currposition.currentboard.GetSideToPlayKings(sidetomove);
                break;
            }
            unsigned long long playerpieceposition = playerposition & currentpieceposition;
            int playerpiecepos = (int)_tzcnt_u64(playerpieceposition);
            while (playerpiecepos != 64) {
                bool isenpassant = false;
                unsigned long long currentattacks;
                unsigned long long tempstore = 0ull;
                switch (i) {
                case 0:
                    currentattacks = PawnAttackGen(playerpiecepos, sidetomove);
                    isenpassant = currentattacks & currposition.currentboard.enpassantpos > 0 ? true : false;
                    currentattacks = currentattacks & currposition.currentboard.enpassantpos + currentattacks & oppositionposition;
                    currentattacks |= PawnMoveGen(playerpiecepos, sidetomove, position);
                    break;
                case 1:
                    currentattacks = KnightMoveGen(playerpiecepos);
                    break;
                case 2:
                    currentattacks = BishopMoveGen(playerpiecepos, position);
                    break;
                case 3:
                    currentattacks = RookMoveGen(playerpiecepos, position);
                    break;
                case 4:
                    currentattacks = QueenMoveGen(playerpiecepos, position);
                    break;
                case 5:
                    currentattacks = KingMoveGen(playerpiecepos);
                    break;
                }
                if (currentattacks & oppositionkingposition != 0ull) {
                    return std::vector<Objects::PositionInfo>();
                }
                currentattacks = currentattacks & ~playerposition;
                tempstore = currentattacks;
                int currentmove = (int)_tzcnt_u64(currentattacks);
                Objects::PositionInfo temp;
                while (currentmove != 64) {
                    Objects::PositionInfo temp;
                    temp.currentboard = currposition.currentboard;
                    temp.currentboard.MovePiece(playerpiecepos, currentmove);
                    childpositions.push_back(temp);
                    temp.currentboard.UpdateCastlingInfo();
                    currentattacks ^= 1ull << currentmove;
                    currentmove = (int)_tzcnt_u64(currentattacks);
                }
                playerpieceposition ^= 1ull << playerpiecepos;
                playerpiecepos = (int)_tzcnt_u64(playerpieceposition);
            }
        }
        return childpositions;
    }
}