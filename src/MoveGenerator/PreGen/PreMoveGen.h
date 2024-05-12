#include <map>
#include <fstream>
#include <sstream>
#include <string>  
namespace MoveGenerator {
    namespace PreGen {
        void KnightMoveGen();
        void KingMoveGen();
        void Init();
        inline void split(std::string str);
        std::map<int, unsigned long long> GetKnightMoves();
    }
}