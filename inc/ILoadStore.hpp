#pragma once

class ILoadStore {
public:
    virtual void request_to_memory() = 0;
};