#ifndef EXECUTE_HPP
#define EXECUTE_HPP

#include <array>
#include <cstdint>

#include "IExecute.hpp"
#include "Instruction.hpp"
#include "ILoadStore.hpp"

class Execute : public IExecute {
private:
    ILoadStore& loadStore;

    std::array<uint16_t, REGISTER_COUNT> registers{};

    bool zeroFlag = false;
    bool halted = false;

    uint16_t lastMemoryData = 0;

    bool isRegisterValid(uint8_t reg) const;
    bool isAligned16(uint16_t address) const;

    void updateZeroFlag(uint16_t value);

    uint16_t request_to_memory(uint16_t address);
    void request_to_memory(uint16_t address, uint16_t value);

    void receive_memory_data(uint16_t value);

public:
    explicit Execute(ILoadStore& loadStore);

    ExecuteResult execute_instruction(const DecodedInstruction& instruction) override;

    uint16_t getRegister(uint8_t reg) const override;
    void setRegister(uint8_t reg, uint16_t value) override;

    bool isHalted() const override;
    bool getZeroFlag() const override;
};

#endif