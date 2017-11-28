void
MemPoolChunked::clean(time_t maxage)
{
    MemChunk *chunk, *freechunk, *listTail;
    time_t age;

    if (!Chunks)
        return;

    flushMetersFull();
    convertFreeCacheToChunkFreeCache();
    /* Now we have all chunks in this pool cleared up, all free items returned to their home */
    /* We start now checking all chunks to see if we can release any */
    /* We start from Chunks->next, so first chunk is not released */
    /* Recreate nextFreeChunk list from scratch */

    chunk = Chunks;
    while ((freechunk = chunk->next) != NULL) {
        age = squid_curtime - freechunk->lastref;
        freechunk->nextFreeChunk = NULL;
        if (freechunk->inuse_count == 0)
            if (age >= maxage) {
                chunk->next = freechunk->next;
                delete freechunk;
                freechunk = NULL;
            }
        if (chunk->next == NULL)
            break;
        chunk = chunk->next;
    }

    /* Recreate nextFreeChunk list from scratch */
    /* Populate nextFreeChunk list in order of "most filled chunk first" */
    /* in case of equal fill, put chunk in lower ram first */
    /* First (create time) chunk is always on top, no matter how full */

    chunk = Chunks;
    nextFreeChunk = chunk;
    chunk->nextFreeChunk = NULL;

    while (chunk->next) {
        chunk->next->nextFreeChunk = NULL;
        if (chunk->next->inuse_count < chunk_capacity) {
            listTail = nextFreeChunk;
            while (listTail->nextFreeChunk) {
                if (chunk->next->inuse_count > listTail->nextFreeChunk->inuse_count)
                    break;
                if ((chunk->next->inuse_count == listTail->nextFreeChunk->inuse_count) &&
                        (chunk->next->objCache < listTail->nextFreeChunk->objCache))
                    break;
                listTail = listTail->nextFreeChunk;
            }
            chunk->next->nextFreeChunk = listTail->nextFreeChunk;
            listTail->nextFreeChunk = chunk->next;
        }
        chunk = chunk->next;
    }
    /* We started from 2nd chunk. If first chunk is full, remove it */
    if (nextFreeChunk->inuse_count == chunk_capacity)
        nextFreeChunk = nextFreeChunk->nextFreeChunk;

    return;
}