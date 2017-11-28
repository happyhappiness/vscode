void
MemPools::flushMeters()
{
    TheMeter.flush();

    MemPoolIterator *iter = memPoolIterate();
    while (MemImplementingAllocator *pool = memPoolIterateNext(iter)) {
        pool->flushMetersFull();
        // are these TheMeter grow() operations or accumulated volumes ?
        TheMeter.alloc += pool->getMeter().alloc.currentLevel() * pool->obj_size;
        TheMeter.inuse += pool->getMeter().inuse.currentLevel() * pool->obj_size;
        TheMeter.idle += pool->getMeter().idle.currentLevel() * pool->obj_size;

        TheMeter.gb_allocated.count += pool->getMeter().gb_allocated.count;
        TheMeter.gb_saved.count += pool->getMeter().gb_saved.count;
        TheMeter.gb_freed.count += pool->getMeter().gb_freed.count;
        TheMeter.gb_allocated.bytes += pool->getMeter().gb_allocated.bytes;
        TheMeter.gb_saved.bytes += pool->getMeter().gb_saved.bytes;
        TheMeter.gb_freed.bytes += pool->getMeter().gb_freed.bytes;
    }
    memPoolIterateDone(&iter);
}