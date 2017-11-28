int
Mem::AllocatorProxy::inUseCount() const
{
    if (!theAllocator)
        return 0;
    else
        return theAllocator->inUseCount();
}