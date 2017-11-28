void
MemPoolChunked::convertFreeCacheToChunkFreeCache()
{
    void *Free;
    /*
     * OK, so we have to go through all the global freeCache and find the Chunk
     * any given Free belongs to, and stuff it into that Chunk's freelist
     */

    while ((Free = freeCache) != NULL) {
        MemChunk *chunk = NULL;
        chunk = const_cast<MemChunk *>(*allChunks.find(Free, memCompObjChunks));
        assert(splayLastResult == 0);
        assert(chunk->inuse_count > 0);
        -- chunk->inuse_count;
        (void) VALGRIND_MAKE_MEM_DEFINED(Free, sizeof(void *));
        freeCache = *(void **)Free; /* remove from global cache */
        *(void **)Free = chunk->freeList;   /* stuff into chunks freelist */
        (void) VALGRIND_MAKE_MEM_NOACCESS(Free, sizeof(void *));
        chunk->freeList = Free;
        chunk->lastref = squid_curtime;
    }

}