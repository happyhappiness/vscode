StoreEntry *
storeCreateEntry(const char *url, const char *log_url, request_flags flags, const HttpRequestMethod& method)
{
    StoreEntry *e = NULL;
    MemObject *mem = NULL;
    debugs(20, 3, "storeCreateEntry: '" << url << "'");

    e = new StoreEntry(url, log_url);
    e->lock_count = 1;          /* Note lock here w/o calling storeLock() */
    mem = e->mem_obj;
    mem->method = method;

    if (neighbors_do_private_keys || !flags.hierarchical)
        e->setPrivateKey();
    else
        e->setPublicKey();

    if (flags.cachable) {
        EBIT_SET(e->flags, ENTRY_CACHABLE);
        EBIT_CLR(e->flags, RELEASE_REQUEST);
    } else {
        /* StoreEntry::releaseRequest() clears ENTRY_CACHABLE */
        e->releaseRequest();
    }

    e->store_status = STORE_PENDING;
    e->setMemStatus(NOT_IN_MEMORY);
    e->swap_status = SWAPOUT_NONE;
    e->swap_filen = -1;
    e->swap_dirn = -1;
    e->refcount = 0;
    e->lastref = squid_curtime;
    e->timestamp = -1;          /* set in StoreEntry::timestampsSet() */
    e->ping_status = PING_NONE;
    EBIT_SET(e->flags, ENTRY_VALIDATED);
    return e;
}