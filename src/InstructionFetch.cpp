#include "./../inc/InstructionFetch.hpp"


InstructionFetch::InstructionFetch(ILoadStore& loadStore)
    : ip(0), loadStore(loadStore) {
}

FetchWindow InstructionFetch::instruction_fetch() {
    FetchWindow window;

    window.address = ip;
    window.data = loadStore.requestInstructionFetch(ip);

    return window;
}

void InstructionFetch::setIP(uint16_t newIP) {
    ip = newIP;
}

uint16_t InstructionFetch::getIP() const {
    return ip;
}

void InstructionFetch::advanceIP(uint16_t bytes) {
    ip += bytes;
}