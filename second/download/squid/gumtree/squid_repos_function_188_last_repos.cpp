static void
xmemFree(memitem * item)
{
    extern MemPool *StringPool;
    assert(item && item->pool);
    if (StringPool == item->pool)
        return memStringFree(item->pool, item->my_ptr, item->size);
    else
        return memFree(item->pool, item->my_ptr);
}