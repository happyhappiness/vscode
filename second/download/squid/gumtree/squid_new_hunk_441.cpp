        storeAppendPrintf(sentry, " connection-auth=auto");

    storeAppendPrintf(sentry, "\n");
}

static void
dump_peers(StoreEntry * sentry, CachePeer * peers)
{
    CachePeer *e = NULL;
    char ntoabuf[MAX_IPSTRLEN];
    CachePeerDomainList *d = NULL;
    icp_opcode op;
    int i;

    if (peers == NULL)
        storeAppendPrintf(sentry, "There are no neighbors installed.\n");

