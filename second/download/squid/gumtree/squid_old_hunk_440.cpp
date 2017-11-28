neighborDumpNonPeers(StoreEntry * sentry)
{
    dump_peers(sentry, non_peers);
}

void
dump_peer_options(StoreEntry * sentry, peer * p)
{
    if (p->options.proxy_only)
        storeAppendPrintf(sentry, " proxy-only");

    if (p->options.no_query)
        storeAppendPrintf(sentry, " no-query");
