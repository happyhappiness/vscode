void
MemPools::flushMeters()
{
    MemImplementingAllocator *pool;
    MemPoolIterator *iter;

    TheMeter.flush();

    iter = memPoolIterate();
    while ((pool = memPoolIterateNext(iter))) {
        pool->flushMetersFull();
        memMeterAdd(TheMeter.alloc, pool->getMeter().alloc.level * pool->obj_size);
        memMeterAdd(TheMeter.inuse, pool->getMeter().inuse.level * pool->obj_size);
        memMeterAdd(TheMeter.idle, pool->getMeter().idle.level * pool->obj_size);
        TheMeter.gb_allocated.count += pool->getMeter().gb_allocated.count;
        TheMeter.gb_saved.count += pool->getMeter().gb_saved.count;
        TheMeter.gb_freed.count += pool->getMeter().gb_freed.count;
        TheMeter.gb_allocated.bytes += pool->getMeter().gb_allocated.bytes;
        TheMeter.gb_saved.bytes += pool->getMeter().gb_saved.bytes;
        TheMeter.gb_freed.bytes += pool->getMeter().gb_freed.bytes;
    }
    memPoolIterateDone(&iter);
}