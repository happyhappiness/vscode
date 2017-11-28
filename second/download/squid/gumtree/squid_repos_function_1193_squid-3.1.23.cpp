void *
memAllocString(size_t net_size, size_t * gross_size)
{
    int i;
    MemAllocator *pool = NULL;
    assert(gross_size);

    for (i = 0; i < mem_str_pool_count; i++) {
        if (net_size <= StrPoolsAttrs[i].obj_size) {
            pool = StrPools[i].pool;
            break;
        }
    }

    *gross_size = pool ? StrPoolsAttrs[i].obj_size : net_size;
    assert(*gross_size >= net_size);
    memMeterInc(StrCountMeter);
    memMeterAdd(StrVolumeMeter, *gross_size);
    return pool ? pool->alloc() : xcalloc(1, net_size);
}