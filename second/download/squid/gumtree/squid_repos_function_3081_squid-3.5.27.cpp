bool
StoreEntry::memoryCachable()
{
    if (!checkCachable())
        return 0;

    if (mem_obj == NULL)
        return 0;

    if (mem_obj->data_hdr.size() == 0)
        return 0;

    if (mem_obj->inmem_lo != 0)
        return 0;

    if (!Config.onoff.memory_cache_first && swap_status == SWAPOUT_DONE && refcount == 1)
        return 0;

    return 1;
}