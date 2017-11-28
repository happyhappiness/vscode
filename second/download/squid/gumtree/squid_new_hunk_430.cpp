ipcacheStatPrint(ipcache_entry * i, StoreEntry * sentry)
{
    int k;
    char buf[MAX_IPSTRLEN];

    if (!sentry) {
        debugs(14, DBG_CRITICAL, HERE << "CRITICAL: sentry is NULL!");
        return;
    }

    if (!i) {
        debugs(14, DBG_CRITICAL, HERE << "CRITICAL: ipcache_entry is NULL!");
        storeAppendPrintf(sentry, "CRITICAL ERROR\n");
        return;
    }

    int count = i->addrs.count;

