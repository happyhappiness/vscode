        storeAppendPrintf(sentry, " connection-auth=auto");

    storeAppendPrintf(sentry, "\n");
}

static void
dump_peers(StoreEntry * sentry, peer * peers)
{
    peer *e = NULL;
    char ntoabuf[MAX_IPSTRLEN];
    struct _domain_ping *d = NULL;
    icp_opcode op;
    int i;

    if (peers == NULL)
        storeAppendPrintf(sentry, "There are no neighbors installed.\n");

