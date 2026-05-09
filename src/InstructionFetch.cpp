#include "./../inc/InstructionFetch.hpp"


InstructionFetch::InstructionFetch(IMemory &memory) : memory(memory)
{
    
}

// void InstructionFetch::fetch()
// {
//     std::cout << "fetch()\n";
// }

void InstructionFetch::dos() {
    std::cout << "InstructionFetch was called\n";
}
