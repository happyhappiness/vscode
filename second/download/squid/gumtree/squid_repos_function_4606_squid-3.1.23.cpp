static StoreEntry *
storeCossAddDiskRestore(CossSwapDir * SD, const cache_key * key,
                        int file_number,
                        uint64_t swap_file_sz,
                        time_t expires,
                        time_t timestamp,
                        time_t lastref,
                        time_t lastmod,
                        u_int32_t refcount,
                        u_int16_t flags,
                        int clean)
{
    StoreEntry *e = NULL;
    debugs(47, 5, "storeCossAddDiskRestore: " << storeKeyText(key)  <<
           ", fileno="<< std::setfill('0') << std::hex << std::uppercase <<
           std::setw(8) << file_number);

    /* if you call this you'd better be sure file_number is not
     * already in use! */
    e = new StoreEntry();
    e->store_status = STORE_OK;
    e->swap_dirn = SD->index;
    e->setMemStatus(NOT_IN_MEMORY);
    e->swap_status = SWAPOUT_DONE;
    e->swap_filen = file_number;
    e->swap_file_sz = swap_file_sz;
    e->lock_count = 0;
    e->lastref = lastref;
    e->timestamp = timestamp;
    e->expires = expires;
    e->lastmod = lastmod;
    e->refcount = refcount;
    e->flags = flags;
    EBIT_SET(e->flags, ENTRY_CACHABLE);
    EBIT_CLR(e->flags, RELEASE_REQUEST);
    EBIT_CLR(e->flags, KEY_PRIVATE);
    e->ping_status = PING_NONE;
    EBIT_CLR(e->flags, ENTRY_VALIDATED);
    e->hashInsert(key);	/* do it after we clear KEY_PRIVATE */
    storeCossAdd(SD, e);
    assert(e->swap_filen >= 0);
    return e;
}