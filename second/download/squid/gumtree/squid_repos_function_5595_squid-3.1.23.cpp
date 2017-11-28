void *
MemPoolChunked::get()
{
    void **Free;

    saved_calls++;

    /* first, try cache */
    if (freeCache) {
        Free = (void **)freeCache;
        (void) VALGRIND_MAKE_MEM_DEFINED(Free, obj_size);
        freeCache = *Free;
        *Free = NULL;
        return Free;
    }
    /* then try perchunk freelist chain */
    if (nextFreeChunk == NULL) {
        /* no chunk with frees, so create new one */
        saved_calls--; // compensate for the ++ above
        createChunk();
    }
    /* now we have some in perchunk freelist chain */
    MemChunk *chunk = nextFreeChunk;

    Free = (void **)chunk->freeList;
    chunk->freeList = *Free;
    *Free = NULL;
    chunk->inuse_count++;
    chunk->lastref = squid_curtime;

    if (chunk->freeList == NULL) {
        /* last free in this chunk, so remove us from perchunk freelist chain */
        nextFreeChunk = chunk->nextFreeChunk;
    }
    (void) VALGRIND_MAKE_MEM_DEFINED(Free, obj_size);
    return Free;
}