#include "./../inc/Memory.hpp"

Memory::Memory(size_t size) : data(size, 0) {}

uint16_t Memory::read16(uint16_t address)  {
    return data[address];
}

void Memory::write16(uint16_t address, uint16_t value)  {
    data[address] = value;
}

uint64_t Memory::read64(uint16_t address)  {
    uint64_t value = 0;
    for (int i = 0; i < 4; i++) {
        value |= ((uint64_t)data[address + i]) << (16 * i);
    }
    return value;
}

void Memory::dos() {
    std::cout << "memory was called\n";
}