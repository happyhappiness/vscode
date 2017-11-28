stat_ipcache_get(StoreEntry * sentry)
{
    dlink_node *m;
    assert(ip_table != NULL);
    storeAppendPrintf(sentry, "IP Cache Statistics:\n");
    storeAppendPrintf(sentry, "IPcache Entries In Use:  %d\n",
                      ipcache_entry::UseCount());
    storeAppendPrintf(sentry, "IPcache Entries Cached:  %d\n",
                      ipcacheCount());
    storeAppendPrintf(sentry, "IPcache Requests: %d\n",
                      IpcacheStats.requests);
    storeAppendPrintf(sentry, "IPcache Hits:            %d\n",
                      IpcacheStats.hits);
