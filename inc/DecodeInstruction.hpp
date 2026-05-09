#ifndef DECODE_INSTRUCTION_HPP
#define DECODE_INSTRUCTION_HPP

#include <cstdint>

#include "IDecodeInstruction.hpp"
#include "Instruction.hpp"
#include "InstructionFetch.hpp"

class DecodeInstruction : public IDecodeInstruction {
private:
    FetchWindow currentWindow{};
    DecodedInstruction lastDecoded{};

    bool hasWindow = false;
    bool needsMoreData = false;

    static uint8_t getByte(uint64_t data, uint8_t index);
    static uint16_t getWord16(uint64_t data, uint8_t index);

    bool isRegisterValid(uint8_t reg) const;

public:
    DecodeInstruction() = default;

    void receive_memory_data(const FetchWindow& window) override;

    DecodedInstruction decode_instruction() override;

    DecodedInstruction send_data_to_execute() const override;

    bool request_to_memory() const override;
};

#endif