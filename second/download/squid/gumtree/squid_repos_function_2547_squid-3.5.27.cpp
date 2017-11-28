void
ipcache_nbgethostbyname(const char *name, IPH * handler, void *handlerData)
{
    ipcache_entry *i = NULL;
    const ipcache_addrs *addrs = NULL;
    generic_cbdata *c;
    debugs(14, 4, "ipcache_nbgethostbyname: Name '" << name << "'.");
    ++IpcacheStats.requests;

    if (name == NULL || name[0] == '\0') {
        debugs(14, 4, "ipcache_nbgethostbyname: Invalid name!");
        ++IpcacheStats.invalid;
        const DnsLookupDetails details("Invalid hostname", -1); // error, no lookup
        if (handler)
            handler(NULL, details, handlerData);
        return;
    }

    if ((addrs = ipcacheCheckNumeric(name))) {
        debugs(14, 4, "ipcache_nbgethostbyname: BYPASS for '" << name << "' (already numeric)");
        ++IpcacheStats.numeric_hits;
        const DnsLookupDetails details(NULL, -1); // no error, no lookup
        if (handler)
            handler(addrs, details, handlerData);
        return;
    }

    i = ipcache_get(name);

    if (NULL == i) {
        /* miss */
        (void) 0;
    } else if (ipcacheExpiredEntry(i)) {
        /* hit, but expired -- bummer */
        ipcacheRelease(i);
        i = NULL;
    } else {
        /* hit */
        debugs(14, 4, "ipcache_nbgethostbyname: HIT for '" << name << "'");

        if (i->flags.negcached)
            ++IpcacheStats.negative_hits;
        else
            ++IpcacheStats.hits;

        i->handler = handler;

        i->handlerData = cbdataReference(handlerData);

        ipcacheCallback(i, -1); // no lookup

        return;
    }

    debugs(14, 5, "ipcache_nbgethostbyname: MISS for '" << name << "'");
    ++IpcacheStats.misses;
    i = ipcacheCreateEntry(name);
    i->handler = handler;
    i->handlerData = cbdataReference(handlerData);
    i->request_time = current_time;
    c = new generic_cbdata(i);
    idnsALookup(hashKeyStr(&i->hash), ipcacheHandleReply, c);
}