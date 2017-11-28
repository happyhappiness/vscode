const char *
fqdncache_gethostbyaddr(IpAddress &addr, int flags)
{
    char name[MAX_IPSTRLEN];
    fqdncache_entry *f = NULL;

    if (addr.IsAnyAddr() || addr.IsNoAddr()) {
        return NULL;
    }

    addr.NtoA(name,MAX_IPSTRLEN);
    FqdncacheStats.requests++;
    f = fqdncache_get(name);

    if (NULL == f) {
        (void) 0;
    } else if (fqdncacheExpiredEntry(f)) {
        fqdncacheRelease(f);
        f = NULL;
    } else if (f->flags.negcached) {
        FqdncacheStats.negative_hits++;
        // ignore f->error_message: the caller just checks FQDN cache presence
        return NULL;
    } else {
        FqdncacheStats.hits++;
        f->lastref = squid_curtime;
        // ignore f->error_message: the caller just checks FQDN cache presence
        return f->names[0];
    }

    /* no entry [any more] */

    FqdncacheStats.misses++;

    if (flags & FQDN_LOOKUP_IF_MISS) {
        fqdncache_nbgethostbyaddr(addr, dummy_handler, NULL);
    }

    return NULL;
}