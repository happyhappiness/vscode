int
MemAllocatorProxy::getStats(MemPoolStats * stats)
{
    return getAllocator()->getStats(stats);
}