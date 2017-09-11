void databasesCron(void) {
    /* Expire keys by random sampling. Not required for slaves
     * as master will synthesize DELs for us. */
    if (server.active_expire_enabled && server.masterhost == NULL) {
        long long totalex = server.stat_expiredkeys;
        activeExpireCycle(0);
        if (server.stat_expiredkeys - totalex)
            printf("EXPIRED SLOW: %lld\n", server.stat_expiredkeys - totalex);
    }

    /* Perform hash tables rehashing if needed, but only if there are no
     * other processes saving the DB on disk. Otherwise rehashing is bad
