static void
ipcacheCallback(ipcache_entry *i, int wait)
{
    IPH *callback = i->handler;
    void *cbdata = NULL;
    i->lastref = squid_curtime;

    if (!i->handler)
        return;

    ipcacheLockEntry(i);

    callback = i->handler;

    i->handler = NULL;

    if (cbdataReferenceValidDone(i->handlerData, &cbdata)) {
        const Dns::LookupDetails details(i->error_message, wait);
        callback((i->addrs.count ? &i->addrs : NULL), details, cbdata);
    }

    ipcacheUnlockEntry(i);
}