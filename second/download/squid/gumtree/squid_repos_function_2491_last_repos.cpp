StoreEntry *
storeCreatePureEntry(const char *url, const char *log_url, const RequestFlags &flags, const HttpRequestMethod& method)
{
    StoreEntry *e = NULL;
    debugs(20, 3, "storeCreateEntry: '" << url << "'");

    e = new StoreEntry();
    e->makeMemObject();
    e->mem_obj->setUris(url, log_url, method);

    if (flags.cachable) {
        EBIT_CLR(e->flags, RELEASE_REQUEST);
    } else {
        e->releaseRequest();
    }

    e->store_status = STORE_PENDING;
    e->refcount = 0;
    e->lastref = squid_curtime;
    e->timestamp = -1;          /* set in StoreEntry::timestampsSet() */
    e->ping_status = PING_NONE;
    EBIT_SET(e->flags, ENTRY_VALIDATED);
    return e;
}