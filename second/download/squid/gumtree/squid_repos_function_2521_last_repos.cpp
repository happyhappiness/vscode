int
StoreEntry::validToSend() const
{
    if (EBIT_TEST(flags, RELEASE_REQUEST))
        return 0;

    if (EBIT_TEST(flags, ENTRY_NEGCACHED))
        if (expires <= squid_curtime)
            return 0;

    if (EBIT_TEST(flags, ENTRY_ABORTED))
        return 0;

    // now check that the entry has a cache backing or is collapsed
    if (swap_filen > -1) // backed by a disk cache
        return 1;

    if (swappingOut()) // will be backed by a disk cache
        return 1;

    if (!mem_obj) // not backed by a memory cache and not collapsed
        return 0;

    // StoreEntry::storeClientType() assumes DISK_CLIENT here, but there is no
    // disk cache backing that store_client constructor will assert. XXX: This
    // is wrong for range requests (that could feed off nibbled memory) and for
    // entries backed by the shared memory cache (that could, in theory, get
    // nibbled bytes from that cache, but there is no such "memoryIn" code).
    if (mem_obj->inmem_lo) // in memory cache, but got nibbled at
        return 0;

    // The following check is correct but useless at this position. TODO: Move
    // it up when the shared memory cache can either replenish locally nibbled
    // bytes or, better, does not use local RAM copy at all.
    // if (mem_obj->memCache.index >= 0) // backed by a shared memory cache
    //    return 1;

    return 1;
}