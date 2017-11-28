        storeAppendPrintf(sentry, " connection-auth=off");
    else if (p->connection_auth == 1)
        storeAppendPrintf(sentry, " connection-auth=on");
    else if (p->connection_auth == 2)
        storeAppendPrintf(sentry, " connection-auth=auto");

    p->secure.dumpCfg(sentry,"tls-");
    storeAppendPrintf(sentry, "\n");
}

static void
dump_peers(StoreEntry * sentry, CachePeer * peers)
{
    char ntoabuf[MAX_IPSTRLEN];
    int i;

    if (peers == NULL)
        storeAppendPrintf(sentry, "There are no neighbors installed.\n");

    for (CachePeer *e = peers; e; e = e->next) {
        assert(e->host != NULL);
        storeAppendPrintf(sentry, "\n%-11.11s: %s\n",
                          neighborTypeStr(e),
                          e->name);
        storeAppendPrintf(sentry, "Host       : %s/%d/%d\n",
                          e->host,
