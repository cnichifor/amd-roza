#ifndef INSTRUCTION_FETCH_HPP
#define INSTRUCTION_FETCH_HPP

#include <cstdint>
#include "ILoadStore.hpp"

struct FetchWindow {
    uint16_t address; // adresa de unde s-a citit blocul
    uint64_t data;    // fetch window de 64 biți
};

class InstructionFetch {
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

#endif