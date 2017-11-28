void
MemPoolChunked::createChunk()
{
    MemChunk *chunk, *newChunk;

    newChunk = new MemChunk(this);

    chunk = Chunks;
    if (chunk == NULL) {	/* first chunk in pool */
        Chunks = newChunk;
        return;
    }
    if (newChunk->objCache < chunk->objCache) {
        /* we are lowest ram chunk, insert as first chunk */
        newChunk->next = chunk;
        Chunks = newChunk;
        return;
    }
    while (chunk->next) {
        if (newChunk->objCache < chunk->next->objCache) {
            /* new chunk is in lower ram, insert here */
            newChunk->next = chunk->next;
            chunk->next = newChunk;
            return;
        }
        chunk = chunk->next;
    }
    /* we are the worst chunk in chain, add as last */
    chunk->next = newChunk;
}