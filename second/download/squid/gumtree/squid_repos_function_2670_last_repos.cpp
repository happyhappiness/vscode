void
fqdncache_nbgethostbyaddr(const Ip::Address &addr, FQDNH * handler, void *handlerData)
{
    fqdncache_entry *f = NULL;
    char name[MAX_IPSTRLEN];
    generic_cbdata *c;
    addr.toStr(name,MAX_IPSTRLEN);
    debugs(35, 4, "fqdncache_nbgethostbyaddr: Name '" << name << "'.");
    ++FqdncacheStats.requests;

    if (name[0] == '\0') {
        debugs(35, 4, "fqdncache_nbgethostbyaddr: Invalid name!");
        const Dns::LookupDetails details("Invalid hostname", -1); // error, no lookup
        if (handler)
            handler(NULL, details, handlerData);
        return;
    }

    f = fqdncache_get(name);

    if (NULL == f) {
        /* miss */
        (void) 0;
    } else if (fqdncacheExpiredEntry(f)) {
        /* hit, but expired -- bummer */
        fqdncacheRelease(f);
        f = NULL;
    } else {
        /* hit */
        debugs(35, 4, "fqdncache_nbgethostbyaddr: HIT for '" << name << "'");

        if (f->flags.negcached)
            ++ FqdncacheStats.negative_hits;
        else
            ++ FqdncacheStats.hits;

        f->handler = handler;

        f->handlerData = cbdataReference(handlerData);

        fqdncacheCallback(f, -1); // no lookup

        return;
    }

    debugs(35, 5, "fqdncache_nbgethostbyaddr: MISS for '" << name << "'");
    ++ FqdncacheStats.misses;
    f = new fqdncache_entry(name);
    f->handler = handler;
    f->handlerData = cbdataReference(handlerData);
    f->request_time = current_time;
    c = new generic_cbdata(f);
    idnsPTRLookup(addr, fqdncacheHandleReply, c);
}