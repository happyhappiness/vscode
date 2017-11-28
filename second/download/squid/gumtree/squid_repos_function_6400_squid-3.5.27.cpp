static void
netdbSaveState(void *foo)
{
    if (strcmp(Config.netdbFilename, "none") == 0)
        return;

    Logfile *lf;
    netdbEntry *n;
    net_db_name *x;

    struct timeval start = current_time;
    int count = 0;
    /*
     * This was nicer when we were using stdio, but thanks to
     * Solaris bugs, its a bad idea.  fopen can fail if more than
     * 256 FDs are open.
     */
    /*
     * unlink() is here because there is currently no way to make
     * logfileOpen() use O_TRUNC.
     */
    unlink(Config.netdbFilename);
    lf = logfileOpen(Config.netdbFilename, 4096, 0);

    if (NULL == lf) {
        debugs(50, DBG_IMPORTANT, "netdbSaveState: " << Config.netdbFilename << ": " << xstrerror());
        return;
    }

    hash_first(addr_table);

    while ((n = (netdbEntry *) hash_next(addr_table))) {
        if (n->pings_recv == 0)
            continue;

        logfilePrintf(lf, "%s %d %d %10.5f %10.5f %d %d",
                      n->network,
                      n->pings_sent,
                      n->pings_recv,
                      n->hops,
                      n->rtt,
                      (int) n->next_ping_time,
                      (int) n->last_use_time);

        for (x = n->hosts; x; x = x->next)
            logfilePrintf(lf, " %s", hashKeyStr(&x->hash));

        logfilePrintf(lf, "\n");

        ++count;

#undef RBUF_SZ

    }

    logfileClose(lf);
    getCurrentTime();
    debugs(38, DBG_IMPORTANT, "NETDB state saved; " <<
           count << " entries, " <<
           tvSubMsec(start, current_time) << " msec" );
    eventAddIsh("netdbSaveState", netdbSaveState, NULL, 3600.0, 1);
}