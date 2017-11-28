MemImplementingAllocator *
memPoolIterateNext(MemPoolIterator * iter)
{
    MemImplementingAllocator *pool;
    assert(iter != NULL);

    pool = iter->pool;
    if (!pool)
        return NULL;

    iter->pool = pool->next;
    return pool;
}