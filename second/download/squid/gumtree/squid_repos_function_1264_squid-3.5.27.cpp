void
memFreeString(size_t size, void *buf)
{
    MemAllocator *pool = NULL;
    assert(buf);

    if (MemIsInitialized) {
        for (unsigned int i = 0; i < mem_str_pool_count; ++i) {
            if (size <= StrPoolsAttrs[i].obj_size) {
                assert(size == StrPoolsAttrs[i].obj_size);
                pool = StrPools[i].pool;
                break;
            }
        }
    }

    // may forget [de]allocations until MemIsInitialized
    memMeterDec(StrCountMeter);
    memMeterDel(StrVolumeMeter, size);
    pool ? pool->freeOne(buf) : xfree(buf);
}