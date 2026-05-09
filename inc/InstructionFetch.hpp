#pragma once

#include <cstdint>
#include "ILoadStore.hpp"
#include "IInstructionFetch.hpp"



class InstructionFetch : public IInstructionFetch {
private:
    uint16_t ip;          // Instruction Pointer / Program Counter
    ILoadStore& loadStore; // comunicare prin interfață

public:
    InstructionFetch(ILoadStore& loadStore);

    FetchWindow instruction_fetch();

    void setIP(uint16_t newIP);
    uint16_t getIP() const;

    void advanceIP(uint16_t bytes);
};
