#include "Display.h"
#define get_bit(bitboard, square) (bitboard & (1ULL << square))
namespace Display {
    const std::string PIECE_STR = "PNBRQK~>pnbrqk.";
    std::ostream& operator<< (std::ostream& os, const int*& p) {
        const char* s = "   +---+---+---+---+---+---+---+---+\n";
        const char* t = "     A   B   C   D   E   F   G   H\n";
        os << t;
        for (int i = 56; i >= 0; i -= 8) {
            os << s << " " << i / 8 + 1 << " ";
            for (int j = 0; j < 8; j++)
                os << "| " << PIECE_STR[p[i + j]] << " ";
            os << "| " << i / 8 + 1 << "\n";
        }
        os << s;
        os << t << "\n";

        return os;
    }
    void print_intboard(int intboard[64])
    {
        printf("\n");
        
        for (int rank = 7; rank >= 0; rank--)
        {
            for (int file = 0; file < 8; file++)
            {
                int square = rank * 8 + file;
                
                if (!file)
                    printf("  %d ", 8 - rank);
                
                printf(" %d", intboard[square]);
            }
            
            printf("\n");
        }
        
        printf("\n     a b c d e f g h\n\n");
    }
    void print_bitboard(unsigned long long bitboard)
    {
        printf("\n");
        
        for (int rank = 7; rank >= 0; rank--)
        {
            for (int file = 0; file < 8; file++)
            {
                int square = rank * 8 + file;
                
                if (!file)
                    printf("  %d ", 8 - rank);
                
                printf(" %d", get_bit(bitboard, square) ? 1 : 0);
            }
            
            printf("\n");
        }
        
        printf("\n     a b c d e f g h\n\n");
        
        printf("     bitboard: %llu\n\n", bitboard);
    }
}