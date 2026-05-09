#include "./../inc/CPU.hpp"

CPU::CPU(IMemory& memory) : 
    instructionFetch(std::make_unique<InstructionFetch>(memory)),
    decodeInstruction(std::make_unique<DecodeInstruction>()),
    loadStore(std::make_unique<LoadStore>()),
    execute(std::make_unique<Execute>())
{
    
}

void CPU::cpu()
{
    std::cout << "cpu\n";
    instructionFetch->dos();
    // decodeInstruction->dos();
    // loadStore->dos();
    // execute->dos();
}
