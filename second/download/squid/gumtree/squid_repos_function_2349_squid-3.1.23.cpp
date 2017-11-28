const ipcache_addrs *
ipcache_gethostbyname(const char *name, int flags)
{
    ipcache_entry *i = NULL;
    ipcache_addrs *addrs;
    assert(name);
    debugs(14, 3, "ipcache_gethostbyname: '" << name  << "', flags=" << std::hex << flags);
    IpcacheStats.requests++;
    i = ipcache_get(name);

    if (NULL == i) {
        (void) 0;
    } else if (ipcacheExpiredEntry(i)) {
        ipcacheRelease(i);
        i = NULL;
    } else if (i->flags.negcached) {
        IpcacheStats.negative_hits++;
        // ignore i->error_message: the caller just checks IP cache presence
        return NULL;
    } else {
        IpcacheStats.hits++;
        i->lastref = squid_curtime;
        // ignore i->error_message: the caller just checks IP cache presence
        return &i->addrs;
    }

    /* no entry [any more] */

    if ((addrs = ipcacheCheckNumeric(name))) {
        IpcacheStats.numeric_hits++;
        return addrs;
    }

    IpcacheStats.misses++;

    if (flags & IP_LOOKUP_IF_MISS)
        ipcache_nbgethostbyname(name, ipcacheHandleCnameRecurse, NULL);

    return NULL;
}