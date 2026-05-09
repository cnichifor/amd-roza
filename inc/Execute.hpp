    #include "IExecute.hpp"

    class Execute : public IExecute {
    public:
        Execute();
        void execute_instruction() override;
    };