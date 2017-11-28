void
MemPools::clean(time_t maxage)
{
    flushMeters();
    if (mem_idle_limit < 0) // no limit to enforce
        return;

    int shift = 1;
    if (TheMeter.idle.level > mem_idle_limit)
        maxage = shift = 0;

    MemImplementingAllocator *pool;
    MemPoolIterator *iter;
    iter = memPoolIterate();
    while ((pool = memPoolIterateNext(iter)))
        if (pool->idleTrigger(shift))
            pool->clean(maxage);
    memPoolIterateDone(&iter);
}