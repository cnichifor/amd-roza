#pragma once
#include <memory> // For std::unique_ptr
#include "Components.hpp"
#include "IInstructionFetch.hpp"
class CPU {
public:
    std::unique_ptr<ILoadStore> loadStore;
    std::unique_ptr<IInstructionFetch> instructionFetch;
    std::unique_ptr<IDecodeInstruction> decodeInstruction;
    std::unique_ptr<IExecute> execute;

    bool isStopped = false;
    uint64_t cycleCount = 0;
    
    CPU(IMemory& memory);
    void cpu();
};