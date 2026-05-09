#pragma once
#include "IDecodeInstruction.hpp"

class DecodeInstruction : public IDecodeInstruction {
public:
    DecodeInstruction();
    void decodeInstruction() override; 
};