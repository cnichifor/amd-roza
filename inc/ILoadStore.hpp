#pragma once

#include <cstdint>

class ILoadStore {
public:
    virtual uint64_t requestInstructionFetch(uint16_t address) = 0;

    virtual uint16_t load16(uint16_t address) = 0;
    virtual void store16(uint16_t address, uint16_t value) = 0;

    virtual ~ILoadStore() = default;
};
