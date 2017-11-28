static void
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

    storeAppendPrintf(sentry, " %-32.32s %c%c %6d %6d %2d(%2d)",
                      hashKeyStr(&i->hash),
                      i->flags.fromhosts ? 'H' : ' ',
                      i->flags.negcached ? 'N' : ' ',
                      (int) (squid_curtime - i->lastref),
                      (int) ((i->flags.fromhosts ? -1 : i->expires - squid_curtime)),
                      (int) i->addrs.count,
                      (int) i->addrs.badcount);

    /** \par
     * Negative-cached entries have no IPs listed. */
    if (i->flags.negcached) {
        storeAppendPrintf(sentry, "\n");
        return;
    }

    /** \par
     * Cached entries have IPs listed with a BNF of:   ip-address '-' ('OK'|'BAD') */
    for (k = 0; k < count; ++k) {
        /* Display tidy-up: IPv6 are so big make the list vertical */
        if (k == 0)
            storeAppendPrintf(sentry, " %45.45s-%3s\n",
                              i->addrs.in_addrs[k].toStr(buf,MAX_IPSTRLEN),
                              i->addrs.bad_mask[k] ? "BAD" : "OK ");
        else
            storeAppendPrintf(sentry, "%s %45.45s-%3s\n",
                              "                                                         ", /* blank-space indenting IP list */
                              i->addrs.in_addrs[k].toStr(buf,MAX_IPSTRLEN),
                              i->addrs.bad_mask[k] ? "BAD" : "OK ");
    }
}