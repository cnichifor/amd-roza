class Memory : public IMemory {
private:
    std::vector<uint8_t> data;

public:
    Memory(std::size_t size);

    uint16_t read16(uint16_t address) override;
    void write16(uint16_t address, uint16_t value) override;
    uint64_t read64(uint16_t address) override;
};