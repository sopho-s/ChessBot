#include "Hash.h"
namespace {
    unsigned long long int ZobristTable[8 * 8][12];
    const int HashSize = 160000000;
    int count = 0;
    bool Taken[HashSize];
    float EvalTable[HashSize];
};
namespace Utilities {
    namespace Hash {
        unsigned long long int randomInt() {
            std::random_device rd;
            std::mt19937_64 eng(rd());
            std::uniform_int_distribution<unsigned long long> distr;
            return distr(eng);
        }
        void InitTable()
        {
            for (int i = 0; i<8; i++)
            for (int j = 0; j<8; j++)
                for (int k = 0; k<12; k++)
                ZobristTable[i + j * 8][k] = randomInt();
        }
        unsigned long long ZorbistHash(int *intboard, int *colours) {
            unsigned long long hash = 0;
            for (int i = 0; i < 64; i++) {
                if (colours[i] != 2) {
                    hash ^= ZobristTable[i][colours[i] * 7 + intboard[i]];
                }
            }
            return hash;
        }
        unsigned long long AddPosition(int *intboard, int *colours) {
            unsigned long long hash = 0;
            for (int i = 0; i < 64; i++) {
                if (colours[i] != 2) {
                    hash ^= ZobristTable[i][colours[i] * 7 + intboard[i]];
                }
            }
            hash = hash % HashSize;
            if (Taken[hash]) {
                return hash;
            }
            count++;
            Taken[hash] = true;
            return hash;
        }
        int GetUnique() {
            return count;
        }
        void Clear() {
            count = 0;
            std::memset(Taken, 0, sizeof(Taken));
        }
    }
}