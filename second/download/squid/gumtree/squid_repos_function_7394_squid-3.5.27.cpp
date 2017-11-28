int
MemAllocatorProxy::inUseCount() const
{
    if (!theAllocator)
        return 0;
    else
        return memPoolInUseCount(theAllocator);
}