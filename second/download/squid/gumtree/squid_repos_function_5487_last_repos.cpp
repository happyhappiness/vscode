int
MemPoolMalloc::getStats(MemPoolStats * stats, int accumulate)
{
    if (!accumulate)    /* need skip memset for GlobalStats accumulation */
        memset(stats, 0, sizeof(MemPoolStats));

    stats->pool = this;
    stats->label = objectType();
    stats->meter = &meter;
    stats->obj_size = obj_size;
    stats->chunk_capacity = 0;

    stats->chunks_alloc += 0;
    stats->chunks_inuse += 0;
    stats->chunks_partial += 0;
    stats->chunks_free += 0;

    stats->items_alloc += meter.alloc.currentLevel();
    stats->items_inuse += meter.inuse.currentLevel();
    stats->items_idle += meter.idle.currentLevel();

    stats->overhead += sizeof(MemPoolMalloc) + strlen(objectType()) + 1;

    return meter.inuse.currentLevel();
}