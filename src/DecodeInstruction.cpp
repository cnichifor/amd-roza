#include "./../inc/DecodeInstruction.hpp"

uint8_t DecodeInstruction::getByte(uint64_t data, uint8_t index)
{
    return static_cast<uint8_t>((data >> (8 * index)) & 0xFF);
}

uint16_t DecodeInstruction::getWord16(uint64_t data, uint8_t index)
{
    uint8_t low = getByte(data, index);
    uint8_t high = getByte(data, index + 1);

    return static_cast<uint16_t>(low | (high << 8));
}

bool DecodeInstruction::isRegisterValid(uint8_t reg) const
{
    return reg < REGISTER_COUNT;
}

void DecodeInstruction::receive_memory_data(const FetchWindow& window)
{
    currentWindow = window;
    hasWindow = true;
    needsMoreData = false;
}

DecodedInstruction DecodeInstruction::decode_instruction()
{
    DecodedInstruction instruction;

    if (!hasWindow) {
        needsMoreData = true;
        lastDecoded = instruction;
        return instruction;
    }

    instruction.instructionAddress = currentWindow.address;

    uint8_t rawOpcode = getByte(currentWindow.data, 0);
    instruction.opcode = static_cast<Opcode>(rawOpcode);

    switch (instruction.opcode) {
    case Opcode::NOP:
        instruction.size = 1;
        instruction.valid = true;
        instruction.complete = true;
        break;

    case Opcode::HALT:
        instruction.size = 1;
        instruction.valid = true;
        instruction.complete = true;
        break;

    case Opcode::MOVI:
        instruction.size = 4;
        instruction.dstReg = getByte(currentWindow.data, 1);
        instruction.immediate = getWord16(currentWindow.data, 2);

        instruction.valid = isRegisterValid(instruction.dstReg);
        instruction.complete = true;
        break;

    case Opcode::ADD:
    case Opcode::SUB:
    case Opcode::DIV:
        instruction.size = 3;
        instruction.dstReg = getByte(currentWindow.data, 1);
        instruction.srcReg = getByte(currentWindow.data, 2);

        instruction.valid =
            isRegisterValid(instruction.dstReg) &&
            isRegisterValid(instruction.srcReg);

        instruction.complete = true;
        break;

    case Opcode::LOAD:
        instruction.size = 4;
        instruction.dstReg = getByte(currentWindow.data, 1);
        instruction.memoryAddress = getWord16(currentWindow.data, 2);

        instruction.valid = isRegisterValid(instruction.dstReg);
        instruction.complete = true;
        break;

    case Opcode::STORE:
        instruction.size = 4;
        instruction.srcReg = getByte(currentWindow.data, 1);
        instruction.memoryAddress = getWord16(currentWindow.data, 2);

        instruction.valid = isRegisterValid(instruction.srcReg);
        instruction.complete = true;
        break;

    case Opcode::JMP:
    case Opcode::JZ:
        instruction.size = 3;
        instruction.memoryAddress = getWord16(currentWindow.data, 1);

        instruction.valid = true;
        instruction.complete = true;
        break;

    default:
        instruction.opcode = Opcode::INVALID;
        instruction.size = 1;
        instruction.valid = false;
        instruction.complete = true;
        break;
    }

    needsMoreData = false;
    lastDecoded = instruction;

    return instruction;
}

DecodedInstruction DecodeInstruction::send_data_to_execute() const
{
    return lastDecoded;
}

bool DecodeInstruction::request_to_memory() const
{
    return needsMoreData;
}