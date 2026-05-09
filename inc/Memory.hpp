<<<<<<< HEAD
class Memory : public IMemory {
private:
    std::vector<uint8_t> data;

public:
    Memory(std::size_t size);
=======
#pragma once

#include <vector>
#include "IMemory.hpp"

class Memory : public IMemory {
private:
    std::vector<uint16_t> data;

public:
    Memory(size_t size) : data(size, 0) {}
>>>>>>> d1fbbfe8407abc9d3a7d3818f105982475211c73

    uint16_t read16(uint16_t address) override;
    void write16(uint16_t address, uint16_t value) override;
    uint64_t read64(uint16_t address) override;
};