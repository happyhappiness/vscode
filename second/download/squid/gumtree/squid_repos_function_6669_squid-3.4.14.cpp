static int
memCompObjChunks(void *const &obj, MemChunk * const &chunk)
{
    /* object is lower in memory than the chunks arena */
    if (obj < chunk->objCache)
        return -1;
    /* object is within the pool */
    if (obj < (void *) ((char *) chunk->objCache + chunk->pool->chunk_size))
        return 0;
    /* object is above the pool */
    return 1;
}