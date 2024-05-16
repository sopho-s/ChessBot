#ifndef HASH_H
#define HASH_H
#include <memory>
#include <random>
#include <limits>
namespace Utilities {
    namespace Hash {
        void InitTable();
        unsigned long long ZorbistHash(int *intboard, int *colours);
        unsigned long long AddPosition(int *intboard, int *colours);
        int GetUnique();
        void Clear();
    }
}
#endif