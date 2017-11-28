static void *
xmemAlloc(memitem * item)
{
    extern MemPool *StringPool;
    assert(item && item->pool);
    if (StringPool == item->pool)
        return memStringAlloc(item->pool, item->size);
    else
        return memAlloc(item->pool);
}