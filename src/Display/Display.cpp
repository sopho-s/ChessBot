#include "Display.h"
#define get_bit(bitboard, square) (bitboard & (1ULL << square))
namespace Display {
    const std::string PIECE_STR = "PNBRQK~>pnbrqk.";
    const std::string MOVE_STR = " NBRQK,";
    const std::string FILE_STR = "abcdefgh";
    const std::string RANK_STR = "12345678";
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
                    printf("  %d ", 1 + rank);
                
                if (intboard[square] != 6) {
                    printf(" %d", intboard[square]);
                } else {
                    printf(" .");
                }
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
    void print_move(int startpiece, int startpos, int endpos, bool istake, bool isshortcastle, bool islongcastle) {
        if (startpos == -1) {
            std::cout << "root" << std::endl;
        }
        std::string output = "";
        output += FILE_STR[startpos % 8];
        output += RANK_STR[(int)((startpos - startpos % 8) / 8)];
        if (istake) {
            output += "x";
        }
        output += MOVE_STR[startpiece];
        output += FILE_STR[endpos % 8];
        output += RANK_STR[(int)((endpos - endpos % 8) / 8)];
        std::cout << output << std::endl;
    }
}