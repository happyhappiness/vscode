void
fqdnStats(StoreEntry * sentry)
{
    fqdncache_entry *f = NULL;
    int k;
    int ttl;

    if (fqdn_table == NULL)
        return;

    storeAppendPrintf(sentry, "FQDN Cache Statistics:\n");

    storeAppendPrintf(sentry, "FQDNcache Entries In Use: %d\n",
                      memInUse(MEM_FQDNCACHE_ENTRY));

    storeAppendPrintf(sentry, "FQDNcache Entries Cached: %d\n",
                      fqdncacheCount());

    storeAppendPrintf(sentry, "FQDNcache Requests: %d\n",
                      FqdncacheStats.requests);

    storeAppendPrintf(sentry, "FQDNcache Hits: %d\n",
                      FqdncacheStats.hits);

    storeAppendPrintf(sentry, "FQDNcache Negative Hits: %d\n",
                      FqdncacheStats.negative_hits);

    storeAppendPrintf(sentry, "FQDNcache Misses: %d\n",
                      FqdncacheStats.misses);

    storeAppendPrintf(sentry, "FQDN Cache Contents:\n\n");

    storeAppendPrintf(sentry, "%-45.45s %3s %3s %3s %s\n",
                      "Address", "Flg", "TTL", "Cnt", "Hostnames");

    hash_first(fqdn_table);

    while ((f = (fqdncache_entry *) hash_next(fqdn_table))) {
        ttl = (f->flags.fromhosts ? -1 : (f->expires - squid_curtime));
        storeAppendPrintf(sentry, "%-45.45s  %c%c %3.3d % 3d",
                          hashKeyStr(&f->hash),
                          f->flags.negcached ? 'N' : ' ',
                          f->flags.fromhosts ? 'H' : ' ',
                          ttl,
                          (int) f->name_count);

        for (k = 0; k < (int) f->name_count; ++k)
            storeAppendPrintf(sentry, " %s", f->names[k]);

        storeAppendPrintf(sentry, "\n");
    }
}