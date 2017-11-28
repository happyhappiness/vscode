StoreEntry *
Fs::Ufs::UFSSwapDir::addDiskRestore(const cache_key * key,
                                    sfileno file_number,
                                    uint64_t swap_file_sz,
                                    time_t expires,
                                    time_t timestamp,
                                    time_t lastref,
                                    time_t lastmod,
                                    uint32_t refcount,
                                    uint16_t newFlags,
                                    int clean)
{
    StoreEntry *e = NULL;
    debugs(47, 5, HERE << storeKeyText(key)  <<
           ", fileno="<< std::setfill('0') << std::hex << std::uppercase << std::setw(8) << file_number);
    /* if you call this you'd better be sure file_number is not
     * already in use! */
    e = new StoreEntry();
    e->store_status = STORE_OK;
    e->setMemStatus(NOT_IN_MEMORY);
    e->swap_status = SWAPOUT_DONE;
    e->swap_filen = file_number;
    e->swap_dirn = index;
    e->swap_file_sz = swap_file_sz;
    e->lastref = lastref;
    e->timestamp = timestamp;
    e->expires = expires;
    e->lastModified(lastmod);
    e->refcount = refcount;
    e->flags = newFlags;
    EBIT_CLR(e->flags, RELEASE_REQUEST);
    e->clearPrivate();
    e->ping_status = PING_NONE;
    EBIT_CLR(e->flags, ENTRY_VALIDATED);
    mapBitSet(e->swap_filen);
    cur_size += fs.blksize * sizeInBlocks(e->swap_file_sz);
    ++n_disk_objects;
    e->hashInsert(key); /* do it after we clear KEY_PRIVATE */
    replacementAdd (e);
    return e;
}