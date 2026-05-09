#pragma once

#include "Instruction.hpp"
#include "InstructionFetch.hpp"

class IDecodeInstruction {
public:
    virtual void receive_memory_data(const FetchWindow& window) = 0;

    virtual DecodedInstruction decode_instruction() = 0;

    virtual DecodedInstruction send_data_to_execute() const = 0;

    virtual bool request_to_memory() const = 0;

    virtual ~IDecodeInstruction() = default;
};
