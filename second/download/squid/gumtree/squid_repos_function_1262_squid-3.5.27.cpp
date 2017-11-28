void *
memAllocString(size_t net_size, size_t * gross_size)
{
    MemAllocator *pool = NULL;
    assert(gross_size);

    // if pools are not yet ready, make sure that
    // the requested size is not poolable so that the right deallocator
    // will be used
    if (!MemIsInitialized && net_size < SmallestStringBeforeMemIsInitialized)
        net_size = SmallestStringBeforeMemIsInitialized;

    unsigned int i;
    for (i = 0; i < mem_str_pool_count; ++i) {
        if (net_size <= StrPoolsAttrs[i].obj_size) {
            pool = StrPools[i].pool;
            break;
        }
    }

    *gross_size = pool ? StrPoolsAttrs[i].obj_size : net_size;
    assert(*gross_size >= net_size);
    // may forget [de]allocations until MemIsInitialized
    memMeterInc(StrCountMeter);
    memMeterAdd(StrVolumeMeter, *gross_size);
    return pool ? pool->alloc() : xcalloc(1, net_size);
}