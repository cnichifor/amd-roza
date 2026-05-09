#pragma once
#include <iostream>
#include <stdint.h>
struct FetchWindow {
    uint16_t address; // adresa de unde s-a citit blocul
    uint64_t data;    // fetch window de 64 biți
};

class IInstructionFetch {
public:
virtual FetchWindow instruction_fetch();
virtual void setIP(uint16_t newIP);
virtual uint16_t getIP() const;
virtual void advanceIP(uint16_t bytes);
};