#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP

#include <cstdint>

constexpr uint8_t REGISTER_COUNT = 8;

enum class Opcode : uint8_t {
    NOP   = 0x00,

    MOVI  = 0x10, // MOV reg, imm16

    ADD   = 0x20, // ADD dst, src
    SUB   = 0x21, // SUB dst, src
    DIV   = 0x22, // DIV dst, src

    LOAD  = 0x30, // LOAD dst, [addr16]
    STORE = 0x31, // STORE [addr16], src

    JMP   = 0x40, // JMP addr16
    JZ    = 0x41, // JZ addr16

    HALT  = 0xFF,

    INVALID = 0xFE
};

struct DecodedInstruction {
    Opcode opcode = Opcode::INVALID;

    uint16_t instructionAddress = 0;
    uint8_t size = 0; // dimensiunea instrucțiunii în bytes

    uint8_t dstReg = 0;
    uint8_t srcReg = 0;

    uint16_t immediate = 0;
    uint16_t memoryAddress = 0;

    bool valid = false;
    bool complete = false;
};

enum class ExecuteStatus {
    Ok,
    Halted,
    InvalidInstruction,
    InvalidRegister,
    DivideByZero,
    MisalignedAccess
};

struct ExecuteResult {
    ExecuteStatus status = ExecuteStatus::Ok;

    bool ipChanged = false;
    uint16_t newIP = 0;
};

#endif