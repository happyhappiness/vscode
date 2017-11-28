MemAllocator *
MemAllocatorProxy::getAllocator() const
{
    if (!theAllocator)
        theAllocator = MemPools::GetInstance().create(objectType(), size);
    return theAllocator;
}