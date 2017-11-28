int
memPoolInUseCount(MemAllocator * pool)
{
    return pool->inUseCount();
}