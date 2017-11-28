static void
fqdncacheCallback(fqdncache_entry * f, int wait)
{
    FQDNH *callback;
    void *cbdata;
    f->lastref = squid_curtime;

    if (!f->handler)
        return;

    fqdncacheLockEntry(f);

    callback = f->handler;

    f->handler = NULL;

    if (cbdataReferenceValidDone(f->handlerData, &cbdata)) {
        const DnsLookupDetails details(f->error_message, wait);
        callback(f->name_count ? f->names[0] : NULL, details, cbdata);
    }

    fqdncacheUnlockEntry(f);
}