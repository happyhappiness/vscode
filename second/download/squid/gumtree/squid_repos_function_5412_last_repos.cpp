int
Mem::AllocatorProxy::getStats(MemPoolStats * stats)
{
    return getAllocator()->getStats(stats);
}