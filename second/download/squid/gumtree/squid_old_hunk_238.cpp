        storeAppendPrintf(sentry, " weight=%d", p->weight);

    if (p->options.closest_only)
        storeAppendPrintf(sentry, " closest-only");

#if USE_HTCP
    if (p->options.htcp)
        storeAppendPrintf(sentry, " htcp");
    if (p->options.htcp_oldsquid)
        storeAppendPrintf(sentry, " htcp-oldsquid");
    if (p->options.htcp_no_clr)
        storeAppendPrintf(sentry, " htcp-no-clr");
    if (p->options.htcp_no_purge_clr)
        storeAppendPrintf(sentry, " htcp-no-purge-clr");
    if (p->options.htcp_only_clr)
        storeAppendPrintf(sentry, " htcp-only-clr");
#endif

    if (p->options.no_netdb_exchange)
        storeAppendPrintf(sentry, " no-netdb-exchange");

#if DELAY_POOLS

    if (p->options.no_delay)
        storeAppendPrintf(sentry, " no-delay");

#endif

    if (p->login)
        storeAppendPrintf(sentry, " login=%s", p->login);

    if (p->mcast.ttl > 0)
