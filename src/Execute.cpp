#include "./../inc/Execute.hpp"

Execute::Execute(ILoadStore& loadStore)
    : loadStore(loadStore) {
}

bool Execute::isRegisterValid(uint8_t reg) const {
    return reg < REGISTER_COUNT;
}

bool Execute::isAligned16(uint16_t address) const {
    return (address % 2) == 0;
}

void Execute::updateZeroFlag(uint16_t value) {
    zeroFlag = (value == 0);
}

ExecuteResult Execute::execute_instruction(const DecodedInstruction& instruction) {
    ExecuteResult result;

    if (!instruction.complete || !instruction.valid) {
        result.status = ExecuteStatus::InvalidInstruction;
        return result;
    }

    switch (instruction.opcode) {
    case Opcode::NOP:
        result.status = ExecuteStatus::Ok;
        break;

    case Opcode::HALT:
        halted = true;
        result.status = ExecuteStatus::Halted;
        break;

    case Opcode::MOVI:
        if (!isRegisterValid(instruction.dstReg)) {
            result.status = ExecuteStatus::InvalidRegister;
            return result;
        }

        registers[instruction.dstReg] = instruction.immediate;
        updateZeroFlag(registers[instruction.dstReg]);

        result.status = ExecuteStatus::Ok;
        break;

    case Opcode::ADD:
        if (!isRegisterValid(instruction.dstReg) ||
            !isRegisterValid(instruction.srcReg)) {
            result.status = ExecuteStatus::InvalidRegister;
            return result;
        }

        registers[instruction.dstReg] =
            static_cast<uint16_t>(
                registers[instruction.dstReg] + registers[instruction.srcReg]
            );

        updateZeroFlag(registers[instruction.dstReg]);

        result.status = ExecuteStatus::Ok;
        break;

    case Opcode::SUB:
        if (!isRegisterValid(instruction.dstReg) ||
            !isRegisterValid(instruction.srcReg)) {
            result.status = ExecuteStatus::InvalidRegister;
            return result;
        }

        registers[instruction.dstReg] =
            static_cast<uint16_t>(
                registers[instruction.dstReg] - registers[instruction.srcReg]
            );

        updateZeroFlag(registers[instruction.dstReg]);

        result.status = ExecuteStatus::Ok;
        break;

    case Opcode::DIV:
        if (!isRegisterValid(instruction.dstReg) ||
            !isRegisterValid(instruction.srcReg)) {
            result.status = ExecuteStatus::InvalidRegister;
            return result;
        }

        if (registers[instruction.srcReg] == 0) {
            result.status = ExecuteStatus::DivideByZero;
            return result;
        }

        registers[instruction.dstReg] =
            static_cast<uint16_t>(
                registers[instruction.dstReg] / registers[instruction.srcReg]
            );

        updateZeroFlag(registers[instruction.dstReg]);

        result.status = ExecuteStatus::Ok;
        break;

    case Opcode::LOAD:
        if (!isRegisterValid(instruction.dstReg)) {
            result.status = ExecuteStatus::InvalidRegister;
            return result;
        }

        if (!isAligned16(instruction.memoryAddress)) {
            result.status = ExecuteStatus::MisalignedAccess;
            return result;
        }

        receive_memory_data(request_to_memory(instruction.memoryAddress));

        registers[instruction.dstReg] = lastMemoryData;
        updateZeroFlag(registers[instruction.dstReg]);

        result.status = ExecuteStatus::Ok;
        break;

    case Opcode::STORE:
        if (!isRegisterValid(instruction.srcReg)) {
            result.status = ExecuteStatus::InvalidRegister;
            return result;
        }

        if (!isAligned16(instruction.memoryAddress)) {
            result.status = ExecuteStatus::MisalignedAccess;
            return result;
        }

        request_to_memory(
            instruction.memoryAddress,
            registers[instruction.srcReg]
        );

        result.status = ExecuteStatus::Ok;
        break;

    case Opcode::JMP:
        result.ipChanged = true;
        result.newIP = instruction.memoryAddress;
        result.status = ExecuteStatus::Ok;
        break;

    case Opcode::JZ:
        if (zeroFlag) {
            result.ipChanged = true;
            result.newIP = instruction.memoryAddress;
        }

        result.status = ExecuteStatus::Ok;
        break;

    default:
        result.status = ExecuteStatus::InvalidInstruction;
        break;
    }

    return result;
}

uint16_t Execute::request_to_memory(uint16_t address) {
    return loadStore.load16(address);
}

void Execute::request_to_memory(uint16_t address, uint16_t value) {
    loadStore.store16(address, value);
}

void Execute::receive_memory_data(uint16_t value) {
    lastMemoryData = value;
}

uint16_t Execute::getRegister(uint8_t reg) const {
    if (!isRegisterValid(reg)) {
        return 0;
    }

    return registers[reg];
}

void Execute::setRegister(uint8_t reg, uint16_t value) {
    if (!isRegisterValid(reg)) {
        return;
    }

    registers[reg] = value;
    updateZeroFlag(value);
}

bool Execute::isHalted() const {
    return halted;
}

bool Execute::getZeroFlag() const {
    return zeroFlag;
}