#include <vector>

#include "IMemory.hpp"

class Memory : public IMemory {
private:
    std::vector<uint16_t> data;

public:
    Memory(size_t size) : data(size, 0) {}

    uint16_t read16(uint16_t address) override {
        return data[address];
    }

    void write16(uint16_t address, uint16_t value) override {
        data[address] = value;
    }

    uint64_t read64(uint16_t address) override {
        uint64_t value = 0;
        for (int i = 0; i < 4; i++) {
            value |= ((uint64_t)data[address + i]) << (16 * i);
        }
        return value;
    }
};