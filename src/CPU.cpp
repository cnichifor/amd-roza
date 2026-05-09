#include "./../inc/CPU.hpp"

CPU::CPU(IMemory& memory) : 
    loadStore(std::make_unique<LoadStore>(memory)),
    instructionFetch(std::make_unique<InstructionFetch>(*loadStore)),
    decodeInstruction(std::make_unique<DecodeInstruction>()),
    execute(std::make_unique<Execute>(*loadStore)),
    isStopped(false),
    cycleCount(0)
{
    
}

void CPU::cpu()
{
    std::cout << "Starting CPU...\n";

    while (!isStopped) {
        std::cout << "Cycle " << cycleCount << "\n";

        // 1. FETCH
        FetchWindow window = instructionFetch->instruction_fetch();

        std::cout << "  IP = " << instructionFetch->getIP() << "\n";

        // 2. DECODE
        decodeInstruction->receive_memory_data(window);

        DecodedInstruction instruction = decodeInstruction->decode_instruction();

        if (!instruction.complete || !instruction.valid) {
            std::cout << "  Invalid or incomplete instruction\n";
            isStopped = true;
            break;
        }

        // 3. EXECUTE
        ExecuteResult result = execute->execute_instruction(instruction);

        // 4. VERIFICARE STATUS
        if (result.status == ExecuteStatus::Halted) {
            std::cout << "  HALT instruction executed\n";
            isStopped = true;
        } else if (result.status != ExecuteStatus::Ok) {
            std::cout << "  Execution error\n";
            isStopped = true;
        } else {
            // 5. UPDATE IP
            if (result.ipChanged) {
                instructionFetch->setIP(result.newIP);
            } else {
                instructionFetch->advanceIP(instruction.size);
            }
        }

        cycleCount++;

        if (cycleCount > 1000) {
            std::cout << "  Too many cycles. isStoppedping CPU.\n";
            isStopped = true;
        }
    }

    std::cout << "CPU isStoppedped after " << cycleCount << " cycles.\n";
}
