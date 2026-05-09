    #include "ILoadStore.hpp"

    class LoadStore : public ILoadStore {
    public:
        LoadStore();
        // void request_to_memory() override;
        void dos() override;
    };