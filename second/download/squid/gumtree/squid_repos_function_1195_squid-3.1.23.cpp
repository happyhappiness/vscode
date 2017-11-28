void
memFreeString(size_t size, void *buf)
{
    int i;
    MemAllocator *pool = NULL;
    assert(size && buf);

    for (i = 0; i < mem_str_pool_count; i++) {
        if (size <= StrPoolsAttrs[i].obj_size) {
            assert(size == StrPoolsAttrs[i].obj_size);
            pool = StrPools[i].pool;
            break;
        }
    }

    memMeterDec(StrCountMeter);
    memMeterDel(StrVolumeMeter, size);
    pool ? pool->free(buf) : xfree(buf);
}