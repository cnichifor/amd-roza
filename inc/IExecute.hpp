#ifndef IEXECUTE_HPP
#define IEXECUTE_HPP

#include <cstdint>

#include "Instruction.hpp"

class IExecute {
public:
    virtual ExecuteResult execute_instruction(const DecodedInstruction& instruction) = 0;

    virtual uint16_t getRegister(uint8_t reg) const = 0;
    virtual void setRegister(uint8_t reg, uint16_t value) = 0;

    virtual bool isHalted() const = 0;
    virtual bool getZeroFlag() const = 0;

    virtual ~IExecute() = default;
};

#endif