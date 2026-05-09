#include <memory> // For std::unique_ptr
#include "Components.hpp"
class CPU {
public:
    std::unique_ptr<IInstructionFetch> instructionFetch;
    std::unique_ptr<IDecodeInstruction> decodeInstruction;
    std::unique_ptr<ILoadStore> loadStore;
    std::unique_ptr<IExecute> execute;
    
    CPU(IMemory& memory);
    void cpu();
};