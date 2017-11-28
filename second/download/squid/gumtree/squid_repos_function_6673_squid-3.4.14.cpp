void
MemPoolChunked::setChunkSize(size_t chunksize)
{
    int cap;
    size_t csize = chunksize;

    if (Chunks)		/* unsafe to tamper */
        return;

    csize = ((csize + MEM_PAGE_SIZE - 1) / MEM_PAGE_SIZE) * MEM_PAGE_SIZE;	/* round up to page size */
    cap = csize / obj_size;

    if (cap < MEM_MIN_FREE)
        cap = MEM_MIN_FREE;
    if (cap * obj_size > MEM_CHUNK_MAX_SIZE)
        cap = MEM_CHUNK_MAX_SIZE / obj_size;
    if (cap > MEM_MAX_FREE)
        cap = MEM_MAX_FREE;
    if (cap < 1)
        cap = 1;

    csize = cap * obj_size;
    csize = ((csize + MEM_PAGE_SIZE - 1) / MEM_PAGE_SIZE) * MEM_PAGE_SIZE;	/* round up to page size */
    cap = csize / obj_size;

    chunk_capacity = cap;
    chunk_size = csize;
}