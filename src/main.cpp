#include "./../inc/Memory.hpp"
#include "./../inc/CPU.hpp"

#include <iostream>
#include <vector>
#include <cstdint>

void writeByte(IMemory& memory, uint16_t address, uint8_t value) {
    uint16_t alignedAddress = address & static_cast<uint16_t>(~1);
    uint16_t word = memory.read16(alignedAddress);

    if ((address & 1) == 0) {
        // scriem byte-ul low
        word = static_cast<uint16_t>((word & 0xFF00) | value);
    } else {
        // scriem byte-ul high
        word = static_cast<uint16_t>((word & 0x00FF) | (value << 8));
    }

    memory.write16(alignedAddress, word);
}

void loadProgram(IMemory& memory, uint16_t startAddress, const std::vector<uint8_t>& program) {
    for (uint16_t i = 0; i < program.size(); i++) {
        writeByte(memory, startAddress + i, program[i]);
    }
}

int main(void) {
    IMemory* memory = new Memory(65536);

    /*
        Program test:

        MOVI R1, 10
        MOVI R2, 3
        ADD  R1, R2
        STORE [0x2000], R1
        HALT

        Rezultat asteptat:
        R1 = 13
        Memory[0x2000] = 13
    */

    std::vector<uint8_t> program = {
        // MOVI R1, 10
        0x10, 0x01, 0x0A, 0x00,

        // MOVI R2, 3
        0x10, 0x02, 0x03, 0x00,

        // ADD R1, R2
        0x20, 0x01, 0x02,

        // STORE [0x2000], R1
        0x31, 0x01, 0x00, 0x20,

        // HALT
        0xFF
    };

    loadProgram(*memory, 0x0000, program);

    CPU* cpu = new CPU(*memory);

    cpu->cpu();

    std::cout << "Memory[0x2000] = "
              << memory->read16(0x2000)
              << std::endl;

    delete cpu;
    delete memory;

    return 0;
}