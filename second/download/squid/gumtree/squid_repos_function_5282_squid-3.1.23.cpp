void
netdbDump(StoreEntry * sentry)
{
#if USE_ICMP
    netdbEntry *n;
    netdbEntry **list;
    net_db_name *x;
    int k;
    int i;
    int j;
    net_db_peer *p;
    storeAppendPrintf(sentry, "Network DB Statistics:\n");
    storeAppendPrintf(sentry, "%-46.46s %9s %7s %5s %s\n",  /* Max between 16 (IPv4) or 46 (IPv6)   */
                      "Network",
                      "recv/sent",
                      "RTT",
                      "Hops",
                      "Hostnames");
    list = (netdbEntry **)xcalloc(memInUse(MEM_NETDBENTRY), sizeof(netdbEntry *));
    i = 0;
    hash_first(addr_table);

    while ((n = (netdbEntry *) hash_next(addr_table)))
        *(list + i++) = n;

    if (i != memInUse(MEM_NETDBENTRY))
        debugs(38, 0, "WARNING: netdb_addrs count off, found " << i <<
               ", expected " << memInUse(MEM_NETDBENTRY));

    qsort((char *) list,
          i,
          sizeof(netdbEntry *),
          sortByRtt);

    for (k = 0; k < i; k++) {
        n = *(list + k);
        storeAppendPrintf(sentry, "%-46.46s %4d/%4d %7.1f %5.1f", /* Max between 16 (IPv4) or 46 (IPv6)   */
                          n->network,
                          n->pings_recv,
                          n->pings_sent,
                          n->rtt,
                          n->hops);

        for (x = n->hosts; x; x = x->next)
            storeAppendPrintf(sentry, " %s", hashKeyStr(&x->hash));

        storeAppendPrintf(sentry, "\n");

        p = n->peers;

        for (j = 0; j < n->n_peers; j++, p++) {
            storeAppendPrintf(sentry, "    %-22.22s %7.1f %5.1f\n",
                              p->peername,
                              p->rtt,
                              p->hops);
        }
    }

    xfree(list);
#else

    storeAppendPrintf(sentry,"NETDB support not compiled into this Squid cache.\n");
#endif
}