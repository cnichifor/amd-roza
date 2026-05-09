#pragma once

#include <cstdint>

class IMemory {
public:
    virtual uint16_t read16(uint16_t address) = 0;
    virtual void write16(uint16_t address, uint16_t value) = 0;
    virtual uint64_t read64(uint16_t address) = 0;
    
    virtual void dos()=0;

    virtual ~IMemory() = default;
};
