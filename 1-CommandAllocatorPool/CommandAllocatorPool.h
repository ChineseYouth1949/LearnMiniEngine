#pragma once

#include <vector>
#include <queue>
#include <mutex>
#include <stdint.h>

class CommandAllocatorPool
{
public:
    CommandAllocatorPool(D3D12_COMMAND_LIST_TYPE Type);
    ~CommandAllocatorPool();

    void Initialize(ID3D12Device* pDevice);
    void Reset();

    ID3D12CommandAllocator* RequestAllocator(uint64_t CompletedFenceValue);
    void DiscardAllocator(uint64_t FenceValue, ID3D12CommandAllocator* Allocator);

    inline size_t Size() { return mAllocatorPool.size(); }

private:

    const D3D12_COMMAND_LIST_TYPE mCommandListType;                           

    ID3D12Device* mDevice;       
    std::vector<ID3D12CommandAllocator*> mAllocatorPool;         
    std::queue<std::pair<uint64_t, ID3D12CommandAllocator*>> mReadyAllocators;  
    std::mutex mAllocatorMutex;                                                 
};