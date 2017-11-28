int
MemPoolChunked::getStats(MemPoolStats * stats, int accumulate)
{
    MemChunk *chunk;
    int chunks_free = 0;
    int chunks_partial = 0;

    if (!accumulate)    /* need skip memset for GlobalStats accumulation */
        memset(stats, 0, sizeof(MemPoolStats));

    clean((time_t) 555555); /* don't want to get chunks released before reporting */

    stats->pool = this;
    stats->label = objectType();
    stats->meter = &meter;
    stats->obj_size = obj_size;
    stats->chunk_capacity = chunk_capacity;

    /* gather stats for each Chunk */
    chunk = Chunks;
    while (chunk) {
        if (chunk->inuse_count == 0)
            ++chunks_free;
        else if (chunk->inuse_count < chunk_capacity)
            ++chunks_partial;
        chunk = chunk->next;
    }

    stats->chunks_alloc += chunkCount;
    stats->chunks_inuse += chunkCount - chunks_free;
    stats->chunks_partial += chunks_partial;
    stats->chunks_free += chunks_free;

    stats->items_alloc += meter.alloc.currentLevel();
    stats->items_inuse += meter.inuse.currentLevel();
    stats->items_idle += meter.idle.currentLevel();

    stats->overhead += sizeof(MemPoolChunked) + chunkCount * sizeof(MemChunk) + strlen(objectType()) + 1;

    return meter.inuse.currentLevel();
}