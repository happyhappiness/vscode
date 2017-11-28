MemAllocator *
Mem::AllocatorProxy::getAllocator() const
{
    if (!theAllocator) {
        theAllocator = MemPools::GetInstance().create(objectType(), size);
        theAllocator->zeroBlocks(doZero);
    }
    return theAllocator;
}