#include "MoveGen.h"
namespace MoveGenerator {
    unsigned long long rookmoves[64];
    unsigned long long bishopmoves[64];
    const unsigned int magicmoves_r_shift[64]=
    {
        52, 53, 53, 53, 53, 53, 53, 52,
        53, 54, 54, 54, 54, 54, 54, 53,
        53, 54, 54, 54, 54, 54, 54, 53,
        53, 54, 54, 54, 54, 54, 54, 53,
        53, 54, 54, 54, 54, 54, 54, 53,
        53, 54, 54, 54, 54, 54, 54, 53,
        53, 54, 54, 54, 54, 54, 54, 53,
        53, 54, 54, 53, 53, 53, 53, 53
    };

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
    int rook_rellevant_bits[64] = {
        12, 11, 11, 11, 11, 11, 11, 12,
        11, 10, 10, 10, 10, 10, 10, 11,
        11, 10, 10, 10, 10, 10, 10, 11,
        11, 10, 10, 10, 10, 10, 10, 11,
        11, 10, 10, 10, 10, 10, 10, 11,
        11, 10, 10, 10, 10, 10, 10, 11,
        11, 10, 10, 10, 10, 10, 10, 11,
        12, 11, 11, 11, 11, 11, 11, 12
    };
    const unsigned long long magicmoves_r_mask[64]=
    {	
        0x000101010101017E, 0x000202020202027C, 0x000404040404047A, 0x0008080808080876,
        0x001010101010106E, 0x002020202020205E, 0x004040404040403E, 0x008080808080807E,
        0x0001010101017E00, 0x0002020202027C00, 0x0004040404047A00, 0x0008080808087600,
        0x0010101010106E00, 0x0020202020205E00, 0x0040404040403E00, 0x0080808080807E00,
        0x00010101017E0100, 0x00020202027C0200, 0x00040404047A0400, 0x0008080808760800,
        0x00101010106E1000, 0x00202020205E2000, 0x00404040403E4000, 0x00808080807E8000,
        0x000101017E010100, 0x000202027C020200, 0x000404047A040400, 0x0008080876080800,
        0x001010106E101000, 0x002020205E202000, 0x004040403E404000, 0x008080807E808000,
        0x0001017E01010100, 0x0002027C02020200, 0x0004047A04040400, 0x0008087608080800,
        0x0010106E10101000, 0x0020205E20202000, 0x0040403E40404000, 0x0080807E80808000,
        0x00017E0101010100, 0x00027C0202020200, 0x00047A0404040400, 0x0008760808080800,
        0x00106E1010101000, 0x00205E2020202000, 0x00403E4040404000, 0x00807E8080808000,
        0x007E010101010100, 0x007C020202020200, 0x007A040404040400, 0x0076080808080800,
        0x006E101010101000, 0x005E202020202000, 0x003E404040404000, 0x007E808080808000,
        0x7E01010101010100, 0x7C02020202020200, 0x7A04040404040400, 0x7608080808080800,
        0x6E10101010101000, 0x5E20202020202000, 0x3E40404040404000, 0x7E80808080808000
    };

    //my original tables for bishops
    const unsigned int magicmoves_b_shift[64]=
    {
        58, 59, 59, 59, 59, 59, 59, 58,
        59, 59, 59, 59, 59, 59, 59, 59,
        59, 59, 57, 57, 57, 57, 59, 59,
        59, 59, 57, 55, 55, 57, 59, 59,
        59, 59, 57, 55, 55, 57, 59, 59,
        59, 59, 57, 57, 57, 57, 59, 59,
        59, 59, 59, 59, 59, 59, 59, 59,
        58, 59, 59, 59, 59, 59, 59, 58
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


    const unsigned long long magicmoves_b_mask[64]=
    {
        0x0040201008040200, 0x0000402010080400, 0x0000004020100A00, 0x0000000040221400,
        0x0000000002442800, 0x0000000204085000, 0x0000020408102000, 0x0002040810204000,
        0x0020100804020000, 0x0040201008040000, 0x00004020100A0000, 0x0000004022140000,
        0x0000000244280000, 0x0000020408500000, 0x0002040810200000, 0x0004081020400000,
        0x0010080402000200, 0x0020100804000400, 0x004020100A000A00, 0x0000402214001400,
        0x0000024428002800, 0x0002040850005000, 0x0004081020002000, 0x0008102040004000,
        0x0008040200020400, 0x0010080400040800, 0x0020100A000A1000, 0x0040221400142200,
        0x0002442800284400, 0x0004085000500800, 0x0008102000201000, 0x0010204000402000,
        0x0004020002040800, 0x0008040004081000, 0x00100A000A102000, 0x0022140014224000,
        0x0044280028440200, 0x0008500050080400, 0x0010200020100800, 0x0020400040201000,
        0x0002000204081000, 0x0004000408102000, 0x000A000A10204000, 0x0014001422400000,
        0x0028002844020000, 0x0050005008040200, 0x0020002010080400, 0x0040004020100800,
        0x0000020408102000, 0x0000040810204000, 0x00000A1020400000, 0x0000142240000000,
        0x0000284402000000, 0x0000500804020000, 0x0000201008040200, 0x0000402010080400,
        0x0002040810204000, 0x0004081020400000, 0x000A102040000000, 0x0014224000000000,
        0x0028440200000000, 0x0050080402000000, 0x0020100804020000, 0x0040201008040200
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

    //Returns number of set bits in the bitboard
    inline int pop_count(unsigned long long x) {
        x = x - ((x >> 1) & k1);
        x = (x & k2) + ((x >> 2) & k2);
        x = (x + (x >> 4)) & k4;
        x = (x * kf) >> 56;
        return int(x);
    }

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
            std::cout << bar << " " << std::setprecision(2) << percent << "%\r";
        }
        std::cout << "Rook move generation: ==================== 100.00%" << std::endl;
    }
    unsigned long long get_bishop_attacks_for_init(Square square, unsigned long long occ) {
        return sliding_attacks(square, occ, MASK_DIAGONAL[7 + div(square, 8).quot - div(square, 8).rem]) |
            sliding_attacks(square, occ, MASK_ANTI_DIAGONAL[div(square, 8).quot + div(square, 8).rem]);
    }
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
            std::cout << bar << " " << std::setprecision(2) << percent << "%\r";
        }
        std::cout << "Bishop move generation: ==================== 100.00%" << std::endl;

    }
    unsigned long long RookMoveGen(Square pos, unsigned long long blockers) {
        return rookattacks[pos][((blockers & ROOK_ATTACK_MASKS[pos]) * ROOK_MAGICS[pos])
		    >> (64-rook_rellevant_bits[pos])];
    }
    unsigned long long BishopMoveGen(Square pos, unsigned long long blockers) {
        return bishopattacks[pos][((blockers & BISHOP_ATTACK_MASKS[pos]) * BISHOP_MAGICS[pos])
		    >> (BISHOP_ATTACK_SHIFTS[pos])];
    }
    unsigned long long QueenMoveGen(Square pos, unsigned long long blockers) {
        return (rookattacks[pos][((blockers & ROOK_ATTACK_MASKS[pos]) * ROOK_MAGICS[pos])
		    >> (64-rook_rellevant_bits[pos])]) | 
            (bishopattacks[pos][((blockers & BISHOP_ATTACK_MASKS[pos]) * BISHOP_MAGICS[pos])
		    >> (BISHOP_ATTACK_SHIFTS[pos])]);
    }
    std::vector<Objects::Board> GetMovesFromPostion(Objects::Board currposition, Side sidetomove) {
        unsigned long long position = currposition.GetPeices();
        unsigned long long playersposition = currposition.GetSideToPlayPeices(sidetomove);
        unsigned long long oppositionsposition = currposition.GetOppositionsPeices(sidetomove);
        unsigned long long queenposition = currposition.GetSideToPlayQueens(sidetomove);
        return std::vector<Objects::Board>();
    }
}