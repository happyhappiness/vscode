        storeAppendPrintf(sentry, " weight=%d", p->weight);

    if (p->options.closest_only)
        storeAppendPrintf(sentry, " closest-only");

#if USE_HTCP
    if (p->options.htcp) {
        storeAppendPrintf(sentry, " htcp");
        if (p->options.htcp_oldsquid || p->options.htcp_no_clr || p->options.htcp_no_purge_clr || p->options.htcp_only_clr) {
            int doneopts=0;
            if (p->options.htcp_oldsquid)
                storeAppendPrintf(sentry, "%soldsquid",(doneopts++>0?",":"="));
            if (p->options.htcp_no_clr)
                storeAppendPrintf(sentry, "%sno-clr",(doneopts++>0?",":"="));
            if (p->options.htcp_no_purge_clr)
                storeAppendPrintf(sentry, "%sno-purge-clr",(doneopts++>0?",":"="));
            if (p->options.htcp_only_clr)
                storeAppendPrintf(sentry, "%sonly-clr",(doneopts++>0?",":"="));
        }
    }
#endif

    if (p->options.no_netdb_exchange)
        storeAppendPrintf(sentry, " no-netdb-exchange");

#if USE_DELAY_POOLS
    if (p->options.no_delay)
        storeAppendPrintf(sentry, " no-delay");
#endif

    if (p->login)
        storeAppendPrintf(sentry, " login=%s", p->login);

    if (p->mcast.ttl > 0)
