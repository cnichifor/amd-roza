#include "LoadStore.hpp"

LoadStore::LoadStore(IMemory& memory)
    : memory(memory) {
}

uint64_t LoadStore::requestInstructionFetch(uint16_t address) {
    return memory.read64(address);
}

uint16_t LoadStore::load16(uint16_t address) {
    return memory.read16(address);
}

void LoadStore::store16(uint16_t address, uint16_t value) {
    memory.write16(address, value);
}