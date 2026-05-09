#include "./../inc/Memory.hpp"
#include "./../inc/CPU.hpp"

int main(void) {

    IMemory* memory = new Memory(5);
    CPU* cpu = new CPU(*memory);

    cpu->cpu();

    return 0;
}