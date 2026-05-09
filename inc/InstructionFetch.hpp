#include "IInstructionFetch.hpp"
#include "IMemory.hpp"
class InstructionFetch : public IInstructionFetch {
public:
    InstructionFetch(IMemory& memory);
    // void fetch() override;
    void dos() override;
private:
    IMemory& memory;
};