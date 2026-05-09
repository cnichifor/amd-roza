#pragma once

#include <cstdint>
#include "ILoadStore.hpp"
#include "IMemory.hpp"

class LoadStore : public ILoadStore {
private:
    IMemory& memory;

public:
    explicit LoadStore(IMemory& memory);

    uint64_t requestInstructionFetch(uint16_t address) override;

    uint16_t load16(uint16_t address) override;
    void store16(uint16_t address, uint16_t value) override;
};
