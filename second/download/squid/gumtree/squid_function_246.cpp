void
dump_peer_options(StoreEntry * sentry, peer * p)
{
    if (p->options.proxy_only)
        storeAppendPrintf(sentry, " proxy-only");

    if (p->options.no_query)
        storeAppendPrintf(sentry, " no-query");

    if (p->options.background_ping)
        storeAppendPrintf(sentry, " background-ping");

    if (p->options.no_digest)
        storeAppendPrintf(sentry, " no-digest");

    if (p->options.default_parent)
        storeAppendPrintf(sentry, " default");

    if (p->options.roundrobin)
        storeAppendPrintf(sentry, " round-robin");

    if (p->options.carp)
        storeAppendPrintf(sentry, " carp");

    if (p->options.userhash)
        storeAppendPrintf(sentry, " userhash");

    if (p->options.sourcehash)
        storeAppendPrintf(sentry, " sourcehash");

    if (p->options.weighted_roundrobin)
        storeAppendPrintf(sentry, " weighted-round-robin");

    if (p->options.mcast_responder)
        storeAppendPrintf(sentry, " multicast-responder");

#if PEER_MULTICAST_SIBLINGS
    if (p->options.mcast_siblings)
        storeAppendPrintf(sentry, " multicast-siblings");
#endif

    if (p->weight != 1)
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
        storeAppendPrintf(sentry, " ttl=%d", p->mcast.ttl);

    if (p->connect_timeout > 0)
        storeAppendPrintf(sentry, " connect-timeout=%d", (int) p->connect_timeout);

    if (p->connect_fail_limit != PEER_TCP_MAGIC_COUNT)
        storeAppendPrintf(sentry, " connect-fail-limit=%d", p->connect_fail_limit);

#if USE_CACHE_DIGESTS

    if (p->digest_url)
        storeAppendPrintf(sentry, " digest-url=%s", p->digest_url);

#endif

    if (p->options.allow_miss)
        storeAppendPrintf(sentry, " allow-miss");

    if (p->options.no_tproxy)
        storeAppendPrintf(sentry, " no-tproxy");

    if (p->max_conn > 0)
        storeAppendPrintf(sentry, " max-conn=%d", p->max_conn);

    if (p->options.originserver)
        storeAppendPrintf(sentry, " originserver");

    if (p->domain)
        storeAppendPrintf(sentry, " forceddomain=%s", p->domain);

    if (p->connection_auth == 0)
        storeAppendPrintf(sentry, " connection-auth=off");
    else if (p->connection_auth == 1)
        storeAppendPrintf(sentry, " connection-auth=on");
    else if (p->connection_auth == 2)
        storeAppendPrintf(sentry, " connection-auth=auto");

    storeAppendPrintf(sentry, "\n");
}