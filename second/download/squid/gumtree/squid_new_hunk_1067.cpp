    if (fqdn_table == NULL)
        return;

    storeAppendPrintf(sentry, "FQDN Cache Statistics:\n");

    storeAppendPrintf(sentry, "FQDNcache Entries In Use: %d\n",
                      fqdncache_entry::UseCount());

    storeAppendPrintf(sentry, "FQDNcache Entries Cached: %d\n",
                      fqdncacheCount());

    storeAppendPrintf(sentry, "FQDNcache Requests: %d\n",
                      FqdncacheStats.requests);
