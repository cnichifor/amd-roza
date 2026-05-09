#pragma once
#include <iostream>
#include <stdint.h>
struct FetchWindow {
    uint16_t address; // adresa de unde s-a citit blocul
    uint64_t data;    // fetch window de 64 biți
};

class IInstructionFetch {
public:
virtual FetchWindow instruction_fetch() = 0;
virtual void setIP(uint16_t newIP) = 0;
virtual uint16_t getIP() const = 0;
virtual void advanceIP(uint16_t bytes) = 0;
};