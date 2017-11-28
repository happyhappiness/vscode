    return result;
}

static void
dump_peer(StoreEntry * entry, const char *name, CachePeer * p)
{
    CachePeerDomainList *d;
    NeighborTypeDomainList *t;
    LOCAL_ARRAY(char, xname, 128);

    while (p != NULL) {
        storeAppendPrintf(entry, "%s %s %s %d %d name=%s",
                          name,
