void
stat_ipcache_get(StoreEntry * sentry)
{
    dlink_node *m;
    assert(ip_table != NULL);
    storeAppendPrintf(sentry, "IP Cache Statistics:\n");
    storeAppendPrintf(sentry, "IPcache Entries In Use:  %d\n",
                      memInUse(MEM_IPCACHE_ENTRY));
    storeAppendPrintf(sentry, "IPcache Entries Cached:  %d\n",
                      ipcacheCount());
    storeAppendPrintf(sentry, "IPcache Requests: %d\n",
                      IpcacheStats.requests);
    storeAppendPrintf(sentry, "IPcache Hits:            %d\n",
                      IpcacheStats.hits);
    storeAppendPrintf(sentry, "IPcache Negative Hits:       %d\n",
                      IpcacheStats.negative_hits);
    storeAppendPrintf(sentry, "IPcache Numeric Hits:        %d\n",
                      IpcacheStats.numeric_hits);
    storeAppendPrintf(sentry, "IPcache Misses:          %d\n",
                      IpcacheStats.misses);
    storeAppendPrintf(sentry, "IPcache Retrieved A:     %d\n",
                      IpcacheStats.rr_a);
    storeAppendPrintf(sentry, "IPcache Retrieved AAAA:  %d\n",
                      IpcacheStats.rr_aaaa);
    storeAppendPrintf(sentry, "IPcache Retrieved CNAME: %d\n",
                      IpcacheStats.rr_cname);
    storeAppendPrintf(sentry, "IPcache CNAME-Only Response: %d\n",
                      IpcacheStats.cname_only);
    storeAppendPrintf(sentry, "IPcache Invalid Request: %d\n",
                      IpcacheStats.invalid);
    storeAppendPrintf(sentry, "\n\n");
    storeAppendPrintf(sentry, "IP Cache Contents:\n\n");
    storeAppendPrintf(sentry, " %-31.31s %3s %6s %6s  %4s\n",
                      "Hostname",
                      "Flg",
                      "lstref",
                      "TTL",
                      "N(b)");

    for (m = lru_list.head; m; m = m->next) {
        assert( m->next != m );
        ipcacheStatPrint((ipcache_entry *)m->data, sentry);
    }
}